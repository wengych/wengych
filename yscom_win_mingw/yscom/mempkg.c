/***************************************************************************/
/**[File Name    ]mempkg.c                                                **/
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
BOOL  YSMPShmIsReady(const char *ShmPath)
{
    void *MHS;
    BOOL bRtn;
 
    bRtn = FALSE;
    MHS = NULL;
    while( 1 )
    {
        if ( NULL==(MHS=YSMPCloneFromShm(ShmPath)) )
        {
            break;
        }
        bRtn = YSMPIsInit(MHS);
        break;
    }
    YSMPFree(MHS);
    MHS = NULL;
    return bRtn;
}
#endif

BOOL  YSMPIsInit(void *MH)
{
    if ( NULL==MH )
    {
        return FALSE;
    }
    return YSLUCK_ISINIT(YSMP_MEM_LUCK(MH));
}

BOOL  YSMPIsMemInit(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return FALSE;
    }
    return RTNCODE_CMPBOOL(YSMP_ST_MEM==YSMP_MEM_ST(MH));
}

BOOL  YSMPIsShmInit(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return FALSE;
    }
    return RTNCODE_CMPBOOL(YSMP_ST_SHM==YSMP_MEM_ST(MH));
}

BOOL  YSMPIsStructInit(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return FALSE;
    }
    return RTNCODE_CMPBOOL(YSMP_ST_STRUCT==YSMP_MEM_ST(MH));
}

INT32 YSMPGetHeadSize()
{
    return YSMPHEAD_ST_SIZE;
}

INT32 YSMPGetHeadSize2(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return RTNCODE_ER;
    }
fprintf(stderr,"---YSMPGetHeadSize2,Size=%d,Max=%d.\n",YSMPHEAD_ST_SIZE_CAL(YSMP_MEM_MAX(MH)),YSMP_MEM_MAX(MH));
    return YSMP_CT_ISHASH(YSMP_MEM_CT(MH)) \
        ?YSMPHEAD_ST_SIZE_CAL(YSMP_MEM_MAX(MH)) \
        :YSMPHEAD_ST_SIZE;
}
 
void *YSMPGetHead(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return NULL;
    }
    return YSMP_MEM_HEAD(MH);
}

void *YSMPGetIdx(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return NULL;
    }
    return YSMP_MEM_IDX(MH);
}

void *YSMPGetCtx(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return NULL;
    }
    return YSMP_MEM_CTX(MH);
}

void *YSMPGetIBuf(void *MH)
{
    if ( !YSMPIsMemInit(MH) )
    {
        return NULL;
    }
    return YSMP_MEM_IBUF(MH);
}

void *YSMPGetCBuf(void *MH)
{
    if ( !YSMPIsMemInit(MH) )
    {
        return NULL;
    }
    return YSMP_MEM_CBUF(MH);
}

INT32 YSMPGetSize(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return RTNCODE_ER;
    }
    return YSMP_MEM_SIZE(MH);
}

INT32 YSMPGetMax(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return RTNCODE_ER;
    }
    return YSMP_MEM_MAX(MH);
}

INT32 YSMPGetLen(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return RTNCODE_ER;
    }
    return YSMP_MEM_LEN(MH);
}

INT32 YSMPGetIdxSize(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return RTNCODE_ER;
    }
    return YSMP_MEM_IDXSIZE(MH);
}

INT32 YSMPGetIdxLen(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return RTNCODE_ER;
    }
    return YSMP_MEM_ILEN(MH);
}

INT32 YSMPGetCtxSize(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return RTNCODE_ER;
    }
    return YSMP_MEM_CTXSIZE(MH);
}

INT32 YSMPGetCtxLen(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return RTNCODE_ER;
    }
    return YSMP_MEM_CLEN(MH);
}

void *YSMPNew()
{
    tYSMPHead HS;
    tYSMPStruct *a;
    void *MH;
    BOOL bRtn;
    if ( NULL==(MH=malloc(YSMP_ST_SIZE)) )
    {
        return NULL;
    }
    a = (tYSMPStruct*)MH;
    memset(MH,0,YSMP_ST_SIZE);
    bRtn = FALSE;
    while( 1 )
    {
        YSMP_MEM_ST(MH) = YSMP_ST_STRUCT;
        if ( NULL==(YSMP_MEM_IBUF(MH)=YSVarBinNew()) )
        {
            break;
        }
        memset(&HS,0,sizeof(HS));
        YSMPHEAD_INIT_LUCK(&HS);
        YSMPHEAD_MEM_STA(&HS) = YSAPP_STATUS_NOT;
        if ( !YSVarBinCat(YSMP_MEM_IBUF(MH),(void *)(&HS),sizeof(HS)) )
        {
            break;
        }
        if ( NULL==(YSMP_MEM_CBUF(MH)=YSVarBinNew()) )
        {
            break;
        }
        YSMP_INIT_LUCK(MH);
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSMPFree(MH);
        MH = NULL;
    }
    return MH;
}

void  YSMPFree(void *MH)
{
    if ( !YSMPIsInit(MH) )
    {
        return;
    }
    YSMP_INIT_LUCK_NOT(MH);
    YSMP_MEM_HEAD(MH) = NULL;
    YSMP_MEM_IDX(MH) = NULL;
    YSMP_MEM_CTX(MH) = NULL;

    if ( YSMP_ST_MEM==YSMP_MEM_ST(MH) )
    {
        if ( NULL!=YSMP_MEM_SHM(MH) )
        {
            free(YSMP_MEM_SHM(MH));
            YSMP_MEM_SHM(MH) = NULL;
        }
    }
    else if ( YSMP_ST_STRUCT==YSMP_MEM_ST(MH) )
    {
        if ( NULL!=YSMP_MEM_IBUF(MH) )
        {
            YSVarFree(YSMP_MEM_IBUF(MH));
        }
        if ( NULL!=YSMP_MEM_CBUF(MH) )
        {
            YSVarFree(YSMP_MEM_CBUF(MH));
        }
    }
#ifdef __OS_LINUX__
    else if ( YSMP_ST_SHM==YSMP_MEM_ST(MH) )
    {
        if ( NULL!=YSMP_MEM_SHM(MH) )
        {
            FEShmFree(YSMP_MEM_SHM(MH));
            memset(&(YSMP_MEM_DS(MH)),0,sizeof(YSMP_MEM_DS(MH)));
        }
    }
#endif
    YSMP_MEM_IBUF(MH) = NULL;
    YSMP_MEM_CBUF(MH) = NULL;
    YSMP_MEM_SHM(MH) = NULL;

    YSMP_MEM_MAX(MH) = 0;
    YSMP_MEM_LEN(MH) = 0;
    YSMP_MEM_IDXSIZE(MH) = 0;
    YSMP_MEM_ILEN(MH) = 0;
    YSMP_MEM_CTXSIZE(MH) = 0;
    YSMP_MEM_CLEN(MH) = 0;
    free(MH);
}

void  YSMPShow(void *MH,INT32 T,void *Buf)
{
    char Log[YSAPP_TMP_LEN];
    char Tab[BUFSIZE_64];
    char TimeStr[BUFSIZE_64];
    INT32 i;
    INT32 L;
    INT32 Addr;
    INT32 Len;
#ifdef __OS_WIN__
    struct tm systm;
#endif

    if ( !YSMPIsInit(MH)||!YSVarIsInit2(Buf,VARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    memset(Tab,0,sizeof(Tab));
    YSVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);
    memset(TimeStr,0,sizeof(TimeStr));
#ifdef __OS_LINUX__
    FETimeToString2(TimeStr,sizeof(TimeStr),(time_t)YSMP_MEM_TIME(MH));
#elif __OS_WIN__
    memcpy(&systm, localtime((const time_t*)(&YSMP_MEM_TIME(MH))), sizeof(struct tm));
    sprintf(TimeStr,"%04d-%02d-%02d %02d:%02d:%02d" \
        ,1900+systm.tm_year,systm.tm_mon+1,systm.tm_mday \
        ,systm.tm_hour,systm.tm_min,systm.tm_sec);
#else
    sprintf(TimeStr,"%d",YSMP_MEM_TIME(MH));
#endif

    snprintf(Log,sizeof(Log),"%s<ShmHead>\n"
         "%s <ShmSize>%d</ShmSize>\n"
         "%s <StructType>%s</StructType>\n"
         "%s <CtxType>%s</CtxType>\n"
         "%s <Ver>%s</Ver>\n"
         "%s <Time>%s</Time>\n"
         "%s <Max>%d</Max>\n"
         "%s <Len>%d</Len>\n"
         "%s <IdxSize>%d</IdxSize>\n"
         "%s <ILen>%d</ILen>\n"
         "%s <CtxSize>%d</CtxSize>\n"
         "%s <CLen>%d</CLen>\n"
        ,Tab \
        ,Tab,YSMP_MEM_SIZE(MH) \
        ,Tab,YSMP_ST_STR(MH) \
        ,Tab,YSMP_CT_STR(YSMP_MEM_CT(MH)) \
        ,Tab,YSMP_MEM_VER(MH) \
        ,Tab,TimeStr \
        ,Tab,YSMP_MEM_MAX(MH) \
        ,Tab,YSMP_MEM_LEN(MH) \
        ,Tab,YSMP_MEM_IDXSIZE(MH) \
        ,Tab,YSMP_MEM_ILEN(MH) \
        ,Tab,YSMP_MEM_CTXSIZE(MH) \
        ,Tab,YSMP_MEM_CLEN(MH));
    YSVarStringCat(Buf,Log,strlen(Log));
    memset(Log,0,sizeof(Log));
    L = 0;
    if ( YSMP_CT_ISHASH(YSMP_MEM_CT(MH)) )
    {
        snprintf(Log+L,sizeof(Log)-L,"%s <Idx>\n",Tab);
        L += strlen(Log+L);
        for ( i=0;i<YSMP_MEM_MAX(MH);i++ )
        {
			Addr = YSMP_MEM_IIDX_ADDR_INT(MH,i);
			FEEndianToHost_Int32(&Addr);
			Len = YSMP_MEM_IIDX_LEN_INT(MH,i);
			FEEndianToHost_Int32(&Len);
            snprintf(Log+L,sizeof(Log)-L,"%s <Addr>%d</Addr>\n"
                 "%s <Len>%d</Len>\n" \
                ,Tab,Addr \
                ,Tab,Len);
            L += strlen(Log+L);
        }
        snprintf(Log+L,sizeof(Log)-L,"%s </Idx>\n",Tab);
        L += strlen(Log+L);
    }
    snprintf(Log+L,sizeof(Log)-L,"%s</ShmHead>\n",Tab);
    L += strlen(Log+L);
    YSVarStringCat(Buf,Log,strlen(Log));
}

BOOL  YSMPMallocBuf(void *MH,INT32 NewSize,BOOL Flag)
{
    BOOL bRtn;
    INT32 Pos;
    if ( !YSMPIsInit(MH) )
    {
        return FALSE;
    }
    if ( Flag )
    {
        bRtn = YSVarBinMalloc2(YSMP_MEM_IBUF(MH),NewSize);
        if ( bRtn )
        {
            YSMP_MEM_HEAD(MH) = YSVarBinGet(YSMP_MEM_IBUF(MH));
            if ( 0>(Pos=YSMPGetHeadSize2(MH)) )
            {
                return FALSE;
            }
fprintf(stderr,"===Pos=%d.\n",Pos);
/*
            if ( YSMP_CT_ISHASH(YSMPHEAD_MEM_TYPE(YSMP_MEM_HEAD(MH))) )
            {
                Size = YSMPHEAD_MEM_MAX_INT(YSMP_MEM_HEAD(MH));
                FEEndianToHost_Int32(&Size);
                Pos += YSMP_HEAD_IDX_CALLEN(Size);
            }
*/
            YSMP_MEM_IDX(MH) = ((BYTE*)YSMP_MEM_HEAD(MH)) \
                +YSMPHEAD_ST_SIZE+Pos;
        }
    }
    else
    {
        bRtn = YSVarBinMalloc2(YSMP_MEM_CBUF(MH),NewSize);
        if ( bRtn )
        {
            YSMP_MEM_CTX(MH) = YSVarBinGet(YSMP_MEM_CBUF(MH));
        }
    }
    return bRtn;
}

void *YSMPClone(void *MHS)
{
    void *MH;
    INT32 Len;
    BOOL bRtn;
    if ( !YSMPIsInit(MHS) )
    {
        return NULL;
    }
    MH = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MH=YSMPNew()) )
        {
            break;
        }
        if ( 0>(Len=YSMPGetHeadSize2(MHS)) )
        {
            break;
        }
        YSMPMallocBuf(MH,Len,TRUE);
        YSMPMallocBuf(MH,YSMP_MEM_CLEN(MHS),FALSE);
        YSMP_MEM_SIZE(MH) = YSMP_MEM_SIZE(MHS);
        YSMP_MEM_ST(MH) = YSMP_ST_STRUCT;
        YSMP_MEM_CT(MH) = YSMP_MEM_CT(MHS);
        if ( !YSVarBinCat(YSMP_MEM_IBUF(MH) \
            ,YSMP_MEM_HEAD(MHS),YSMPHEAD_ST_SIZE) )
        {
            break;
        }
        if ( !YSVarBinCat(YSMP_MEM_IBUF(MH) \
            ,YSMP_MEM_IDX(MHS),YSMP_MEM_ILEN(MHS)) )
        {
            break;
        }
        if ( !YSVarBinCat(YSMP_MEM_CBUF(MH) \
            ,YSMP_MEM_CTX(MHS),YSMP_MEM_CLEN(MHS)) )
        {
            break;
        }
        YSMP_MEM_SHM(MH) = NULL;
#ifdef __OS_LINUX__
        memset(&(YSMP_MEM_DS(MH)),0,sizeof(YSMP_MEM_DS(MH)));
#endif
        YSMP_MEM_MAX(MH) = YSMP_MEM_MAX(MHS);
        YSMP_MEM_LEN(MH) = YSMP_MEM_LEN(MHS);
        YSMP_MEM_IDXSIZE(MH) = YSMP_MEM_IDXSIZE(MHS);
        YSMP_MEM_ILEN(MH) = YSMP_MEM_ILEN(MHS);
        YSMP_MEM_CTXSIZE(MH) = YSMP_MEM_CTXSIZE(MHS);
        YSMP_MEM_CLEN(MH) = YSMP_MEM_CLEN(MHS);
        YSMP_INIT_LUCK(MH);
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSMPFree(MH);
    }
    return MH;
}

BOOL  YSMPMemFind(void *MH,const char *Key,INT32 Idx \
    ,INT32 *PIdx,void **V,INT32 *PL)
{
    INT32 Cnt;
    INT32 HK;
    if ( NULL==Key )
    {
        return FALSE;
    }
    if ( 0==(Cnt=strlen(Key)) )
    {
        return FALSE;
    }
    if ( 0==(HK=FEHashCalKey(Key,Cnt)) )
    {
        return FALSE;
    }
    return YSMPMemFind2(MH,HK,Idx,PIdx,V,PL);
}

BOOL  YSMPMemFind2(void *MH,INT32 HashKey,INT32 Idx \
    ,INT32 *PIdx,void **V,INT32 *PL)
{
    INT32 HK;
    INT32 Cnt;
    INT32 IPos;
    INT32 ILen;
    void *IB;
    INT32 IBL;
    INT32 CPos;
    BOOL bRtn;

    if ( !YSMPIsInit(MH) )
    {
        return FALSE;
    }
    if ( (NULL==PIdx)&&((NULL==V)||(NULL==PL)) )
    {
        return FALSE;
    }
    HK = HashKey;
    IPos = YSCAL_MAX(0,Idx);
    IPos = IPos * YSMPIDX_ST_SIZE;
    if ( YSMP_CT_ISHASH(YSMP_MEM_CT(MH)) )
    {
        Cnt = FEHashGetIdx(HK,YSMP_MEM_MAX(MH));
        if ( (0>Cnt)||(YSMP_MEM_MAX(MH)<=Cnt) )
        {
            return FALSE;
        }
        ILen = YSMPHEAD_MEM_IIDX_ADDR_INT(YSMP_MEM_HEAD(MH),Cnt);
        FEEndianToHost_Int32(&ILen);
        IPos += ILen;
        ILen = YSMPHEAD_MEM_IIDX_LEN_INT(YSMP_MEM_HEAD(MH),Cnt);
        FEEndianToHost_Int32(&ILen);
    }
    else
    {
        ILen = YSMP_MEM_MAX(MH);
    }
    FEEndianToNet(&HK,INT32_SIZE);
    Cnt = Idx;
    bRtn = FALSE;
    *V = NULL;
    *PL = 0;
    while( Cnt<ILen )
    {
        if ( !YSMPIdxUnPackByPos(MH,IPos,&IB,&IBL) )
        {
            break;
        }
        Cnt ++;
        IPos += IBL;
        if ( YSMPIDX_MEM_HK_INT(IB)!=HK )
        {
            continue;
        }
        CPos = YSMPIDX_MEM_A_INT(IB);
        FEEndianToHost(&CPos,INT32_SIZE);
        if ( NULL!=PIdx )
        {
            *PIdx = Cnt-1;
        }
        if ( (NULL!=V)&&(NULL!=PL) )
        {
            *V = ((BYTE*)YSMP_MEM_CTX(MH))+CPos;
            *PL = YSMPIDX_MEM_L_INT(IB);
        }
        FEEndianToHost(PL,INT32_SIZE);
        bRtn = TRUE;
        break;
    }
    return bRtn;
}

BOOL  YSMPToMem(void **MHS,void *Var)
{
    INT32 Base;
    INT32 MM;
    INT32 IdxSize;
    INT32 ILen;
    INT32 CtxSize;
    INT32 CLen;
    INT32 Len;
    void *V;
    void *Head;
    void *MH;
    BOOL bRtn;
    if ( (NULL==MHS)||!YSVarIsInit(Var) )
    {
        return FALSE;
    }
    if ( !YSMP_CT_IS(YSVarGetType(Var)) )
    {
        return FALSE;
    }
    Base = 0;
    IdxSize = YSMPIDX_ST_SIZE;
    CtxSize = 0;
    Len = 0;
    MH = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(MH=YSMPNew()) )
        {
            break;
        }
        YSMP_MEM_CT(MH) = YSVarGetType(Var);
        if ( YSMP_CT_ISHASH(YSMP_MEM_CT(MH)) )
        {
            Len = YSVarHashGetLen(Var);
            MM = YSVarHashGetBase(Var);
            Base = MM;
            bRtn = YSMPHashToMem(Var,YSMP_MEM_IBUF(MH),YSMP_MEM_CBUF(MH));
        }
        else if ( YSMP_CT_ISARRAY(YSMP_MEM_CT(MH)) )
        {
            Len = YSVarArrayGetLen(Var);
            MM = Len;
            bRtn = YSMPArrayToMem(Var,YSMP_MEM_IBUF(MH),YSMP_MEM_CBUF(MH));
        }
        else if ( YSMP_CT_ISSTRUCT(YSMP_MEM_CT(MH)) )
        {
            bRtn = FALSE;
            if ( NULL==(V=YSVarStructGet(Var,YSMP_CT_STRUCT_LEN_IDX)) )
            {
                break;
            }
            if ( !YSVarInt32Get(V,&Len) )
            {
                break;
            }
            if ( NULL==(V=YSVarStructGet(Var,YSMP_CT_STRUCT_MAX_IDX)) )
            {
                break;
            }
            if ( !YSVarInt32Get(V,&MM) )
            {
                break;
            }
            if ( Len>MM )
            {
                break;
            }
            if ( NULL==(V=YSVarStructGet(Var,YSMP_CT_STRUCT_IDXSIZE_IDX)) )
            {
                break;
            }
            if ( !YSVarInt32Get(V,&IdxSize) )
            {
                break;
            }
            if ( NULL==(V=YSVarStructGet(Var,YSMP_CT_STRUCT_CTXSIZE_IDX)) )
            {
                break;
            }
            if ( !YSVarInt32Get(V,&CtxSize) )
            {
                break;
            }
            bRtn = YSMPStructToMem(Var,YSMP_MEM_IBUF(MH),YSMP_MEM_CBUF(MH));
        }
        if ( !bRtn )
        {
            break;
        }
        ILen = YSVarBinGetLen(YSMP_MEM_IBUF(MH))-YSMPHEAD_ST_SIZE_CAL(Base);
        CLen = YSVarBinGetLen(YSMP_MEM_CBUF(MH));
        YSMP_MEM_SIZE(MH) = YSVarBinGetLen(YSMP_MEM_IBUF(MH)) + CLen;
        Head = YSVarBinGet(YSMP_MEM_IBUF(MH));

        YSMPHEAD_MEM_SIZE_INT(Head) = YSMP_MEM_SIZE(MH);
        FEEndianToNet(YSMPHEAD_MEM_SIZE(Head),INT32_SIZE);

        YSMPHEAD_MEM_STA(Head) = YSAPP_STATUS_RUNNING;
        YSMPHEAD_MEM_TYPE(Head) = YSMP_MEM_CT(MH);

        /* R[2] */

        if ( YSVarHasKey(Var) )
        {
            MEMNCPY(YSMPHEAD_MEM_VER(Head),YSVarGetKey(Var) \
                ,sizeof(YSMPHEAD_MEM_VER(Head)),YSVarGetKeyLen(Var));
        }

        YSMPHEAD_MEM_MAX_INT(Head) = MM;
        FEEndianToNet(YSMPHEAD_MEM_MAX(Head),INT32_SIZE);

        YSMPHEAD_MEM_LEN_INT(Head) = Len;
        FEEndianToNet(YSMPHEAD_MEM_LEN(Head),INT32_SIZE);

        YSMPHEAD_MEM_IDXSIZE_INT(Head) = IdxSize;
        FEEndianToNet(YSMPHEAD_MEM_IDXSIZE(Head),INT32_SIZE);

        YSMPHEAD_MEM_ILEN_INT(Head) = ILen;
        FEEndianToNet(YSMPHEAD_MEM_ILEN(Head),INT32_SIZE);

        YSMPHEAD_MEM_CTXSIZE_INT(Head) = CtxSize;
        FEEndianToNet(YSMPHEAD_MEM_CTXSIZE(Head),INT32_SIZE);

        YSMPHEAD_MEM_CLEN_INT(Head) = CLen;
        FEEndianToNet(YSMPHEAD_MEM_CLEN(Head),INT32_SIZE);

        YSMPHEAD_INIT_LUCK(Head);
        YSMPHeadUpdateTime(Head,YSMP_MEM_SIZE(MH));

        YSMPMallocBuf(MH,0,TRUE);
        YSMPMallocBuf(MH,0,FALSE);
        *MHS = MH;
        MH = NULL;
        bRtn = TRUE;
        break;
    }
    YSMPFree(MH);
    MH = NULL;
    return bRtn;
}

BOOL  YSMPHashToMem(void *Var,void *IBuf,void *CBuf)
{   
    INT32 i;
    INT32 Size;
    INT32 LIdx;
    INT32 LLen;
    void *Link;
    void *V;

    INT32 CPos;
    INT32 CLen;

    INT32 IL;
    INT32 CL;

    BOOL bRtn;

    if ( !YSVarIsInit2(Var,VARTYPE_MEM_VT_HASH) \
        || !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        || !YSVarIsInit2(CBuf,VARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( 0>=(Size=YSVarHashGetBase(Var)) )
    {
        return FALSE;
    }
    if ( 0>(LLen=YSVarHashGetLen(Var)) )
    {
        return FALSE;
    }
    if ( !FEVarBinMalloc(IBuf,YSMP_HEAD_IDX_CALLEN(Size)+LLen*YSMPIDX_ST_SIZE) )
    {
        return FALSE;
    }
    if ( !FEVarBinSetLen(IBuf,YSMPHEAD_ST_SIZE_CAL(Size)) )
    {
        return FALSE;
    }
    IL = YSVarBinGetLen(IBuf);
    CL = YSVarBinGetLen(CBuf);
    bRtn = TRUE;

    for ( i=0;i<Size;i++ )
    {
        if ( NULL==(Link=YSVarHashGetLinkByIdx(Var,i)) )
        {
            bRtn = FALSE;
            break;
        }
        LLen = YSVarLinkGetLen(Link);
        if ( !YSMPHeadSetHashIdx(IBuf,Size,i,LLen) )
        {
            bRtn = FALSE;
            break;
        }
        for ( LIdx=0;LIdx<LLen;LIdx++ )
        {
            if ( NULL==(V=YSVarLinkGet(Link,LIdx)) )
            {
                bRtn = FALSE;
                break;
            }
            if ( !YSVarHasKey(V) )
            {
                bRtn = FALSE;
                break;
            }
            CPos = YSVarBinGetLen(CBuf);
            if ( !YSVarPack(V,CBuf) )
            {
                bRtn = FALSE;
                break;
            }
            if ( 0>(CLen=YSVarBinGetLen(CBuf)) )
            {
                bRtn = FALSE;
                break;
            }
            if ( !YSMPIdxAdd(IBuf,YSVarGetKeyHash(V),CPos,CLen-CPos) )
            {
                bRtn = FALSE;
                break;
            }
        }/* for ( LIdx=0;LIdx<LLen;LIdx++ ) */
    }/* for ( i=0;i<Size;i++ ) */
    if ( !bRtn )
    {
        YSVarBinSetLen(IBuf,IL);
        YSVarBinSetLen(CBuf,CL);
    }
    return bRtn;
}

BOOL  YSMPArrayToMem(void *Var,void *IBuf,void *CBuf)
{   
    INT32 i;
    INT32 Len;
    void *V;

    INT32 CPos;
    INT32 CLen;

    INT32 IL;
    INT32 CL;

    BOOL bRtn;

    if ( !YSVarIsInit2(Var,VARTYPE_MEM_VT_ARRAY) \
        || !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        || !YSVarIsInit2(CBuf,VARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( 0>(Len=YSVarArrayGetLen(Var)) )
    {
        return FALSE;
    }
    if ( !FEVarBinMalloc(IBuf,Len*YSMPIDX_ST_SIZE) )
    {
        return FALSE;
    }
    IL = YSVarBinGetLen(IBuf);
    CL = YSVarBinGetLen(CBuf);
    bRtn = TRUE;

    for ( i=0;i<Len;i++ )
    {
        if ( NULL==(V=YSVarArrayGet(Var,i)) )
        {
            bRtn = FALSE;
            break;
        }
        if ( !YSVarHasKey(V) )
        {
            bRtn = FALSE;
            break;
        }
        CPos = YSVarBinGetLen(CBuf);
        if ( !YSVarPack(V,CBuf) )
        {
            bRtn = FALSE;
            break;
        }
        if ( 0>(CLen=YSVarBinGetLen(CBuf)) )
        {
            bRtn = FALSE;
            break;
        }
        if ( !YSMPIdxAdd(IBuf,YSVarGetKeyHash(V),CPos,CLen-CPos) )
        {
            bRtn = FALSE;
            break;
        }
    }/* for ( i=0;i<Len;i++ ) */
    if ( !bRtn )
    {
        YSVarBinSetLen(IBuf,IL);
        YSVarBinSetLen(CBuf,CL);
    }
    return bRtn;
}

BOOL  YSMPStructToMem(void *Var,void *IBuf,void *CBuf)
{
    void *V;

    INT32 IL;
    INT32 CL;

    BOOL bRtn;

    if ( !YSVarIsInit2(Var,VARTYPE_MEM_VT_STRUCT) \
        || !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        || !YSVarIsInit2(CBuf,VARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    IL = YSVarBinGetLen(IBuf);
    CL = YSVarBinGetLen(CBuf);
    bRtn = TRUE;

    while( 1 )
    {
        if ( NULL==(V=YSVarStructGet(Var,YSMP_CT_STRUCT_IDX_IDX)) )
        {
            bRtn = FALSE;
            break;
        }
        if ( !YSVarBinCat(IBuf,YSVarBinGet(V),YSVarBinGetLen(V)) )
        {
            bRtn = FALSE;
            break;
        }
        if ( NULL==(V=YSVarStructGet(Var,YSMP_CT_STRUCT_CTX_IDX)) )
        {
            bRtn = FALSE;
            break;
        }
        if ( !YSVarBinCat(CBuf,YSVarBinGet(V),YSVarBinGetLen(V)) )
        {
            bRtn = FALSE;
            break;
        }
        break;
    }
    if ( !bRtn )
    {
        YSVarBinSetLen(IBuf,IL);
        YSVarBinSetLen(CBuf,CL);
    }
    return bRtn;
}

void *YSMPFromMem(void *MHS)
{
    void *Bin;
    void *Var;
    void *vRtn;
    Bin = NULL;
    Var = NULL;
    while( 1 )
    {
        if ( !YSMPIsInit(MHS) )
        {
            break;
        }
        if ( YSMP_CT_ISSTRUCT(YSMP_MEM_CT(MHS)) )
        {
            Var = YSMPStructFromMP(MHS);
        }
        else if ( NULL==(Bin=YSVarBinSetValue(YSMP_MEM_CTX(MHS) \
            ,YSMP_MEM_CLEN(MHS),YSMP_MEM_CLEN(MHS))) )
        {
            break;
        }
        else if ( YSMP_CT_ISHASH(YSMP_MEM_CT(MHS)) )
        {
            Var = YSMPHashFromVarBin(Bin,YSMP_MEM_MAX(MHS));
        }
        else if ( YSMP_CT_ISARRAY(YSMP_MEM_CT(MHS)) )
        {
            Var = YSMPArrayFromVarBin(Bin);
        }
        if ( NULL==Var )
        {
            break;
        }
        if ( 0<strlen(YSMP_MEM_VER(MHS)) )
        {
            if ( !YSVarCpyKey(Var,YSMP_MEM_VER(MHS)) )
            {
                break;
            }
        }
        vRtn = Var;
        Var = NULL;
        break;
    }
    YSVarHashFree(Var);
    Var = NULL;
    YSVarBinFree(Bin);
    Bin = NULL;
    return vRtn;
}

void *YSMPHashFromVarBin(void *Bin,INT32 Max)
{
    INT32 Pos;
    INT32 Pos2;
    void *vRtn;
    void *V;
    void *Var;

    vRtn = NULL;
    V = NULL;
    Var = NULL;
    while( 1 )
    {
        if ( !YSVarIsInit2(Bin,VARTYPE_MEM_VT_BIN) )
        {
            break;
        }
        if ( NULL==(Var=YSVarHashNew(Max)) )
        {
            break;
        }
        Pos = 0;
        while( 1 )
        {
            if ( 0>(Pos2=YSVarUnPack(&V,Bin,Pos)) )
            {
                break;
            }
            if ( !YSVarHashAdd(Var,V) )
            {
                break;
            }
            V = NULL;
            Pos = Pos2;
        }
        if ( YSVarBinGetLen(Bin)!=Pos )
        {
            break;
        }
        vRtn = Var;
        Var = NULL;
        break;
    }
    YSVarFree(V);
    V = NULL;
    YSVarFree(Var);
    Var = NULL;
    return vRtn;
}

void *YSMPArrayFromVarBin(void *Bin)
{
    INT32 Pos;
    INT32 Pos2;
    void *vRtn;
    void *V;
    void *Var;

    vRtn = NULL;
    V = NULL;
    Var = NULL;
    while( 1 )
    {
        if ( !YSVarIsInit2(Bin,VARTYPE_MEM_VT_BIN) )
        {
            break;
        }
        if ( NULL==(Var=YSVarArrayNew(0)) )
        {
            break;
        }
        Pos = 0;
        while( 1 )
        {
            if ( 0>(Pos2=YSVarUnPack(&V,Bin,Pos)) )
            {
                break;
            }
            if ( !YSVarArrayAdd(Var,V) )
            {
                break;
            }
            V = NULL;
            Pos = Pos2;
        }
        if ( YSVarBinGetLen(Bin)!=Pos )
        {
            break;
        }
        vRtn = Var;
        Var = NULL;
        break;
    }
    YSVarFree(V);
    V = NULL;
    YSVarFree(Var);
    Var = NULL;
    return vRtn;
}

void *YSMPStructFromMP(void *MHS)
{
    void *vRtn;
    void *V1;
    void *V2;
    void *Var;

    V1 = NULL;
    V2 = NULL;
    Var = NULL;
    vRtn = NULL;
    while( 1 )
    {
        if ( !YSMPIsInit(MHS) )
        {
            break;
        }
        if ( NULL==(Var=YSMPStructNew(YSMP_MEM_VER(MHS),YSMP_MEM_LEN(MHS) \
            ,YSMP_MEM_MAX(MHS),YSMP_MEM_IDXSIZE(MHS),YSMP_MEM_CTXSIZE(MHS) \
            ,(V1=YSVarBinSave(YSMP_MEM_IDX(MHS),YSMP_MEM_ILEN(MHS))) \
            ,(V2=YSVarBinSave(YSMP_MEM_CTX(MHS),YSMP_MEM_CLEN(MHS))))) )
        {
            break;
        }
        V1 = NULL;
        V2 = NULL;
        vRtn = Var;
        Var = NULL;
        break;
    }
    YSVarFree(V1);
    V1 = NULL;
    YSVarFree(V2);
    V2 = NULL;
    YSVarFree(Var);
    Var = NULL;
    return vRtn;
}

#ifdef __OS_LINUX__

BOOL  YSMPToShm(const char *Key,void *Var)
{
    BOOL bRtn;
    void *MH;
    if ( !YSVarIsInit(Var) )
    {
        return FALSE;
    }
    if ( !YSMP_CT_IS(YSVarGetType(Var)) )
    {
        return FALSE;
    }
    
    MH = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( !YSMPToMem(&MH,Var) )
        {
            break;
        }
        if ( !YSMPShmUpdate(Key,MH) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    YSMPFree(MH);
    MH = NULL;
    return bRtn;
}

BOOL  YSMPFromShm(void **Var,const char *Key)
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
        if ( NULL==(MHS=YSMPCloneFromShm(Key)) )
        {
            break;
        }
        if ( NULL==(*Var=YSMPFromMem(MHS)) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    YSMPFree(MHS);
    MHS = NULL;
    return bRtn;
}

void *YSMPShmFind(const char *File,const char *Key)
{
    void *Buf;
    void *V;

    if ( NULL==(Buf=YSVarBinNew(Buf)) )
    {
        return NULL;
    }
    V = NULL;
    while( 1 )
    {
        if ( !YSMPShmFind2(File,Key,0,Buf) )
        {
            break;
        }
        YSVarUnPack(&V,Buf,0);
        break;
    }
    YSVarBinFree(Buf);
    return V;
}

BOOL  YSMPShmFind2(const char *File,const char *Key,INT32 Idx,void *Buf)
{
    void *V;
    INT32 PL;
    void *MHS;
    INT32 Len;
    INT32 IIdx;
    BOOL bRtn;
    
    MHS = NULL;
    bRtn = FALSE;
    Len = YSCAL_MAX(0,Idx);
    V = NULL;
    PL = 0;
    while( 1 )
    {
        if ( (NULL==File)||(NULL==Key)||!YSVarIsInit2(Buf,VARTYPE_MEM_VT_BIN) )
        {
            break;
        }
        if ( (0==strlen(File))||(0==strlen(Key)) )
        {
            break;
        }
        if ( NULL==(MHS=YSMPCloneFromShm(File)) )
        {
            break;
        }
        for ( IIdx=0;IIdx<=Len;IIdx++ )
        {
            if ( !(bRtn=YSMPMemFind(MHS,Key,IIdx,NULL,&V,&PL)) )
            {
                break;
            }
        }
        if ( (IIdx==Len)||!bRtn )
        {
            break;
        }
        bRtn = YSVarBinCat(Buf,V,PL);
        break;
    }
    YSMPFree(MHS);
    MHS = NULL;
    return bRtn;
}

BOOL  YSMPShmMultiFind(const char *Ver,void *Arr,void *Buf)
{
    void *V;
    INT32 PL;
    void *MHS;
    char *Key;
    INT32 Idx;
    BOOL Flag;
    INT32 IIdx;
    BOOL bRtn;
    
    MHS = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( (NULL==Ver)||(NULL==Buf) )
        {
            break;
        }
        if ( 0==strlen(Ver) )
        {
            break;
        }
        if ( NULL==(MHS=YSMPCloneFromShm(Ver)) )
        {
            break;
        }
        Idx = 0;
        if ( NULL==Arr )
        {
            Idx = -1;
        }
        else if ( 0==YSVarArrayGetLen(Arr) )
        {
            Idx = -1;
        }
        if ( -1==Idx )
        {
            bRtn = YSVarBinCat(Buf,YSMP_MEM_CTX(MHS),YSMP_MEM_CLEN(MHS));
            break;
        }

        while( 1 )
        {
            if ( NULL==(Key=(char *)YSVarStringGet(YSVarArrayGet(Arr,Idx))) )
            {
                bRtn = TRUE;
                break;
            }
            Idx ++;
            Flag = TRUE;
            IIdx = 0;
            while( 1 )
            {
                if ( !(bRtn=YSMPMemFind(MHS,Key,IIdx,NULL,&V,&PL)) )
                {
                    Flag = RTNCODE_CMPBOOL(0==IIdx);
                    break;
                }
                if ( !YSVarBinCat(Buf,V,PL) )
                {
                    Flag = FALSE;
                    break;
                }
                IIdx ++;
            }
            if ( !Flag )
            {
                break;
            }
        }
        break;
    }
    YSMPFree(MHS);
    MHS = NULL;
    return bRtn;
}

#endif

void *YSMPStructNew(const char *Key,INT32 Len,INT32 Max \
    ,INT32 IdxSize,INT32 CtxSize,void *IBuf,void *CBuf)
{
    void *vRtn;
    void *V;
    void *Var;

    vRtn = NULL;
    V = NULL;
    Var = NULL;
    while( 1 )
    {
        if ( NULL!=Key )
        {
            if ( NULL==(Var=YSVarStructNew_Key(YSMP_CT_STRUCT_SIZE,Key)) )
            {
                break;
            }
        }
        else if ( NULL==(Var=YSVarStructNew(YSMP_CT_STRUCT_SIZE)) )
        {
            break;
        }
        if ( NULL==(V=YSVarInt32Save2("LEN",Len)) )
        {
            break;
        }
        if ( !YSVarStructSet(Var,YSMP_CT_STRUCT_LEN_IDX,V) )
        {
            break;
        }
        V = NULL;
        if ( NULL==(V=YSVarInt32Save2("MAX",Max)) )
        {
            break;
        }
        if ( !YSVarStructSet(Var,YSMP_CT_STRUCT_MAX_IDX,V) )
        {
            break;
        }
        V = NULL;
        if ( !YSVarStructSet(Var,YSMP_CT_STRUCT_IDXSIZE_IDX
            ,(V=YSVarInt32Save2("IdxSize",IdxSize))) )
        {
            break;
        }
        V = NULL;
        if ( !YSVarStructSet(Var,YSMP_CT_STRUCT_CTXSIZE_IDX \
            ,(V=YSVarInt32Save2("CtxSize",CtxSize))) )
        {
            break;
        }
        V = NULL;
        if ( !YSVarStructSet(Var,YSMP_CT_STRUCT_IDX_IDX \
            ,(V=YSVarBinClone(IBuf))) )
        {
            break;
        }
        V = NULL;
        if ( !YSVarStructSet(Var,YSMP_CT_STRUCT_CTX_IDX \
            ,(V=YSVarBinClone(CBuf))) )
        {
            break;
        }
        V = NULL;
        vRtn = Var;
        Var = NULL;
        break;
    }
    YSVarFree(V);
    V = NULL;
    YSVarFree(Var);
    Var = NULL;
    return vRtn;
}

#ifdef __cplusplus
}
#endif
 
