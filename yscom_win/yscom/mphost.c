/***************************************************************************/
/**[File Name    ]mphost.c                                                **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Filesion     ]0.1.0                                                   **/
/**[Memo         ]define func for share memory ( hash / host )            **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif
 
#ifdef __OS_LINUX__

BOOL  YSHostToShm(const char *File)
{
    char FileName[MAXPATH];
    void *Host;
    void *Buf;
    char Tmp[YSAPP_TMP_LEN];
    BOOL bRtn;

    if ( !YSAppArgsIsInit()||(NULL==File) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : YSAppArgs or FileName is not ready.");
        return FALSE;
    }
    if ( 0==strlen(File) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : FileName is null .");
        return FALSE;
    }
    bRtn = FALSE;
    Host = NULL;
    while( 1 )
    {
        memset(FileName,0,sizeof(FileName));
        if ( NULL==YSHostGetFileName(FileName,sizeof(FileName),File) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSHostGetFileName(%s).",File);
            break;
        }
        if ( NULL==(Host=YSHostLoadFromFile2(File,FileName)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSHostLoadFromFile2(%s:%s)." \
                ,File,FileName);
            break;
        }
        if ( NULL!=(Buf=YSVarStringNew2(8192)) )
        {
            YSVarHashShow(Host,0,Buf);
            YSTraceAll(YSAppArgsGetLogArgs(),"Host Info" \
                ,YSVarStringGet(Buf),YSVarStringGetLen(Buf));
            YSVarStringFree(Buf);
        }
        if ( !YSMPToShm(FileName,Host,YSVarHashGetLen(Host)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSMPToShm.");
            break;
        }
        bRtn = TRUE;
        YSTracesAll(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"OK : Update Host (File->Shm)[File=%s].",File);
        break;
    }
    YSVarFree(Host);
    Host = NULL;
    return bRtn;
}

#endif

#ifdef __cplusplus
}
#endif

