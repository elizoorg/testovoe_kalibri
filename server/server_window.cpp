#include "server_window.h"
#include "settings_dialog.h"

#include <QDateTime>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QScrollBar>
#include <QVBoxLayout>
#include <qtextobject.h>

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setupMenuBar();

    server_thread_ = new QThread(this);
    network_server_ = new NetworkServer();
    network_server_->moveToThread(server_thread_);

    connect(server_thread_, &QThread::finished, network_server_, &QObject::deleteLater);

    server_thread_->start();
    setupConnections();

    data_flush_timer_ = new QTimer(this);
    data_flush_timer_->setInterval(kDataFlushIntervalMs);
    data_flush_timer_->setSingleShot(false);
    connect(data_flush_timer_, &QTimer::timeout, this, &ServerWindow::flushDataBuffer);
    data_flush_timer_->start();

    log_flush_timer_ = new QTimer(this);
    log_flush_timer_->setInterval(kLogFlushIntervalMs);
    log_flush_timer_->setSingleShot(false);
    connect(log_flush_timer_, &QTimer::timeout, this, &ServerWindow::flushLogBuffer);
    log_flush_timer_->start();
}

ServerWindow::~ServerWindow()
{
    if (network_server_) {
        QMetaObject::invokeMethod(network_server_, "stop", Qt::QueuedConnection);
    }
    if (server_thread_) {
        server_thread_->quit();
        server_thread_->wait(3000);
    }
}

void ServerWindow::setupUi()
{
    setWindowTitle("Телекоммуникационный сервер — Управление устройствами");
    setMinimumSize(1100, 750);
    resize(1200, 800);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    auto *main_layout = new QVBoxLayout(central);
    main_layout->setSpacing(8);
    main_layout->setContentsMargins(10, 10, 10, 10);

    auto *control_layout = new QHBoxLayout();

    toggle_server_btn_ = new QPushButton("Запустить сервер", this);
    toggle_server_btn_->setMinimumWidth(180);
    toggle_server_btn_->setToolTip("Запуск / остановка прослушивания порта");

    start_clients_btn_ = new QPushButton("Старт клиентов", this);
    start_clients_btn_->setEnabled(false);
    start_clients_btn_->setMinimumWidth(150);

    stop_clients_btn_ = new QPushButton("Стоп клиентов", this);
    stop_clients_btn_->setEnabled(false);
    stop_clients_btn_->setMinimumWidth(150);

    settings_btn_ = new QPushButton("Настройки", this);
    settings_btn_->setMinimumWidth(120);

    status_label_ = new QLabel("Сервер остановлен", this);
    status_label_->setStyleSheet("font-weight: bold; color: #cc0000;");

    control_layout->addWidget(toggle_server_btn_);
    control_layout->addWidget(start_clients_btn_);
    control_layout->addWidget(stop_clients_btn_);
    control_layout->addWidget(settings_btn_);
    control_layout->addStretch();
    control_layout->addWidget(status_label_);

    main_layout->addLayout(control_layout);

    auto *clients_group = new QGroupBox("Подключённые клиенты", this);
    auto *clients_layout = new QVBoxLayout(clients_group);

    clients_table_ = new QTableWidget(this);
    clients_table_->setColumnCount(4);
    clients_table_->setHorizontalHeaderLabels({"ID клиента", "IP-адрес", "Порт", "Статус"});
    clients_table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    clients_table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    clients_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    clients_table_->setAlternatingRowColors(true);
    clients_table_->setMaximumHeight(200);

    clients_layout->addWidget(clients_table_);
    main_layout->addWidget(clients_group);

    auto *data_group = new QGroupBox("Данные от клиентов", this);
    auto *data_layout = new QVBoxLayout(data_group);

    data_table_ = new QTableWidget(this);
    data_table_->setColumnCount(4);
    data_table_->setHorizontalHeaderLabels({"ID клиента", "Тип данных", "Содержимое", "Время"});
    data_table_->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    data_table_->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    data_table_->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    data_table_->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    data_table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    data_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    data_table_->setAlternatingRowColors(true);

    data_layout->addWidget(data_table_);
    main_layout->addWidget(data_group, /*stretch=*/1);

    auto *log_group = new QGroupBox("Лог событий", this);
    auto *log_layout = new QVBoxLayout(log_group);

    log_edit_ = new QTextEdit(this);
    log_edit_->setReadOnly(true);
    log_edit_->setMaximumHeight(150);
    log_edit_->setFont(QFont("Consolas", 9));

    log_layout->addWidget(log_edit_);
    main_layout->addWidget(log_group);

    statusBar()->showMessage("Готов к работе");
}

void ServerWindow::setupMenuBar()
{
    auto *menu_bar = menuBar();

    auto *file_menu = menu_bar->addMenu("Файл");
    QAction *quit_action = file_menu->addAction("Выход");
    connect(quit_action, &QAction::triggered, this, &QMainWindow::close);

    auto *settings_menu = menu_bar->addMenu("Настройки");
    QAction *settings_action = settings_menu->addAction("Пороговые значения...");
    connect(settings_action, &QAction::triggered, this, &ServerWindow::onOpenSettings);
}

void ServerWindow::setupConnections()
{
    connect(toggle_server_btn_, &QPushButton::clicked, this, &ServerWindow::onToggleServer);
    connect(start_clients_btn_, &QPushButton::clicked, this, &ServerWindow::onStartClients);
    connect(stop_clients_btn_, &QPushButton::clicked, this, &ServerWindow::onStopClients);
    connect(settings_btn_, &QPushButton::clicked, this, &ServerWindow::onOpenSettings);

    connect(network_server_,
            &NetworkServer::clientConnected,
            this,
            &ServerWindow::onClientConnected,
            Qt::QueuedConnection);
    connect(network_server_,
            &NetworkServer::clientDisconnected,
            this,
            &ServerWindow::onClientDisconnected,
            Qt::QueuedConnection);
    connect(network_server_,
            &NetworkServer::dataReceived,
            this,
            &ServerWindow::onDataReceived,
            Qt::QueuedConnection);
    connect(network_server_,
            &NetworkServer::logMessage,
            this,
            &ServerWindow::onLogMessage,
            Qt::QueuedConnection);
    connect(network_server_,
            &NetworkServer::serverStateChanged,
            this,
            &ServerWindow::onServerStateChanged,
            Qt::QueuedConnection);
}

void ServerWindow::onToggleServer()
{
    if (!network_server_) {
        return;
    }

    bool result = false;
    QMetaObject::invokeMethod(
        network_server_,
        [this]() { return network_server_->start(kDefaultPort); },
        Qt::BlockingQueuedConnection,
        &result);

    if (!result) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Не удалось запустить сервер. "
                             "Возможно, порт уже занят.");
    }
}

void ServerWindow::onStartClients()
{
    if (network_server_) {
        QMetaObject::invokeMethod(network_server_, "startAllClients", Qt::QueuedConnection);
    }
}

void ServerWindow::onStopClients()
{
    if (network_server_) {
        QMetaObject::invokeMethod(network_server_, "stopAllClients", Qt::QueuedConnection);
    }
}

void ServerWindow::onOpenSettings()
{
    SettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        if (network_server_) {
            QMetaObject::invokeMethod(network_server_,
                                      "setThresholds",
                                      Qt::QueuedConnection,
                                      Q_ARG(double, dialog.criticalBandwidth()),
                                      Q_ARG(double, dialog.criticalLatency()),
                                      Q_ARG(double, dialog.criticalPacketLoss()),
                                      Q_ARG(int, dialog.criticalCpuUsage()),
                                      Q_ARG(int, dialog.criticalMemoryUsage()));
        }
    }
}

void ServerWindow::onClientConnected(int client_id, const QString &ip, quint16 port)
{
    updateClientRow(client_id, ip, port, "Подключён");
    statusBar()->showMessage(
        QString("Клиент #%1 подключён (%2:%3)").arg(client_id).arg(ip).arg(port));
}

void ServerWindow::onClientDisconnected(int client_id)
{
    for (int row = 0; row < clients_table_->rowCount(); ++row) {
        QTableWidgetItem *item = clients_table_->item(row, 0);
        if (item && item->text().toInt() == client_id) {
            clients_table_->item(row, 3)->setText("Отключён");
            clients_table_->item(row, 3)->setForeground(QColor(0xcc0000));

            QTimer::singleShot(3000, this, [this, client_id]() {
                for (int r = 0; r < clients_table_->rowCount(); ++r) {
                    QTableWidgetItem *id_item = clients_table_->item(r, 0);
                    if (id_item && id_item->text().toInt() == client_id) {
                        clients_table_->removeRow(r);
                        break;
                    }
                }
            });
            break;
        }
    }
    statusBar()->showMessage(QString("Клиент #%1 отключён").arg(client_id));
}

void ServerWindow::onDataReceived(int client_id,
                                  const QString &data_type,
                                  const QString &content,
                                  const QDateTime &time)
{
    data_buffer_.append({client_id, data_type, content, time});
}

void ServerWindow::onLogMessage(const QString &message)
{
    log_buffer_.append(message);
}

void ServerWindow::onServerStateChanged(bool is_running)
{
    if (is_running) {
        toggle_server_btn_->setText("Остановить сервер");
        status_label_->setText("Сервер запущен");
        status_label_->setStyleSheet("font-weight: bold; color: #009933;");
        start_clients_btn_->setEnabled(true);
        stop_clients_btn_->setEnabled(true);
        statusBar()->showMessage(QString("Сервер запущен на порту %1").arg(kDefaultPort));
    } else {
        toggle_server_btn_->setText("Запустить сервер");
        status_label_->setText("Сервер остановлен");
        status_label_->setStyleSheet("font-weight: bold; color: #cc0000;");
        start_clients_btn_->setEnabled(false);
        stop_clients_btn_->setEnabled(false);
        statusBar()->showMessage("Сервер остановлен");
    }
}

void ServerWindow::flushDataBuffer()
{
    if (data_buffer_.isEmpty()) {
        return;
    }

    data_table_->setUpdatesEnabled(false);

    int rows_to_add = data_buffer_.size();

    int current_rows = data_table_->rowCount();
    int max_rows = 500;
    if (current_rows + rows_to_add > max_rows) {
        int rows_to_remove = (current_rows + rows_to_add) - max_rows;
        for (int i = 0; i < rows_to_remove && data_table_->rowCount() > 0; ++i) {
            data_table_->removeRow(0);
        }
    }

    for (const auto &item : std::as_const(data_buffer_)) {
        int row = data_table_->rowCount();
        data_table_->insertRow(row);

        data_table_->setItem(row, 0, new QTableWidgetItem(QString::number(item.client_id)));
        data_table_->setItem(row, 1, new QTableWidgetItem(item.data_type));
        data_table_->setItem(row, 2, new QTableWidgetItem(item.content));
        data_table_->setItem(row, 3, new QTableWidgetItem(item.time.toString("HH:mm:ss.zzz")));

        QColor type_color;
        if (item.data_type == "NetworkMetrics") {
            type_color = QColor(0x0066cc);
        } else if (item.data_type == "DeviceStatus") {
            type_color = QColor(0x009933);
        } else if (item.data_type == "Log") {
            type_color = QColor(0x996600);
        }
        data_table_->item(row, 1)->setForeground(type_color);
    }

    data_buffer_.clear();
    data_table_->setUpdatesEnabled(true);
    data_table_->scrollToBottom();
}

void ServerWindow::flushLogBuffer()
{
    if (log_buffer_.isEmpty()) {
        return;
    }

    log_edit_->setUpdatesEnabled(false);

    QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss");
    for (const QString &msg : std::as_const(log_buffer_)) {
        log_edit_->append(QString("[%1] %2").arg(timestamp, msg));
    }
    log_buffer_.clear();

    if (log_edit_->document()->blockCount() > 1000) {
        QTextCursor cursor(log_edit_->document()->begin());
        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor, 200);
        cursor.removeSelectedText();
    }

    log_edit_->setUpdatesEnabled(true);

    QScrollBar *sb = log_edit_->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void ServerWindow::updateClientRow(int client_id,
                                   const QString &ip,
                                   quint16 port,
                                   const QString &status)
{
    for (int row = 0; row < clients_table_->rowCount(); ++row) {
        QTableWidgetItem *item = clients_table_->item(row, 0);
        if (item && item->text().toInt() == client_id) {
            clients_table_->item(row, 1)->setText(ip);
            clients_table_->item(row, 2)->setText(QString::number(port));
            clients_table_->item(row, 3)->setText(status);
            clients_table_->item(row, 3)->setForeground(QColor(0x009933));
            return;
        }
    }

    int row = clients_table_->rowCount();
    clients_table_->insertRow(row);

    auto *id_item = new QTableWidgetItem(QString::number(client_id));
    id_item->setTextAlignment(Qt::AlignCenter);
    clients_table_->setItem(row, 0, id_item);

    clients_table_->setItem(row, 1, new QTableWidgetItem(ip));

    auto *port_item = new QTableWidgetItem(QString::number(port));
    port_item->setTextAlignment(Qt::AlignCenter);
    clients_table_->setItem(row, 2, port_item);

    auto *status_item = new QTableWidgetItem(status);
    status_item->setForeground(QColor(0x009933));
    status_item->setTextAlignment(Qt::AlignCenter);
    clients_table_->setItem(row, 3, status_item);
}