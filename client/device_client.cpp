#include "device_client.h"
#include <QDateTime>
#include <QJsonDocument>
#include <qjsonobject.h>

const QStringList DeviceClient::kShortLogTemplates = {
    "Interface eth0 restarted",
    "DNS query timeout",
    "ARP cache flushed",
    "Route updated",
    "DHCP lease renewed",
    "NTP sync completed",
    "Firewall rule added",
    "MTU adjusted to 1500",
    "Link detected on eth1",
    "Bonding mode active",
};

const QStringList DeviceClient::kMediumLogTemplates = {
    "Connection to upstream router 10.0.0.1 established, "
    "latency measured at %1 ms, jitter %2 ms, "
    "MOS score: %3",

    "Bandwidth utilization on interface eth0 reached %1%%, "
    "peak throughput: %2 Mbps, "
    "average packet size: %3 bytes",

    "SIP registration with proxy %1:%2 completed successfully, "
    "expires in %3 seconds, transport: UDP, "
    "contact header updated",

    "BGP session with neighbor %1 established, "
    "received %2 prefixes, sent %3 prefixes, "
    "hold time: %4 seconds",

    "SNMP trap sent to manager %1: "
    "interface %2 status changed to %3, "
    "ifOperStatus=%4, ifAdminStatus=%5",
};

const QStringList DeviceClient::kLongLogTemplates = {
    "Performing periodic health check on subsystem network-stack-v2: "
    "TCP retransmission rate is %1%% (threshold: 2%%), "
    "out-of-order packet ratio: %2%%, "
    "average RTT across 50 samples: %3 ms (stddev: %4 ms), "
    "active connections: %5 (established: %6, time_wait: %7), "
    "buffer utilization: %8%%, "
    "kernel socket queue depth: %9, "
    "memory pressure: %10 — action: %11",

    "Detailed traffic analysis report for interface %1: "
    "inbound traffic: %2 Mbps (packets: %3, errors: %4, drops: %5), "
    "outbound traffic: %6 Mbps (packets: %7, errors: %8, drops: %9), "
    "multicast traffic: %10 Mbps, "
    "broadcast traffic: %11 Mbps, "
    "top 5 protocols by volume: %12, "
    "top talkers: %13, "
    "recommendation: %14",

    "Auto-healing procedure triggered for link aggregation group %1: "
    "member port %2 went down (reason: %3), "
    "redistributing traffic across %4 remaining active ports, "
    "LACP state: %5, "
    "hash algorithm: %6, "
    "failover time: %7 ms, "
    "affected flows: approximately %8, "
    "CDF update sent to peers, "
    "port %9 selected as backup, "
    "estimated recovery time: %10 seconds",
};

const QStringList DeviceClient::kSeverityLevels = {"DEBUG", "INFO", "WARNING", "ERROR"};

DeviceClient::DeviceClient(QObject *parent)
    : QObject(parent)
    , socket_(new QTcpSocket(this))
    , reconnect_timer_(new QTimer(this))
    , data_timer_(new QTimer(this))
{
    // Таймер переподключения: 5 секунд
    reconnect_timer_->setInterval(5000);
    reconnect_timer_->setSingleShot(true);

    // Таймер отправки данных: 10–100 мс (случайная задержка)
    data_timer_->setSingleShot(true);

    // Подключение сигналов сокета
    connect(socket_, &QTcpSocket::connected, this, &DeviceClient::onConnected);
    connect(socket_, &QTcpSocket::disconnected, this, &DeviceClient::onDisconnected);
    connect(socket_, &QTcpSocket::readyRead, this, &DeviceClient::onReadyRead);
    connect(socket_, &QTcpSocket::errorOccurred, this, &DeviceClient::onErrorOccurred);

    connect(reconnect_timer_, &QTimer::timeout, this, [this]() { connectToServer(host_, port_); });

    connect(data_timer_, &QTimer::timeout, this, &DeviceClient::sendRandomData);
}

void DeviceClient::connectToServer(const QString &host, quint16 port)
{
    host_ = host;
    port_ = port;

    if (socket_->state() != QAbstractSocket::UnconnectedState) {
        socket_->disconnectFromHost();
        socket_->waitForDisconnected(1000);
    }

    emit logMessage(QString("[КЛИЕНТ] Попытка подключения к %1:%2...").arg(host_).arg(port));
    socket_->connectToHost(host_, port);
}

void DeviceClient::onConnected()
{
    is_connected_ = true;
    emit logMessage(QString("[КЛИЕНТ] Подключён к %1:%2").arg(host_).arg(port_));
}

void DeviceClient::onDisconnected()
{
    is_connected_ = false;
    is_started_ = false;
    data_timer_->stop();
    client_id_ = -1;

    emit logMessage("[КЛИЕНТ] Соединение разорвано. Переподключение через 5 сек...");
    scheduleReconnect();
}

void DeviceClient::onErrorOccurred(QAbstractSocket::SocketError socket_error)
{
    Q_UNUSED(socket_error)
    emit logMessage(QString("[КЛИЕНТ] Ошибка: %1").arg(socket_->errorString()));
}

void DeviceClient::onReadyRead()
{
    read_buffer_.append(socket_->readAll());

    while (true) {
        int newline_pos = read_buffer_.indexOf('\n');
        if (newline_pos == -1) {
            break;
        }

        QByteArray message_data = read_buffer_.left(newline_pos);
        read_buffer_.remove(0, newline_pos + 1);

        if (message_data.isEmpty()) {
            continue;
        }

        QJsonParseError parse_error;
        QJsonDocument doc = QJsonDocument::fromJson(message_data, &parse_error);
        if (parse_error.error != QJsonParseError::NoError || !doc.isObject()) {
            emit logMessage(QString("[КЛИЕНТ] Ошибка парсинга ответа сервера: %1")
                                .arg(parse_error.errorString()));
            continue;
        }

        processServerMessage(doc.object());
    }
}

void DeviceClient::processServerMessage(const QJsonObject &json)
{
    QString type = json.value("type").toString();

    if (type == "ConnectAck") {
        client_id_ = json.value("client_id").toInt(-1);
        QString status = json.value("status").toString("unknown");
        emit logMessage(QString("[КЛИЕНТ] Подтверждение подключения: ID=%1, статус=%2")
                            .arg(client_id_)
                            .arg(status));
    } else if (type == "StartCommand") {
        is_started_ = true;
        emit logMessage("[КЛИЕНТ] Получена команда Start. Начинаю отправку данных.");
        sendRandomData();
    } else if (type == "StopCommand") {
        is_started_ = false;
        data_timer_->stop();
        emit logMessage("[КЛИЕНТ] Получена команда Stop. Отправка данных приостановлена.");
    } else if (type == "Log") {
        QString message = json.value("message").toString();
        QString severity = json.value("severity").toString();
        emit logMessage(QString("[СЕРВЕР-LOG] [%1] %2").arg(severity, message));
    } else {
        emit logMessage(QString("[КЛИЕНТ] Неизвестный тип сообщения: %1").arg(type));
    }
}

void DeviceClient::sendRandomData()
{
    if (!is_connected_ || !is_started_) {
        return;
    }

    int type_roll = QRandomGenerator::global()->bounded(3);
    QJsonObject json;

    switch (type_roll) {
    case 0:
        json = generateNetworkMetrics();
        break;
    case 1:
        json = generateDeviceStatus();
        break;
    case 2:
        json = generateLog();
        break;
    default:
        json = generateLog();
        break;
    }

    sendJson(json);

    int delay_ms = QRandomGenerator::global()->bounded(10, 101);
    data_timer_->start(delay_ms);
}

QJsonObject DeviceClient::generateNetworkMetrics()
{
    QJsonObject json;
    json["type"] = "NetworkMetrics";
    json["bandwidth"] = QRandomGenerator::global()->generateDouble() * 200.0;  // 0–200 Мбит/с
    json["latency"] = QRandomGenerator::global()->generateDouble() * 150.0;    // 0–150 мс
    json["packet_loss"] = QRandomGenerator::global()->generateDouble() * 10.0; // 0–10%
    return json;
}

QJsonObject DeviceClient::generateDeviceStatus()
{
    QJsonObject json;
    json["type"] = "DeviceStatus";
    json["uptime"] = QRandomGenerator::global()->bounded(60, 864000);    // 1 мин — 10 дней
    json["cpu_usage"] = QRandomGenerator::global()->bounded(1, 101);     // 1–100%
    json["memory_usage"] = QRandomGenerator::global()->bounded(10, 101); // 10–100%
    return json;
}

QJsonObject DeviceClient::generateLog()
{
    QJsonObject json;
    json["type"] = "Log";

    int length_roll = QRandomGenerator::global()->bounded(100);

    if (length_roll < 40) {
        json["message"] = generateShortLog();
    } else if (length_roll < 80) {
        json["message"] = generateMediumLog();
    } else {
        json["message"] = generateLongLog();
    }

    json["severity"] = kSeverityLevels[QRandomGenerator::global()->bounded(kSeverityLevels.size())];
    return json;
}

QString DeviceClient::generateShortLog()
{
    return kShortLogTemplates[QRandomGenerator::global()->bounded(kShortLogTemplates.size())];
}

namespace {

int countPlaceholders(const QString &s)
{
    int count = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == QLatin1Char('%') && i + 1 < s.size() && s[i + 1].isDigit()) {
            ++count;
        }
    }
    return count;
}

} // namespace

QString DeviceClient::generateMediumLog()
{
    QString template_str
        = kMediumLogTemplates[QRandomGenerator::global()->bounded(kMediumLogTemplates.size())];
    int placeholders = countPlaceholders(template_str);
    for (int i = 0; i < placeholders; ++i) {
        template_str = template_str.arg(QRandomGenerator::global()->bounded(1, 1000));
    }
    return template_str;
}

QString DeviceClient::generateLongLog()
{
    QString template_str
        = kLongLogTemplates[QRandomGenerator::global()->bounded(kLongLogTemplates.size())];
    int placeholders = countPlaceholders(template_str);
    for (int i = 0; i < placeholders; ++i) {
        template_str = template_str.arg(QRandomGenerator::global()->bounded(1, 1000));
    }
    return template_str;
}
void DeviceClient::scheduleReconnect()
{
    if (!reconnect_timer_->isActive()) {
        reconnect_timer_->start();
    }
}

void DeviceClient::sendJson(const QJsonObject &json)
{
    if (socket_->state() != QAbstractSocket::ConnectedState) {
        return;
    }

    QJsonDocument doc(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact) + '\n';
    socket_->write(data);
    socket_->flush();
}