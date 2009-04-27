/***************************************************************************/
/**[File Name    ]mpserv.c                                                **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Filesion     ]0.1.0                                                   **/
/**[Memo         ]define func for share memory ( hash / service info )    **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif
 
#ifdef __OS_LINUX__

BOOL  YSServToShm(const char *Ver)
{
    char FileName[MAXPATH];
    char Tmp[YSAPP_TMP_LEN];

    if ( !YSAppArgsIsInit()||(NULL==Ver) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : YSAppArgs or Ver is not ready.");
        return FALSE;
    }
    if ( 0==strlen(Ver) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Ver is null .");
        return FALSE;
    }
    memset(FileName,0,sizeof(FileName));
    if ( NULL==YSServGetFileName(FileName,sizeof(FileName),Ver) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Failed at YSServGetFileName(%s).",Ver);
        return FALSE;
    }
    return YSServToShm2(Ver,FileName);
}

BOOL  YSServToShm2(const char *Ver,const char *FileName)
{
    void *Serv;
    char Tmp[YSAPP_TMP_LEN];
    void *Buf;
    BOOL bRtn;

    if ( !YSAppArgsIsInit()||(NULL==Ver) \
        ||(RTNCODE_OK!=FEFileTest(FileName)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : YSAppArgs or Ver is not ready.");
        return FALSE;
    }
    if ( 0==strlen(Ver) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Ver is null .");
        return FALSE;
    }
    bRtn = FALSE;
    Serv = NULL;
    while( 1 )
    {
        if ( NULL==(Serv=YSServLoadFromFile2(Ver,FileName)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSServLoadFromFile2(%s:%s)." \
                ,Ver,FileName);
            break;
        }
        if ( NULL!=(Buf=YSVarStringNew2(8192)) )
        {
            YSVarHashShow(Serv,0,Buf);
            YSTraceAll(YSAppArgsGetLogArgs(),"Service Info" \
                ,YSVarStringGet(Buf),YSVarStringGetLen(Buf));
            YSVarStringFree(Buf);
        }
        if ( !YSMPToShm(FileName,Serv) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSMPToShm.");
            break;
        }
        bRtn = TRUE;
        YSTracesAll(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"OK : Update Serv (File->Shm)[Ver=%s].",Ver);
        break;
    }
    YSVarFree(Serv);
    Serv = NULL;
    return bRtn;
}

#endif

#ifdef __cplusplus
}
#endif

