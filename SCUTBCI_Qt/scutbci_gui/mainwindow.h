#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPlainTextEdit>
#include "hrtimer.h"
#include "flashbutton.h"
#include "tcpserver.h"

static const char CHAR_MATRIX[] = {
    "ABCDEFGHIJ"
    "KLMNOPQRST"
    "UVWXYZ-,.?"
    "0123456789"
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    int m_nMargin;
    int m_nBtnMargin;
    int m_nRows;
    int m_nColumns;
    int m_nNumBtns;
    QRect* m_rcBtnSpeller;
    FlashButton** m_pBtnSpeller;

    TCPServer* m_pServer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void presentStimulus(int target);
    void presentFeedback(int result);

protected:
    void paintEvent(QPaintEvent*);

public slots:
    void onReceived(IOContext* pContext);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
