/***************************************************************************/
/**[File Name    ]userbus.c                                               **/
/**[File Path    ]$(SRCDIR)/libsrc/yscom                                  **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(HOME)/lib                                             **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for userbus                                 **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <yscom.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __OS_LINUX__
void *YSUserBusNew(INT32 Size)
{
    return YSVarHashNew(Size);
}

void *YSUserBusNew_Key(INT32 Size,const char *Key)
{
    void *UserBus;

    if ( NULL==(UserBus=YSUserBusNew(Size)) )
    {
        return UserBus;
    }
    if ( !YSVarCpyKey(UserBus,Key) )
    {
        YSUserBusFree(UserBus);
        UserBus = NULL;
    }
    return UserBus;
}

void  YSUserBusFree(void *UserBus)
{
    YSVarHashFree(UserBus);
}

void  YSUserBusShow(void *UserBus,INT32 T,void *Buf)
{
    YSVarHashShow(UserBus,T,Buf);
}

BOOL  YSUserBusPack(void *UserBus,void *Buf)
{
    return YSVarHashPack(UserBus,Buf);
}

INT32 YSUserBusUnPack(void **UserBus,void *Buf,INT32 P)
{
    return YSVarHashUnPack(UserBus,Buf,P);
}

BOOL  YSUserBusIsInit(void *UserBus)
{
    return YSVarIsInit(UserBus);
}

BOOL  YSUserBusIsEmpty(void *UserBus)
{
    return YSVarFifoIsEmpty(UserBus);
}

void *YSUserBusGetArray(void *UserBus,const char *Key)
{
    return YSVarHashGet(UserBus,Key);
}

void *YSUserBusGet(void *UserBus,const char *Key)
{
    return YSUserBusArrayGet(UserBus,Key,0);
}

void *YSUserBusArrayGet(void *UserBus,const char *Key,INT32 Idx)
{
    return YSVarArrayGet(YSVarHashGet(UserBus,Key),Idx);
}

BOOL  YSUserBusDelete(void *UserBus,const char *Key)
{
    return YSVarHashDelete(UserBus,Key);
}

BOOL  YSUserBusArrayDelete(void *UserBus,const char *Key,INT32 Idx)
{
    return YSVarArrayDelete(YSVarHashGet(UserBus,Key),FECAL_MAX(0,Idx));
}

BOOL  YSUserBusAddValue(void *UserBus,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    return YSUserBusArrayAddValue(UserBus,Key,0,V,Clone,Free,Show,Pack);
}

BOOL  YSUserBusArrayAddValue(void *UserBus,const char *Key,INT32 Idx \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    void *Obj;

    if ( NULL==(Obj=YSVarObjectSave2(Key,V,Clone,Free,Show,Pack)) )
    {
        return FALSE;
    }
    if ( !YSUserBusArrayAddVar(UserBus,Idx,Obj) )
    {
        YSVarObjectFree(Obj);
        return FALSE;
    }
    return TRUE;
}

BOOL  YSUserBusAddString(void *UserBus,const char *Key \
    ,const char *Str,INT32 Len)
{
    return YSUserBusArrayAddString(UserBus,Key,0,Str,Len);
}

BOOL  YSUserBusArrayAddString(void *UserBus,const char *Key,INT32 Idx \
    ,const char *Str,INT32 Len)
{
    void *Obj;

    if ( NULL==(Obj=YSVarStringSave2(Key,(void *)Str,Len)) )
    {
        return FALSE;
    }
    if ( !YSUserBusArrayAddVar(UserBus,Idx,Obj) )
    {
        YSVarObjectFree(Obj);
        return FALSE;
    }
    return TRUE;
}

BOOL  YSUserBusAddInt32(void *UserBus,const char *Key,INT32 n)
{
    return YSUserBusArrayAddInt32(UserBus,Key,0,n);
}

BOOL  YSUserBusArrayAddInt32(void *UserBus,const char *Key,INT32 Idx,INT32 n)
{
    void *Obj;

    if ( NULL==(Obj=YSVarInt32Save2(Key,n)) )
    {
        return FALSE;
    }
    if ( !YSUserBusArrayAddVar(UserBus,Idx,Obj) )
    {
        YSVarObjectFree(Obj);
        return FALSE;
    }
    return TRUE;
}

BOOL  YSUserBusAddVar(void *UserBus,void *V)
{
    return YSUserBusArrayAddVar(UserBus,0,V);
}

BOOL  YSUserBusArrayAddVar(void *UserBus,INT32 Idx,void *V)
{
    void *Key;
    void *Arr;
    void *NArr;
    BOOL bRtn;

    bRtn = FALSE;
    Arr = NULL;
    NArr = NULL;
    
    if ( !YSVarIsInit(V)||!YSVarIsInit2(UserBus,VARTYPE_MEM_VT_HASH) )
    {
        return FALSE;
    }
    if ( NULL==(Key=YSVarGetKey(V)) )
    {
        return FALSE;
    }
    if ( 0==strlen(Key) )
    {
        return FALSE;
    }
    while( 1 )
    {
        if ( NULL==(Arr=YSVarHashGet(UserBus,Key)) )
        {
            if ( NULL==(NArr=YSVarArrayNew_Key(0,Key)) )
            {
                break;
            }
            if ( !YSVarHashAdd(UserBus,NArr) )
            {
                break;
            }
            Arr = NArr;
        }
        if ( !YSVarArrayInsert(Arr,FECAL_MAX(0,Idx),V) )
        {
            break;
        }
        NArr = NULL;
        bRtn = TRUE;
        break;
    }
    YSVarArrayFree(NArr);
    NArr = NULL;
    return bRtn;
}

INT32 YSUserBusGetLen(void *UserBus)
{
    return YSVarHashGetLen(UserBus);
}

INT32 YSUserBusArrayGetLen(void *UserBus,const char *Key)
{
    return YSVarArrayGetLen(YSVarArrayGetByKey(UserBus,Key,strlen(Key)));
}

BOOL  YSUserBusReplaceValue(void *UserBus,const char *Key,void *V)
{
    return YSUserBusArrayReplaceValue(UserBus,Key,0,V);
}

BOOL  YSUserBusArrayReplaceValue(void *UserBus \
    ,const char *Key,INT32 Idx,void *V)
{
    return YSVarArrayReplaceValue(YSVarHashGet(UserBus,Key),Idx,V);
}

#else
void *YSUserBusNew(INT32 Size)
{
    void *UserBus;
    void *Lock;
    BOOL Flag;
    char Tmp[TMP_MAX_BUFFER];

    UserBus = NULL;
    Lock = NULL;
    Flag = FALSE;
    while( 1 )
    {
        if ( NULL==(UserBus=YSVarHashNew(Size)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarHashNew.");
            break;
        }
        if ( NULL==(Lock=YSPLockNewRWLock()) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockNewRWLock.");
            break;
        }
        if ( !YSVarSetRes(UserBus,Lock \
            ,YSPLockNewWRLock,YSPLockFree,YSPLockShow) )
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
        YSVarHashFree(UserBus);
        UserBus = NULL;
        YSPLockFree(Lock);
        Lock = NULL;
    }
    return UserBus;
}

void *YSUserBusNew_Key(INT32 Size,const char *Key)
{
    void *UserBus;

    if ( NULL==(UserBus=YSUserBusNew(Size)) )
    {
        return UserBus;
    }
    if ( !YSVarCpyKey(UserBus,Key) )
    {
        YSUserBusFree(UserBus);
        UserBus = NULL;
    }
    return UserBus;
}

void  YSUserBusFree(void *UserBus)
{
    YSVarHashFree(UserBus);
}

void  YSUserBusShow(void *UserBus,INT32 T,void *Buf)
{
    void *Lock;
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockReadTryLock(Lock) )
        {
            return ;
        }
    }
    YSVarHashShow(UserBus,T,Buf);
    if ( NULL!=Lock )
    {
        YSPLockReadUnLock(Lock);
    }
}

BOOL  YSUserBusPack(void *UserBus,void *Buf)
{
    BOOL bRtn;
    void *Lock;
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockReadTryLock(Lock) )
        {
            return FALSE;
        }
    }
    bRtn = YSVarHashPack(UserBus,Buf);
    if ( NULL!=Lock )
    {
        YSPLockReadUnLock(Lock);
    }
    return bRtn;
}

INT32 YSUserBusUnPack(void **UserBus,void *Buf,INT32 P)
{
    INT32 Pos;
    INT32 iRtn;
    void *Lock;
    char Tmp[TMP_MAX_BUFFER];

    *UserBus = NULL;
    if ( 0>(iRtn=YSVarHashUnPack(UserBus,Buf,P)) )
    {
        YSUserBusFree(*UserBus);
        *UserBus = NULL;
        return iRtn;
    }
    Pos = iRtn;
    Lock = NULL;
    iRtn = YSRTN_ERVAR_UNPACK;
    while( 1 )
    {
        if ( NULL==(Lock=YSPLockNewRWLock()) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockNewRWLock.");
            break;
        }
        if ( !YSVarSetRes(*UserBus,Lock \
            ,YSPLockNewWRLock,YSPLockFree,YSPLockShow) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarSetRes.");
            break;
        }
        Lock = NULL;
        iRtn = Pos;
        break;
    }
    if ( 0>=iRtn )
    {
        YSVarHashFree(*UserBus);
        *UserBus = NULL;
        YSPLockFree(Lock);
        Lock = NULL;
    }
    return iRtn;
}

BOOL  YSUserBusIsInit(void *UserBus)
{
    return YSVarIsInit(UserBus);
}

BOOL  YSUserBusIsEmpty(void *UserBus)
{
    BOOL bRtn;
    void *Lock;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return FALSE;
        }
    }
    bRtn = YSVarFifoIsEmpty(UserBus);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

void *YSUserBusGetArray(void *UserBus,const char *Key)
{
    void *Lock;
    void *Arr;
    char Tmp[TMP_MAX_BUFFER];

    Arr = NULL;

    if ( NULL==Key )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Key is null.");
        return NULL;
    }
    if ( 0==strlen(Key) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Key is null .");
        return NULL;
    }
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return NULL;
        }
    }
    Arr = YSVarHashGet(UserBus,Key);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return Arr;
}

void *YSUserBusGet(void *UserBus,const char *Key)
{
    return YSUserBusArrayGet(UserBus,Key,0);
}

void *YSUserBusArrayGet(void *UserBus,const char *Key,INT32 Idx)
{
    void *Lock;
    void *Arr;
    void *V;
    char Tmp[TMP_MAX_BUFFER];

    V = NULL;
    if ( NULL==Key )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Key is null.");
        return NULL;
    }
    if ( 0==strlen(Key) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Key is null .");
        return NULL;
    }
    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return NULL;
        }
    }
    while( 1 )
    {
        if ( NULL==(Arr=YSVarHashGet(UserBus,Key)) )
        {
            break;
        }
        V = YSVarArrayGet(Arr,Idx);
        break;
    }
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return V;
}

BOOL  YSUserBusDelete(void *UserBus,const char *Key)
{
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    if ( NULL==Key )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args is null.");
        return FALSE;
    }
    Lock = NULL;

    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return FALSE;
        }
    }
    bRtn = YSVarHashDelete(UserBus,Key);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

BOOL  YSUserBusArrayDelete(void *UserBus,const char *Key,INT32 Idx)
{
    void *Arr;
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    if ( NULL==Key )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args is null.");
        return FALSE;
    }
    Lock = NULL;

    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return FALSE;
        }
    }
    bRtn = FALSE;
    if ( NULL!=(Arr=YSVarHashGet(UserBus,Key)) )
    {
        bRtn = YSVarArrayDelete(Arr,FECAL_MAX(0,Idx));
    }
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return bRtn;
}

BOOL  YSUserBusAddValue(void *UserBus,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    return YSUserBusArrayAddValue(UserBus,Key,0,V,Clone,Free,Show,Pack);
}

BOOL  YSUserBusArrayAddValue(void *UserBus,const char *Key,INT32 Idx \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    void *Obj;
    char Tmp[TMP_MAX_BUFFER];

    if ( NULL==(Obj=YSVarObjectSave2(Key,V,Clone,Free,Show,Pack)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSVarObjectSave2.");
        return FALSE;
    }
    if ( !YSUserBusArrayAddVar(UserBus,Idx,Obj) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSUserBusArrayAddVar.");
        YSVarObjectFree(Obj);
        return FALSE;
    }
    return TRUE;
}

BOOL  YSUserBusAddString(void *UserBus,const char *Key \
    ,const char *Str,INT32 Len)
{
    return YSUserBusArrayAddString(UserBus,Key,0,Str,Len);
}

BOOL  YSUserBusArrayAddString(void *UserBus,const char *Key,INT32 Idx \
    ,const char *Str,INT32 Len)
{
    void *Obj;
    char Tmp[TMP_MAX_BUFFER];

    if ( NULL==(Obj=YSVarStringSave2(Key,(void *)Str,Len)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSVarStringSave2.");
        return FALSE;
    }
    if ( !YSUserBusArrayAddVar(UserBus,Idx,Obj) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSUserBusArrayAddVar.");
        YSVarObjectFree(Obj);
        return FALSE;
    }
    return TRUE;
}

BOOL  YSUserBusAddInt32(void *UserBus,const char *Key,INT32 n)
{
    return YSUserBusArrayAddInt32(UserBus,Key,0,n);
}

BOOL  YSUserBusArrayAddInt32(void *UserBus,const char *Key,INT32 Idx,INT32 n)
{
    void *Obj;
    char Tmp[TMP_MAX_BUFFER];

    if ( NULL==(Obj=YSVarInt32Save2(Key,n)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSVarInt32Save2.");
        return FALSE;
    }
    if ( !YSUserBusArrayAddVar(UserBus,Idx,Obj) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSUserBusArrayAddVar.");
        YSVarObjectFree(Obj);
        return FALSE;
    }
    return TRUE;
}

BOOL  YSUserBusAddVar(void *UserBus,void *V)
{
    return YSUserBusArrayAddVar(UserBus,0,V);
}

BOOL  YSUserBusArrayAddVar(void *UserBus,INT32 Idx,void *V)
{
    void *Lock;
    void *Key;
    void *Arr;
    void *NArr;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    bRtn = FALSE;
    Lock = NULL;
    Arr = NULL;
    NArr = NULL;
    
    if ( !YSVarIsInit(V)||!YSVarIsInit2(UserBus,VARTYPE_MEM_VT_HASH) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Var is not ready.");
        return FALSE;
    }
    if ( NULL==(Key=YSVarGetKey(V)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Key is null.");
        return FALSE;
    }
    if ( 0==strlen(Key) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Key is null .");
        return FALSE;
    }
    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return bRtn;
        }
    }
    while( 1 )
    {
        if ( NULL==(Arr=YSVarHashGet(UserBus,Key)) )
        {
            if ( NULL==(NArr=YSVarArrayNew_Key(0,Key)) )
            {
                YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Error : Failed at YSVarArrayNew.");
                break;
            }
            if ( !YSVarHashAdd(UserBus,NArr) )
            {
                YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Error : Failed at YSVarHashAdd.");
                break;
            }
            Arr = NArr;
        }
        if ( !YSVarArrayInsert(Arr,FECAL_MAX(0,Idx),V) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarArrayInsert.");
            break;
        }
        NArr = NULL;
        bRtn = TRUE;
        break;
    }
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    YSVarArrayFree(NArr);
    NArr = NULL;
    return bRtn;
}

INT32 YSUserBusGetLen(void *UserBus)
{
    void *Lock;
    INT32 iRtn;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return YSRTN_ERAPP_ARG;
        }
    }
    iRtn = YSVarHashGetLen(UserBus);
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return iRtn;
}

INT32 YSUserBusArrayGetLen(void *UserBus,const char *Key)
{
    void *Lock;
    void *Arr;
    INT32 iRtn;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;
    if ( NULL==Key )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Key is null.");
        return FERTN_ERAPP_ARG;
    }
    if ( 0==strlen(Key) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Key is null .");
        return FERTN_ERAPP_ARG;
    }

    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return YSRTN_ERAPP_ARG;
        }
    }
    iRtn = 0;
    if ( NULL!=(Arr=YSVarArrayGetByKey(UserBus,Key,strlen(Key))) )
    {
        iRtn = YSVarArrayGetLen(Arr);
    }
    if ( NULL!=Lock )
    {
        YSPLockWriteUnLock(Lock);
    }
    return iRtn;
}

BOOL  YSUserBusReplaceValue(void *UserBus,const char *Key,void *V)
{
    return YSUserBusArrayReplaceValue(UserBus,Key,0,V);
}

BOOL  YSUserBusArrayReplaceValue(void *UserBus \
    ,const char *Key,INT32 Idx,void *V)
{
    void *Arr;
    void *Lock;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    Lock = NULL;

    if ( NULL!=(Lock=YSVarGetRes(UserBus)) )
    {
        if ( YSRTN_OK!=YSPLockWriteLock(Lock) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPLockWriteLock.");
            return FALSE;
        }
    }
    bRtn = FALSE;
    if ( NULL!=(Arr=YSVarHashGet(UserBus,Key)) )
    {
        bRtn = YSVarArrayReplaceValue(Arr,Idx,V);
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

