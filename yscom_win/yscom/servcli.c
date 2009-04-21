/***************************************************************************/
/**[File Name    ]servcli.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for service client call                     **/
/**[Modify       ]                                                        **/
/***************************************************************************/

#include <yscom.h>

#ifdef __cplusplus
extern "C"{
#endif

BOOL  YSServiceClientCallSock(const char *IP,INT32 Port,INT32 TO \
    ,void *SendBus,void **RecvBus)
{
    void *Pkg;
    tYSPkgHeadStruct HS;
    INT32 Sock;
    INT32 Flag;
    BOOL bRtn;
    if ( (NULL==IP)||(0>=Port) \
        || !YSVarIsInit2(SendBus,VARTYPE_MEM_VT_HASH) ||(NULL==RecvBus) )
    {
        return FALSE;
    }
    if ( 0==strlen(IP) )
    {
        return FALSE;
    }
    *RecvBus = NULL;
    Pkg = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(Pkg=YSVarBinNew2(10240)) )
        {
            break;
        }
        if ( !YSUserBusPack(SendBus,Pkg) )
        {
            break;
        }
        memset(&HS,0,sizeof(HS));
        YSPkgStructInitReq(&HS,YSPKG_HEAD_TYPE_SERVHASH \
            ,YSVarBinGetLen(Pkg),YSVarBinGet(Pkg));

#ifdef __OS_WIN__
        if ( 0>(Sock=SocketOpen((char *)IP,Port)) )
#else
        if ( 0>(Sock=FETcpClient((char *)IP,Port)) )
#endif
        {
            break;
        }
        Flag = FALSE;
        while( 1 )
        {
            if ( !YSPkgTcpWrite(Sock,TO,&HS) )
            {
                break;
            }
            YSVarBinReset(Pkg);
            memset(&HS,0,sizeof(HS));
            if ( !YSPkgTcpRead(Sock,TO,Pkg,&HS) )
            {
                break;
            }
            Flag = TRUE;
            break;
        }
#ifdef __OS_WIN__
        SocketClose(Sock);
#else
        FETcpClientClose(Sock);
#endif
        if ( Flag )
        {
            if ( 0>YSUserBusUnPack(RecvBus,Pkg \
                ,YSPKG_HEADSTRUCT_MEM_HEADLEN(&HS)) )
            {
                break;
            }
        }
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSUserBusFree(*RecvBus);
        *RecvBus = NULL;
    }
    YSVarBinFree(Pkg);
    Pkg = NULL;
    return bRtn;
}

#ifdef __cplusplus
}
#endif

