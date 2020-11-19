#ifndef EPOCHMANAGER_H
#define EPOCHMANAGER_H

#include <QObject>
#include <QMutex>
#include <QLinkedList>

class Epoch {
public:
    int event;
    int channels;
    int epochlen;
    float* data;
    int pointindex;

    Epoch(int channels, int epochlen) {
        init(channels, epochlen);
    }

    void init(int channels, int epochlen)
    {
        this->channels = channels;
        this->epochlen = epochlen;

        this->event = 0;
        if (this->channels*this->epochlen > 0)
            this->data = new float[channels*epochlen];
        else
            this->data = 0;

        this->pointindex = 0;
    }

    void insertSample(float* data)
    {
        if (pointindex < epochlen) {
            for (int ch=0; ch<channels; ch++)
            {
                this->data[pointindex*channels+ch] = data[ch];
            }
            pointindex += 1;
        }
    }

    bool isFull()
    {
        return ((pointindex+1) >= epochlen);
    }
};

class EpochManager : public QObject
{
    Q_OBJECT
protected:
    int m_nEpochLen;
    int m_nEEGChannels;
    int m_nEventChannels;
    int m_nAllChannels;
    int m_queueEvent[4];
    int m_nMaxEpochs;
    QMutex m_mutexEpoch;
    QLinkedList<Epoch*> m_queueEpoch;

public:
    explicit EpochManager();

    void setChannelInfo(int eegch, int eventch, int epochlen);
    void insertData(char* data, int points, bool b32bit);

    void addEpoch(Epoch* pEpoch);
    Epoch* removeEpoch();
    Epoch* getEpoch(bool bRemove);
    void clearEpochs();

protected:
    bool isAriseEvent(int event);

signals:
    void dataready(Epoch*);

public slots:
};

#endif // EPOCHMANAGER_H
