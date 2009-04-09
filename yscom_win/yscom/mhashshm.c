/***************************************************************************/
/**[File Name    ]mhashshm.c                                              **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for share memory ( hash )                   **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <mhash.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __OS_LINUX__
BOOL  YSMHashShmUpdate(const char *Key,void *MH)
{
    INT32 L1;
    INT32 L2;
    struct shmid_ds ds;
    INT32 Id;
    void *Shm;
    BOOL bRtn;
    BOOL Flag;
    if ( !YSMHashIsInit(MH) )
    {
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
                Flag = TRUE;
                break;
            }
            memset(&ds,0,sizeof(ds));
            if ( !FEShmGetStatById(Id,&ds,sizeof(ds)) )
            {
                Flag = TRUE;
                break;
            }
            if ( ds.shm_segsz<YSMHASH_MEM_SIZE(MH) )
            {
                FEShmDestroyById(Id);
                Flag = TRUE;
                break;
            }
            if ( NULL==(Shm=FEShmWriteGetById(Id)) )
            {
                Flag = TRUE;
                break;
            }
            break;
        }
        if ( Flag )
        {
            if ( NULL==(Shm=FEShmNew(Key,YSMHASH_MEM_SIZE(MH))) )
            {
                break;
            }
            memset(&ds,0,sizeof(ds));
            if ( !FEShmGetStatByKey(Key,&ds,sizeof(ds)) )
            {
                break;
            }
        }
        memset(Shm,0,YSMHASH_MEM_SIZE(MH));
        if ( 0>=(L1=YSVarBinGetLen(YSMHASH_MEM_IBUF(MH))) )
        {
            break;
        }
        if ( 0>=(L2=YSVarBinGetLen(YSMHASH_MEM_CBUF(MH))) )
        {
            break;
        }
        memcpy(((BYTE*)Shm),YSVarBinGet(YSMHASH_MEM_IBUF(MH)),L1);
        memcpy(((BYTE*)Shm)+L1,YSVarBinGet(YSMHASH_MEM_CBUF(MH)),L2);

        bRtn = TRUE;
        break;
    }
    return bRtn;
}

void *YSMHHashCloneFromShm(const char *Key)
{
    struct shmid_ds ds;
    INT32 Id;
    void *Shm;
    void *MHS;
    BOOL bRtn;
    char Tmp[YSAPP_TMP_LEN];

    if ( 0>(Id=FEShmGetId(Key)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at FEShmGetId.");
        return NULL;
    }
    memset(&ds,0,sizeof(ds));
    if ( !FEShmGetStatById(Id,&ds,sizeof(ds)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at FEShmGetStatById(%s).\n",Key);
        return FALSE;
    }
    if ( NULL==(Shm=FEShmReadGetByKey(Key)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at FEShmReadGetByKey(%s).",Key);
        return FALSE;
    }
    MHS = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MHS=YSMHHashCloneFromMem(Shm,ds.shm_segsz)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSMHHashCloneFromMem(%s).",Key);
            break;
        }
        YSMHASH_MEM_ST(MHS) = YSMHASH_ST_SHM;
        memcpy(&(YSMHASH_MEM_DS(MHS)),&ds,sizeof(ds));
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        FEShmFree(Shm);
        Shm = NULL;
        YSMHashFree(MHS);
        MHS = NULL;
    }
    return MHS;
}
#endif

#ifdef __cplusplus
}
#endif

