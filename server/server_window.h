#ifndef SERVER_WINDOW_H
#define SERVER_WINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTableWidget>
#include <QTextEdit>
#include <QThread>
#include <QTimer>
#include <QVector>

#include "network_server.h"

struct PendingDataRow
{
    int client_id;
    QString data_type;
    QString content;
    QDateTime time;
};

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow() override;

private slots:
    void onToggleServer();

    void onStartClients();

    void onStopClients();

    void onOpenSettings();

    void onClientConnected(int client_id, const QString &ip, quint16 port);
    void onClientDisconnected(int client_id);
    void onDataReceived(int client_id,
                        const QString &data_type,
                        const QString &content,
                        const QDateTime &time);
    void onLogMessage(const QString &message);
    void onServerStateChanged(bool is_running);

    void flushDataBuffer();
    void flushLogBuffer();

private:
    void setupUi();
    void setupMenuBar();
    void setupConnections();

    void updateClientRow(int client_id, const QString &ip, quint16 port, const QString &status);

    QThread *server_thread_ = nullptr;
    NetworkServer *network_server_ = nullptr;

    QTableWidget *clients_table_ = nullptr;
    QTableWidget *data_table_ = nullptr;
    QTextEdit *log_edit_ = nullptr;

    QPushButton *toggle_server_btn_ = nullptr;
    QPushButton *start_clients_btn_ = nullptr;
    QPushButton *stop_clients_btn_ = nullptr;
    QPushButton *settings_btn_ = nullptr;

    QLabel *status_label_ = nullptr;

    QVector<PendingDataRow> data_buffer_;
    QStringList log_buffer_;
    QTimer *data_flush_timer_ = nullptr;
    QTimer *log_flush_timer_ = nullptr;

    static constexpr quint16 kDefaultPort = 12345;
    static constexpr int kDataFlushIntervalMs = 200;
    static constexpr int kLogFlushIntervalMs = 300;
};

#endif