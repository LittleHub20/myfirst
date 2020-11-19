#include <string.h>
#include "matlabeng.h"

CMatlabEng::CMatlabEng()
{
    m_matEng = 0;
}

CMatlabEng::~CMatlabEng()
{

}

bool CMatlabEng::openEng(bool bVisible)
{
    if (!(m_matEng = engOpen(0)))
    {
        return false;
    }
    engSetVisible(m_matEng, bVisible);

    return true;
}

bool CMatlabEng::closeEng()
{
    if (m_matEng != 0)
    {
        if (!engClose(m_matEng))
        {
            m_matEng = 0;
            return true;
        }
        else
        {
            m_matEng = 0;
            return false;
        }
    }
    return true;
}

int CMatlabEng::evalCmd(const char* szCmd)
{
    if (m_matEng)
        return engEvalString(m_matEng, szCmd);
	
    return false;
}

int CMatlabEng::getIntVariable(const char* szResult)
{
    int result;
    mxArray* resultArray = 0;
	resultArray = engGetVariable(m_matEng, szResult);
    if (resultArray)
		result = *(int*)(mxGetPr(resultArray));
    else
		result = -1;
	
	mxDestroyArray(resultArray);
		
	return result;
}

double CMatlabEng::getDoubleVariable(const char* szResult)
{
    double result;
    mxArray* resultArray = 0;
	resultArray = engGetVariable(m_matEng, szResult);
    if (resultArray)
		result = *(double*)(mxGetPr(resultArray));
    else
		result = -1;
	
	mxDestroyArray(resultArray);
	
	return result;
}

int CMatlabEng::putVariable(const char* szName, mxArray* varArray)
{
	if (!varArray)
        return false;
	return engPutVariable(m_matEng, szName, varArray);
}

int CMatlabEng::putVariable(const char* szName, char* szValue)
{
    mxArray* varArray = 0;
	varArray = mxCreateString(szValue);
	if (!varArray)
        return false;
	return engPutVariable(m_matEng, szName, varArray);
}

int CMatlabEng::putVariable(const char* szName, double fValue)
{
    mxArray* varArray = 0;
    varArray = mxCreateDoubleScalar(fValue);
	if (!varArray)
        return false;
	return engPutVariable(m_matEng, szName, varArray);
}

int CMatlabEng::putVariable(const char* szName, double* pData, int row, int col)
{
    mxArray* varArray = 0;
	varArray = mxCreateNumericMatrix(row, col, mxDOUBLE_CLASS, mxREAL);
	if (!varArray)
        return false;
	memcpy((void*)mxGetPr(varArray),(void*)pData, row*col*sizeof(double));
	return engPutVariable(m_matEng, szName, varArray);
}
