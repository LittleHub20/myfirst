#ifndef NETACTUATOR_H
#define NETACTUATOR_H

#include <QDialog>
#include "tcpclient.h"

namespace Ui {
class NetActuator;
}

class NetActuator : public QDialog
{
    Q_OBJECT
public:
    int m_nPort;
    QString m_strServer;
    QString m_strPrefix;
    SocketHandler* m_pSocket;

public:
    explicit NetActuator(QWidget *parent = 0);
    ~NetActuator();

    bool isConnected();
    void sendCommand(QString cmd);

protected:
    void enableControls(bool bConnected);

private slots:
    void on_btnConnect_clicked();
    void on_btnHide_clicked();
    void on_btnSend_clicked();

    void onConnected();
    void onDisconnected();
    void onReceived(IOBuffer* buff);

private:
    Ui::NetActuator *ui;
};

#endif // NETACTUATOR_H
