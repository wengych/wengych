/***************************************************************************/
/**[File Name    ]checkpwd.c                                              **/
/**[File Path    ]$(SRCDIR)/ys/mobik/checkpwd                             **/
/**[Library Name ]libmobik.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define service for mobi-k(checkpwd)                     **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <yscom.h>
#include <mobik.h>

#ifdef __cplusplus
extern "C"{
#endif

INT32 MobiKCheckPwd(void *Bus)
{
    void *Acc;
    void *Trno;
    void *Pwd;
    void *Send;
    void *Bin;
    void *Recv;
    char *V;
    INT32 L;
    INT32 iRtn;
    INT32 Rtn;
    void *Cfg;
    void *BinView;
    void *View;
    char *Ver;
    char *IP;
    INT32 Port;
    INT32 TO;
    char Tmp[YSAPP_TMP_LEN];

    if ( !YSVarIsInit2(Bus,VARTYPE_MEM_VT_HASH) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Bus is not ready.");
        return RTNCODE_ER;
    }
    iRtn = RTNCODE_ER;
    Rtn = RTNCODE_ER;
    Send = NULL;
    Recv = NULL;
    Bin = NULL;
    BinView = NULL;
    View = NULL;
    while( 1 )
    {
        if ( NULL==(Cfg=YSAppArgsGetCfg()) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSAppArgsGetCfg.");
            break;
        }
        if ( NULL==(Ver=YSVarStringGet(YSVarHashGet(Cfg,MOBIK_8583_VIEW))) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at Get MobiK ISO8583 Information.");
            break;
        }
        if ( NULL==(BinView=YSMgrShmGetISO8583(Ver)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSMgrShmGetISO8583.");
            break;
        }
        if ( NULL==(View=ISO8583InfoGetFields(YSVarBinGet(BinView) \
            ,YSVarBinGetLen(BinView))) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583InfoGetFields.");
            break;
        }
        if ( NULL==(Send=ISO8583New()) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583New.");
            break;
        }
        MOBIK_USERBUS_MACRO_GETFIELD(Bus,MOBIK_ACCOUNT,Acc,V,L);
        if ( !ISO8583SetField(Send,ISO8583_IDX_2,View,V,L) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583SetField(%d).",ISO8583_IDX_2);
            break;
        }
        if ( !ISO8583SetField(Send,ISO8583_IDX_3,View,"010000",6) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583SetField(%d).",ISO8583_IDX_3);
            break;
        }
        MOBIK_USERBUS_MACRO_GETFIELD(Bus,MOBIK_TRACENO,Trno,V,L);
        if ( !ISO8583SetField(Send,ISO8583_IDX_11,View,V,L) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583SetField(%d).",ISO8583_IDX_2);
            break;
        }
        MOBIK_USERBUS_MACRO_GETFIELD(Bus,MOBIK_PASSWORD,Pwd,V,L);
#if 1
char ITmp[BUFSIZE_8];
char OTmp[BUFSIZE_8];
char ATmp[BUFSIZE_16+1];
#define MOBIK_DES_KEY \
    "\x12\x34\x56\x78\xAB\xCD\xEF\x90\xAB\xCD\xEF\x90\x12\x34\x56\x78"
memset(ITmp,0,sizeof(ITmp));
memset(OTmp,0,sizeof(OTmp));
memset(ATmp,0,sizeof(ATmp));
memcpy(ITmp,V,YSCAL_MIN(L,sizeof(ITmp)));
DESEncrypt(MOBIK_DES_KEY,0,"",sizeof(ITmp),ITmp,OTmp);
FEStrBytes2Hex(ATmp,sizeof(ATmp),OTmp,sizeof(OTmp));
fprintf(stderr,"ATmp=%s.\n",ATmp);
int i;
for ( i=0;i<8;i++ )
{
fprintf(stderr,"%02X ",((UCHAR*)OTmp)[i]);
}
fprintf(stderr,"\n");
        if ( !ISO8583SetField(Send,ISO8583_IDX_52,View,ATmp,sizeof(ATmp)-1) )
#else
        if ( !ISO8583SetField(Send,ISO8583_IDX_52,View,V,L) )
#endif
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583SetField(%d).",ISO8583_IDX_53);
            break;
        }
        if ( !ISO8583SetField(Send,ISO8583_IDX_MSGTYPE,View \
            ,MOBIK_MSGTYPE_SEND,MOBIK_MSGTYPE_SEND_LEN) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583SetField(%d).",ISO8583_IDX_MSGTYPE);
            break;
        }
        if ( NULL==(IP=YSVarStringGet(YSVarHashGet(Cfg,MOBIK_SERVER_IP))) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarHashGet(%s).",MOBIK_SERVER_IP);
            break;
        }
        if ( NULL==(V=YSVarStringGet(YSVarHashGet(Cfg,MOBIK_SERVER_PORT))) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarHashGet(%s).",MOBIK_SERVER_PORT);
            break;
        }
        Port = atoi(V);
        if ( NULL==(V=YSVarStringGet(YSVarHashGet(Cfg,MOBIK_SERVER_PORT))) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarHashGet(%s).",MOBIK_SERVER_PORT);
            break;
        }
        TO = atoi(V);
        if ( NULL==(Recv=ISO8583New()) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583New.");
            break;
        }

        if ( RTNCODE_OK!=ISO8583TcpClient(IP,Port,TO,Send,Recv,View) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at ISO8583TcpClient(%s:%d).",IP,Port);
            break;
        }

        /* Call Successfully , but need check rtn(39) */
        iRtn = RTNCODE_OK;
        MOBIK_USERBUS_MACRO_GETFIELD2(ISO8583_IDX_MSGTYPE,V);
        if ( memcmp(MOBIK_MSGTYPE_RECV,V,MOBIK_MSGTYPE_RECV_LEN) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at (%d).",ISO8583_IDX_MSGTYPE);
            break;
        }
        MOBIK_USERBUS_MACRO_GETFIELD2(ISO8583_IDX_39,V);
        Rtn = atoi(V);
        break;
    }
    if ( !YSServiceCallSetUserRtn(Bus,Rtn,V) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSServiceCallSetUserRtn.");
        iRtn = RTNCODE_ER;
    }
    ISO8583Free(Send);
    Send = NULL;
    ISO8583Free(Recv);
    Recv = NULL;
    YSVarBinFree(Bin);
    Bin = NULL;
    YSVarFree(BinView);
    BinView = NULL;
    return iRtn;
}

#ifdef __cplusplus
}
#endif

