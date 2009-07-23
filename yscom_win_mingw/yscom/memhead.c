/***************************************************************************/
/**[File Name    ]memhead.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for share memory ( head )                   **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifdef __OS_WIN__
#include <winsock2.h>
#ifdef __WITH_MINGW__
#include <sys/types.h>
#endif
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
 
INT32 YSMPHeadSize()
{
    return YSMPHEAD_ST_SIZE;
}
 
void  YSMPHeadShow(void *Head,INT32 T,void *Buf)
{
    char Log[YSAPP_TMP_LEN];
    char Tab[BUFSIZE_64];
    INT32 i;
    INT32 L;
    INT32 Size;
 
    if ( !YSMPIsInit(Head)||!YSVarIsInit2(Buf,VARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    memset(Tab,0,sizeof(Tab));
    YSVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    memset(Log,0,sizeof(Log));
    snprintf(Log,sizeof(Log),"%s<Head>\n"
         "%s <Size>%d / %08X</Size>\n"
         "%s <Status>%s</Status>\n"
         "%s <Type>%d</Type>\n"
         "%s <Ver>%s</Ver>\n"
         "%s <Time>%d / %08X</Time>\n"
         "%s <Max>%d / %08X</Max>\n"
         "%s <Len>%d / %08X</Len>\n"
         "%s <IdxSize>%d / %08X</IdxSize>\n"
         "%s <ILen>%d / %08X</ILen>\n"
         "%s <CtxSize>%d / %08X</CtxSize>\n"
         "%s <CLen>%d / %08X</CLen>\n"
        ,Tab \
        ,Tab,ntohl(YSMPHEAD_MEM_SIZE_INT(Head)) \
            ,YSMPHEAD_MEM_SIZE_INT(Head) \
        ,Tab,YSAPP_STATUS_STR(YSMPHEAD_MEM_STA(Head)) \
        ,Tab,YSMPHEAD_MEM_TYPE(Head) \
        ,Tab,YSMPHEAD_MEM_VER(Head) \
        ,Tab,ntohl(YSMPHEAD_MEM_TIME_INT(Head)) \
            ,YSMPHEAD_MEM_TIME_INT(Head) \
        ,Tab,ntohl(YSMPHEAD_MEM_MAX_INT(Head)) \
            ,YSMPHEAD_MEM_MAX_INT(Head) \
        ,Tab,ntohl(YSMPHEAD_MEM_LEN_INT(Head)) \
            ,YSMPHEAD_MEM_LEN_INT(Head) \
        ,Tab,ntohl(YSMPHEAD_MEM_IDXSIZE_INT(Head)) \
            ,YSMPHEAD_MEM_IDXSIZE_INT(Head) \
        ,Tab,ntohl(YSMPHEAD_MEM_ILEN_INT(Head)) \
            ,YSMPHEAD_MEM_ILEN_INT(Head) \
        ,Tab,ntohl(YSMPHEAD_MEM_CTXSIZE_INT(Head)) \
            ,YSMPHEAD_MEM_CTXSIZE_INT(Head) \
        ,Tab,ntohl(YSMPHEAD_MEM_CLEN_INT(Head)) \
            ,YSMPHEAD_MEM_CLEN_INT(Head));
    YSVarStringCat(Buf,Log,strlen(Log));

    memset(Log,0,sizeof(Log));
    L = 0;
    if ( YSMP_CT_ISHASH(YSMPHEAD_MEM_TYPE(Head)) )
    {
        Size = YSMPHEAD_MEM_MAX_INT(Head);
        FEEndianToHost_Int32(&Size);
        for ( i=0;i<Size;i++ )
        {
            if ( L > sizeof(Log)/2 )
            {
                YSVarStringCat(Buf,Log,L);
                memset(Log,0,sizeof(Log));
                L = 0;
            }
            snprintf(Log+L,sizeof(Log)-L,"%s <Idx>\n"
                 "%s  <Addr>%d / %08X</Addr>\n"
                 "%s  <Len>%d / %08X</Len>\n"
                 "%s </Idx>\n"
                ,Tab \
                ,Tab,ntohl(YSMPHEAD_MEM_IIDX_ADDR_INT(Head,i)) \
                    ,YSMPHEAD_MEM_IIDX_ADDR_INT(Head,i) \
                ,Tab,ntohl(YSMPHEAD_MEM_IIDX_LEN_INT(Head,i)) \
                    ,YSMPHEAD_MEM_IIDX_LEN_INT(Head,i) \
                ,Tab);
            L += strlen(Log+L);
        }
    }
    snprintf(Log+L,sizeof(Log)-L,"%s</Head>\n",Tab);
    L += strlen(Log+L);
    YSVarStringCat(Buf,Log,L);
}

BOOL  YSMPHeadSetHashIdx(void *IBuf,INT32 Max,INT32 Idx,INT32 Len)
{
    void *V;
    INT32 L;
    if ( !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        ||( (0>Idx)||(Max<=Idx) )||(0>Len) )
    {
        return FALSE;
    }
    if ( NULL==(V=YSVarBinGet(IBuf)) )
    {
        return FALSE;
    }
    L = YSVarBinGetLen(IBuf);
    if ( (INT32)YSMPHEAD_ST_SIZE_CAL(Max)>L )
    {
        return FALSE;
    }
    YSMPHEAD_MEM_IIDX_ADDR_INT(V,Idx) = L-YSMPHEAD_ST_SIZE_CAL(Max);
    YSMPHEAD_MEM_IIDX_LEN_INT(V,Idx) = Len;
    FEEndianToNet_Int32(YSMPHEAD_MEM_IIDX_ADDR(V,Idx));
    FEEndianToNet_Int32(YSMPHEAD_MEM_IIDX_LEN(V,Idx));
    return TRUE;
}

BOOL  YSMPHeadIsInit(void *Head,INT32 Size)
{
    if ( (NULL==Head)||(YSMPHEAD_ST_SIZE>Size) )
    {
        return FALSE;
    }
    return YSLUCK_ISINIT(YSMPHEAD_MEM_LUCK_INT(Head));
}

BOOL  YSMPHeadUpdateTime(void *Head,INT32 Size)
{
    if ( !YSMPHeadIsInit(Head,Size) )
    {
        return FALSE;
    }
    YSMPHEAD_MEM_TIME_INT(Head) = (INT32)time(NULL);
    FEEndianToNet(YSMPHEAD_MEM_TIME(Head),INT32_SIZE);
    return TRUE;
}

BOOL  YSMPHeadNeedUpdate(void *Head,INT32 Size,INT32 Time)
{
    INT32 T;
    if ( !YSMPHeadIsInit(Head,Size) )
    {
        return FALSE;
    }
    T = YSMPHEAD_MEM_TIME_INT(Head);
    FEEndianToHost(&T,INT32_SIZE);
    return RTNCODE_CMPBOOL(T!=Time);
}

BOOL  YSMPHeadLenPlus(void *Head,INT32 Size,BOOL Flag)
{
    INT32 Len;
    if ( !YSMPHeadIsInit(Head,Size) )
    {
        return FALSE;
    }
    Len = YSMPHEAD_MEM_LEN_INT(Head);
    FEEndianToHost(&Len,INT32_SIZE);
    Len += ((Flag)?1:-1);
    FEEndianToNet(&Len,INT32_SIZE);
    YSMPHEAD_MEM_LEN_INT(Head) = Len;
    return TRUE;
}

#ifdef __cplusplus
}
#endif
 
