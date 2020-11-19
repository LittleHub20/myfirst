#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QThread>
#include <QTcpSocket>
#include "sockethandler.h"

class TCPClient : public SocketHandler
{
    Q_OBJECT
protected:
    QString m_strType = "TCP";
    IOBuffer m_Buffer;
    QTcpSocket* m_pSocket;

public:
    explicit TCPClient();
    QTcpSocket* getSocket() { return m_pSocket; }
    bool isConnected() {
        return (m_pSocket && (m_pSocket->state() == QAbstractSocket::ConnectedState));
    }

    void onConnect(const QString host, const long port);
    void onDisconnect();
    void onSend(const char *data, long len);
    void onSend(const char *data);
    void onSend(QByteArray data);
    void onSend(QString data);

public slots:
    // handling signals from QTcpSocket
    void onConnected();
    void onDisconnected();
    void onReceived();
    void onSent(qint64 bytes);
    void onError(QAbstractSocket::SocketError);
};

#endif // TCPCLIENT_H
