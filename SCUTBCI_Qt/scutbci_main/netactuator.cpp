#include "netactuator.h"
#include "ui_netactuator.h"
#include <QMessageBox>

NetActuator::NetActuator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetActuator)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    m_nPort = 6000;
    m_strServer = "192.168.0.100";
    m_pSocket = 0;
    m_strPrefix = "ID001CH";

    ui->editPort->setText(QString::number(m_nPort));
    ui->editServer->setText(m_strServer);
    ui->editPrefix->setText(m_strPrefix);
}

NetActuator::~NetActuator()
{
    delete ui;
}

void NetActuator::on_btnConnect_clicked()
{
    m_nPort = ui->editPort->text().toInt();
    m_strServer = ui->editServer->text();

    if (m_pSocket == 0)  {
        m_pSocket = new TCPClient();
        connect(m_pSocket, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        connect(m_pSocket, SIGNAL(received(IOBuffer*)), this, SLOT(onReceived(IOBuffer*)));
        // connect(m_pSocket, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
    }

    if (!m_pSocket->isConnected()) {
        m_pSocket->onConnect(m_strServer, m_nPort);
    } else {
        m_pSocket->onDisconnect();
    }
}

void NetActuator::on_btnHide_clicked()
{
    hide();
}

void NetActuator::on_btnSend_clicked()
{
    m_strPrefix = ui->editPrefix->text();
    QString strCmd = ui->editCommand->toPlainText().toLocal8Bit();
    sendCommand(m_strPrefix+strCmd);
}

void NetActuator::onConnected()
{
    enableControls(isConnected());
}

void NetActuator::onDisconnected()
{
    enableControls(isConnected());
}

void NetActuator::onReceived(IOBuffer* buff)
{
    qDebug(buff->data());
}

void NetActuator::sendCommand(QString cmd)
{
    if (isConnected()) m_pSocket->onSend(cmd);
}

bool NetActuator::isConnected()
{
    return (m_pSocket && m_pSocket->isConnected());
}

void NetActuator::enableControls(bool bConnected)
{
    ui->editPort->setEnabled(!bConnected);
    ui->editServer->setEnabled(!bConnected);
    ui->btnConnect->setText(bConnected?"Disconnect":"Connect");
}
