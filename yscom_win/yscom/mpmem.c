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
    return YSLUCK_ISINIT(YSMPHEAD_MEM_LUCK_INT(Shm));
}

void *YSMPCloneFromMem(void *Mem,INT32 Len)
{
    void *MHS;
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
        YSMP_MEM_SIZE(MHS) = YSMPHEAD_MEM_SIZE_INT(Mem);
        FEEndianToHost_Int32(&YSMP_MEM_SIZE(MHS));
        YSMP_MEM_ST(MHS) = YSMP_ST_MEM;
        YSMP_MEM_CT(MHS) = YSMPHEAD_MEM_TYPE(Mem);

        memcpy(YSMP_MEM_VER(MHS),YSMPHEAD_MEM_VER(Mem) \
            ,sizeof(YSMP_MEM_VER(MHS)));
        YSMP_MEM_TIME(MHS) = YSMPHEAD_MEM_TIME_INT(Mem);
        FEEndianToHost_Int32(&YSMP_MEM_TIME(MHS));
        YSMP_MEM_MAX(MHS) = YSMPHEAD_MEM_MAX_INT(Mem);
        FEEndianToHost_Int32(&YSMP_MEM_MAX(MHS));
        YSMP_MEM_LEN(MHS) = YSMPHEAD_MEM_LEN_INT(Mem);
        FEEndianToHost_Int32(&YSMP_MEM_LEN(MHS));
        YSMP_MEM_IDXSIZE(MHS) = YSMPHEAD_MEM_IDXSIZE_INT(Mem);
        FEEndianToHost_Int32(&YSMP_MEM_IDXSIZE(MHS));
        YSMP_MEM_ILEN(MHS) = YSMPHEAD_MEM_ILEN_INT(Mem);
        FEEndianToHost_Int32(&YSMP_MEM_ILEN(MHS));
        YSMP_MEM_CTXSIZE(MHS) = YSMPHEAD_MEM_CTXSIZE_INT(Mem);
        FEEndianToHost_Int32(&YSMP_MEM_CTXSIZE(MHS));
        YSMP_MEM_CLEN(MHS) = YSMPHEAD_MEM_CLEN_INT(Mem);
        FEEndianToHost_Int32(&YSMP_MEM_CLEN(MHS));

        YSMP_MEM_HEAD(MHS) = Mem;
        if ( YSMP_CT_ISHASH(YSMPHEAD_MEM_TYPE(Mem)) )
        {
            YSMP_MEM_IDX(MHS) = \
                ((BYTE*)Mem)+YSMPHEAD_ST_SIZE_CAL(YSMP_MEM_MAX(MHS));
        }
        else
        {
            YSMP_MEM_IDX(MHS) = ((BYTE*)Mem)+YSMPHEAD_ST_SIZE;
        }
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

