#include "epochmanager.h"

EpochManager::EpochManager()
{
    m_nEpochLen = 150;
    m_nEEGChannels = 0;
    m_nEventChannels = 1;
    memset(m_queueEvent, 0, sizeof(m_queueEvent));
    m_nMaxEpochs = 100;
}

void EpochManager::setChannelInfo(int eegch, int eventch, int epochlen)
{
    clearEpochs();
    m_nEpochLen = epochlen;
    m_nEEGChannels = eegch;
    m_nEventChannels = eventch;
    m_nAllChannels = m_nEEGChannels + m_nEventChannels;
}

void EpochManager::addEpoch(Epoch* pEpoch)
{
    m_mutexEpoch.lock();
    m_queueEpoch.append(pEpoch);
    m_mutexEpoch.unlock();
}

Epoch* EpochManager::removeEpoch()
{
    Epoch* pEpoch = 0;
    m_mutexEpoch.lock();
    if (m_queueEpoch.size() > 0) pEpoch = m_queueEpoch.takeFirst();
    m_mutexEpoch.unlock();
    return pEpoch;
}

Epoch* EpochManager::getEpoch(bool bRemove)
{
    Epoch* pEpoch = 0;
    m_mutexEpoch.lock();
    QMutableLinkedListIterator<Epoch*> it(m_queueEpoch);
    while (it.hasNext()) {
        Epoch* pTemp = it.next();
        if (pTemp->isFull()) {
            pEpoch = pTemp;
            if (bRemove) it.remove();
            break;
        }
    }
    m_mutexEpoch.unlock();
    return pEpoch;
}

void EpochManager::clearEpochs()
{
    m_mutexEpoch.lock();
    while (m_queueEpoch.size() > 0) {
        Epoch* pEpoch = m_queueEpoch.takeFirst();
        delete pEpoch;
    }
    m_mutexEpoch.unlock();
}

void EpochManager::insertData(char* data, int points, bool b32bit)
{
    int eventCode = 0;
    int* pData32 = (int*)data;
    short* pData16 = (short*)data;
    float* sliceData = new float[m_nEEGChannels];
    Epoch* pEpoch = 0;

    for (int i=0; i<points; i++)
    {
        for (int ch=0; ch<m_nEEGChannels; ch++)
        {
            if (b32bit)
                sliceData[ch] = pData32[i*m_nAllChannels+ch];
            else
                sliceData[ch] = pData16[i*m_nAllChannels+ch];
        }

        if (b32bit) {
            eventCode = pData32[i*m_nAllChannels+m_nEEGChannels];
        }
        else {
            eventCode = pData16[i*m_nAllChannels+m_nEEGChannels];
        }

        eventCode &= 0xFF;
        if (eventCode > 0 && isAriseEvent(eventCode)) {
            pEpoch = new Epoch(m_nEEGChannels, m_nEpochLen);
            pEpoch->event = eventCode;
            addEpoch(pEpoch);
        }

        // update all the epoch items
        m_mutexEpoch.lock();
        foreach(pEpoch, m_queueEpoch)
        {
            pEpoch->insertSample(sliceData);
            if (pEpoch->isFull()) {
                emit dataready(pEpoch);
            }
        }
        m_mutexEpoch.unlock();
    }
    delete [] sliceData;

    // remove epochs if its size is large than 1000
    if (m_queueEpoch.size() > m_nMaxEpochs)
    {
        Epoch* pEpoch = removeEpoch();
        if (pEpoch) delete pEpoch;
    }
}

bool EpochManager::isAriseEvent(int event)
{
    bool bArise = false;

    m_queueEvent[3] = m_queueEvent[2];
    m_queueEvent[2] = m_queueEvent[1];
    m_queueEvent[1] = m_queueEvent[0];
    m_queueEvent[0] = event;

    bool temp1 = (m_queueEvent[0]==0x00);
    bool temp2 = (m_queueEvent[0]==0xFF);

    if (!temp1 && !temp2) {
        bArise = !((m_queueEvent[0] == m_queueEvent[1]) |
                   (m_queueEvent[0] == m_queueEvent[2]) |
                   (m_queueEvent[0] == m_queueEvent[3]));
    }
    return bArise;
}
