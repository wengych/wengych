/***************************************************************************/
/**[File Name    ]ysfifo.c                                                **/
/**[File Path    ]$(SRCDIR)/libsrc/yscom                                  **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for fifo manager                            **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <yscom.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __OS_LINUX__

void *YSFifoNew(INT32 Max)
{
     return YSVarFifoNew2(Max);
}

void *YSFifoNew_Key(INT32 Max,const char *Key)
{
    void *Fifo;

    if ( NULL==(Fifo=YSFifoNew(Max)) )
    {
        return Fifo;
    }
    if ( !YSVarCpyKey(Fifo,Key) )
    {
        YSFifoFree(Fifo);
        Fifo = NULL;
    }
    return Fifo;
}

void  YSFifoFree(void *Fifo)
{
    YSVarFifoFree(Fifo);
}

void  YSFifoShow(void *Fifo,INT32 T,void *Buf)
{
    YSVarFifoShow(Fifo,T,Buf);
}

BOOL  YSFifoIsEmpty(void *Fifo)
{
    return YSVarFifoIsEmpty(Fifo);
}

INT32 YSFifoGetLen(void *Fifo)
{
    return YSVarFifoGetLen(Fifo);
}

BOOL  YSFifoPop(void *Fifo,void **V)
{
    return YSVarFifoPop(Fifo,V);
}

BOOL  YSFifoPushValue(void *Fifo \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    void *Obj;
    BOOL bRtn;

    bRtn = FALSE;
    Obj = NULL;
    while( 1 )
    {
        if ( NULL==(Obj=YSVarObjectSave(V,Clone,Free,Show,Pack)) )
        {
            break;
        }
        if ( !YSVarFifoPush(Fifo,Obj) )
        {
            break;
        }
        Obj = NULL;
        bRtn = TRUE;
        break;
    }
    YSVarFree(Obj);
    return bRtn;
}

BOOL  YSFifoPushString(void *Fifo,const char *Str,INT32 Len)
{
    void *Obj;
    BOOL bRtn;

    bRtn = FALSE;
    if ( (NULL==Str)||(0>Len) )
    {
        return bRtn;
    }
    while( 1 )
    {
        if ( NULL==(Obj=YSVarStringNew()) )
        {
            break;
        }
        if ( !YSVarStringCat(Obj,(void *)Str,Len) )
        {
            break;
        }
        if ( !YSVarFifoPush(Fifo,Obj) )
        {
            break;
        }
        Obj = NULL;
        bRtn = TRUE;
        break;
    }
    YSVarFree(Obj);
    return bRtn;
}

BOOL  YSFifoPushVar(void *Fifo,void *Var)
{
    return YSVarFifoPush(Fifo,Var);
}

#else

void *YSFifoNew(INT32 Max)
{
    void *Fifo;
    void *Lock;
    char Tmp[TMP_MAX_BUFFER];
    BOOL Flag;

    Fifo = NULL;
    Lock = NULL;
    Flag = FALSE;
    while( 1 )
    {
        if ( NULL==(Fifo=YSVarFifoNew2(Max)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarFifoNew2.");
            break;
        }
        if ( NULL==(Lock=YSPLockNewRWLock()) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockNewRWLock.");
            break;
        }
        if ( !YSVarSetRes(Fifo,Lock,YSPLockNewWRLock,YSPLockFree,YSPLockShow) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarSetRes.");
            break;
        }
        Lock = NULL;
        Flag = TRUE;
        break;
    }
    if ( !Flag )
    {
        YSVarFifoFree(Fifo);
        Fifo = NULL;
        YSPLockFree(Lock);
        Lock = NULL;
    }
    return Fifo;
}

void *YSFifoNew_Key(INT32 Max,const char *Key)
{
    void *Fifo;

    if ( NULL==(Fifo=YSFifoNew(Max)) )
    {
        return Fifo;
    }
    if ( !YSVarCpyKey(Fifo,Key) )
    {
        YSFifoFree(Fifo);
        Fifo = NULL;
    }
    return Fifo;
}

void  YSFifoFree(void *Fifo)
{
    YSVarFifoFree(Fifo);
}

void  YSFifoShow(void *Fifo,INT32 T,void *Buf)
{
    void *Lock;
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Fifo)) )
    {
        if ( RTNCODE_OK!=YSPLockReadTryLock(Lock) )
        {
            return ;
        }
    }
    YSVarFifoShow(Fifo,T,Buf);
    if ( NULL!=Lock )
    {
        YSPLockReadUnLock(Lock);
    }
}

BOOL  YSFifoIsEmpty(void *Fifo)
{
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    bRtn = FALSE;
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Fifo)) )
    {
        if ( RTNCODE_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return bRtn;
        }
    }
    bRtn = YSVarFifoIsEmpty(Fifo);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

INT32 YSFifoGetLen(void *Fifo)
{
    void *Lock;
    INT32 iRtn;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Fifo)) )
    {
        if ( RTNCODE_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return RTNCODE_ER;
        }
    }
    iRtn = YSVarFifoGetLen(Fifo);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return iRtn;
}

BOOL  YSFifoPop(void *Fifo,void **V)
{
    void *Lock;
    void *Obj;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    bRtn = FALSE;
    Lock = NULL;
    Obj = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Fifo)) )
    {
        if ( RTNCODE_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return bRtn;
        }
    }
    while( 1 )
    {
        if ( !YSVarFifoPop(Fifo,&Obj) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarFifoPop.");
            break;
        }
        if ( NULL!=V )
        {
            *V = Obj;
        }
        else
        {
            YSVarFree(Obj);
            Obj = NULL;
        }
        bRtn = TRUE;
        break;
    }
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

BOOL  YSFifoPushValue(void *Fifo \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    void *Lock;
    void *Obj;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    bRtn = FALSE;
    Lock = NULL;
    Obj = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Fifo)) )
    {
        if ( RTNCODE_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return bRtn;
        }
    }
    while( 1 )
    {
        if ( NULL==(Obj=YSVarObjectSave(V,Clone,Free,Show,Pack)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarObjectNew.");
            break;
        }
        if ( !YSVarFifoPush(Fifo,Obj) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarFifoPush.");
            break;
        }
        Obj = NULL;
        bRtn = TRUE;
        break;
    }
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    YSVarFree(Obj);
    return bRtn;
}

BOOL  YSFifoPushString(void *Fifo,const char *Str,INT32 Len)
{
    void *Lock;
    void *Obj;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    bRtn = FALSE;
    Lock = NULL;
    if ( (NULL==Str)||(0>Len) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args is null.");
        return bRtn;
    }
    if ( NULL!=(Lock=YSVarGetRes(Fifo)) )
    {
        if ( RTNCODE_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return bRtn;
        }
    }
    while( 1 )
    {
        if ( NULL==(Obj=YSVarStringNew()) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarStringNew.");
            break;
        }
        if ( !YSVarStringCat(Obj,(void *)Str,Len) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarStringCat.");
            break;
        }
        if ( !YSVarFifoPush(Fifo,Obj) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarFifoPush.");
            break;
        }
        Obj = NULL;
        bRtn = TRUE;
        break;
    }
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    YSVarFree(Obj);
    return bRtn;
}

BOOL  YSFifoPushVar(void *Fifo,void *Var)
{
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    bRtn = FALSE;
    Lock = NULL;
    if ( !YSVarIsInit(Var) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Variable is not VarType.");
        return FALSE;
    }
    if ( NULL!=(Lock=YSVarGetRes(Fifo)) )
    {
        if ( RTNCODE_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return bRtn;
        }
    }
    if ( FALSE==(bRtn=YSVarFifoPush(Fifo,Var)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSVarFifoPush.");
    }
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}
#endif

#ifdef __cplusplus
}
#endif

