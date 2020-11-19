#include <QDir>
#include "eegalgomatlab.h"

void EEGAlgoMatlab::init()
{
    qDebug("EEGAlgoMatlab::init() called");
    if(!m_matEng.openEng(true)) {
        qDebug("Open matlab engine failed.");
        return;
    }

    m_strCmd = QString("cd '%1/../matlab'").arg(QDir::currentPath());
    m_matEng.evalCmd(m_strCmd.toLocal8Bit());
    setInput();
    m_strCmd.sprintf("[output,param,state] = P300Speller_Thread_Initialization_Asyn(input)");
    m_matEng.evalCmd(m_strCmd.toLocal8Bit());
}

void EEGAlgoMatlab::reset()
{
    qDebug("EEGAlgoMatlab::reset() called");
    m_strCmd.sprintf("");
    m_matEng.evalCmd(m_strCmd.toLocal8Bit());
}

void EEGAlgoMatlab::round()
{
    // qDebug("EEGAlgoMatlab::round() called");
    setInput();
    m_strCmd.sprintf("[output,result,state] = P300Speller_Round_Processing_Asyn(input,param,state)");
    m_matEng.evalCmd(m_strCmd.toLocal8Bit());
    m_nResult = m_matEng.getDoubleVariable("result");
}

void EEGAlgoMatlab::evaluate()
{
    qDebug("EEGAlgoMatlab::evaluate() called");
}

void EEGAlgoMatlab::setInput()
{
    mxArray* inputArray = 0;
    mxArray* eventArray = 0;
    mxArray* epochArray = 0;
    mxArray* subjectArray = 0;
    const char* fields[]= {"subject", "event", "epoch"};
    inputArray = mxCreateStructMatrix(1,1,3,fields);
    subjectArray = mxCreateString(m_strSubject.toLocal8Bit());
    mxSetField(inputArray, 0, "subject", subjectArray);
    if(m_nEvent > 0) {
        eventArray = mxCreateDoubleScalar((double)m_nEvent);
        mxSetField(inputArray, 0, "event", eventArray);

        epochArray = mxCreateDoubleMatrix(m_nChannels, m_nDataPoints, mxREAL);
        memcpy((void*)mxGetPr(epochArray), (void*)m_pEpochData,
               m_nChannels*m_nDataPoints*sizeof(double));
        mxSetField(inputArray, 0, "epoch", epochArray);
    }
    m_matEng.putVariable("input", inputArray);

    if(epochArray) {
        mxDestroyArray(epochArray);
        epochArray = NULL;
    }
}
