/****************************************************************************/
/**[File Name    ]appdef.h                                                 **/
/**[File Path    ]$(TOPDIR)/libsrc/yscom                                   **/
/**[Library Name ]                                                         **/
/**[Library Path ]                                                         **/
/**[Author       ]Wang Honggang                                            **/
/**[Copyright    ]Wang Honggang                                            **/
/**[Date         ]2008/11/11                                               **/
/**[Version      ]0.1.0                                                    **/
/**[Memo         ]define const variable                                    **/
/**[Modify       ]                                                         **/
/****************************************************************************/
#ifndef YSDEF_H__
#define YSDEF_H__

#include <yscom.h>

#ifdef __cplusplus
extern "C" {
#endif

#define YSAPP_TIMEOUT_MAX       120

#define YSAPP_STATUS_NOT        0
#define YSAPP_STATUS_RUNNING    1
#define YSAPP_STATUS_PROC       2
#define YSAPP_STATUS_STOP       3
#define YSAPP_STATUS_SHUT       4
#define YSAPP_STATUS_DEFAULT    5
#define YSAPP_STATUS_ISCMD(std) \
    ( (YSAPP_STATUS_NOT==(std))||(YSAPP_STATUS_RUNNING==(std)) \
    ||(YSAPP_STATUS_PROC==(std))||(YSAPP_STATUS_STOP==(std)) \
    ||(YSAPP_STATUS_SHUT==(std))||(YSAPP_STATUS_DEFAULT==(std)))
#define YSAPP_STATUS_STR(sta) \
    ((YSAPP_STATUS_NOT==(sta))?"Not Running" \
    :((YSAPP_STATUS_RUNNING==(sta))?"Running" \
        :((YSAPP_STATUS_PROC==(sta))?"Proc" \
            :((YSAPP_STATUS_STOP==(sta))?"Stop" \
                :((YSAPP_STATUS_SHUT==(sta))?"Shutdown" \
                    :((YSAPP_STATUS_DEFAULT==(sta))?"Default":"Not") \
                ) \
            ) \
        ) \
    ))

/****************************************************************************/
/** define const variable name for system                                  **/
/** Args : --CFG=cfgfile                                                   **/
/****************************************************************************/
#define YSAPP_USAGE_CFG         "--CFG="

/****************************************************************************/
/** define const variable name for system                                  **/
/****************************************************************************/
#define YSAPP_CFG                   "__YSAPP_CFG"
#define YSAPP_VER_MAXLEN            (BUFSIZE_64)  
#define YSAPP_VER_DEFINE            "#VER="
#define YSAPP_VER_DEFINE_LEN        5
/****************************************************************************/
/****************************************************************************/

#define YSAPP_LOADCFG_BASE 1000
#define YSAPP_LOADCFG_FILE_CAL(f,fs,t,v,d) \
    memset((f),0,(fs)); \
    snprintf((f),(fs),"%s%s%03d",(t),(v),(d)%YSAPP_LOADCFG_BASE)
#define YSAPP_LOADCFG_FILE_CAL2(f,fs,t,v,d) \
    memset((f),0,(fs)); \
    snprintf((f),(fs),"%s_%s_%03d",(t),(v),(d)%YSAPP_LOADCFG_BASE)
#define YSAPP_LOADCFG_FILE_CAL3(f,fs,t,v,d) \
    memset((f),0,(fs)); \
    snprintf((f),(fs),"%s_%s%03d",(t),(v),(d)%YSAPP_LOADCFG_BASE)
#define YSAPP_LOADCFG_FILE_CAL4(f,fs,t,v,d) \
    memset((f),0,(fs)); \
    snprintf((f),(fs),"%s%s_%03d",(t),(v),(d)%YSAPP_LOADCFG_BASE)
/****************************************************************************/
/** define CONFIG FILE                                                     **/
/** KeyValue of cfgfile : LOAD_CFG_[000~999] = <cfg_file>                  **/
/** Sign is Space,Tab,|,=                                                  **/
/** Format is : Key <sign> Value                                           **/
/** Key = Value                                                            **/
/** Key   Value                                                            **/
/** Key | Value                                                            **/
/** Key \t Value                                                           **/
/****************************************************************************/
#define YSAPP_LOAD_CFG_         "LOAD_CFG_"
#define YSAPP_LOAD_CFG_CAL(b,s,v) \
    YSAPP_LOADCFG_FILE_CAL((b),(s),YSAPP_LOAD_CFG_,"",(v))
/****************************************************************************/
/****************************************************************************/
#define YSENV_APPDIR                    ENV_APPDIR
#define YSENV_HOME                      ENV_HOME
#define YSENV_LOGLEVEL                  ENV_LOGLEVEL
#define YSENV_LOGFILE                   ENV_LOGFILE
#define YSENV_LOGLISTFILE               ENV_LOGLISTFILE
#define YSENV_LOGDIR                    ENV_LOGDIR
#define YSENV_DEFAULT_DIR               ENV_DEFAULT_DIR
#define YSENV_LOGDIR_DEFAULT            ENV_LOGDIR_DEFAULT
#define YSENV_LOGFILE_DEFAULT           ENV_LOGFILE_DEFAULT
#define YSENV_LOGLISTFILE_DEFAULT       ENV_LOGLISTFILE_DEFAULT
#define YSENV_LOGLEVEL_DEFAULT          ENV_LOGLEVEL_DEFAULT

#define YSAPP_LOAD_NAME                 "APP_NAME"
#define YSAPP_LOAD_TERM                 "APP_TERM"
#define YSAPP_LOAD_SIDFILE              "SIDFILE"
#define YSAPP_LOAD_SIDFILE_DEFAULT      "sid.cnt"
#define YSAPP_LOAD_MGRPATH              "YSAPP_MGR_PATH"
#define YSAPP_LOAD_MGRPATH_DEFAULT      "system.cfg"
#define YSAPP_LOAD_HOST_DEFAULT         "host"

/** Install default thread flow **/
/**
APP_INSTALL_[000,999] = <type>,Name
APP_INSTALL_[000,999] = <type>|Name
APP_INSTALL_[000,999] = <type>\tName
<Type> is [USERTHD,DBUS,TCP]
**/
#define YSAPP_LOAD_INSTALL              "APP_INSTALL_"
#define YSAPP_LOAD_INSTALL_CAL(b,s,v) \
    YSAPP_LOADCFG_FILE_CAL((b),(s),YSAPP_LOAD_INSTALL,"",(v))

#define YSAPP_INSTALL                   "__YSAPP_INSTALL"
#define YSAPP_INSTALL_TYPE_THD          1
#define YSAPP_INSTALL_TYPE_THD_STR      "USERTHD"
#define YSAPP_INSTALL_TYPE_DBUS         2
#define YSAPP_INSTALL_TYPE_DBUS_STR     "DBUS"
#define YSAPP_INSTALL_TYPE_TCP          3
#define YSAPP_INSTALL_TYPE_TCP_STR      "TCP"
#define YSAPP_INSTALL_TYPE_TCPTHD       4
#define YSAPP_INSTALL_TYPE_TCPTHD_STR   "TCPTHD"
#define YSAPP_INSTALL_TYPE_STR(sta) \
    ((YSAPP_INSTALL_TYPE_THD==(sta))?YSAPP_INSTALL_TYPE_THD_STR \
    :( \
        ((YSAPP_INSTALL_TYPE_DBUS==(sta))?YSAPP_INSTALL_TYPE_DBUS_STR \
        :( \
            ((YSAPP_INSTALL_TYPE_TCP==(sta))?YSAPP_INSTALL_TYPE_TCP_STR \
            :( \
                ((YSAPP_INSTALL_TYPE_TCPTHD==(sta))? \
                    YSAPP_INSTALL_TYPE_TCPTHD_STR:"Unknown Type") \
            )) \
        )) \
    ))

/** UserThread **/
/**
APP_USERTHD_THD_MAX_<Name>  = [1,50] ( Default is 1 )
APP_USERTHD_FIFO_MAX_<Name> = [1,500] ( Default is 10 )
**/
#define YSAPP_LOAD_USERTHD_THD_MAX      "APP_USERTHD_THD_MAX_%s" 
#define YSAPP_LOAD_USERTHD_FIFO_MAX     "APP_USERTHD_FIFO_MAX_%s"
#define YSAPP_USERTHD                   "__YSAPP_USERTHD_%s"
#define YSAPP_USERTHD_FIFO              "__YSAPP_USERTHD_FIFO_%s"
#define YSAPP_USERTHD_FIFO_WAIT         "__YSAPP_USERTHD_FIFO_WAIT_%s"
#define YSAPP_USERTHD_FIFO_OUT          "__YSAPP_USERTHD_OUT_%s"
#define YSAPP_USERTHD_THD_MIN           1
#define YSAPP_USERTHD_THD_MAX           50
#define YSAPP_USERTHD_THD_DEFAULT       1
#define YSAPP_USERTHD_FIFO_MIN          1
#define YSAPP_USERTHD_FIFO_MAX          500
#define YSAPP_USERTHD_FIFO_DEFAULT      10

/** DBusSrv **/

/** TcpSrv **/
/**
APP_TCPSRV_<Name>_[000,999]   = <Port>,<FifoName>
APP_TCPSRV_<Name>_[000,999]   = <Port>|<FifoName>
APP_TCPSRV_<Name>_[000,999]   = <Port>\t<FifoName>
<Port> = [1,65535)
<FifoName> is [YSAPP_LOAD_USERTHD_<%03d>=<Name>]
**/
#define YSAPP_LOAD_TCPSRV               "APP_TCPSRV_"
#define YSAPP_LOAD_TCPSRV_CAL(b,s,v1,v2) \
    YSAPP_LOADCFG_FILE_CAL4((b),(s),YSAPP_LOAD_TCPSRV,(v1),(v2))
#define YSAPP_TCPSRV                    "__YSAPP_TCPSRV_%s"
#define YSAPP_TCPSRV_THD_DEFAULT        YSAPP_USERTHD_THD_DEFAULT

/****************************************************************************/
/** define Manager shared memory                                           **/
/****************************************************************************/
#define YSAPP_MGR_INFOIDX           "__YSAPP_MGR_INFOIDX"
#define YSAPP_LOAD_MGR_INFO_NUM     "YSAPP_MGR_INFO_NUM"
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** define DICT                                                            **/
/** KeyValue of cfgfile : LOAD_DICT_[000~999] = <dict_file>                **/
/** Sign is Space,Tab,|,=                                                  **/
/** Format is : Name <sign> Type <sign> Max <sign> min <sign> view         **/
/****************************************************************************/
#define YSAPP_DICT                  "__YSAPP_DICT_%s"
#define YSAPP_DICT_VER_CAL(V,VS,ver) \
    memset((V),0,(VS)); \
    snprintf((V),(VS),YSAPP_DICT,(ver))
#define YSAPP_LOAD_DICT_VER     "YSAPP_DICT_VER"
#define YSAPP_LOAD_DICT_        "LOAD_DICT_"
#define YSAPP_LOAD_DICT_CAL(f,fs,d) \
    YSAPP_LOADCFG_FILE_CAL((f),(fs),YSAPP_LOAD_DICT_,"",(d))
#define YSAPP_LOAD_DICT_FILE_   "%s/dict.%s.ini"
#define YSAPP_LOAD_DICT_FILE_CAL(f,fs,v,d) \
    snprintf((f),(fs),YSAPP_LOAD_DICT_FILE_,(v),(d))
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** define SERVICE INFO                                                    **/
/** Service file name is : LOAD_SERVICE_[000~999] = <serv_version>         **/
/****************************************************************************/
#define YSAPP_SERV             "__YSAPP_SERV_%s"
#define YSAPP_SERV_VER_CAL(V,VS,ver) \
    memset((V),0,(VS)); \
    snprintf((V),(VS),YSAPP_SERV,(ver))
#define YSAPP_LOAD_SERV_VER     "YSAPP_SERV_VER"
#define YSAPP_LOAD_SERV_        "LOAD_SERV_"
#define YSAPP_LOAD_SERV_CAL(f,fs,d) \
    YSAPP_LOADCFG_FILE_CAL((f),(fs),YSAPP_LOAD_SERV_FILE_,"",(d))
#define YSAPP_LOAD_SERV_FILE_   "%s/serviceinfo.%s.ini"
#define YSAPP_LOAD_SERV_FILE_CAL(f,fs,v,d) \
    snprintf((f),(fs),YSAPP_LOAD_SERV_FILE_,(v),(d))

/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** define HOST                                                            **/
/** Host file name is : LOAD_HOST [000~999] = <host_file>                  **/
/****************************************************************************/
#define YSAPP_LOAD_HOST_        "LOAD_HOST_"
#define YSAPP_LOAD_HOST_CAL(f,fs,d) \
    YSAPP_LOADCFG_FILE_CAL((f),(fs),YSAPP_LOAD_HOST_,"",(d))
#define YSAPP_LOAD_HOST_FILE_   "%s/%s.ini"
#define YSAPP_LOAD_HOST_FILE_CAL(f,fs,v,d) \
    snprintf((f),(fs),YSAPP_LOAD_HOST_FILE_,(v),(d))
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** define SOCKET INFO                                                     **/
/** Pkg Struct Request (Pkg n)                                             **/
/**     PkgVerM     : 1  (default 0x01)                                    **/
/**     PkgVerS     : 1  (default 0x00)                                    **/
/**     ReqType     : 1  [0,Request;1,Response] (default 0)                **/
/**     PkgType     : 8  PKGVAR                                            **/
/**     PkgSum      : 1  [0x01~0xFF]                                       **/
/**     PkgNum      : 1  [0x01~0xFF]                                       **/
/**     DataSum     : 4  [0x0000 0000 ~0xFFFF FFFF ]                       **/
/**     DataLen     : 4  [0x0000 0000 ~0x00FF FFFF ]                       **/
/**     Data        : <DataLen>                                            **/
/** Pkg Struct Response (Pkg 1)                                            **/
/**     PkgVerM     : 1  (default 0x01)                                    **/
/**     PkgVerS     : 1  (default 0x00)                                    **/
/**     ReqType     : 1  [0,Request;1,Response] (default 1)                **/
/**     PkgType     : 8  PKGVAR                                            **/
/**     PkgSum      : 1  [0x01~0xFF]                                       **/
/**     PkgNum      : 1  [0x01~0xFF]                                       **/
/**     DataSum     : 4  [0x0000 0000 ~0xFFFF FFFF ]                       **/
/**     DataLen     : 4  [0x0000 0000 ~0x00FF FFFF ]                       **/
/**     RtnCodeLen  : 1  [0x01~0x0F]                                       **/
/**     RtnMsgLen   : 1  [0x01~0xFF]                                       **/
/**     RtnCode     : <RtnCodeLen>                                         **/
/**     RtnMsg      : <RtnMsgLen>                                          **/
/**     Data        : <DataLen>-1-<RtnCodeLen>-1-<RtnMsgLen>               **/
/** Pkg Struct Response (Pkg n)                                            **/
/**     PkgVerM     : 1  (default 0x01)                                    **/
/**     PkgVerS     : 1  (default 0x00)                                    **/
/**     ReqType     : 1  [0,Request;1,Response] (default 1)                **/
/**     PkgType     : 8  PKGVAR                                            **/
/**     PkgSum      : 1  [0x01~0xFF]                                       **/
/**     PkgNum      : 1  [0x01~0xFF]                                       **/
/**     DataSum     : 4  [0x0000 0000 ~0xFFFF FFFF ]                       **/
/**     DataLen     : 4  [0x0000 0000 ~0x00FF FFFF ]                       **/
/**     Data        : <DataLen>                                            **/
/** Pkg Struct (All part in one) Request                                   **/
/**     PkgVerM     : 1  (default 0x01)                                    **/
/**     PkgVerS     : 1  (default 0x00)                                    **/
/**     ReqType     : 1  [0,Request;1,Response] (default 1)                **/
/**     PkgType     : 8  PKGVAR                                            **/
/**     DataLen     : 4  [0x0000 0000 ~0x00FF FFFF ]                       **/
/**     Data        : <DataLen>                                            **/
/** Pkg Struct (All part in one) Response                                  **/
/**     PkgVerM     : 1  (default 0x01)                                    **/
/**     PkgVerS     : 1  (default 0x00)                                    **/
/**     ReqType     : 1  [0,Request;1,Response] (default 1)                **/
/**     PkgType     : 8  PKGVAR                                            **/
/**     PkgSum      : 1  [0x01~0xFF]                                       **/
/**     PkgNum      : 1  [0x01~0xFF]                                       **/
/**     DataSum     : 4  [0x0000 0000 ~0xFFFF FFFF ]                       **/
/**     DataLen     : 4  [0x0000 0000 ~0x00FF FFFF ]                       **/
/**     RtnCodeLen  : 1  [0x01~0x0F]                                       **/
/**     RtnMsgLen   : 1  [0x01~0xFF]                                       **/
/**     RtnCode     : <RtnCodeLen>                                         **/
/**     RtnMsg      : <RtnMsgLen>                                          **/
/**     Data        : <DataLen>-1-<RtnCodeLen>-1-<RtnMsgLen>               **/
/****************************************************************************/
#define YSPKG_MAX_SIZE                      0x00FFFFFF
#define YSPKG_MAX_NUM                       0xFF
#define YSPKG_HEADPKG_RTN_MAXLEN            255
#define YSPKG_HEADPKG_MSG_MAXLEN            255

#define YSPKG_HEADPKG_VERM                  0x01
#define YSPKG_HEADPKG_VERS                  0x00

#define YSPKG_HEADPKG_REQT_REQ              0
#define YSPKG_HEADPKG_REQT_RESP             1
#define YSPKG_HEADPKG_ISREQT(v) \
    ( (YSPKG_HEADPKG_REQT_REQ==(v))||(YSPKG_HEADPKG_REQT_RESP==(v)) )
#define YSPKG_HEADPKG_REQT_STR(v) \
    ( (YSPKG_HEADPKG_REQT_REQ==(v))?"Request":"Response" )

#define YSPKG_HEADPKG_VERM_LEN             1
#define YSPKG_HEADPKG_VERS_LEN             1
#define YSPKG_HEADPKG_REQT_LEN             1
#define YSPKG_HEADPKG_TYPE_LEN             8
#define YSPKG_HEADPKG_SUM_LEN              1
#define YSPKG_HEADPKG_NUM_LEN              1
#define YSPKG_HEADPKG_DSUM_LEN              4
#define YSPKG_HEADPKG_DLEN_LEN              4
#define YSPKG_HEADPKG_LEN \
    (YSPKG_HEADPKG_VERM_LEN+YSPKG_HEADPKG_VERS_LEN \
    +YSPKG_HEADPKG_REQT_LEN+YSPKG_HEADPKG_TYPE_LEN \
    +YSPKG_HEADPKG_SUM_LEN+YSPKG_HEADPKG_NUM_LEN \
    +YSPKG_HEADPKG_DSUM_LEN+YSPKG_HEADPKG_DLEN_LEN)
#define YSPKG_HEADPKG_RTNLEN_LEN            1
#define YSPKG_HEADPKG_MSGLEN_LEN            1

#define YSPKG_HEADPKG_MINLEN        YSPKG_HEADPKG_LEN
#define YSPKG_HEADPKG_MAXLEN        \
    (YSPKG_HEADPKG_LEN \
    +YSPKG_HEADPKG_RTNLEN_LEN+YSPKG_HEADPKG_RTN_MAXLEN \
    +YSPKG_HEADPKG_MSGLEN_LEN+YSPKG_HEADPKG_MSG_MAXLEN )

#define YSPKG_HEADPKG_VERM_POS      0
#define YSPKG_HEADPKG_VERS_POS \
    (YSPKG_HEADPKG_VERM_POS+YSPKG_HEADPKG_VERM_LEN)
#define YSPKG_HEADPKG_REQT_POS \
    (YSPKG_HEADPKG_VERS_POS+YSPKG_HEADPKG_VERS_LEN)
#define YSPKG_HEADPKG_TYPE_POS \
    (YSPKG_HEADPKG_REQT_POS+YSPKG_HEADPKG_REQT_LEN)

#define YSPKG_HEADPKG_SUM_POS \
    (YSPKG_HEADPKG_TYPE_POS+YSPKG_HEADPKG_TYPE_LEN)
#define YSPKG_HEADPKG_NUM_POS \
    (YSPKG_HEADPKG_SUM_POS+YSPKG_HEADPKG_SUM_LEN)

#define YSPKG_HEADPKG_DSUM_POS \
    (YSPKG_HEADPKG_NUM_POS+YSPKG_HEADPKG_NUM_LEN)
#define YSPKG_HEADPKG_DLEN_POS \
    (YSPKG_HEADPKG_DSUM_POS+YSPKG_HEADPKG_DSUM_LEN)

#define YSPKG_HEADPKG_DATA_POS      (YSPKG_HEADPKG_DLEN_POS)

#define YSPKG_HEADPKG_RTNLEN_POS \
    (YSPKG_HEADPKG_DLEN_POS+YSPKG_HEADPKG_DLEN_LEN)
#define YSPKG_HEADPKG_MSGLEN_POS \
    (YSPKG_HEADPKG_RTNLEN_POS+YSPKG_HEADPKG_RTNLEN_LEN)
#define YSPKG_HEADPKG_RTN_POS \
    (YSPKG_HEADPKG_MSGLEN_POS+YSPKG_HEADPKG_MSGLEN_LEN)
#define YSPKG_HEADPKG_MSG_POS(n)    (YSPKG_HEADPKG_RTN_POS+(n))
#define YSPKG_HEADPKG_DATA2_POS(n,m)  (YSPKG_HEADPKG_MSG_POS(n)+(m))

typedef struct tagYSPkgHeadStruct
{
    UCHAR PkgVerM;
    UCHAR PkgVerS;
    UCHAR ReqType;
    UCHAR PkgType[YSPKG_HEADPKG_TYPE_LEN+1];
    UCHAR PkgSum;
    UCHAR PkgNum;
    INT32 PkgDataSum;
    /* length of current packet data */
    /*  if resp & 1==PkgNum, include rtn and msg */
    INT32 PkgDataLen;       
    INT32 RtnCodeLen;       /* length of rtn */
    UCHAR RtnCode[256];     /* rtn */
    INT32 RtnMsgLen;        /* length of msg */
    UCHAR RtnMsg[256];      /* msg */
    INT32 DataLen;          /* length of userdata */
    UCHAR *Data;            /* current userdata ( not include rtn or msg ) */
    INT32 HeadLen;          /* length of current packet head */
    INT32 PkgLen;           /* length of current packet */
}tYSPkgHeadStruct;
#define YSPKG_HEADSTRUCT_ST_SIZE        (sizeof(tYSPkgHeadStruct))
#define YSPKG_HEADSTRUCT_MEM_VERM(v)    (((tYSPkgHeadStruct*)(v))->PkgVerM)
#define YSPKG_HEADSTRUCT_MEM_VERS(v)    (((tYSPkgHeadStruct*)(v))->PkgVerS)
#define YSPKG_HEADSTRUCT_MEM_REQT(v)    (((tYSPkgHeadStruct*)(v))->ReqType)
#define YSPKG_HEADSTRUCT_MEM_TYPE(v)    (((tYSPkgHeadStruct*)(v))->PkgType)
#define YSPKG_HEADSTRUCT_MEM_SUM(v)     (((tYSPkgHeadStruct*)(v))->PkgSum) 
#define YSPKG_HEADSTRUCT_MEM_NUM(v)     (((tYSPkgHeadStruct*)(v))->PkgNum) 
#define YSPKG_HEADSTRUCT_MEM_DSUM(v)    (((tYSPkgHeadStruct*)(v))->PkgDataSum)
#define YSPKG_HEADSTRUCT_MEM_DLEN(v)    (((tYSPkgHeadStruct*)(v))->PkgDataLen)
#define YSPKG_HEADSTRUCT_MEM_RTNLEN(v)  (((tYSPkgHeadStruct*)(v))->RtnCodeLen)
#define YSPKG_HEADSTRUCT_MEM_MSGLEN(v)  (((tYSPkgHeadStruct*)(v))->RtnMsgLen)
#define YSPKG_HEADSTRUCT_MEM_RTN(v)     (((tYSPkgHeadStruct*)(v))->RtnCode)
#define YSPKG_HEADSTRUCT_MEM_MSG(v)     (((tYSPkgHeadStruct*)(v))->RtnMsg)
#define YSPKG_HEADSTRUCT_MEM_DATALEN(v) (((tYSPkgHeadStruct*)(v))->DataLen)
#define YSPKG_HEADSTRUCT_MEM_DATA(v)    (((tYSPkgHeadStruct*)(v))->Data)
#define YSPKG_HEADSTRUCT_MEM_HEADLEN(v) (((tYSPkgHeadStruct*)(v))->HeadLen)
#define YSPKG_HEADSTRUCT_MEM_PKGLEN(v)  (((tYSPkgHeadStruct*)(v))->PkgLen)


/****************************************************************************/
/** define app                                                             **/
/** MAXKEYBUF must < 0x7F                                                  **/
/****************************************************************************/
#define YSAPP_CMD_LEN           MAXKEYBUF
#define YSAPP_SID_LEN           (BUFSIZE_32-1)
/* YYYYMMDDHHMMSS[0000,9999][000000,000000][0000000,9999999] */
#define YSAPP_NAME_LEN          MAXKEYBUF
#define YSAPP_VER_LEN           MAXKEYBUF
#define YSAPP_TMP_LEN           TMP_MAX_BUFFER
#define YSAPP_FILENAME_LEN      (FILE_NAME_MAX-1)

#define YSAPP_MIN_RECORD        64
#define YSAPP_MAX_RECORD        1024
 
#define YSDICT_VER_LEN          YSAPP_VER_LEN
#define YSSERV_VER_LEN          YSAPP_VER_LEN
#define YSSERV_NAME_LEN         YSAPP_NAME_LEN
#define YSSERV_LIB_LEN          YSAPP_NAME_LEN
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Service Call Tcp Type                                                  **/
/****************************************************************************/
#define YSPKG_HEAD_TYPE_SERVHASH    "SERVHASH"
#define YSPKG_HEAD_TYPE_DICTHASH    "DICTHASH"

#define YSAPP_SERV_CFG_TYPE_SYNC        0
#define YSAPP_SERV_CFG_TYPE_SYNC_STR    "SYNC"
#define YSAPP_SERV_CFG_TYPE_ASYNC       1
#define YSAPP_SERV_CFG_TYPE_ASYNC_STR   "ASYNC"
#define YSAPP_SERV_CFG_TYPE_ASYNC2      2
#define YSAPP_SERV_CFG_TYPE_ASYNC2_STR  "ASYNC2"
 
#define YSSERVICECALL_TYPE_MSG(t) \
    ((YSAPP_SERV_CFG_TYPE_SYNC==(t)) \
        ?YSAPP_SERV_CFG_TYPE_SYNC_STR \
        :( \
            (YSAPP_SERV_CFG_TYPE_ASYNC==(t)) \
                ?YSAPP_SERV_CFG_TYPE_ASYNC_STR \
                :YSAPP_SERV_CFG_TYPE_ASYNC2_STR \
         ) \
    )
#define YSSERVICECALL_RTYPE_MSG(t) \
    ((TRUE==(t))?"Remote Service":"Local Service")
/****************************************************************************/
/****************************************************************************/
 
/****************************************************************************/
/** YsPay Application manager                                              **/
/****************************************************************************/
#define YSMGR_TYPE_NOT              0
#define YSMGR_TYPE_FILE             1
#define YSMGR_TYPE_DICT             11
#define YSMGR_TYPE_SERV             12
#define YSMGR_TYPE_HOST             13
#define YSMGR_TYPE_APP              14
#define YSMGR_TYPE_MGRAPP           15
#define YSMGR_TYPE_IS(v) \
    ((YSMGR_TYPE_NOT==(v))||(YSMGR_TYPE_FILE==(v)) \
    ||(YSMGR_TYPE_DICT==(v))||(YSMGR_TYPE_SERV==(v)) \
    ||(YSMGR_TYPE_HOST==(v))||(YSMGR_TYPE_APP==(v)) \
    ||(YSMGR_TYPE_MGRAPP==(v)) )

#define YSMGR_TYPE_MGRAPP_STR       "Manager of Application"

#define YSMGR_TYPE_STR(sta) \
    ((YSMGR_TYPE_DICT==(sta))?"Dict" \
    :((YSMGR_TYPE_SERV==(sta))?"Service" \
        :((YSMGR_TYPE_HOST==(sta))?"Host" \
            :((YSMGR_TYPE_APP==(sta))?"Application" \
                :((YSMGR_TYPE_MGRAPP==(sta))?YSMGR_TYPE_MGRAPP_STR:"Not") \
            ) \
        ) \
    ))
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef YSDEF_H__ */ 

