#ifndef MATLABENG_H
#define MATLABENG_H

#include <engine.h>

class CMatlabEng  
{
public:
	CMatlabEng();
	virtual ~CMatlabEng();

protected:
	Engine *m_matEng;

public:
    bool	openEng(bool bVisible);
    bool	closeEng();
    int 	evalCmd(const char* szCmd);
    int		getIntVariable(const char* szResult);
    double	getDoubleVariable(const char* szResult);
    int		putVariable(const char* szName, char* szValue);
    int		putVariable(const char* szName, mxArray* varArray);
    int		putVariable(const char* szName, double fValue);
    int		putVariable(const char* szName, double* pData, int row, int col);
};

#endif // MATLABENG_H
