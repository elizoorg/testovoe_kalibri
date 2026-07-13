#ifndef DEVICE_CLIENT_H
#define DEVICE_CLIENT_H

#include <QByteArray>
#include <QObject>
#include <QRandomGenerator>
#include <QStringList>
#include <QTcpSocket>
#include <QTimer>

class DeviceClient : public QObject
{
    Q_OBJECT

public:
    explicit DeviceClient(QObject *parent = nullptr);

    void connectToServer(const QString &host = "127.0.0.1", quint16 port = 12345);

signals:
    void logMessage(const QString &message);

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError socket_error);
    void onReadyRead();
    void sendRandomData();

private:
    void scheduleReconnect();
    void processServerMessage(const QJsonObject &json);
    void sendJson(const QJsonObject &json);

    QJsonObject generateNetworkMetrics();
    QJsonObject generateDeviceStatus();
    QJsonObject generateLog();

    QString generateShortLog();
    QString generateMediumLog();
    QString generateLongLog();

    QTcpSocket *socket_ = nullptr;
    QTimer *reconnect_timer_ = nullptr;
    QTimer *data_timer_ = nullptr;

    QString host_;
    quint16 port_ = 12345;
    int client_id_ = -1;
    bool is_started_ = false;
    bool is_connected_ = false;

    QByteArray read_buffer_;

    static const QStringList kShortLogTemplates;
    static const QStringList kMediumLogTemplates;
    static const QStringList kLongLogTemplates;
    static const QStringList kSeverityLevels;
};

#endif