/***************************************************************************/
/**[File Name    ]mpmem.c                                                 **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for memory ( hash )                         **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif

BOOL  YSMPMemIsInit(void *Shm)
{
    if ( NULL==Shm )
    {
        return FALSE;
    }
    return YSLUCK_ISINIT((*(INT32*)YSMPHEAD_MEM_LUCK(Shm)));
}

void *YSMPCloneFromMem(void *Mem,INT32 Len)
{
    void *MHS;
    INT32 i;
    BOOL bRtn;

    if ( (NULL==Mem)||(YSMPHEAD_ST_SIZE>Len) )
    {
        return NULL;
    }
    MHS = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( !YSMPMemIsInit(Mem) )
        {
            break;
        }
        if ( NULL==(MHS=malloc(YSMP_ST_SIZE)) )
        {
            break;
        }
        memset(MHS,0,YSMP_ST_SIZE);
        YSMP_INIT_LUCK(MHS);
        YSMP_MEM_SIZE(MHS) = *(INT32*)YSMPHEAD_MEM_SIZE(Mem);
        FEEndianToHost((void *)(&YSMP_MEM_SIZE(MHS)),INT32_SIZE);
        YSMP_MEM_ST(MHS) = YSMP_ST_MEM;
        YSMP_MEM_CT(MHS) = YSMPHEAD_MEM_TYPE(Mem);

        memcpy(YSMP_MEM_VER(MHS),YSMPHEAD_MEM_VER(Mem) \
            ,sizeof(YSMP_MEM_VER(MHS)));
        YSMP_MEM_MAX(MHS) = *(INT32*)YSMPHEAD_MEM_MAX(Mem);
        FEEndianToHost((void *)(&YSMP_MEM_MAX(MHS)),INT32_SIZE);
        YSMP_MEM_LEN(MHS) = *(INT32*)YSMPHEAD_MEM_LEN(Mem);
        FEEndianToHost((void *)(&YSMP_MEM_LEN(MHS)),INT32_SIZE);
        YSMP_MEM_ILEN(MHS) = *(INT32*)YSMPHEAD_MEM_ILEN(Mem);
        FEEndianToHost((void *)(&YSMP_MEM_ILEN(MHS)),INT32_SIZE);
        YSMP_MEM_CLEN(MHS) = *(INT32*)YSMPHEAD_MEM_CLEN(Mem);
        FEEndianToHost((void *)(&YSMP_MEM_CLEN(MHS)),INT32_SIZE);
        for ( i=0;i<YSMP_HEAD_BASE;i++ )
        {
            YSMP_MEM_IIDX_ADDR(MHS,i) = \
                *(INT32*)YSMPHEAD_MEM_IDX_ADDR(Mem,i);
            FEEndianToHost((void *)(&YSMP_MEM_IIDX_ADDR(MHS,i)),INT32_SIZE);
            YSMP_MEM_IIDX_LEN(MHS,i) = \
                *(INT32*)YSMPHEAD_MEM_IDX_LEN(Mem,i);
            FEEndianToHost((void *)(&YSMP_MEM_IIDX_LEN(MHS,i)),INT32_SIZE);
        }
        
        YSMP_MEM_HEAD(MHS) = Mem;
        YSMP_MEM_IDX(MHS) = ((BYTE*)Mem)+YSMPHEAD_ST_SIZE;
        YSMP_MEM_CTX(MHS) = ((BYTE*)YSMP_MEM_IDX(MHS)) \
            +YSMP_MEM_ILEN(MHS);
        YSMP_MEM_IBUF(MHS) = NULL;
        YSMP_MEM_CBUF(MHS) = NULL;
        YSMP_MEM_SHM(MHS) = Mem;
        
        if ( Len<YSMP_MEM_SIZE(MHS) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSMPFree(MHS);
        MHS = NULL;
    }
    return MHS;
}

#ifdef __cplusplus
}
#endif

