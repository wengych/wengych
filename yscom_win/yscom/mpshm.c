/***************************************************************************/
/**[File Name    ]mpshm.c                                                 **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for share memory ( hash )                   **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __OS_LINUX__
BOOL  YSMPShmUpdate(const char *Key,void *MH)
{
    INT32 Id;
    INT32 L1;
    INT32 L2;
    struct shmid_ds ds;
    void *Shm;
    BOOL bRtn;
    BOOL Flag;
    char Tmp[YSAPP_TMP_LEN];
    if ( !YSMPIsInit(MH) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : MH is not ready.");
        return FALSE;
    }
    Shm = NULL;
    bRtn = FALSE;
    Flag = FALSE;
    while( 1 )
    {
        while( 1 )
        {
            if ( -1==(Id=FEShmGetId(Key)) )
            {
                YSTracesWarn(YSAppArgsGetLogArgs() \
                    ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Warnning : Failed at FEShmGetId.");
                Flag = TRUE;
                break;
            }
            memset(&ds,0,sizeof(ds));
            if ( !FEShmGetStatById(Id,&ds,sizeof(ds)) )
            {
                YSTracesWarn(YSAppArgsGetLogArgs() \
                    ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Warnning : Failed at FEShmGetStatById.");
                Flag = TRUE;
                break;
            }
            if ( ds.shm_segsz<YSMP_MEM_SIZE(MH) )
            {
                YSTracesInfo(YSAppArgsGetLogArgs() \
                    ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Info : Recreate share memory(%d<%s)." \
                    ,ds.shm_segsz,YSMP_MEM_SIZE(MH));
                FEShmDestroyById(Id);
                Flag = TRUE;
                break;
            }
            if ( NULL==(Shm=FEShmWriteGetById(Id)) )
            {
                YSTracesWarn(YSAppArgsGetLogArgs() \
                    ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Warnning : Failed at FEShmWriteGetById.");
                Flag = TRUE;
                break;
            }
            break;
        }
        if ( Flag )
        {
            if ( NULL==(Shm=FEShmNew(Key,YSMP_MEM_SIZE(MH))) )
            {
                YSTracesError(YSAppArgsGetLogArgs() \
                    ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Error: Failed at FEShmNew.");
                break;
            }
            memset(&ds,0,sizeof(ds));
            if ( !FEShmGetStatByKey(Key,&ds,sizeof(ds)) )
            {
                YSTracesError(YSAppArgsGetLogArgs() \
                    ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Error: Failed at FEShmGetStatByKey.");
                break;
            }
        }
        memset(Shm,0,YSMP_MEM_SIZE(MH));
        if ( 0>=(L1=YSVarBinGetLen(YSMP_MEM_IBUF(MH))) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error: Failed at YSVarBinGetLen.");
            break;
        }
        if ( 0>=(L2=YSVarBinGetLen(YSMP_MEM_CBUF(MH))) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error: Failed at YSVarBinGetLen.");
            break;
        }
        memcpy(((BYTE*)Shm),YSVarBinGet(YSMP_MEM_IBUF(MH)),L1);
        memcpy(((BYTE*)Shm)+L1,YSVarBinGet(YSMP_MEM_CBUF(MH)),L2);

        bRtn = TRUE;
        break;
    }
    return bRtn;
}

void *YSMPCloneFromShm(const char *Key)
{
    INT32 Id;
    struct shmid_ds ds;
    void *Shm;
    void *MHS;
    BOOL bRtn;
    char Tmp[YSAPP_TMP_LEN];
    if ( 0>(Id=FEShmGetId(Key)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at FEShmGetId.");
        return FALSE;
    }

    memset(&ds,0,sizeof(ds));
    if ( !FEShmGetStatById(Id,&ds,sizeof(ds)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at FEShmGetStatById(%d).\n",Id);
        return FALSE;
    }
    if ( NULL==(Shm=FEShmReadGetById(Id)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at FEShmReadGetByKey(%d).",Id);
        return FALSE;
    }
    MHS = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MHS=YSMPCloneFromMem(Shm,ds.shm_segsz)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSMPCloneFromMem(%d).",Id);
            break;
        }
        YSMP_MEM_ST(MHS) = YSMP_ST_SHM;
        memcpy(&(YSMP_MEM_DS(MHS)),&ds,sizeof(ds));
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        FEShmFree(Shm);
        Shm = NULL;
        YSMPFree(MHS);
        MHS = NULL;
    }
    return MHS;
}
#endif

#ifdef __cplusplus
}
#endif

