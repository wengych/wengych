/***************************************************************************/
/**[File Name    ]ysarray.c                                               **/
/**[File Path    ]$(SRCDIR)/libsrc/yscom                                  **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(HOME)/lib                                             **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for array                                   **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <yscom.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __OS_LINUX_
void *YSArrayNew(INT32 Max)
{
    return YSVarArrayNew2(Max);
}

void *YSArrayNew_Key(INT32 Max,const char *Key)
{
    void *Array;

    if ( NULL==(Array=YSArrayNew(Max)) )
    {
        return Array;
    }
    if ( !YSVarCpyKey(Array,Key) )
    {
        YSArrayFree(Array);
        Array = NULL;
    }
    return Array;
}

void  YSArrayFree(void *Array)
{
    YSVarArrayFree(Array);
}

void  YSArrayShow(void *Array,INT32 T,void *Buf)
{
    YSVarArrayShow(Array,T,Buf);
}

BOOL  YSArrayIsEmpty(void *Array)
{
    return YSVarArrayIsEmpty(Array);
}

BOOL  YSArrayIsFull(void *Array)
{
    return YSVarArrayIsFull(Array);
}

INT32 YSArrayGetLen(void *Array)
{
    return YSVarArrayGetLen(Array);
}

void *YSArrayGet(void *Array,INT32 Idx)
{
    return YSVarArrayGet(Array,Idx);
}

BOOL  YSArrayInsertObject(void *Array,INT32 Idx \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    BOOL bRtn;
    void *Obj;

    Obj = NULL;
    if ( NULL==(Obj=YSVarObjectSave(V,Clone,Free,Show,Pack)) )
    {
        return FALSE;
    }
    if ( FALSE==(bRtn=YSArrayInsertVar(Array,Idx,Obj)) )
    {
        YSVarObjectFree(Obj);
        Obj = NULL;
    }
    return bRtn;
}

BOOL  YSArrayInsertObject2(void *Array,INT32 Idx,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    BOOL bRtn;
    void *Obj;

    Obj = NULL;
    if ( NULL==(Obj=YSVarObjectSave2(Key,V,Clone,Free,Show,Pack)) )
    {
        return FALSE;
    }
    if ( FALSE==(bRtn=YSArrayInsertVar(Array,Idx,Obj)) )
    {
        YSVarObjectFree(Obj);
        Obj = NULL;
    }
    return bRtn;
}

BOOL  YSArrayInsertVar(void *Array,INT32 Idx,void *Var)
{
    return YSVarArrayInsert(Array,Idx,Var);
}

BOOL  YSArrayAddObject(void *Array \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    BOOL bRtn;
    void *Obj;

    Obj = NULL;
    if ( NULL==(Obj=YSVarObjectSave(V,Clone,Free,Show,Pack)) )
    {
        return FALSE;
    }
    if ( FALSE==(bRtn=YSArrayAddVar(Array,Obj)) )
    {
        YSVarObjectFree(Obj);
        Obj = NULL;
    }
    return bRtn;
}

BOOL  YSArrayAddObject2(void *Array,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    BOOL bRtn;
    void *Obj;

    Obj = NULL;
    if ( NULL==(Obj=YSVarObjectSave2(Key,V,Clone,Free,Show,Pack)) )
    {
        return FALSE;
    }
    if ( FALSE==(bRtn=YSArrayAddVar(Array,Obj)) )
    {
        YSVarObjectFree(Obj);
        Obj = NULL;
    }
    return bRtn;
}

BOOL  YSArrayAddVar(void *Array,void *Var)
{
    return YSVarArrayAdd(Array,Var);
}

BOOL  YSArrayDelete(void *Array,INT32 Idx)
{
    return YSVarArrayDelete(Array,Idx);
}

#else

void *YSArrayNew(INT32 Max)
{
    void *Array;
    void *Lock;
    char Tmp[TMP_MAX_BUFFER];
    BOOL Flag;

    Array = NULL;
    Lock = NULL;
    Flag = FALSE;
    while( 1 )
    {
        if ( NULL==(Array=YSVarArrayNew2(Max)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error :Failed at YSVarArrayNew2.");
            break;
        }
        if ( NULL==(Lock=YSPLockNewRWLock()) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error :Failed at YSPLockNewRWLock.");
            break;
        }
        if ( !YSVarSetRes(Array,Lock,YSPLockNewWRLock,YSPLockFree,YSPLockShow) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error :Failed at YSVarSetRes.");
            break;
        }
        Lock = NULL;
        Flag = TRUE;
        break;
    }
    if ( !Flag )
    {
        YSVarArrayFree(Array);
        Array = NULL;
        YSPLockFree(Lock);
        Lock = NULL;
    }
    return Array;
}

void *YSArrayNew_Key(INT32 Max,const char *Key)
{
    void *Array;

    if ( NULL==(Array=YSArrayNew(Max)) )
    {
        return Array;
    }
    if ( !YSVarCpyKey(Array,Key) )
    {
        YSArrayFree(Array);
        Array = NULL;
    }
    return Array;
}

void  YSArrayFree(void *Array)
{
    YSVarArrayFree(Array);
}

void  YSArrayShow(void *Array,INT32 T,void *Buf)
{
    void *Lock;
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Array)) )
    {
        if ( YSRTN_OK!=YSPLockReadTryLock(Lock) )
        {
            return ;
        }
    }
    YSVarArrayShow(Array,T,Buf);
    if ( NULL!=Lock )
    {
        YSPLockReadUnLock(Lock);
    }
}

BOOL  YSArrayIsEmpty(void *Array)
{
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    bRtn = FALSE;
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Array)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return bRtn;
        }
    }
    bRtn = YSVarArrayIsEmpty(Array);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

BOOL  YSArrayIsFull(void *Array)
{
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    bRtn = FALSE;
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Array)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return bRtn;
        }
    }
    bRtn = YSVarArrayIsFull(Array);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

INT32 YSArrayGetLen(void *Array)
{
    void *Lock;
    INT32 iRtn;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Array)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return FERTN_ER;
        }
    }
    iRtn = YSVarArrayGetLen(Array);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return iRtn;
}

void *YSArrayGet(void *Array,INT32 Idx)
{
    void *Lock;
    void *Obj;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    Obj = NULL;
    if ( NULL!=(Lock=YSVarGetRes(Array)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return Obj;
        }
    }
    Obj = YSVarArrayGet(Array,Idx);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return Obj;
}

BOOL  YSArrayInsertObject(void *Array,INT32 Idx \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    BOOL bRtn;
    void *Obj;
    char Tmp[YSAPP_TMP_LEN];

    Obj = NULL;
    if ( NULL==(Obj=YSVarObjectSave(V,Clone,Free,Show,Pack)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSVarObjectSave.");
        return FALSE;
    }
    if ( FALSE==(bRtn=YSArrayInsertVar(Array,Idx,Obj)) )
    {
        YSVarObjectFree(Obj);
        Obj = NULL;
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSArrayInsertVar.");
    }
    return bRtn;
}

BOOL  YSArrayInsertObject2(void *Array,INT32 Idx,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    BOOL bRtn;
    void *Obj;
    char Tmp[YSAPP_TMP_LEN];

    Obj = NULL;
    if ( NULL==(Obj=YSVarObjectSave2(Key,V,Clone,Free,Show,Pack)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSVarObjectSave.");
        return FALSE;
    }
    if ( FALSE==(bRtn=YSArrayInsertVar(Array,Idx,Obj)) )
    {
        YSVarObjectFree(Obj);
        Obj = NULL;
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSArrayInsertVar.");
    }
    return bRtn;
}

BOOL  YSArrayInsertVar(void *Array,INT32 Idx,void *Var)
{
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    bRtn = FALSE;
    if ( !YSVarIsInit(Var) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Var is not ready.");
        return FALSE;
    }
    if ( NULL!=(Lock=YSVarGetRes(Array)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return FALSE;
        }
    }
    bRtn = YSVarArrayInsert(Array,Idx,Var);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

BOOL  YSArrayAddObject(void *Array \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    BOOL bRtn;
    void *Obj;
    char Tmp[YSAPP_TMP_LEN];

    Obj = NULL;
    if ( NULL==(Obj=YSVarObjectSave(V,Clone,Free,Show,Pack)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSVarObjectSave.");
        return FALSE;
    }
    if ( FALSE==(bRtn=YSArrayAddVar(Array,Obj)) )
    {
        YSVarObjectFree(Obj);
        Obj = NULL;
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSArrayAddVar.");
    }
    return bRtn;
}

BOOL  YSArrayAddObject2(void *Array,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    BOOL bRtn;
    void *Obj;
    char Tmp[YSAPP_TMP_LEN];

    Obj = NULL;
    if ( NULL==(Obj=YSVarObjectSave2(Key,V,Clone,Free,Show,Pack)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSVarObjectSave.");
        return FALSE;
    }
    if ( FALSE==(bRtn=YSArrayAddVar(Array,Obj)) )
    {
        YSVarObjectFree(Obj);
        Obj = NULL;
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSArrayAddVar.");
    }
    return bRtn;
}

BOOL  YSArrayAddVar(void *Array,void *Var)
{
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    bRtn = FALSE;
    if ( !YSVarIsInit(Var) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Var is not ready.");
        return FALSE;
    }
    if ( NULL!=(Lock=YSVarGetRes(Array)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return FALSE;
        }
    }
    bRtn = YSVarArrayAdd(Array,Var);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

BOOL  YSArrayDelete(void *Array,INT32 Idx)
{
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    bRtn = FALSE;
    if ( NULL!=(Lock=YSVarGetRes(Array)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return FALSE;
        }
    }
    bRtn = YSVarArrayDelete(Array,Idx);
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

