#include "network_server.h"
#include <QDataStream>
#include <QJsonDocument>

NetworkServer::NetworkServer(QObject *parent)
    : QObject(parent)
    , tcp_server_(new QTcpServer(this))
{
    connect(tcp_server_, &QTcpServer::newConnection, this, &NetworkServer::onNewConnection);
}

NetworkServer::~NetworkServer()
{
    stop();
}

bool NetworkServer::start(quint16 port)
{
    if (is_running_) {
        return true;
    }
    if (!tcp_server_->listen(QHostAddress::Any, port)) {
        emit logMessage(QString("[ОШИБКА] Не удалось запустить сервер на порту %1: %2")
                            .arg(port)
                            .arg(tcp_server_->errorString()));
        return false;
    }
    is_running_ = true;
    emit serverStateChanged(true);
    emit logMessage(QString("[СЕРВЕР] Запущен на порту %1").arg(port));
    return true;
}

void NetworkServer::stop()
{
    if (!is_running_) {
        return;
    }

    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        QTcpSocket *sock = it->socket;
        sock->disconnectFromHost();
        sock->deleteLater();
    }
    clients_.clear();
    read_buffers_.clear();

    tcp_server_->close();
    is_running_ = false;
    next_client_id_ = 1;
    emit serverStateChanged(false);
    emit logMessage("[СЕРВЕР] Остановлен");
}

void NetworkServer::startAllClients()
{
    QJsonObject cmd;
    cmd["type"] = "StartCommand";

    int started = 0;
    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        it->is_running = true;
        sendJsonToClient(it.key(), cmd);
        ++started;
    }
    emit logMessage(QString("[СЕРВЕР] Команда Start отправлена %1 клиентам").arg(started));
}

void NetworkServer::stopAllClients()
{
    QJsonObject cmd;
    cmd["type"] = "StopCommand";

    int stopped = 0;
    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        it->is_running = false;
        sendJsonToClient(it.key(), cmd);
        ++stopped;
    }
    emit logMessage(QString("[СЕРВЕР] Команда Stop отправлена %1 клиентам").arg(stopped));
}

void NetworkServer::setThresholds(double critical_bandwidth,
                                  double critical_latency,
                                  double critical_packet_loss,
                                  int critical_cpu_usage,
                                  int critical_memory_usage)
{
    critical_bandwidth_ = critical_bandwidth;
    critical_latency_ = critical_latency;
    critical_packet_loss_ = critical_packet_loss;
    critical_cpu_usage_ = critical_cpu_usage;
    critical_memory_usage_ = critical_memory_usage;
    emit logMessage("[СЕРВЕР] Пороговые значения обновлены");
}

void NetworkServer::onNewConnection()
{
    QTcpSocket *client_socket = tcp_server_->nextPendingConnection();
    if (!client_socket) {
        return;
    }

    int client_id = next_client_id_++;

    ClientInfo info;
    info.id = client_id;
    info.socket = client_socket;
    info.ip = client_socket->peerAddress().toString();
    info.port = client_socket->peerPort();
    info.is_running = false;

    clients_.insert(client_id, info);
    read_buffers_.insert(client_id, QByteArray());

    connect(client_socket, &QTcpSocket::readyRead, this, &NetworkServer::onReadyRead);
    connect(client_socket, &QTcpSocket::disconnected, this, &NetworkServer::onClientDisconnected);

    QJsonObject ack;
    ack["type"] = "ConnectAck";
    ack["client_id"] = client_id;
    ack["status"] = "connected";
    sendJsonToClient(client_id, ack);

    emit clientConnected(client_id, info.ip, info.port);
    emit logMessage(
        QString("[КЛИЕНТ] #%1 подключён (%2:%3)").arg(client_id).arg(info.ip).arg(info.port));
}

void NetworkServer::onClientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) {
        return;
    }

    int client_id = -1;
    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        if (it->socket == socket) {
            client_id = it.key();
            break;
        }
    }
    if (client_id == -1) {
        socket->deleteLater();
        return;
    }

    QString ip = clients_[client_id].ip;
    clients_.remove(client_id);
    read_buffers_.remove(client_id);
    socket->deleteLater();

    emit clientDisconnected(client_id);
    emit logMessage(QString("[КЛИЕНТ] #%1 отключён (%2)").arg(client_id).arg(ip));
}

void NetworkServer::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) {
        return;
    }

    // Определяем client_id
    int client_id = -1;
    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        if (it->socket == socket) {
            client_id = it.key();
            break;
        }
    }
    if (client_id == -1) {
        return;
    }

    read_buffers_[client_id].append(socket->readAll());
    while (true) {
        QByteArray &buffer = read_buffers_[client_id];
        int newline_pos = buffer.indexOf('\n');
        if (newline_pos == -1) {
            break;
        }

        QByteArray message_data = buffer.left(newline_pos);
        buffer.remove(0, newline_pos + 1);

        if (message_data.isEmpty()) {
            continue;
        }

        QJsonParseError parse_error;
        QJsonDocument doc = QJsonDocument::fromJson(message_data, &parse_error);
        if (parse_error.error != QJsonParseError::NoError || !doc.isObject()) {
            emit logMessage(QString("[ОШИБКА] Некорректный JSON от клиента #%1: %2")
                                .arg(client_id)
                                .arg(parse_error.errorString()));
            continue;
        }

        processJson(client_id, doc.object());
    }
}

void NetworkServer::processJson(int client_id, const QJsonObject &json)
{
    QString type = json.value("type").toString();

    if (type == "NetworkMetrics") {
        handleNetworkMetrics(client_id, json);
    } else if (type == "DeviceStatus") {
        handleDeviceStatus(client_id, json);
    } else if (type == "Log") {
        handleLog(client_id, json);
    } else {
        emit logMessage(
            QString("[ПРЕДУПРЕЖДЕНИЕ] Неизвестный тип данных от #%1: %2").arg(client_id).arg(type));
    }
}

void NetworkServer::handleNetworkMetrics(int client_id, const QJsonObject &json)
{
    double bandwidth = json.value("bandwidth").toDouble(0.0);
    double latency = json.value("latency").toDouble(0.0);
    double packet_loss = json.value("packet_loss").toDouble(0.0);

    QString content = QString("BW: %1 Мбит/с | Задержка: %2 мс | Потери: %3%")
                          .arg(bandwidth, 0, 'f', 2)
                          .arg(latency, 0, 'f', 2)
                          .arg(packet_loss, 0, 'f', 3);

    emit dataReceived(client_id, "NetworkMetrics", content, QDateTime::currentDateTime());

    checkNetworkThresholds(client_id, json);
}

void NetworkServer::handleDeviceStatus(int client_id, const QJsonObject &json)
{
    int uptime = json.value("uptime").toInt(0);
    int cpu_usage = json.value("cpu_usage").toInt(0);
    int memory_usage = json.value("memory_usage").toInt(0);

    int hours = uptime / 3600;
    int minutes = (uptime % 3600) / 60;
    int seconds = uptime % 60;

    QString content = QString("Аптайм: %1ч %2м %3с | CPU: %4% | Память: %5%")
                          .arg(hours)
                          .arg(minutes)
                          .arg(seconds)
                          .arg(cpu_usage)
                          .arg(memory_usage);

    emit dataReceived(client_id, "DeviceStatus", content, QDateTime::currentDateTime());

    checkDeviceThresholds(client_id, json);
}

void NetworkServer::handleLog(int client_id, const QJsonObject &json)
{
    QString message = json.value("message").toString("—");
    QString severity = json.value("severity").toString("UNKNOWN");

    QString content = QString("[%1] %2").arg(severity, message);
    emit dataReceived(client_id, "Log", content, QDateTime::currentDateTime());
}

void NetworkServer::checkNetworkThresholds(int client_id, const QJsonObject &json)
{
    double bandwidth = json.value("bandwidth").toDouble(0.0);
    double latency = json.value("latency").toDouble(0.0);
    double packet_loss = json.value("packet_loss").toDouble(0.0);

    QStringList warnings;

    if (bandwidth < critical_bandwidth_) {
        warnings << QString("Полоса пропускания %1 Мбит/с ниже критического уровня %2 Мбит/с")
                        .arg(bandwidth, 0, 'f', 2)
                        .arg(critical_bandwidth_, 0, 'f', 2);
    }
    if (latency > critical_latency_) {
        warnings << QString("Задержка %1 мс превышает критический уровень %2 мс")
                        .arg(latency, 0, 'f', 2)
                        .arg(critical_latency_, 0, 'f', 2);
    }
    if (packet_loss > critical_packet_loss_) {
        warnings << QString("Потери пакетов %1% превышают критический уровень %2%")
                        .arg(packet_loss, 0, 'f', 3)
                        .arg(critical_packet_loss_, 0, 'f', 2);
    }

    for (const QString &warning : std::as_const(warnings)) {
        QJsonObject log_packet;
        log_packet["type"] = "Log";
        log_packet["message"]
            = QString("[СЕРВЕР-ПРЕДУПРЕЖДЕНИЕ] Клиент #%1: %2").arg(client_id).arg(warning);
        log_packet["severity"] = "WARNING";
        sendJsonToClient(client_id, log_packet);

        emit logMessage(QString("[ПРЕДУПРЕЖДЕНИЕ] Клиент #%1: %2").arg(client_id).arg(warning));
    }
}

void NetworkServer::checkDeviceThresholds(int client_id, const QJsonObject &json)
{
    int cpu_usage = json.value("cpu_usage").toInt(0);
    int memory_usage = json.value("memory_usage").toInt(0);

    QStringList warnings;

    if (cpu_usage > critical_cpu_usage_) {
        warnings << QString("Загрузка CPU %1% превышает критический уровень %2%")
                        .arg(cpu_usage)
                        .arg(critical_cpu_usage_);
    }
    if (memory_usage > critical_memory_usage_) {
        warnings << QString("Использование памяти %1% превышает критический уровень %2%")
                        .arg(memory_usage)
                        .arg(critical_memory_usage_);
    }

    for (const QString &warning : std::as_const(warnings)) {
        QJsonObject log_packet;
        log_packet["type"] = "Log";
        log_packet["message"]
            = QString("[СЕРВЕР-ПРЕДУПРЕЖДЕНИЕ] Клиент #%1: %2").arg(client_id).arg(warning);
        log_packet["severity"] = "WARNING";
        sendJsonToClient(client_id, log_packet);

        emit logMessage(QString("[ПРЕДУПРЕЖДЕНИЕ] Клиент #%1: %2").arg(client_id).arg(warning));
    }
}

void NetworkServer::sendJsonToClient(int client_id, const QJsonObject &json)
{
    if (!clients_.contains(client_id)) {
        return;
    }

    QTcpSocket *socket = clients_[client_id].socket;
    if (!socket || socket->state() != QAbstractSocket::ConnectedState) {
        return;
    }

    QJsonDocument doc(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact) + '\n';
    socket->write(data);
    socket->flush();
}