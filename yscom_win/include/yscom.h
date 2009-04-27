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
#ifdef __OS_LINUX__
char *YSDictGetFileName(char *Str,INT32 Size,const char *Ver);
#endif
char *YSDictGetVerString(char *Str,INT32 Size,const char *Ver);

INT32 YSDictGetFieldLen(INT32 VT);
INT32 YSDictLoadFromFile(void *Hash,const char *FileName);
void *YSDictLoadFromFile2(const char *Ver,const char *FileName);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Service Info                                                           **/
/****************************************************************************/
#ifdef __OS_LINUX__
char *YSServGetFileName(char *Str,INT32 Size,const char *Ver);
#endif
char *YSServGetVerString(char *Str,INT32 Size,const char *Ver);

INT32 YSServGetFiledLen();
char *YSServGetFieldName(INT32 Idx);
INT32 YSServLoadFromFile(void *Hash,const char *FileName);
void *YSServLoadFromFile2(const char *Ver,const char *FileName);

void *YSServVSGetName(void *Var);
void *YSServVSGetType(void *Var);
void *YSServVSGetVer(void *Var);
void *YSServVSGetAppName(void *Var);
void *YSServVSGetFunc(void *Var);
void *YSServVSGetLib(void *Var);
void *YSServVSGetDictVer(void *Var);
void *YSServVSGetDictIn(void *Var);
void *YSServVSGetDictOut(void *Var);

INT32 YSServVSType(const char *Type);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Host Info                                                              **/
/****************************************************************************/
char *YSHostCalAppName(char *Str,INT32 Size,const char *Name,const char *Term);
#ifdef __OS_LINUX__
char *YSHostGetFileName(char *Str,INT32 Size,const char *FileName);
#endif
INT32 YSHostGetFiledLen();
INT32 YSHostLoadFromFile(void *Hash,const char *FileName);
void *YSHostLoadFromFile2(const char *Key,const char *FileName);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Share memory func( Shm/Mem <=> VarHash )                               **/
/****************************************************************************/
/* memhead.c */
void  YSMPHeadShow(void *Head,INT32 T,void *Buf);
BOOL  YSMPHeadSetHashIdx(void *IBuf,INT32 Max,INT32 Idx,INT32 Len);
BOOL  YSMPHeadIsInit(void *Head,INT32 Size);
BOOL  YSMPHeadUpdateTime(void *Head,INT32 Size);
BOOL  YSMPHeadNeedUpdate(void *Head,INT32 Size,INT32 Time);
BOOL  YSMPHeadLenPlus(void *Head,INT32 Size,BOOL Flag);
/* memidx.c */
INT32 YSMPIdxSize();
BOOL  YSMPIdxAdd(void *IBuf,INT32 HK,INT32 Pos,INT32 Len);
BOOL  YSMPIdxSet(void *Buf,INT32 Size,INT32 HK,INT32 Pos,INT32 Len);
BOOL  YSMPIdxUpdateHK(void *Buf,INT32 Size,INT32 HK);
BOOL  YSMPIdxUpdateAddr(void *Buf,INT32 Size,INT32 Pos,INT32 Len);
BOOL  YSMPIdxUnPack(void *MH,INT32 Idx,void **IB,INT32 *PL);
BOOL  YSMPIdxUnPackByPos(void *MH,INT32 Pos,void **IB,INT32 *PL);
BOOL  YSMPIdxCmpHashKey(void *IB,INT32 Size,INT32 HK);
BOOL  YSMPIdxGetAddr(void *IB,INT32 Size,INT32 *PA,INT32 *PL);

/* mempkg.c */
#ifdef __OS_LINUX__
BOOL  YSMPShmIsReady(const char *ShmPath);
#endif
BOOL  YSMPIsInit(void *MH);
BOOL  YSMPIsMemInit(void *MH);
#ifdef __OS_LINUX__
BOOL  YSMPIsShmInit(void *MH);
#endif
BOOL  YSMPIsStructInit(void *MH);
INT32 YSMPGetHeadSize();
INT32 YSMPGetHeadSize2(void *MH);
void *YSMPGetHead(void *MH);
void *YSMPGetIdx(void *MH);
void *YSMPGetCtx(void *MH);
void *YSMPGetIBuf(void *MH);
void *YSMPGetCBuf(void *MH);
INT32 YSMPGetSize(void *MH);
INT32 YSMPGetMax(void *MH);
INT32 YSMPGetLen(void *MH);
INT32 YSMPGetIdxSize(void *MH);
INT32 YSMPGetIdxLen(void *MH);
INT32 YSMPGetCtxSize(void *MH);
INT32 YSMPGetCtxLen(void *MH);

void *YSMPNew();
void  YSMPFree(void *MH);
void  YSMPShow(void *MH,INT32 T,void *Buf);
BOOL  YSMPMallocBuf(void *MH,INT32 NewSize,BOOL Flag);
void *YSMPClone(void *MHS);
BOOL  YSMPMemFind(void *MH,const char *Key,INT32 Idx \
    ,INT32 *PIdx,void **V,INT32 *PL);
BOOL  YSMPMemFind2(void *MH,INT32 HashKey,INT32 Idx \
    ,INT32 *PIdx,void **V,INT32 *PL);
BOOL  YSMPToMem(void **MHS,void *Var);
BOOL  YSMPHashToMem(void *Var,void *IBuf,void *CBuf);
BOOL  YSMPArrayToMem(void *Var,void *IBuf,void *CBuf);
BOOL  YSMPStructToMem(void *Var,void *IBuf,void *CBuf);
void *YSMPFromMem(void *MHS);
void *YSMPHashFromVarBin(void *Bin,INT32 Max);
void *YSMPArrayFromVarBin(void *Bin);
void *YSMPStructFromMP(void *MHS);
#ifdef __OS_LINUX__
BOOL  YSMPToShm(const char *Key,void *Var);
BOOL  YSMPFromShm(void **Var,const char *Key);
void *YSMPShmFind(const char *File,const char *Key);
BOOL  YSMPShmFind2(const char *File,const char *Key,INT32 Idx,void *Buf);
BOOL  YSMPShmMultiFind(const char *Ver,void *Arr,void *Buf);
#endif
void *YSMPStructNew(const char *Key,INT32 Len,INT32 Max \
    ,INT32 IdxLen,INT32 CtxLen,void *IBuf,void *CBuf);

#ifdef __OS_LINUX__
void *YSMPCloneFromShm(const char *Key);
#endif

#ifdef __OS_LINUX__
BOOL  YSDictToShm(const char *Ver);
BOOL  YSDictToShm2(const char *Ver,const char *FileName);
BOOL  YSServToShm(const char *Ver);
BOOL  YSServToShm2(const char *Ver,const char *FileName);
BOOL  YSHostToShm(const char *File);
BOOL  YSHostToShm2(const char *File,const char *FileName);
#endif

/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Define Dict variable                                                   **/
/****************************************************************************/
#define YSDICT_IN           "__DICT_IN"
#define YSDICT_IN2          "__DICT_IN2"
#define YSDICT_OUT          "__DICT_OUT"
#define YSDICT_OUT2         "__DICT_OUT2"
#define YSDICT_BIN          "__DICT_BIN"
#define YSDICT_BIN2         "__DICT_BIN2"
#define YSDICT_FLAG         "__DICT_FLAG"
#define YSDICT_FLAG2        "__DICT_FLAG2"
 
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
 
#define YSDICT_USER_RTN     "__DICT_USER_RTN"
#define YSDICT_USER_RTNMSG  "__DICT_USER_RTNMSG"
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
/****************************************************************************/
/****************************************************************************/

BOOL  YSServiceClientCallSock(const char *IP,INT32 Port,INT32 TO \
    ,void *SendBus,void **RecvBus);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FECOM_H__ */ 

