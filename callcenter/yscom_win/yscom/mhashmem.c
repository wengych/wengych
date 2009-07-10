/***************************************************************************/
/**[File Name    ]mhashmem.c                                              **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for memory ( hash )                         **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <mhash.h>

#ifdef __cplusplus
extern "C"{
#endif

BOOL  YSMHashMemIsInit(void *Shm)
{
    if ( NULL==Shm )
    {
        return FALSE;
    }
    return YSLUCK_ISINIT((*(INT32*)YSMHASHHEAD_MEM_LUCK(Shm)));
}

void *YSMHHashCloneFromMem(void *Mem,INT32 Len)
{
    void *MHS;
    INT32 i;
    BOOL bRtn;

    if ( (NULL==Mem)||(YSMHASHHEAD_ST_SIZE>Len) )
    {
        return NULL;
    }
    MHS = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( !YSMHashMemIsInit(Mem) )
        {
            break;
        }
        if ( NULL==(MHS=malloc(YSMHASH_ST_SIZE)) )
        {
            break;
        }
        memset(MHS,0,YSMHASH_ST_SIZE);
        YSMHASH_INIT_LUCK(MHS);
        YSMHASH_MEM_SIZE(MHS) = *(INT32*)YSMHASHHEAD_MEM_SIZE(Mem);
        FEEndianToHost((void *)(&YSMHASH_MEM_SIZE(MHS)),INT32_SIZE);
        YSMHASH_MEM_ST(MHS) = YSMHASH_ST_MEM;
        YSMHASH_MEM_CT(MHS) = YSMHASHHEAD_MEM_TYPE(Mem);

        memcpy(YSMHASH_MEM_VER(MHS),YSMHASHHEAD_MEM_VER(Mem) \
            ,sizeof(YSMHASH_MEM_VER(MHS)));
        YSMHASH_MEM_LEN(MHS) = *(INT32*)YSMHASHHEAD_MEM_LEN(Mem);
        FEEndianToHost((void *)(&YSMHASH_MEM_LEN(MHS)),INT32_SIZE);
        YSMHASH_MEM_ILEN(MHS) = *(INT32*)YSMHASHHEAD_MEM_ILEN(Mem);
        FEEndianToHost((void *)(&YSMHASH_MEM_ILEN(MHS)),INT32_SIZE);
        YSMHASH_MEM_CLEN(MHS) = *(INT32*)YSMHASHHEAD_MEM_CLEN(Mem);
        FEEndianToHost((void *)(&YSMHASH_MEM_CLEN(MHS)),INT32_SIZE);
        for ( i=0;i<YSMHASH_HEAD_BASE;i++ )
        {
            YSMHASH_MEM_IIDX_ADDR(MHS,i) = \
                *(INT32*)YSMHASHHEAD_MEM_IDX_ADDR(Mem,i);
            FEEndianToHost((void *)(&YSMHASH_MEM_IIDX_ADDR(MHS,i)),INT32_SIZE);
            YSMHASH_MEM_IIDX_LEN(MHS,i) = \
                *(INT32*)YSMHASHHEAD_MEM_IDX_LEN(Mem,i);
            FEEndianToHost((void *)(&YSMHASH_MEM_IIDX_LEN(MHS,i)),INT32_SIZE);
        }
        
        YSMHASH_MEM_HEAD(MHS) = Mem;
        YSMHASH_MEM_IDX(MHS) = ((BYTE*)Mem)+YSMHASHHEAD_ST_SIZE;
        YSMHASH_MEM_CTX(MHS) = ((BYTE*)YSMHASH_MEM_IDX(MHS)) \
            +YSMHASH_MEM_ILEN(MHS);
        YSMHASH_MEM_IBUF(MHS) = NULL;
        YSMHASH_MEM_CBUF(MHS) = NULL;
        YSMHASH_MEM_SHM(MHS) = Mem;
        
        if ( Len<YSMHASH_MEM_SIZE(MHS) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSMHashFree(MHS);
        MHS = NULL;
    }
    return MHS;
}

#ifdef __cplusplus
}
#endif

