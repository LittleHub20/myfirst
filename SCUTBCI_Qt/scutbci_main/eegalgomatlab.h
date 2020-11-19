#ifndef EEGALGOMATLAB_H
#define EEGALGOMATLAB_H

#include "matlabeng.h"
#include "eegalgoeng.h"

class EEGAlgoMatlab : public EEGAlgoEng
{
protected:
    QString m_strCmd;
    CMatlabEng	m_matEng;

protected:
    void init();
    void reset();
    void round();
    void evaluate();
    void setInput();
};

#endif // EEGALGOMATLAB_H
