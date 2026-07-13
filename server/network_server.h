#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include <QByteArray>
#include <QDateTime>
#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

struct ClientInfo
{
    int id;
    QTcpSocket *socket;
    QString ip;
    quint16 port;
    bool is_running;
};

class NetworkServer : public QObject
{
    Q_OBJECT

public:
    explicit NetworkServer(QObject *parent = nullptr);
    ~NetworkServer() override;

    bool start(quint16 port);

    void stop();

    Q_INVOKABLE void startAllClients();

    Q_INVOKABLE void stopAllClients();

    Q_INVOKABLE void setThresholds(double critical_bandwidth,
                                   double critical_latency,
                                   double critical_packet_loss,
                                   int critical_cpu_usage,
                                   int critical_memory_usage);

signals:
    void clientConnected(int client_id, const QString &ip, quint16 port);

    void clientDisconnected(int client_id);

    void dataReceived(int client_id,
                      const QString &data_type,
                      const QString &content,
                      const QDateTime &time);

    void logMessage(const QString &message);

    void serverStateChanged(bool is_running);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    void processJson(int client_id, const QJsonObject &json);
    void sendJsonToClient(int client_id, const QJsonObject &json);
    void handleNetworkMetrics(int client_id, const QJsonObject &json);
    void handleDeviceStatus(int client_id, const QJsonObject &json);
    void handleLog(int client_id, const QJsonObject &json);
    void extracted(int &client_id, QStringList &warnings);
    void checkNetworkThresholds(int client_id, const QJsonObject &json);
    void checkDeviceThresholds(int client_id, const QJsonObject &json);

    QTcpServer *tcp_server_ = nullptr;
    QMap<int, ClientInfo> clients_;
    QMap<int, QByteArray> read_buffers_;
    int next_client_id_ = 1;

    double critical_bandwidth_ = 10.0;
    double critical_latency_ = 100.0;
    double critical_packet_loss_ = 5.0;
    int critical_cpu_usage_ = 90;
    int critical_memory_usage_ = 90;

    bool is_running_ = false;
};

#endif