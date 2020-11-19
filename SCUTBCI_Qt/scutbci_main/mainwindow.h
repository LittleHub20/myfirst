#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPlainTextEdit>
#include "hrtimer.h"
#include "netreader.h"
#include "netmarker.h"
#include "netactuator.h"
#include "netpresenter.h"
#include "eegalgocpp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static const int MODE_TRAIN = 1;
    static const int MODE_ONLINE = 2;

    static const int STATE_START = 1;
    static const int STATE_PREPARE = 2;
    static const int STATE_ROUNDINIT = 3;
    static const int STATE_ROUND = 4;
    static const int STATE_REST = 5;

    static const int EVENT_DATA_BEGIN = 1;
    static const int EVENT_DATA_END = 40;
    static const int EVENT_TRAIN_BEGIN = 41;
    static const int EVENT_TRAIN_END = 80;
    static const int EVENT_SYSTEM_START = 81;

protected:
    int m_nNumBtns;
    QLabel m_labelStatus;

    int m_nMode;
    int m_nState;
    bool m_bUserStop;
    bool m_bWaitForNextTrial;
    QList<int> m_seqStim;
    QList<int> m_seqStimOld;
    QList<int> m_seqStimTrain;
    QList<int> m_seqReceive;
    HRTimer m_timerFSM;
    HRTimer m_timerData;
    HRTimer m_timerConnection;

    int m_nRecvIndex;
    int m_nStimIndex;
    int m_nRoundIndex;
    int m_nFlashIndex;
    int m_nTrainRounds;
    int m_nMaxTrial;
    int m_nCurrentTrial;
    int m_nTimeStart2Prepare;
    int m_nTimePrepare2Round;
    int m_nTimeOneStimulus;
    int m_nTimeRest2Prepare;

    NetReader* m_pNetReader;
    NetMarker* m_pNetMarker;
    NetActuator* m_pNetActuator;
    NetPresenter* m_pNetPresenter;
    EEGAlgoCpp m_Algorithm;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void enableControls(bool bStarted);
    bool initSystem();
    void setParameterTrain();
    void setParameterOnline();

    void FSM(int state);
    void startTimerFSM(int state, int interval);
    void stopTimerFSM();
    void checkDataReady();
    void startTimerData(int interval);
    void stopTimerData();
    void checkConnection();
    void startTimerConnection(int interval);
    void stopTimerConnection();
    void feedback(int result);
    void outputResult(int result);

    void randperm(int* seq, int n);
    void generateSeq(QList<int> &newSeq, QList<int> &oldSeq, int len, int interval);
    void displaySeq(QList<int> &seq);

protected:
    void paintEvent(QPaintEvent*);

signals:

public slots:
    void onTimerFSM();
    void onTimerData();
    void onTimerConnection();

    void on_actionNetReader_triggered();
    void on_actionNetMarker_triggered();
    void on_actionNetActuator_triggered();
    void on_actionNetPresenter_triggered();
    void on_actionStimSeq_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
