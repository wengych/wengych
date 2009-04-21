/***************************************************************************/
/**[File Name    ]mpdict.c                                                **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for share memory ( hash / dict )            **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif
 
#ifdef __OS_LINUX__

BOOL  YSDictToShm(const char *Ver)
{
    void *Dict;
    char FileName[MAXPATH];
    char Tmp[YSAPP_TMP_LEN];
    void *Buf;
    BOOL bRtn;

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
    bRtn = FALSE;
    Dict = NULL;
    while( 1 )
    {
        memset(FileName,0,sizeof(FileName));
        if ( NULL==YSDictGetFileName(FileName,sizeof(FileName),Ver) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSDictGetFileName(%s).",Ver);
            break;
        }
        if ( NULL==(Dict=YSDictLoadFromFile2(Ver,FileName)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSDictLoadFromFile2(%s:%s).",Ver,FileName);
            break;
        }
        if ( NULL!=(Buf=YSVarStringNew2(8192)) )
        {
            YSVarHashShow(Dict,0,Buf);
            YSTraceAll(YSAppArgsGetLogArgs(),"Dict Info" \
                ,YSVarStringGet(Buf),YSVarStringGetLen(Buf));
            YSVarStringFree(Buf);
        }
        if ( !YSMPToShm(FileName,Dict,YSVarHashGetLen(Dict)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSMPToShm.");
            break;
        }
        bRtn = TRUE;
        YSTracesAll(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"OK : Update Dict (File->Shm)[Ver=%s].",Ver);
        break;
    }
    YSVarFree(Dict);
    Dict = NULL;
    return bRtn;
}

#endif

#ifdef __cplusplus
}
#endif

