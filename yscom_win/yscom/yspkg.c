/***************************************************************************/
/**[File Name    ]yspkg.c                                                 **/
/**[File Path    ]$(SRCDIR)/libsrc/yscom                                  **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(HOME)/lib                                             **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for pkg                                     **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#ifdef __OS_WIN__
#include <winsock2.h>
#ifdef _WINDEF_
#define __OS_WIN_WINDEF__ 1
#endif
#endif
#include <yscom.h>
#ifdef __OS_LINUX__
#include <feunit.h>
#endif


#ifdef __cplusplus
extern "C"{
#endif

BOOL  YSPkgTcpWritePkg(INT32 Sock,INT32 TO,void *Head);

BOOL  YSPkgDataToStruct(void *PkgStruct,INT32 PkgSize,void *Pkg,INT32 PkgLen)
{
    INT32 RtnPos;
    INT32 MsgPos;
    INT32 DataPos;
    if ( (NULL==PkgStruct)||(YSPKG_HEADSTRUCT_ST_SIZE>PkgSize) \
        ||(NULL==Pkg)||(YSPKG_HEADPKG_LEN>PkgLen) )
    {
        return FALSE;
    }
    memset(PkgStruct,0,YSPKG_HEADSTRUCT_ST_SIZE);
    YSPKG_HEADSTRUCT_MEM_VERM(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_VERM_POS];
    YSPKG_HEADSTRUCT_MEM_VERS(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_VERS_POS];

    YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_REQT_POS];
    memcpy(YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct) \
        ,((UCHAR*)Pkg)+YSPKG_HEADPKG_TYPE_POS,YSPKG_HEADPKG_TYPE_LEN);

    YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_SUM_POS];
    YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_NUM_POS];
    if ( (0>=YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) \
        ||(YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
        >YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct)) )
    {
        return FALSE;
    }

    memcpy((UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct))) \
        ,((UCHAR*)Pkg)+YSPKG_HEADPKG_DSUM_POS,YSPKG_HEADPKG_DSUM_LEN);
    FEEndianToHost((UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct))) \
        ,YSPKG_HEADPKG_DSUM_LEN);
    memcpy((UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct))) \
        ,((UCHAR*)Pkg)+YSPKG_HEADPKG_DLEN_POS,YSPKG_HEADPKG_DLEN_LEN);
    FEEndianToHost((UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct))) \
        ,YSPKG_HEADPKG_DLEN_LEN);

    if ( YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
        >YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) )
    {
        return FALSE;
    }

    if ( (YSPKG_HEADPKG_REQT_RESP==YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) \
        && (1==YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) )
    {
        YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) \
            = ((UCHAR*)Pkg)[YSPKG_HEADPKG_RTNLEN_POS];
        YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct) \
            = ((UCHAR*)Pkg)[YSPKG_HEADPKG_MSGLEN_POS];
        RtnPos = YSPKG_HEADPKG_RTN_POS;
        MsgPos = RtnPos+YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct);
        DataPos = MsgPos+YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
        if ( (PkgLen<=RtnPos)||(PkgLen<=MsgPos)||(PkgLen<=DataPos) )
        {
        }
        else
        {
            MEMCPY(YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct),((UCHAR*)Pkg)+RtnPos \
                ,sizeof(YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct)) \
                ,YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct));
            MEMCPY(YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct),((UCHAR*)Pkg)+MsgPos \
                ,sizeof(YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct)) \
                ,YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct));
            if ( PkgLen \
                ==YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) )
            {
                YSPKG_HEADSTRUCT_MEM_DATALEN(PkgStruct) \
                    = YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) \
                    -YSPKG_HEADPKG_RTNLEN_LEN \
                    -YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) \
                    -YSPKG_HEADPKG_MSGLEN_LEN \
                    -YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
            }
            else
            {
                YSPKG_HEADSTRUCT_MEM_DATALEN(PkgStruct) \
                    = YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
                    -YSPKG_HEADPKG_RTNLEN_LEN \
                    -YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) \
                    -YSPKG_HEADPKG_MSGLEN_LEN \
                    -YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
            }
            YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) = YSPKG_HEADPKG_LEN \
                +YSPKG_HEADPKG_RTNLEN_LEN \
                +YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) \
                +YSPKG_HEADPKG_MSGLEN_LEN \
                +YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
        }
    }
    else
    {
        YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) = 0;
        YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct) = 0;
        DataPos = YSPKG_HEADPKG_LEN;
        YSPKG_HEADSTRUCT_MEM_DATALEN(PkgStruct) \
            = YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct);
        YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) = YSPKG_HEADPKG_LEN;
    }
    if ( PkgLen>DataPos )
    {
        YSPKG_HEADSTRUCT_MEM_DATA(PkgStruct) = ((UCHAR*)Pkg)+DataPos;
    }
    else
    {
        YSPKG_HEADSTRUCT_MEM_DATA(PkgStruct) = NULL;
    }
    YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct) \
        = YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct)+YSPKG_HEADPKG_LEN;
    return TRUE;
}

INT32 YSPkgStructToData(void *Pkg,INT32 PkgSize,void *PkgStruct)
{
    INT32 RtnPos;
    INT32 MsgPos;
    INT32 DataPos;
    if ( (NULL==Pkg)||(YSPKG_HEADPKG_LEN>PkgSize)||(NULL==PkgStruct) )
    {
        return YSRTN_ERAPP_ARG;
    }
    memset(Pkg,0,PkgSize);
    
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_VERM_POS] \
        = YSPKG_HEADSTRUCT_MEM_VERM(PkgStruct);
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_VERS_POS] \
        = YSPKG_HEADSTRUCT_MEM_VERS(PkgStruct);

    if ( !YSPKG_HEADPKG_ISREQT(YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) )
    {
        return YSRTN_ERPKG_PACK;
    }
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_REQT_POS] \
        = YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct);
        
    if ( 0==strlen(YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct)) )
    {
        return YSRTN_ERPKG_PACK;
    }
    memcpy(((UCHAR*)Pkg)+YSPKG_HEADPKG_TYPE_POS \
        ,YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct),YSPKG_HEADPKG_TYPE_LEN);

    if ( (0>=YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) \
        ||(YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
        >YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct)) )
    {
        return YSRTN_ERPKG_PACK;
    }
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_SUM_POS] = YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct);
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_NUM_POS] = YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct);

    if ( PkgSize<YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) )
    {
        return YSRTN_ERPKG_PACK;
    }
    if ( YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
        >YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) )
    {
        return YSRTN_ERPKG_PACK;
    }
    memcpy(((UCHAR*)Pkg)+YSPKG_HEADPKG_DSUM_POS \
        ,(UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct))) \
        ,YSPKG_HEADPKG_DSUM_LEN);
    FEEndianToNet(((UCHAR*)Pkg)+YSPKG_HEADPKG_DSUM_POS,YSPKG_HEADPKG_DSUM_LEN);
    memcpy(((UCHAR*)Pkg)+YSPKG_HEADPKG_DLEN_POS \
        ,(UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct))) \
        ,YSPKG_HEADPKG_DLEN_LEN);
    FEEndianToNet(((UCHAR*)Pkg)+YSPKG_HEADPKG_DLEN_POS,YSPKG_HEADPKG_DLEN_LEN);

    if ( (YSPKG_HEADPKG_REQT_RESP==YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) \
        && (1==YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) )
    {
        ((UCHAR*)Pkg)[YSPKG_HEADPKG_RTNLEN_POS] \
            = YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct)%0xFF;
         ((UCHAR*)Pkg)[YSPKG_HEADPKG_MSGLEN_POS] \
            = YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct)%0xFF;
        RtnPos = YSPKG_HEADPKG_RTN_POS;
        MsgPos = RtnPos+YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct);
        DataPos = MsgPos+YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
        if ( (PkgSize<RtnPos)||(0>=YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct)) \
            ||(PkgSize<MsgPos)||(PkgSize<DataPos) )
        {
            return YSRTN_ERPKG_PACK;
        }
        if ( 0<YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) )
        {
            memcpy(((UCHAR*)Pkg)+RtnPos,YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct) \
                ,YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct));
        }
        if ( 0<YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct) )
        {
            memcpy(((UCHAR*)Pkg)+MsgPos,YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct) \
                ,YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct));
        }
    }
    if ( 0<YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) )
    {
        if ( NULL==YSPKG_HEADSTRUCT_MEM_DATA(PkgStruct) )
        {
            return YSRTN_ERPKG_PACK;
        }
    }
    if ( YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct) \
        !=YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) )
    {
        return YSRTN_ERPKG_PACK;
    }
    return YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct);
}

BOOL  YSPkgStructInit(void *PkgStruct,BOOL ReqT,const char *Type \
    ,INT32 PkgSum,INT32 PkgNum,INT32 DSum,INT32 DLen,void *Data \
    ,INT32 RtnLen,void *Rtn,INT32 MsgLen,void *Msg)
{
    if ( (NULL==PkgStruct)||(NULL==Type) \
        ||(0>=PkgNum)||(PkgNum>PkgSum)||(0>DLen)||(DLen>DSum) )
    {
        return FALSE;
    }
    if ( 0==strlen(Type) )
    {
        return FALSE;
    }
    memset(PkgStruct,0,YSPKG_HEADSTRUCT_ST_SIZE);

    YSPKG_HEADSTRUCT_MEM_VERM(PkgStruct) = YSPKG_HEADPKG_VERM;
    YSPKG_HEADSTRUCT_MEM_VERS(PkgStruct) = YSPKG_HEADPKG_VERS;

    YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct) = \
        (ReqT)?YSPKG_HEADPKG_REQT_REQ:YSPKG_HEADPKG_REQT_RESP;

    MEMCPY(YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct),Type \
        ,sizeof((((tYSPkgHeadStruct*)(PkgStruct))->PkgType)),strlen(Type));

    YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct) = PkgSum;
    YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) = PkgNum;
    if ( !ReqT && (1==PkgNum) )
    {
        if ( (NULL==Rtn)||(0>=RtnLen) )
        {
            return FALSE;
        }
        YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) = RtnLen;
        YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct) = MsgLen;
        if ( (0<MsgLen)&&(NULL==Msg) )
        {
            return FALSE;
        }
        MEMCPY(YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct),Rtn \
            ,sizeof(YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct)),RtnLen);
        if ( (0<MsgLen)&&(NULL!=Msg) )
        {
            MEMCPY(YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct),Msg \
                ,sizeof(YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct)),MsgLen);
        }

        YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) = DSum \
            +YSPKG_HEADPKG_RTNLEN_LEN+RtnLen \
            +YSPKG_HEADPKG_MSGLEN_LEN+MsgLen;
        YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) = DLen \
            +YSPKG_HEADPKG_RTNLEN_LEN+RtnLen \
            +YSPKG_HEADPKG_MSGLEN_LEN+MsgLen;
        YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) = YSPKG_HEADPKG_LEN \
            +YSPKG_HEADPKG_RTNLEN_LEN+RtnLen \
            +YSPKG_HEADPKG_MSGLEN_LEN+MsgLen;
    }
    else
    {
        YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) = DSum;
        YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) = DLen;
        YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) = YSPKG_HEADPKG_LEN;
    }
    YSPKG_HEADSTRUCT_MEM_DATALEN(PkgStruct) = DLen;
    YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct) \
        = YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct);
    YSPKG_HEADSTRUCT_MEM_DATA(PkgStruct) = Data;
    return TRUE;
    
}

void  YSPkgHeadStructShow(void *PkgStruct,INT32 T,void *Buf)
{
    char Tmp[TMP_MAX_BUFFER];
    char Tab[64];
    if ( NULL==PkgStruct )
    {
        return ;
    }
    memset(Tab,0,sizeof(Tab));
    YSVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    memset(Tmp,0,sizeof(Tmp));
    snprintf(Tmp,sizeof(Tmp),"%s<Ver>%d.%d</Ver>\n" 
         "%s<PkgReq>%s</PkgReq>\n"
         "%s<PkgType>%s</PkgType>\n"
         "%s<PkgSum>%d</PkgSum>\n"
         "%s<PkgNum>%d</PkgNum>\n"
         "%s<DataSum>%d</DataSum>\n"
         "%s<DataLen>%d</DataLen>\n"
         "%s<HeadLen>%d</HeadLen>\n"
         "%s<PkgLen>%d</PkgLen>\n"
        ,Tab,YSPKG_HEADSTRUCT_MEM_VERM(PkgStruct) \
            ,YSPKG_HEADSTRUCT_MEM_VERS(PkgStruct) \
        ,Tab,YSPKG_HEADPKG_REQT_STR(YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct));
    YSVarStringCat(Buf,Tmp,strlen(Tmp));
#if 0
    if ( (YSPKG_HEADPKG_REQT_RESP==YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) \
        &&(1==SPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) )
    {
        memset(Tmp,0,sizeof(Tmp));
        snprinf(Tmp,sizeof(Tmp),"%s<RtnCode>%s</RtnCode>\n" 
             "%s<RtnMsg>%s</RtnMsg>\n" \
            ,Tab,PKG_HEADSTRUCT_MEM_RTN(PkgStruct) \
            ,Tab,PKG_HEADSTRUCT_MEM_MSG(PkgStruct));
        YSVarStringCat(Buf,Tmp,strlen(Tmp));
    }
#endif
}

BOOL  YSPkgTcpRead(INT32 Sock,INT32 TO,void *Pkg,void *Head)
{
    INT32 T;
    char SBuf[YSPKG_HEADPKG_MAXLEN+1];
    void *Buf;
    void *Recv;
    INT32 Len;
    INT32 iRtn;
    INT32 RLen;
    BOOL bRtn;
#ifdef __OS_LINUX__
    char Tmp[TMP_MAX_BUFFER];
#endif
	char aa[1024];
	FILE * fp;
    if ( (0>Sock)||!YSVarIsInit2(Pkg,VARTYPE_MEM_VT_BIN)||(NULL==Head) )
    {
        return FALSE;
    }

    Buf = NULL;
    T = YSCAL_MAX(1,TO);
    T = YSCAL_MIN(T,TCP_TIMEOUT);
    while( 1 )
    {
        Recv = NULL;
        memset(SBuf,0,sizeof(SBuf));
        if ( YSPKG_HEADPKG_LEN!=recv(Sock,SBuf,YSPKG_HEADPKG_LEN,MSG_PEEK) )
        {
            break;
        }
        memset(Head,0,YSPKG_HEADSTRUCT_ST_SIZE);
        if ( !YSPkgDataToStruct(Head,YSPKG_HEADSTRUCT_ST_SIZE \
            ,SBuf,YSPKG_HEADPKG_LEN) )
        {
            break;
        }
        if ( YSVarIsInit(Buf) )
        {
            YSVarStringReset(Buf);
        }
        else if ( NULL==(Buf= \
            YSVarStringNew2(YSPKG_HEADSTRUCT_MEM_PKGLEN((Head)))) )
        {
            break;
        }
#ifdef __OS_LINUX__
        Len = 0;
        iRtn = FETcpRead(Sock,T \
            ,YSVarStringGet(Buf),&Len,YSPKG_HEADSTRUCT_MEM_PKGLEN((Head)));
#elif __OS_WIN__
        Len = YSPKG_HEADSTRUCT_MEM_PKGLEN(Head);
		
		fp = fopen("lib.log", "a+");
		memset(aa,0,sizeof(aa));
		sprintf(aa,"Len=%d,%d,%d,%08X\n",Len,YSPKG_HEADSTRUCT_MEM_PKGLEN(Head),*(INT32*)(SBuf+YSPKG_HEADPKG_DSUM_POS),*(INT32*)(SBuf+YSPKG_HEADPKG_DSUM_POS));
		fprintf(fp,"%s",aa);
		fclose(fp);
        if ( Len!=(iRtn=SocketRead(Sock,T,YSVarStringGet(Buf),Len)) )
        {
            Len = 0;
            if ( 0<iRtn )
            {
                iRtn = 0;
            }
        }
        else
        {
            iRtn = 2;
        }
#endif
        if ( 0>iRtn )
        {
            break;
        }
        if ( 0<Len )
        {
            YSVarStringSetLen(Buf,Len);
        }
        if ( Len==YSPKG_HEADSTRUCT_MEM_PKGLEN(Head) )
        {
            if ( 1==YSPKG_HEADSTRUCT_MEM_NUM(Head) )
            {
                Recv = YSVarStringGet(Buf);
                RLen = Len;
            }
            else
            {
                Recv = ((char*)YSVarStringGet(Buf))+YSPKG_HEADPKG_LEN;
                RLen = Len-YSPKG_HEADPKG_LEN;
            }
            if ( !YSVarBinCat(Pkg,Recv,RLen) )
            {
                break;
            }
        }
        /* 0 : time out & piRecvLen is length of data */
        /* 1 socket close or read over & piRecvLen is length of data */
        /* 2 read data of length */
        /* 3 : socket close & read data is 0 */
        if ( YSPKG_HEADSTRUCT_MEM_SUM(Head)==YSPKG_HEADSTRUCT_MEM_NUM(Head) )
        {
            bRtn = TRUE;
            break;
        }
        if ( (2!=iRtn) \
            ||(Len!=YSPKG_HEADSTRUCT_MEM_PKGLEN(Head)) )
        {
            break;
        }
    }
    if ( bRtn )
    {
        if ( !YSPkgDataToStruct(Head,YSPKG_HEADSTRUCT_ST_SIZE \
            ,YSVarBinGet(Pkg),YSVarBinGetLen(Pkg)) )
        {
            bRtn = FALSE;
        }
        else
        {
#ifdef __OS_LINUX__
            YSHexTraceDebug(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,YSVarBinGet(Pkg),YSVarBinGetLen(Pkg));
#endif
        }
    }
    YSVarStringFree(Buf);
    Buf = NULL;
    return bRtn;
}

BOOL  YSPkgTcpWrite(INT32 Sock,INT32 TO,void *Head)
{
    UINT32 DSum;
    INT32 DLen;
    INT32 Sum;
    INT32 Num;
    INT32 Pos;
    char *P;
    tYSPkgHeadStruct HS;
    BOOL bRtn;

    if ( (0>Sock)||(NULL==Head) )
    {
        return FALSE;
    }
    bRtn = TRUE;
    DSum = YSPKG_HEADSTRUCT_MEM_DATALEN(Head);
    Sum = (YSPKG_MAX_SIZE<DSum)?(DSum/YSPKG_MAX_SIZE):1;
    Pos = 0;
    P = YSPKG_HEADSTRUCT_MEM_DATA(Head);
    for ( Num=1;Num<=Sum;Num++ )
    {
        DLen = DSum-Pos;
        DLen = YSCAL_MIN(YSPKG_MAX_SIZE,DLen);
        P = P+Pos;
        memset(&HS,0,sizeof(HS));
        if ( !YSPkgStructInit(&HS \
            ,YSRTN_CMPBOOL(YSPKG_HEADPKG_REQT_REQ \
                ==YSPKG_HEADSTRUCT_MEM_REQT(Head)) \
            ,YSPKG_HEADSTRUCT_MEM_TYPE(Head) \
            ,Sum,Num,DSum,DLen,P \
            ,YSPKG_HEADSTRUCT_MEM_RTNLEN(Head),YSPKG_HEADSTRUCT_MEM_RTN(Head) \
            ,YSPKG_HEADSTRUCT_MEM_MSGLEN(Head),YSPKG_HEADSTRUCT_MEM_MSG(Head)) )
        {
            bRtn = FALSE;
            break;
        }
        if ( !YSPkgTcpWritePkg(Sock,TO,&HS) )
        {
            bRtn = FALSE;
            break;
        }

        Pos += DLen;
    }
    return bRtn;
}

BOOL  YSPkgTcpWritePkg(INT32 Sock,INT32 TO,void *Head)
{
    char SBuf[TMP_MAX_BUFFER];
    INT32 T;
    INT32 iRtn;
    BOOL bRtn;
#ifdef __OS_LINUX__
    char Tmp[TMP_MAX_BUFFER];
#endif

    if ( (0>Sock)||(NULL==Head) )
    {
        return FALSE;
    }
    bRtn = FALSE;
    iRtn = YSRTN_OK;
    T = YSCAL_MAX(1,TO);
    T = YSCAL_MIN(T,TCP_TIMEOUT);
    while( 1 )
    {
        memset(SBuf,0,sizeof(SBuf));
        if ( YSPKG_HEADSTRUCT_MEM_PKGLEN(Head)!= \
            YSPkgStructToData(SBuf,sizeof(SBuf),Head) )
        {
            break;
        }
#ifdef __OS_LINUX__
        iRtn = FETcpWrite(Sock,T,SBuf,YSPKG_HEADSTRUCT_MEM_HEADLEN(Head));
#elif __OS_WIN__
        iRtn = SocketWrite(Sock,T,SBuf,YSPKG_HEADSTRUCT_MEM_HEADLEN(Head));
#endif
        if ( 0>iRtn )
        {
            break;
        }
#ifdef __OS_LINUX__
        iRtn = FETcpWrite(Sock,T \
            ,YSPKG_HEADSTRUCT_MEM_DATA(Head) \
            ,YSPKG_HEADSTRUCT_MEM_DATALEN(Head));
#else
        iRtn = SocketWrite(Sock,T \
            ,YSPKG_HEADSTRUCT_MEM_DATA(Head) \
            ,YSPKG_HEADSTRUCT_MEM_DATALEN(Head));
#endif
        if ( 0>iRtn )
        {
            break;
        }
#ifdef __OS_LINUX__
        YSHexTraceDebug(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,SBuf,YSPKG_HEADSTRUCT_MEM_HEADLEN(Head));
        YSHexTraceDebug(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,YSPKG_HEADSTRUCT_MEM_DATA(Head) \
            ,YSPKG_HEADSTRUCT_MEM_DATALEN(Head));
#endif
        bRtn = TRUE;
        break;
    }
    return bRtn;
}


#ifdef __OS_WIN__
int SocketOpen(const char *Ip,int port)
{
    SOCKADDR_IN sockAddr; 
    SOCKET      sockfd;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port   = htons(port);
    sockAddr.sin_addr.s_addr = inet_addr( Ip );

    if ( INVALID_SOCKET==(sockfd=socket(PF_INET,SOCK_STREAM,0)) )
    {
        return -1;
    }
    if ( SOCKET_ERROR==connect(sockfd,(LPSOCKADDR)&sockAddr,sizeof(sockAddr)) )
    {
        return -1;
    }
    return sockfd;
}

int SocketClose(int sock)
{
    return closesocket(sock);
}

int SocketReadTimtOut(int sockfd,int iTimeOut)
{
    fd_set readmask;
    struct timeval stTimeOut;
    int iResult;

    FD_ZERO(&readmask);
    FD_SET(sockfd,&readmask);
    stTimeOut.tv_sec = iTimeOut;
    stTimeOut.tv_usec = 0;

    iResult=select(sockfd+1,&readmask,(fd_set *)0,(fd_set *)0,&stTimeOut);
    if (iResult<0)
    {
        return -1;
    }
    else if (iResult==0)   /* select timeout */
    {
        return 0;
    }

    if (FD_ISSET(sockfd,&readmask))
        return 1;
    return 0;
}

int SocketWriteTimtOut(int sockfd,int iTimeOut)
{
    fd_set writemask;
    struct timeval stTimeOut;
    int iResult;

    FD_ZERO(&writemask);
    FD_SET(sockfd,&writemask);
    stTimeOut.tv_sec = iTimeOut;
    stTimeOut.tv_usec = 0;

    iResult=select(sockfd+1,(fd_set *)0,&writemask,(fd_set *)0,&stTimeOut);

    if (iResult<0)
    {
        return -1;
    }
    else if (iResult==0) /* select timeout */
    {
        return 0;
    }

    if (FD_ISSET(sockfd,&writemask))
        return 1;
    return 0;
}

int SocketRead(int sockfd,int iTimeOut,char *pcBuffer,int iLength)
{
	int r;
	int p;
	int l;
	FILE *fp;
	int i;
	p = 0;
	r = 0;
	l = iLength;
	while( p<l )
	{
		if ( !SocketReadTimtOut(sockfd,iTimeOut) )
		{
			break;
		}
		if ( 0>(r=recv(sockfd,pcBuffer,l-p,0)) )
		{
			continue;
		}
		fp = fopen("lib.log", "a+");
		fprintf(fp,"SocketRead: l=%d,r=%d,p=%d,r+p=%d\n",l,r,p,r+p);
		fclose(fp);
		p += r;
	}
	fp = fopen("lib.log", "a+");
	fprintf(fp,"SocketRead: l=%d,p=%d\n",l,p);

	for (i = 0; i < iLength /16; ++i) {
		fprintf(fp, "%6d %x %x %x %x %x %x %x %x  %x %x %x %x %x %x %x %x  $ %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c $",
			i,
			pcBuffer[i*16 + 0], pcBuffer[i*16 + 1], pcBuffer[i*16 + 2], pcBuffer[i*16 + 3], pcBuffer[i*16 + 4], pcBuffer[i*16 + 5], pcBuffer[i*16 + 6], pcBuffer[i*16 + 7],
			pcBuffer[i*16 + 8], pcBuffer[i*16 + 9], pcBuffer[i*16 + 10], pcBuffer[i*16 + 11], pcBuffer[i*16 + 12], pcBuffer[i*16 + 13], pcBuffer[i*16 + 14], pcBuffer[i*16 + 15],
			pcBuffer[i*16 + 0], pcBuffer[i*16 + 1], pcBuffer[i*16 + 2], pcBuffer[i*16 + 3], pcBuffer[i*16 + 4], pcBuffer[i*16 + 5], pcBuffer[i*16 + 6], pcBuffer[i*16 + 7],
			pcBuffer[i*16 + 8], pcBuffer[i*16 + 9], pcBuffer[i*16 + 10], pcBuffer[i*16 + 11], pcBuffer[i*16 + 12], pcBuffer[i*16 + 13], pcBuffer[i*16 + 14], pcBuffer[i*16 + 15]);
	}
	fclose(fp);
	return p;
}

int SocketWrite(int sockfd,int iTimeOut,char *pcBuffer,int iLength)
{
    if ( !SocketWriteTimtOut(sockfd,iTimeOut) )
    {
        return -1;
    }
    return send( sockfd,pcBuffer,iLength,0 );
}

#endif

#ifdef __cplusplus
}
#endif

