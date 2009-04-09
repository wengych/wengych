/***************************************************************************/
/**[File Name    ]yscom.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define common of pthread for YsPay                      **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef YSCOM_H__
#define YSCOM_H__

#include <fecom.h>
#include <ysdef.h>
#include <ysrtn.h>
#include <ysmacro.h>
#include <ysvar.h>

#ifdef __OS_LINUX__
#include <pthread.h>
#include <ysunit.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************/
/** YsArray                                                                **/
/****************************************************************************/
void *YSArrayNew(INT32 Max);
void *YSArrayNew_Key(INT32 Max,const char *Key);
void  YSArrayFree(void *Array);
void  YSArrayShow(void *Array,INT32 T,void *Buf);
BOOL  YSArrayIsEmpty(void *Array);
BOOL  YSArrayIsFull(void *Array);
INT32 YSArrayGetLen(void *Array);
void *YSArrayGet(void *Array,INT32 Idx);
BOOL  YSArrayInsertObject(void *Array,INT32 Idx \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
BOOL  YSArrayInsertObject2(void *Array,INT32 Idx,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
BOOL  YSArrayInsertVar(void *Array,INT32 Idx,void *Var);
BOOL  YSArrayAddObject(void *Array \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
BOOL  YSArrayAddObject2(void *Array,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
BOOL  YSArrayAddVar(void *Array,void *Var);
BOOL  YSArrayDelete(void *Array,INT32 Idx);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** YSFifo                                                                 **/
/****************************************************************************/
void *YSFifoNew(INT32 Max);
void *YSFifoNew_Key(INT32 Max,const char *Key);
void  YSFifoFree(void *Fifo);
void  YSFifoShow(void *Fifo,INT32 T,void *Buf);
BOOL  YSFifoIsEmpty(void *Fifo);
INT32 YSFifoGetLen(void *Fifo);
BOOL  YSFifoPop(void *Fifo,void **V);
BOOL  YSFifoPushValue(void *Fifo \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
BOOL  YSFifoPushString(void *Fifo,const char *Str,INT32 Len);
BOOL  YSFifoPushVar(void *Fifo,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** YSUserBus                                                              **/
/****************************************************************************/
void *YSUserBusNew(INT32 Size);
void *YSUserBusNew_Key(INT32 Size,const char *Key);
void  YSUserBusFree(void *UserBus);
void  YSUserBusShow(void *UserBus,INT32 T,void *Buf);
BOOL  YSUserBusPack(void *UserBus,void *Buf);
INT32 YSUserBusUnPack(void **UserBus,void *Buf,INT32 P);
BOOL  YSUserBusIsInit(void *UserBus);
BOOL  YSUserBusIsEmpty(void *UserBus);

void *YSUserBusGet(void *UserBus,const char *Key);
void *YSUserBusGetArray(void *UserBus,const char *Key);
void *YSUserBusArrayGet(void *UserBus,const char *Key,INT32 Idx);
BOOL  YSUserBusDelete(void *UserBus,const char *Key);
BOOL  YSUserBusArrayDelete(void *UserBus,const char *Key,INT32 Idx);
BOOL  YSUserBusAddValue(void *UserBus,const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
BOOL  YSUserBusArrayAddValue(void *UserBus,const char *Key,INT32 Idx \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
BOOL  YSUserBusAddString(void *UserBus,const char *Key \
    ,const char *Str,INT32 Len);
BOOL  YSUserBusArrayAddString(void *UserBus,const char *Key,INT32 Idx \
    ,const char *Str,INT32 Len);
BOOL  YSUserBusAddInt32(void *UserBus,const char *Key,INT32 n);
BOOL  YSUserBusArrayAddInt32(void *UserBus,const char *Key,INT32 Idx,INT32 n);
BOOL  YSUserBusAddVar(void *UserBus,void *V);
BOOL  YSUserBusArrayAddVar(void *UserBus,INT32 Idx,void *V);
INT32 YSUserBusGetLen(void *UserBus);
INT32 YSUserBusArrayGetLen(void *UserBus,const char *Key);
BOOL  YSUserBusReplaceValue(void *UserBus,const char *Key,void *V);
BOOL  YSUserBusArrayReplaceValue(void *UserBus \
    ,const char *Key,INT32 Idx,void *V);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Dict                                                                   **/
/****************************************************************************/
INT32 YSDictLoadFromFile(void *Dict,const char *Ver);
void *YSDictLoadFromFile2(const char *Ver);
void *YSDictNew();
void *YSDictNew2();
void  YSDictFree(void *Dict);
void  YSDictShow(void *Dict,INT32 T,void *Buf);
BOOL  YSDictSetVer(void *Dict,const char *Ver);
void *YSServInfoGet(void *Root,const char *SName);
char *YSDictGetVerString(char *Str,INT32 Size,const char *Ver);
char *YSDictGetFileName(char *Str,INT32 Size,const char *Ver);
BOOL  YSDictHashToMem(void *Var,void *IBuf,void *CBuf \
    ,void *IdxFunc,void *IBufFunc);
BOOL  YSDictMemToHash(void **Var,void *MHS,void *IdxFunc);

void  YSMHashFree(void *MH);
void  YSMHashShow(void *MH,INT32 T,void *Buf);
#ifdef __OS_LINUX__
BOOL  YSMHashDictToShm(const char *Key,void *Var);
BOOL  YSMHashShmToDict(void **Var,const char *Key);
#endif
BOOL  YSMHashDictToMem(void **MHS,INT32 Size,void *Var);
BOOL  YSMHashMemToDict(void **Var,void *Mem,INT32 Len);
/****************************************************************************/
/** Define Dict variablE                                                   **/
/****************************************************************************/
#define YSDICT_IN           "__DICT_IN"
#define YSDICT_IN2          "__DICT_IN2"
#define YSDICT_OUT          "__DICT_OUT"
#define YSDICT_OUT2         "__DICT_OUT2"
 
/** Application Information **/
#define YSDICT_APPNAME      "__DICT_APP_NAME"
#define YSDICT_APPTERM      "__DICT_APP_NAME"
 
/** Term Info **/
#define YSDICT_TERM_AREA    "__DICT_TERM_AREA"
#define YSDICT_TERM_ID      "__DICT_TERM_ID"
 
/** Session Info **/
#define YSDICT_SID          "__DICT_SESSION_ID"
 
/** Service Call **/
/** Remote service Call **/
#define YSDICT_SERVNAME     "__DICT_SCALL_NAME"
#define YSDICT_SERVVER      "__DICT_SCALL_VER"
 
/** Service Call return**/
#define YSDICT_RTN          "__DICT_SCALL_RTN"
#define YSDICT_RTNMSG       "__DICT_SCALL_RTNMSG"
/** Service Call **/
 
/** UserThd Name **/
#define YSDICT_USERTHD_NAME "__DICT_USERTHD_NAME"
 
/** UserThd install info */
#define YSDICT_USERTHD_INSTALL "__DICT_USERTHD_INSTALL"
 
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Pkg func                                                               **/
/****************************************************************************/
BOOL  YSPkgDataToStruct(void *PkgStruct,INT32 PkgSize,void *Pkg,INT32 PkgLen);
INT32 YSPkgStructToData(void *Pkg,INT32 PkgSize,void *PkgStruct);
BOOL  YSPkgStructInit(void *PkgStruct,BOOL ReqT,const char *Type \
    ,INT32 PkgSum,INT32 PkgNum,INT32 DSum,INT32 DLen,void *Data \
    ,INT32 RtnLen,void *Rtn,INT32 MsgLen,void *Msg);
#define YSPkgStructInitReq(PkgStruct,Type,DSum,Data) \
    YSPkgStructInit((PkgStruct),TRUE,(Type) \
        ,1,1,(DSum),(DSum),(Data),0,NULL,0,NULL)
#define YSPkgStructInitResp(PkgStruct,Type,DSum,Data,RL,R,ML,M) \
    YSPkgStructInit((PkgStruct),FALSE,(Type) \
        ,1,1,(DSum),(DSum),(Data),(RL),(R),(ML),(M))
void  YSPkgHeadStructShow(void *PkgStruct,INT32 T,void *Buf);
BOOL  YSPkgTcpRead(INT32 Sock,INT32 TO,void *Pkg,void *Head);
BOOL  YSPkgTcpWrite(INT32 Sock,INT32 TO,void *Head);
#ifdef __OS_WIN__
int SocketOpen(const char *Ip,int port);
int SocketClose(int sock);
int SocketReadTimtOut(int sockfd,int iTimeOut);
int SocketWriteTimtOut(int sockfd,int iTimeOut);
int SocketRead(int sockfd,int iTimeOut,char *pcBuffer,int iLength);
int SocketWrite(int sockfd,int iTimeOut,char *pcBuffer,int iLength);
#endif

BOOL  YSServiceClientCallSock(const char *IP,INT32 Port,INT32 TO \
    ,void *SendBus,void **RecvBus);
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FECOM_H__ */ 

