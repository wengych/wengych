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
#ifdef __OS_WIN__
#include <winsock2.h>
#ifdef _WINDEF_
#ifndef __OS_WIN_WINDEF__
#define __OS_WIN_WINDEF__ 1
#endif
#endif
#endif
#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif
 
void  YSMPHeadShow(void *Head,INT32 T,void *Buf)
{
    char Log[YSAPP_TMP_LEN];
    char Tab[BUFSIZE_64];
    INT32 i;
    INT32 L;
 
    if ( !YSMPIsInit(Head)||!YSVarIsInit2(Buf,VARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    memset(Tab,0,sizeof(Tab));
    YSVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    memset(Log,0,sizeof(Log));
    snprintf(Log,sizeof(Log),"%s<Size>%d / %08X</Size>\n"
         "%s<Status>%s</Status>\n"
         "%s<Type>%d</Type>\n"
         "%s<Ver>%s</Ver>\n"
         "%s<Max>%d / %08X</Max>\n"
         "%s<Len>%d / %08X</Len>\n"
         "%s<ILen>%d / %08X</ILen>\n"
         "%s<CLen>%d / %08X</CLen>\n"
        ,Tab,ntohl(*(INT32*)(YSMPHEAD_MEM_SIZE(Head))) \
            ,*(INT32*)(YSMPHEAD_MEM_SIZE(Head)) \
        ,Tab,YSAPP_STATUS_STR(YSMPHEAD_MEM_STA(Head)) \
        ,Tab,YSMPHEAD_MEM_TYPE(Head) \
        ,Tab,YSMPHEAD_MEM_VER(Head) \
        ,Tab,ntohl(*((INT32*)(YSMPHEAD_MEM_MAX(Head)))) \
            ,*(INT32*)(YSMPHEAD_MEM_MAX(Head)) \
        ,Tab,ntohl(*((INT32*)(YSMPHEAD_MEM_LEN(Head)))) \
            ,*(INT32*)(YSMPHEAD_MEM_LEN(Head)) \
        ,Tab,ntohl(*(INT32*)(YSMPHEAD_MEM_ILEN(Head))) \
            ,*(INT32*)(YSMPHEAD_MEM_ILEN(Head)) \
        ,Tab,ntohl(*(INT32*)(YSMPHEAD_MEM_CLEN(Head))) \
            ,*(INT32*)(YSMPHEAD_MEM_CLEN(Head)));
    YSVarStringCat(Buf,Log,strlen(Log));
    memset(Log,0,sizeof(Log));
    L = 0;
    for ( i=0;i<YSMP_HEAD_BASE;i++ )
    {
        if ( L > sizeof(Log)/2 )
        {
            YSVarStringCat(Buf,Log,L);
            memset(Log,0,sizeof(Log));
            L = 0;
        }
        snprintf(Log+L,sizeof(Log)-L,"%s<Idx>\n"
             "%s <Addr>%d / %08X</Addr>\n"
             "%s <Len>%d / %08X</Len>\n"
             "%s</Idx>\n"
            ,Tab \
            ,Tab,ntohl(*(INT32*)(YSMPHEAD_MEM_IDX_ADDR(Head,i))) \
                ,*(INT32*)(YSMPHEAD_MEM_IDX_ADDR(Head,i)) \
            ,Tab,ntohl(*(INT32*)(YSMPHEAD_MEM_IDX_LEN(Head,i))) \
                ,*(INT32*)(YSMPHEAD_MEM_IDX_LEN(Head,i)) \
            ,Tab);
        L += strlen(Log+L);
    }
    YSVarStringCat(Buf,Log,L);
}

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

void *YSMPGetIBuf(void *MH)
{
    if ( !YSMPIsMemInit(MH) )
    {
        return FALSE;
    }
    return YSMP_MEM_IBUF(MH);
}

void *YSMPGetCBuf(void *MH)
{
    if ( !YSMPIsMemInit(MH) )
    {
        return FALSE;
    }
    return YSMP_MEM_CBUF(MH);
}

BOOL  YSMPPackBase(void *IBuf,INT32 Idx,INT32 Len)
{
    void *V;
    INT32 L;
    if ( !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        || ( (0>Idx)||(YSMP_HEAD_BASE<=Idx) ) \
        || (0>Len) )
    {
        return FALSE;
    }
    if ( NULL==(V=YSVarBinGet(IBuf)) )
    {
        return FALSE;
    }
    L = YSVarBinGetLen(IBuf);
    if ( YSMPHEAD_ST_SIZE>L )
    {
        return FALSE;
    }
    
    *(INT32 *)(YSMPHEAD_MEM_IDX_ADDR(V,Idx)) = L-YSMPHEAD_ST_SIZE;
    *(INT32 *)(YSMPHEAD_MEM_IDX_LEN(V,Idx)) = Len;
    FEEndianToNet(YSMPHEAD_MEM_IDX_ADDR(V,Idx),INT32_SIZE);
    FEEndianToNet(YSMPHEAD_MEM_IDX_LEN(V,Idx),INT32_SIZE);
    return TRUE;
}

BOOL  YSMPPackIdx(void *IBuf,INT32 HK,INT32 Pos,INT32 Len)
{
    tYSMPIdx IB;
    if ( !YSMPPackIdx2(&IB,sizeof(IB),HK,Pos,Len) )
    {
        return FALSE;
    }
    return YSVarBinCat(IBuf,&IB,sizeof(IB));
}

BOOL  YSMPPackIdx2(void *Buf,INT32 Size,INT32 HK,INT32 Pos,INT32 Len)
{
    INT32 P;
    P = 0;
    if ( !YSMPUpdateIdxHK(((BYTE*)Buf)+P,Size-P,HK) )
    {
        return FALSE;
    }
    P += INT32_SIZE;
    return YSMPUpdateIdxAddr(((BYTE*)Buf)+P,Size-P,Pos,Len);
}

BOOL  YSMPUpdateIdxHK(void *Buf,INT32 Size,INT32 HK)
{
    if ( (NULL==Buf)||(INT32_SIZE>Size)||(0==HK) )
    {
        return FALSE;
    }
    *(INT32 *)(YSMPIDX_MEM_HK(Buf)) = YSCAL_MAX(0,HK);
    FEEndianToNet(YSMPIDX_MEM_HK(Buf),INT32_SIZE);
    return TRUE;
}

BOOL  YSMPUpdateIdxAddr(void *Buf,INT32 Size,INT32 Pos,INT32 Len)
{
    if ( (NULL==Buf)||(INT32_SIZE+INT32_SIZE>Size) )
    {
        return FALSE;
    }
    *(INT32 *)(YSMPIDX_MEM_A(Buf)) = YSCAL_MAX(0,Pos);
    FEEndianToNet(YSMPIDX_MEM_A(Buf),INT32_SIZE);
    *(INT32 *)(YSMPIDX_MEM_L(Buf)) = YSCAL_MAX(0,Len);
    FEEndianToNet(YSMPIDX_MEM_L(Buf),INT32_SIZE);
    return TRUE;
}

BOOL  YSMPUnPackIdx(void *MH,INT32 Idx,tYSMPIdx *IB)
{
    if ( !YSMPIsInit(MH)||(0>Idx)||(NULL==IB) )
    {
        return FALSE;
    }
    if ( YSMP_MEM_LEN(MH)<=Idx )
    {
        return FALSE;
    }
    memset(IB,0,sizeof(tYSMPIdx));
    memcpy(IB,((BYTE*)YSMP_MEM_IDX(MH))+Idx*YSMPIDX_ST_SIZE \
        ,YSMPIDX_ST_SIZE);
    FEEndianToHost(YSMPIDX_MEM_HK(IB),INT32_SIZE);
    FEEndianToHost(YSMPIDX_MEM_A(IB),INT32_SIZE);
    FEEndianToHost(YSMPIDX_MEM_L(IB),INT32_SIZE);
    return TRUE;
}

BOOL  YSMPUnPackIdx2(void *MH,INT32 Idx,void **IB,INT32 *PL)
{
    if ( !YSMPIsInit(MH)||(0>Idx)||(NULL==IB)||(NULL==PL) )
    {
        return FALSE;
    }
    if ( YSMP_MEM_LEN(MH)<=Idx )
    {
        return FALSE;
    }
    *IB = ((BYTE*)YSMP_MEM_IDX(MH))+Idx*YSMPIDX_ST_SIZE;
    *PL = YSMPIDX_ST_SIZE;
    return TRUE;
}

BOOL  YSMPUnPackIdxByPos(void *MH,INT32 Pos,tYSMPIdx *IB)
{
    if ( !YSMPIsInit(MH)||(0>Pos)||(NULL==IB) )
    {
        return FALSE;
    }
    if ( (YSMP_MEM_ILEN(MH)<=Pos)||(0!=(Pos%YSMPIDX_ST_SIZE)) )
    {
        return FALSE;
    }
    memset(IB,0,sizeof(tYSMPIdx));
    memcpy(IB,((BYTE*)YSMP_MEM_IDX(MH))+Pos,YSMPIDX_ST_SIZE);
    FEEndianToHost(YSMPIDX_MEM_HK(IB),INT32_SIZE);
    FEEndianToHost(YSMPIDX_MEM_A(IB),INT32_SIZE);
    FEEndianToHost(YSMPIDX_MEM_L(IB),INT32_SIZE);
    return TRUE;
}

BOOL  YSMPUnPackIdxByPos2(void *MH,INT32 Pos,void **IB,INT32 *PL)
{
    if ( !YSMPIsInit(MH)||(0>Pos)||(NULL==IB)||(NULL==PL) )
    {
        return FALSE;
    }
    if ( (YSMP_MEM_ILEN(MH)<=Pos)||(0!=(Pos%YSMPIDX_ST_SIZE)) )
    {
        return FALSE;
    }
    *IB = ((BYTE*)YSMP_MEM_IDX(MH))+Pos;
    *PL = YSMPIDX_ST_SIZE;
    return TRUE;
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
    YSMP_MEM_ILEN(MH) = 0;
    YSMP_MEM_CLEN(MH) = 0;
    memset(YSMP_MEM_IIDX(MH),0,sizeof(YSMP_MEM_IIDX(MH)));
    free(MH);
}

void  YSMPShow(void *MH,INT32 T,void *Buf)
{
    char Log[YSAPP_TMP_LEN];
    char Tab[BUFSIZE_64];
    INT32 i;
    INT32 L;

    if ( !YSMPIsInit(MH)||!YSVarIsInit2(Buf,VARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    memset(Tab,0,sizeof(Tab));
    YSVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    snprintf(Log,sizeof(Log),"%s<ShmSize>%d</ShmSize>\n"
         "%s<StructType>%s</StructType>\n"
         "%s<CtxType>%s</CtxType>\n"
         "%s<Max>%d</Max>\n"
         "%s<Len>%d</Len>\n"
         "%s<IdxLen>%d</IdxLen>\n"
         "%s<CtxLen>%d</CtxLen>\n"
         "%s<Idx>\n"
        ,Tab,YSMP_MEM_SIZE(MH) \
        ,Tab,YSMP_ST_STR(MH) \
        ,Tab,YSMP_CT_STR(YSMP_MEM_CT(MH)) \
        ,Tab,YSMP_MEM_MAX(MH) \
        ,Tab,YSMP_MEM_LEN(MH) \
        ,Tab,YSMP_MEM_ILEN(MH) \
        ,Tab,YSMP_MEM_CLEN(MH) \
        ,Tab);
    YSVarStringCat(Buf,Log,strlen(Log));
    memset(Log,0,sizeof(Log));
    L = 0;
    for ( i=0;i<YSMP_HEAD_BASE;i++ )
    {
        snprintf(Log+L,sizeof(Log)-L,"%s <Addr>%d</Addr>\n"
             "%s <Len>%d</Len>\n" \
            ,Tab,YSMP_MEM_IIDX_ADDR(MH,i) \
            ,Tab,YSMP_MEM_IIDX_LEN(MH,i));
        L += strlen(Log+L);
    }
    snprintf(Log+L,sizeof(Log)-L,"%s</Idx>\n",Tab);
    L += strlen(Log+L);
    YSVarStringCat(Buf,Log,strlen(Log));
}

BOOL  YSMPMallocBuf(void *MH,INT32 NewSize,BOOL Flag)
{
    BOOL bRtn;
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
            YSMP_MEM_IDX(MH) = ((BYTE*)YSMP_MEM_HEAD(MH)) \
                +YSMPHEAD_ST_SIZE;
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
        YSMPMallocBuf(MH,YSMPHEAD_ST_SIZE+YSMP_MEM_ILEN(MHS),TRUE);
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
        YSMP_MEM_ILEN(MH) = YSMP_MEM_ILEN(MHS);
        YSMP_MEM_CLEN(MH) = YSMP_MEM_CLEN(MHS);
        memcpy(YSMP_MEM_IIDX(MH) \
            ,YSMP_MEM_IIDX(MHS),sizeof(YSMP_MEM_IIDX(MHS)));
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
    INT32 IPos;
    INT32 ILen;
    void *IB;
    INT32 IBL;
    INT32 CPos;
    BOOL bRtn;

    if ( !YSMPIsInit(MH)||(NULL==Key) )
    {
        return FALSE;
    }
    if ( (NULL==PIdx)&&((NULL==V)||(NULL==PL)) )
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
    Cnt = FEHashGetIdx(HK,YSMP_HEAD_BASE);
    if ( (0>Cnt)||(YSMP_HEAD_BASE<=Cnt) )
    {
        return FALSE;
    }
    IPos = YSCAL_MAX(0,Idx);
    IPos = IPos * YSMPIDX_ST_SIZE;
    IPos += YSMP_MEM_IIDX_ADDR(MH,Cnt);
    ILen = YSMP_MEM_IIDX_LEN(MH,Cnt);
    FEEndianToNet(&HK,INT32_SIZE);
    Cnt = 0;
    bRtn = FALSE;
    *V = NULL;
    *PL = 0;
    while( Cnt<ILen )
    {
        if ( !YSMPUnPackIdxByPos2(MH,IPos,&IB,&IBL) )
        {
            break;
        }
        Cnt ++;
        IPos += IBL;
        if ( *(INT32*)(YSMPIDX_MEM_HK(IB))!=HK )
        {
            continue;
        }
        CPos = *(INT32*)(YSMPIDX_MEM_A(IB));
        FEEndianToHost(&CPos,INT32_SIZE);
        if ( NULL!=PIdx )
        {
            *PIdx = Cnt-1;
        }
        if ( (NULL!=V)||(NULL!=PL) )
        {
            *V = ((BYTE*)YSMP_MEM_CTX(MH))+CPos;
            *PL = *(INT32*)(YSMPIDX_MEM_L(IB));
        }
        FEEndianToHost(PL,INT32_SIZE);
        bRtn = TRUE;
        break;
    }
    return bRtn;
}

BOOL  YSMPToMem(void **MHS,void *Var,INT32 Max)
{
    INT32 M;
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
    M = 0;
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
            M = YSVarHashGetLen(Var);
            bRtn = YSMPHashToMem(Var \
                ,YSMP_MEM_IBUF(MH),YSMP_MEM_CBUF(MH));
        }
        else if ( YSMP_CT_ISARRAY(YSMP_MEM_CT(MH)) )
        {
            M = YSVarArrayGetLen(Var);
            bRtn = YSMPArrayToMem(Var \
                ,YSMP_MEM_IBUF(MH),YSMP_MEM_CBUF(MH));
        }
        if ( !bRtn||(M>Max) )
        {
            break;
        }
        YSMPMallocBuf(MH,0,TRUE);
        YSMPMallocBuf(MH,0,FALSE);
        YSMP_MEM_SIZE(MH) = YSVarBinGetLen(YSMP_MEM_IBUF(MH)) \
            + YSVarBinGetLen(YSMP_MEM_CBUF(MH));

        Head = YSMP_MEM_HEAD(MH);

        *(INT32*)YSMPHEAD_MEM_SIZE(Head) = YSMP_MEM_SIZE(MH);
        FEEndianToNet(YSMPHEAD_MEM_SIZE(Head),INT32_SIZE);

        YSMPHEAD_MEM_STA(Head) = YSAPP_STATUS_RUNNING;
        YSMPHEAD_MEM_TYPE(Head) = YSMP_MEM_CT(MH);

        /* R[2] */

        if ( YSVarHasKey(Var) )
        {
            MEMNCPY(YSMPHEAD_MEM_VER(Head),YSVarGetKey(Var) \
                ,sizeof(YSMPHEAD_MEM_VER(Head)),YSVarGetKeyLen(Var));
        }

        *(INT32*)YSMPHEAD_MEM_MAX(Head) = Max;
        FEEndianToNet(YSMPHEAD_MEM_MAX(Head),INT32_SIZE);

        *(INT32*)YSMPHEAD_MEM_LEN(Head) = M;
        FEEndianToNet(YSMPHEAD_MEM_LEN(Head),INT32_SIZE);

        *(INT32*)YSMPHEAD_MEM_ILEN(Head) = \
            YSVarBinGetLen(YSMP_MEM_IBUF(MH)) - YSMPHEAD_ST_SIZE;
        FEEndianToNet(YSMPHEAD_MEM_ILEN(Head),INT32_SIZE);

        *(INT32*)YSMPHEAD_MEM_CLEN(Head) = \
            YSVarBinGetLen(YSMP_MEM_CBUF(MH));
        FEEndianToNet(YSMPHEAD_MEM_CLEN(Head),INT32_SIZE);

        YSMPHEAD_INIT_LUCK(Head);
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
    Size = YSVarHashGetBase(Var);
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
        if ( !YSMPPackBase(IBuf,i,LLen) )
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
            if ( !YSMPPackIdx(IBuf,YSVarGetKeyHash(V),CPos,CLen-CPos) )
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
    Len = YSVarArrayGetLen(Var);
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
        if ( !YSMPPackIdx(IBuf,YSVarGetKeyHash(V),CPos,CLen-CPos) )
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
        if ( NULL==(Bin=YSVarBinSetValue(YSMP_MEM_CTX(MHS) \
            ,YSMP_MEM_CLEN(MHS),YSMP_MEM_CLEN(MHS))) )
        {
            break;
        }
        if ( YSMP_CT_ISHASH(YSMP_MEM_CT(MHS)) )
        {
            Var = YSMPHashFromVarBin(Bin);
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

void *YSMPHashFromVarBin(void *Bin)
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
        if ( NULL==(Var=YSVarHashNew(YSMP_HEAD_BASE)) )
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

#ifdef __OS_LINUX__

BOOL  YSMPToShm(const char *Key,void *Var,INT32 Max)
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
        if ( !YSMPToMem(&MH,Var,Max) )
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
    Len = YSCAL_MAX(1,Idx);
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
        for ( IIdx=0;IIdx<Len;IIdx++ )
        {
            if ( !(bRtn=YSMPMemFind(MHS,Key,IIdx,NULL,&V,&PL)) )
            {
                break;
            }
        }
        if ( (IIdx<Len)||!bRtn )
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

#ifdef __cplusplus
}
#endif
 
