#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

#include <QtBluetooth/qbluetoothaddress.h>
#include <QtBluetooth/qbluetoothserviceinfo.h>

QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void startServer(const QBluetoothAddress &localAdapter = QBluetoothAddress());

public slots:
    void sendMessage(const QString &message);

signals:
    void clientConnected(const QString &name);
    void messageReceived(const QString &sender, const QString &message);
    void clientDisconnected(const QString &name);


private:
    QBluetoothServer *rfcommServer = nullptr;
    QBluetoothServiceInfo serviceInfo;
    QList<QBluetoothSocket *> clientSockets;
    QMap<QBluetoothSocket *, QString> clientNames;

private slots:
    void clientConnected();
    void readSocket();
    void clientDisconnected();


};

#endif // SERVER_H
