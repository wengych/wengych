/***************************************************************************/
/**[File Name    ]mhash.c                                                 **/
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

BOOL  YSMHashIsInit(void *MH)
{
    if ( NULL==MH )
    {
        return FALSE;
    }
    return YSLUCK_ISINIT(YSMHASH_MEM_LUCK(MH));
}

BOOL  YSMHashPackBase(void *IBuf,INT32 Idx,INT32 Len)
{
    void *V;
    INT32 L;
    if ( !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        || ( (0>Idx)||(YSMHASH_HEAD_BASE<=Idx) ) \
        || (0>Len) )
    {
        return FALSE;
    }
    if ( NULL==(V=YSVarBinGet(IBuf)) )
    {
        return FALSE;
    }
    L = YSVarBinGetLen(IBuf);
    if ( YSMHASHHEAD_ST_SIZE>L )
    {
        return FALSE;
    }
    *(INT32 *)(YSMHASHHEAD_MEM_IDX_ADDR(V,Idx)) = L-YSMHASHHEAD_ST_SIZE;
    FEEndianToNet(YSMHASHHEAD_MEM_IDX_ADDR(V,Idx),INT32_SIZE);
    *(INT32 *)(YSMHASHHEAD_MEM_IDX_LEN(V,Idx)) = Len;
    FEEndianToNet(YSMHASHHEAD_MEM_IDX_LEN(V,Idx),INT32_SIZE);
    return TRUE;
}

BOOL  YSMHashPackIdx(void *IBuf,const char *Key,void *CBuf)
{
    tYSMHashIdx IB;
    INT32 Len;
    if ( !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        || (NULL==Key) \
        || !YSVarIsInit2(CBuf,VARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( 0==(Len=strlen(Key)) )
    {
        return FALSE;
    }
    memset(&IB,0,sizeof(IB));
    *(INT32 *)(YSMHASHIDX_MEM_HK(&IB)) = FEHashCalKey(Key,Len);
    FEEndianToNet(YSMHASHIDX_MEM_HK(&IB),INT32_SIZE);
    *(INT32 *)(YSMHASHIDX_MEM_A(&IB)) = YSVarBinGetLen(CBuf);
    FEEndianToNet(YSMHASHIDX_MEM_A(&IB),INT32_SIZE);
    MEMNCPY(YSMHASHIDX_MEM_K(&IB),Key,sizeof(YSMHASHIDX_MEM_K(&IB)),Len);
    return YSVarBinCat(IBuf,&IB,sizeof(IB));
}

BOOL  YSMHashUnPackIdx(void *MH,INT32 Idx,tYSMHashIdx *IB)
{
    if ( !YSMHashIsInit(MH)||(0>Idx)||(NULL==IB) )
    {
        return FALSE;
    }
    if ( YSMHASH_MEM_LEN(MH)<=Idx )
    {
        return FALSE;
    }
    memset(IB,0,sizeof(tYSMHashIdx));
    memcpy(IB,((BYTE*)YSMHASH_MEM_IDX(MH))+Idx*YSMHASHIDX_ST_SIZE \
        ,YSMHASHIDX_ST_SIZE);
    FEEndianToHost(YSMHASHIDX_MEM_HK(IB),INT32_SIZE);
    FEEndianToHost(YSMHASHIDX_MEM_A(IB),INT32_SIZE);
    return TRUE;
}

void  YSMHashFree(void *MH)
{
    if ( !YSMHashIsInit(MH) )
    {
        return;
    }
    YSMHASH_INIT_LUCK_NOT(MH);
    YSMHASH_MEM_HEAD(MH) = NULL;
    YSMHASH_MEM_IDX(MH) = NULL;
    YSMHASH_MEM_CTX(MH) = NULL;

    if ( YSMHASH_ST_MEM==YSMHASH_MEM_ST(MH) )
    {
        if ( NULL!=YSMHASH_MEM_SHM(MH) )
        {
            free(YSMHASH_MEM_SHM(MH));
            YSMHASH_MEM_SHM(MH) = NULL;
        }
    }
    else if ( YSMHASH_ST_STRUCT==YSMHASH_MEM_ST(MH) )
    {
        if ( NULL!=YSMHASH_MEM_IBUF(MH) )
        {
            YSVarFree(YSMHASH_MEM_IBUF(MH));
        }
        if ( NULL!=YSMHASH_MEM_CBUF(MH) )
        {
            YSVarFree(YSMHASH_MEM_CBUF(MH));
        }
    }
#ifdef __OS_LINUX__
    else if ( YSMHASH_ST_SHM==YSMHASH_MEM_ST(MH) )
    {
        if ( NULL!=YSMHASH_MEM_SHM(MH) )
        {
            FEShmFree(YSMHASH_MEM_SHM(MH));
            memset(&(YSMHASH_MEM_DS(MH)),0,sizeof(YSMHASH_MEM_DS(MH)));
        }
    }
#endif
    YSMHASH_MEM_IBUF(MH) = NULL;
    YSMHASH_MEM_CBUF(MH) = NULL;
    YSMHASH_MEM_SHM(MH) = NULL;

    YSMHASH_MEM_LEN(MH) = 0;
    YSMHASH_MEM_ILEN(MH) = 0;
    YSMHASH_MEM_CLEN(MH) = 0;
    memset(YSMHASH_MEM_IIDX(MH),0,sizeof(YSMHASH_MEM_IIDX(MH)));
    free(MH);
}

void *YSMHashNew()
{
    tYSMHashHead HS;
    tYSMHashStruct *a;
    void *MH;
    BOOL bRtn;
    if ( NULL==(MH=malloc(YSMHASH_ST_SIZE)) )
    {
        return NULL;
    }
    a = (tYSMHashStruct*)MH;
    memset(MH,0,YSMHASH_ST_SIZE);
    bRtn = FALSE;
    while( 1 )
    {
        YSMHASH_MEM_ST(MH) = YSMHASH_ST_STRUCT;
        if ( NULL==(YSMHASH_MEM_IBUF(MH)=YSVarBinNew()) )
        {
            break;
        }
        memset(&HS,0,sizeof(HS));
        YSMHASHHEAD_INIT_LUCK(&HS);
        YSMHASHHEAD_MEM_STA(&HS) = YSAPP_STATUS_NOT;
        if ( !YSVarBinCat(YSMHASH_MEM_IBUF(MH),(void *)(&HS),sizeof(HS)) )
        {
            break;
        }
        if ( NULL==(YSMHASH_MEM_CBUF(MH)=YSVarBinNew()) )
        {
            break;
        }
        YSMHASH_INIT_LUCK(MH);
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSMHashFree(MH);
        MH = NULL;
    }
    return MH;
}

void  YSMHashShow(void *MH,INT32 T,void *Buf)
{
    char Log[YSAPP_TMP_LEN];
    char Tab[BUFSIZE_64];
    INT32 i;
    INT32 L;

    if ( !YSMHashIsInit(MH)||!YSVarIsInit2(Buf,VARTYPE_MEM_VT_BIN) )
    {
        return ;
    }
    memset(Tab,0,sizeof(Tab));
    YSVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    snprintf(Log,sizeof(Log),"%s<ShmSize>%d</ShmSize>\n"
         "%s<StructType>%s</StructType>\n"
         "%s<CtxType>%s</CtxType>\n"
         "%s<Len>%d</Len>\n"
         "%s<IdxLen>%d</IdxLen>\n"
         "%s<CtxLen>%d</CtxLen>\n"
         "%s<Idx>\n"
        ,Tab,YSMHASH_MEM_SIZE(MH) \
        ,Tab,YSMHASH_ST_STR(MH) \
        ,Tab,YSMHASH_CT_STR(MH) \
        ,Tab,YSMHASH_MEM_LEN(MH) \
        ,Tab,YSMHASH_MEM_ILEN(MH) \
        ,Tab,YSMHASH_MEM_CLEN(MH) \
        ,Tab);
    YSVarBinCat(Buf,Log,strlen(Log));
    memset(Log,0,sizeof(Log));
    L = 0;
    for ( i=0;i<YSMHASH_HEAD_BASE;i++ )
    {
        snprintf(Log+L,sizeof(Log)-L,"%s <Addr>%d</Addr>\n"
             "%s <Len>%d</Len>\n" \
            ,Tab,YSMHASH_MEM_IIDX_ADDR(MH,i) \
            ,Tab,YSMHASH_MEM_IIDX_LEN(MH,i));
        L += strlen(Log+L);
    }
    snprintf(Log+L,sizeof(Log)-L,"%s</Idx>\n",Tab);
    L += strlen(Log+L);
    YSVarBinCat(Buf,Log,strlen(Log));
}

BOOL  YSMHashMallocBuf(void *MH,INT32 NewSize,BOOL Flag)
{
    BOOL bRtn;
    if ( !YSMHashIsInit(MH) )
    {
        return FALSE;
    }
    if ( Flag )
    {
        bRtn = YSVarBinMalloc2(YSMHASH_MEM_IBUF(MH),NewSize);
        if ( bRtn )
        {
            YSMHASH_MEM_HEAD(MH) = YSVarBinGet(YSMHASH_MEM_IBUF(MH));
            YSMHASH_MEM_IDX(MH) = ((BYTE*)YSMHASH_MEM_HEAD(MH)) \
                +YSMHASHHEAD_ST_SIZE;
        }
    }
    else
    {
        bRtn = YSVarBinMalloc2(YSMHASH_MEM_CBUF(MH),NewSize);
        if ( bRtn )
        {
            YSMHASH_MEM_CTX(MH) = YSVarBinGet(YSMHASH_MEM_CBUF(MH));
        }
    }
    return bRtn;
}

void *YSMHashClone(void *MHS)
{
    void *MH;
    BOOL bRtn;
    if ( !YSMHashIsInit(MHS) )
    {
        return NULL;
    }
    MH = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MH=YSMHashNew()) )
        {
            break;
        }
        YSMHashMallocBuf(MH,YSMHASHHEAD_ST_SIZE+YSMHASH_MEM_ILEN(MHS),TRUE);
        YSMHashMallocBuf(MH,YSMHASH_MEM_CLEN(MHS),FALSE);
        YSMHASH_MEM_SIZE(MH) = YSMHASH_MEM_SIZE(MHS);
        YSMHASH_MEM_ST(MH) = YSMHASH_ST_STRUCT;
        YSMHASH_MEM_CT(MH) = YSMHASH_MEM_CT(MHS);
        if ( !YSVarBinCat(YSMHASH_MEM_IBUF(MH) \
            ,YSMHASH_MEM_HEAD(MHS),YSMHASHHEAD_ST_SIZE) )
        {
            break;
        }
        if ( !YSVarBinCat(YSMHASH_MEM_IBUF(MH) \
            ,YSMHASH_MEM_IDX(MHS),YSMHASH_MEM_ILEN(MHS)) )
        {
            break;
        }
        if ( !YSVarBinCat(YSMHASH_MEM_CBUF(MH) \
            ,YSMHASH_MEM_CTX(MHS),YSMHASH_MEM_CLEN(MHS)) )
        {
            break;
        }
        YSMHASH_MEM_SHM(MH) = NULL;
#ifdef __OS_LINUX__
        memset(&(YSMHASH_MEM_DS(MH)),0,sizeof(YSMHASH_MEM_DS(MH)));
#endif
        YSMHASH_MEM_LEN(MH) = YSMHASH_MEM_LEN(MHS);
        YSMHASH_MEM_ILEN(MH) = YSMHASH_MEM_ILEN(MHS);
        YSMHASH_MEM_CLEN(MH) = YSMHASH_MEM_CLEN(MHS);
        memcpy(YSMHASH_MEM_IIDX(MH) \
            ,YSMHASH_MEM_IIDX(MHS),sizeof(YSMHASH_MEM_IIDX(MHS)));
        YSMHASH_INIT_LUCK(MH);
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSMHashFree(MH);
    }
    return MH;
}

#ifdef __OS_LINUX__
BOOL  YSMHashDictToShm(const char *Key,void *Var)
{
    void *Head;
    void *MH;
    void *MHS;
    BOOL bRtn;
    if ( !YSVarIsInit2(Var,VARTYPE_MEM_VT_HASH) )
    {
        return FALSE;
    }
    MH = NULL;
    MHS = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MH=YSMHashNew()) )
        {
            break;
        }
        if ( !YSDictHashToMem(Var,YSMHASH_MEM_IBUF(MH),YSMHASH_MEM_CBUF(MH) \
            ,YSMHashPackBase,YSMHashPackIdx) )
        {
            break;
        }
        YSMHashMallocBuf(MH,0,TRUE);
        YSMHashMallocBuf(MH,0,FALSE);
        YSMHASH_MEM_SIZE(MH) = YSVarBinGetLen(YSMHASH_MEM_IBUF(MH)) \
            + YSVarBinGetLen(YSMHASH_MEM_CBUF(MH));

        Head = YSMHASH_MEM_HEAD(MH);
        *(INT32*)YSMHASHHEAD_MEM_SIZE(Head) = YSMHASH_MEM_SIZE(MH);
        FEEndianToNet(YSMHASHHEAD_MEM_SIZE(Head),INT32_SIZE);
        YSMHASHHEAD_MEM_STA(Head) = YSAPP_STATUS_RUNNING;
        YSMHASHHEAD_MEM_TYPE(Head) = YSMHASH_CT_DICT;
        if ( NULL!=YSVarGetKey(Var) )
        {
            snprintf(YSMHASHHEAD_MEM_VER(Head) \
                ,sizeof(YSMHASHHEAD_MEM_VER(Head))
                ,"%s",YSVarGetKey(Var));
        }
        *(INT32*)YSMHASHHEAD_MEM_LEN(Head) = YSVarHashGetLen(Var);
        FEEndianToNet(YSMHASHHEAD_MEM_LEN(Head),INT32_SIZE);
        *(INT32*)YSMHASHHEAD_MEM_ILEN(Head) = \
            YSVarBinGetLen(YSMHASH_MEM_IBUF(MH)) - YSMHASHHEAD_ST_SIZE;
        FEEndianToNet(YSMHASHHEAD_MEM_ILEN(Head),INT32_SIZE);
        *(INT32*)YSMHASHHEAD_MEM_CLEN(Head) = \
            YSVarBinGetLen(YSMHASH_MEM_CBUF(MH));
        FEEndianToNet(YSMHASHHEAD_MEM_CLEN(Head),INT32_SIZE);
        YSMHASHHEAD_INIT_LUCK(Head);

        if ( !YSMHashShmUpdate(Key,MH) )
        {
            break;
        }

        bRtn = TRUE;
        break;
    }
    YSMHashFree(MH);
    MH = NULL;
    return bRtn;
}

BOOL  YSMHashShmToDict(void **Var,const char *Key)
{
    void *MHS;
    BOOL bRtn;
    if ( NULL==Var )
    {
        return FALSE;
    }
    MHS = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MHS=YSMHHashCloneFromShm(Key)) )
        {
            break;
        }
        if ( !YSDictMemToHash(Var,MHS,YSMHashUnPackIdx) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    YSMHashFree(MHS);
    MHS = NULL;
    return bRtn;
}
#endif

BOOL  YSMHashDictToMem(void **MHS,INT32 Size,void *Var)
{
    void *Head;
    void *MH;
    BOOL bRtn;
    if ( (NULL==MHS)||(YSMHASH_ST_SIZE>Size) \
        ||!YSVarIsInit2(Var,VARTYPE_MEM_VT_HASH) )
    {
        return FALSE;
    }
    MH = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MH=YSMHashNew()) )
        {
            break;
        }
        if ( !YSDictHashToMem(Var,YSMHASH_MEM_IBUF(MH),YSMHASH_MEM_CBUF(MH) \
            ,YSMHashPackBase,YSMHashPackIdx) )
        {
            break;
        }
        YSMHashMallocBuf(MH,0,TRUE);
        YSMHashMallocBuf(MH,0,FALSE);
        YSMHASH_MEM_SIZE(MH) = YSVarBinGetLen(YSMHASH_MEM_IBUF(MH)) \
            + YSVarBinGetLen(YSMHASH_MEM_CBUF(MH));
        if ( NULL!=YSVarGetKey(Var) )
        {
            snprintf(YSMHASHHEAD_MEM_VER(MH),sizeof(YSMHASHHEAD_MEM_VER(MH)) \
                ,"%s",YSVarGetKey(Var));
        }

        Head = YSMHASH_MEM_HEAD(MH);
        *(INT32*)YSMHASHHEAD_MEM_SIZE(Head) = YSMHASH_MEM_SIZE(MH);
        FEEndianToNet(YSMHASHHEAD_MEM_SIZE(Head),INT32_SIZE);
        YSMHASHHEAD_MEM_STA(Head) = YSAPP_STATUS_RUNNING;
        YSMHASHHEAD_MEM_TYPE(Head) = YSMHASH_CT_DICT;
        *(INT32*)YSMHASHHEAD_MEM_LEN(Head) = YSVarHashGetLen(Var);
        FEEndianToNet(YSMHASHHEAD_MEM_LEN(Head),INT32_SIZE);
        *(INT32*)YSMHASHHEAD_MEM_ILEN(Head) = \
            YSVarBinGetLen(YSMHASH_MEM_IBUF(MH)) - YSMHASHHEAD_ST_SIZE;
        FEEndianToNet(YSMHASHHEAD_MEM_ILEN(Head),INT32_SIZE);
        *(INT32*)YSMHASHHEAD_MEM_CLEN(Head) = \
            YSVarBinGetLen(YSMHASH_MEM_CBUF(MH));
        FEEndianToNet(YSMHASHHEAD_MEM_CLEN(Head),INT32_SIZE);
        YSMHASHHEAD_INIT_LUCK(Head);
        *MHS = MH;
        MH = NULL;
        bRtn = TRUE;
        break;
    }
    YSMHashFree(MH);
    MH = NULL;
    return bRtn;
}

BOOL  YSMHashMemToDict(void **Var,void *Mem,INT32 Len)
{
    void *MHS;
    BOOL bRtn;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MHS=YSMHHashCloneFromMem(Mem,Len)) )
        {
            break;
        }
        if ( !YSDictMemToHash(Var,MHS,YSMHashUnPackIdx) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    YSMHashFree(MHS);
    MHS = NULL;
    return bRtn;
}

#ifdef __cplusplus
}
#endif

