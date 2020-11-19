#ifndef NETREADER_H
#define NETREADER_H

#include <QDialog>
#include <QLineEdit>
#include <QThread>
#include <qtconcurrentrun.h>
#include "amptransport.h"
#include "epochmanager.h"
#include "eeggraph.h"

namespace Ui {
class NetReader;
}

class  AmpBasicInfo
{
public:
    int dwSize;         // Size of structure, used for version control
    int nEegChan;       // Number of EEG channels
    int nEvtChan;       // Number of event channels
    int nBlockPnts;     // Samples in block
    int nRate;          // Sampling rate (in Hz)
    int nDataSize;      // 2 for "short", 4 for "int" type of data
    float fResolution;  // Resolution for LSB

    AmpBasicInfo() { memset((void*)&dwSize,0,sizeof(AmpBasicInfo)); }

    bool validate()
    {
        return (nBlockPnts > 0 && nRate > 0 && nEegChan > 0  && nDataSize > 0);
    }
};

class NetReader : public QDialog
{
    Q_OBJECT
public:
    int m_nPort;
    QString m_strServer;
    AmpBasicInfo m_BasicInfo;
    AmpTransport* m_pTransport;

    int m_nScale;
    int m_nDuration;
    float m_fScaleCoef;

    int m_nAllChannels;
    int m_nBlockPoints;
    int m_nTotalPoints;
    int* m_pRawData;
    bool m_bRunning;
    QFuture<void> m_WorkThread;
    EEGGraph* m_pEEGGraph;
    int m_nEpochLen;
    EpochManager m_EpochManager;

public:
    explicit NetReader(QWidget *parent = 0);
    ~NetReader();

    bool isConnected();
    void setEpochLen(int epochlen);
    Epoch* getEpoch();
    void clearEpochs();

protected:
    void showStatus(QString strStatus);
    void showInstructions();
    void enableControls(bool bConnected);

    bool startAcquisition();
    bool stopAcquisition();
    void worker();

// overide
protected:

private slots:
    void on_btnConnect_clicked();
    void on_btnHide_clicked();
    void on_spinDuration_valueChanged(int arg1);
    void on_spinScale_valueChanged(int arg1);

    void onConnected();
    void onDisconnected();
    void onCtrlMsg(AmpMessage* pMsg);
    void onDataMsg(AmpMessage* pMsg);

private:
    Ui::NetReader *ui;
};

#endif // NETREADER_H
