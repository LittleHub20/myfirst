#ifndef NETPRESENTER_H
#define NETPRESENTER_H

#include <QDialog>
#include <QThread>
#include <QWaitCondition>
#include <qtconcurrentrun.h>
#include "protocol.h"
#include "tcpclientmt.h"

namespace Ui {
class NetPresenter;
}

class NetPresenter : public QDialog
{
    Q_OBJECT

    static const int MODE_LOCAL = 1;
    static const int MODE_REMOTE = 2;

public:
    int m_nMode;
    int m_nPort;
    QString m_strServer;
    QString m_strContent;
    TCPClientMT* m_pSocket;

    int m_nTarget;
    int m_nStimulusNumber;
    bool m_bRunning;
    QFuture<void> m_WorkThread;

public:
    explicit NetPresenter(QWidget *parent = 0);
    ~NetPresenter();

    void onConnect();
    void onDisconnect();
    bool isConnected();
    void setMode(int mode);
    void queryStimulusNumber();
    void presentStimulus(int target);
    void presentFeedback(int result);

protected:
    void worker();
    void queryStimulus();
    void sendFeedback(int result);
    void sendStimulus(int target);

    void onStimulusNumber(int num);

    void enableControls(bool bConnected);

signals:
    void stimulusnumber(int num);
    void error(int errorno, const QString errorstr);

private slots:
    void on_btnConnect_clicked();
    void on_btnHide_clicked();
    void on_btnSend_clicked();

    void onConnected();
    void onDisconnected();
    void onError(int errorno, QString errorstr);
    void onReceived(IOBuffer* buff);

private:
    Ui::NetPresenter *ui;
};

#endif // NETPRESENTER_H
