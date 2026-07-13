#include <QCoreApplication>
#include <QDateTime>
#include <QStringList>
#include <QTextStream>
#include "device_client.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    QCoreApplication app(argc, argv);
    app.setApplicationName("QtTelecomClient");
    QTextStream out(stdout);

#ifdef Q_OS_WIN
    out.setEncoding(QStringConverter::System);
#else
#endif

    QString host = "127.0.0.1";
    quint16 port = 12345;

    const QStringList args = app.arguments();
    if (args.size() >= 2) {
        host = args.at(1);
    }
    if (args.size() >= 3) {
        bool ok = false;
        int parsed_port = args.at(2).toInt(&ok);
        if (ok && parsed_port > 0 && parsed_port <= 65535) {
            port = static_cast<quint16>(parsed_port);
        } else {
            out << "Предупреждение: некорректный порт, используется по умолчанию (12345)\n";
            out.flush();
        }
    }

    out << "=== Эмулятор устройства (клиент) ===\n";
    out << QString("Сервер: %1:%2\n").arg(host).arg(port);
    out << "Нажмите Ctrl+C для выхода.\n\n";
    out.flush();

    DeviceClient client;

    QObject::connect(&client, &DeviceClient::logMessage, &app, [&out](const QString &msg) {
        QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
        out << QString("[%1] %2\n").arg(timestamp, msg);
        out.flush();
    });

    client.connectToServer(host, port);

    return app.exec();
}