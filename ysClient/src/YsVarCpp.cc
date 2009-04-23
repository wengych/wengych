#include "YsVarCpp.h"

void CYsVar::Free()
{
    if (NULL == m_hVar)
        return ;
    YSVarFree(m_hVar);
    m_hVar = NULL;
}

void CYsVar::Show( INT32 T, CYsString& str )
{
    YSVarShow(m_hVar, T, str.get_handle());
}

void* CYsVar::get_handle()
{
    return m_hVar;
}

BOOL CYsVar::IsInit()
{
    return YSVarIsInit(m_hVar);
}

INT32 CYsVar::GetType()
{
    return YSVarGetType(m_hVar);
}

CYsVar::CYsVar() : m_hVar(NULL)
{
}

CYsVar::CYsVar( CYsVar& rhs ) : m_hVar(rhs.m_hVar)
{
    rhs.Clear();
}

CYsVar::~CYsVar()
{
    Free();
}

void CYsVar::Clear()
{
    m_hVar = NULL;
}
