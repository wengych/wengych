/*
* YsVarCpp.h
*
*  Created on: 2009.4.23
*      Author: wengych
*
*  C++ wrapper for YsVar
*/

#include <ysdef.h>
#include <boost/shared_ptr.hpp>

#ifndef YSVAR_CPP_H_
#define YSVAR_CPP_H_

class CYsBin;
class CYsString;

class CYsVar
{
public:
    CYsVar();
    explicit CYsVar(CYsVar& rhs);
    virtual ~CYsVar();

    virtual void Clear();
    virtual void Free();
    virtual void Show(INT32 T, CYsString& str);
    virtual BOOL IsInit();
    virtual INT32 GetType();

    void* get_handle();

protected:
    void* m_hVar;
};

class CYsBin : public CYsVar
{
public:
    CYsBin(){ m_hVar = YSVarBinNew(); }
};

class CYsString : public CYsVar
{

};

#endif // YSVAR_CPP_H_
