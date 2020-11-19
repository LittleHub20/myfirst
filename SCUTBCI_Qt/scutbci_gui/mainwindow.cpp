#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "protocol.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_nMargin = 10;
    m_nBtnMargin = 30;
    m_nRows = 4;
    m_nColumns = 10;
    m_nNumBtns = 40;
    m_rcBtnSpeller = new QRect[m_nNumBtns];
    m_pBtnSpeller = new FlashButton*[m_nNumBtns];
    for (int i=0; i<m_nNumBtns; i++)
    {
        m_pBtnSpeller[i] = new FlashButton("", this);
        m_pBtnSpeller[i]->setText(QString(CHAR_MATRIX[i]));
    }

    m_pServer = new TCPServer();
    m_pServer->onSetup(UI_SOCKET_PORT);
    connect(m_pServer, SIGNAL(dataReceived(IOContext*)), this, SLOT(onReceived(IOContext*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QRect rcGround = ui->centralwidget->geometry();
    QRect rcKeyboard = QRect(rcGround.left() + m_nMargin,
                             rcGround.top() + m_nMargin,
                             rcGround.width() - 2*m_nMargin,
                             rcGround.height() - 2*m_nMargin);

    m_nBtnMargin = rcKeyboard.width()/(2*m_nColumns);
    int w = (rcKeyboard.width()+m_nBtnMargin)/m_nColumns - m_nBtnMargin;
    int h = (rcKeyboard.height()+m_nBtnMargin)/m_nRows - m_nBtnMargin;
    for(int i=0; i<m_nRows; i++)
    {
        for(int j=0; j<m_nColumns; j++)
        {
            m_rcBtnSpeller[i*m_nColumns+j] =
                    QRect(rcKeyboard.left() + j*(w+m_nBtnMargin),
                          rcKeyboard.top() + i*(h+m_nBtnMargin),
                          w,
                          h);
        }
    }
    for(int i=0; i<m_nNumBtns; i++) m_pBtnSpeller[i]->setGeometry(m_rcBtnSpeller[i]);
}

void MainWindow::presentStimulus(int target)
{
    m_pBtnSpeller[target]->flashOnce(100);
}


void MainWindow::presentFeedback(int result)
{

}

void MainWindow::onReceived(IOContext* pContext)
{
    IOBuffer* pBuffer = pContext->m_pBuffer;
    UICommand cmd;
    if (pBuffer->length() >= sizeof(UICommand)) {
        pBuffer->read((char*)&cmd, sizeof(UICommand));

        if (cmd.type == CMDTYPE::CMDTYPE_QUERY) {
            qDebug("CMDTYPE_QUERY received");
            UICommand response = {CMDTYPE::CMDTYPE_RESULT, m_nNumBtns};
            m_pServer->onSend(pContext, (char*)&response, sizeof(UICommand));
        } else if (cmd.type == CMDTYPE::CMDTYPE_STIMULUS) {
            // qDebug("CMDTYPE_STIMULUS received");
            presentStimulus(cmd.content);
        } else if (cmd.type == CMDTYPE::CMDTYPE_RESULT) {
            qDebug("CMDTYPE_RESULT received");
            presentFeedback(cmd.content);
        }
    }
}
