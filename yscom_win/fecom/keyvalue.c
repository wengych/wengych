/***************************************************************************/
/**[File Name    ]keyvalue.c                                              **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for key value                               **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <fecom.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagFEKVStruct
{
    char Key[MAXKEYBUF+1];
    char Value[MAXVALUEBUF+1];
}tFEKVStruct;
INT32 FEKVAnalyseLine(tFEKVStruct *kv,char *Line);

void *FEKVNew()
{
    return FEVarHashNew(17);
}

void  FEKVFree(void *V)
{
    FEVarFree(V);
}

INT32 FEKVLoadFromFile(void *Hash,const char *FileName)
{
    INT32 iRtn;
    FILE *fp;
    void *V;
    tFEKVStruct KV;
    char acLine[BUFSIZE_2048];
    if ( NULL==Hash )
    {
        return FERTN_ERAPP_ARG;
    }
#ifdef __OS_LINUX__
    if ( FERTN_OK!=(iRtn=FEFileTest(FileName)) )
    {
        return iRtn;
    }
#endif
    fp = NULL;
    V = NULL;
    iRtn = FERTN_OK;
    if ( NULL==(fp=fopen(FileName,"r")) )
    {
        return FERTN_ERFILE_OPEN;
    }
    while( 1 )
    {
        memset(acLine,0,sizeof(acLine));
        if ( NULL==fgets(acLine,sizeof(acLine)-1,fp) )
        {
            if ( feof(fp) )
            {
                iRtn = FERTN_OK;
                break;
            }
            iRtn = FERTN_ERFILE_READ;
            break;
        }/* if ( NULL==fgets(acLine,sizeof(acLine)-1,fp) ) */
        FEStrTrimChangeLine(acLine);
        FEStrTrimSigns(acLine,STR_TRIMLINE_SIGN);
        if ( '#'==acLine[0] )
        {
            /* Mask Line */
            continue;
        }
        if ( 2>strlen(acLine) )
        {
            /* Space Line */
            continue;
        }
        memset(&KV,0,sizeof(KV));
        if (FERTN_OK1!=(iRtn=FEKVAnalyseLine(&KV,acLine)) )
        {
            if ( FERTN_OK==iRtn )
            {
                continue;
            }
            break;
        }
        if ( NULL==(V=FEVarStringSave(KV.Value,strlen(KV.Value))) )
        {
            iRtn = FERTN_ERVAR_NEW;
            break;
        }
        if ( !FEVarCpyKey(V,KV.Key,strlen(KV.Key)) )
        {
            iRtn = FERTN_ERVAR_NEW;
            break;
        }
        if ( !FEVarHashAdd(Hash,V) )
        {
            iRtn = FERTN_ERVAR_ADD;
            break;
        }
        V = NULL;
    }
    fclose(fp);
    if ( FERTN_OK!=iRtn )
    {
        FEVarStringFree(V);
        V = NULL;
    }
    return iRtn;
}

void *FEKVLoadFromFile2(const char *FileName)
{
    void *Hash;
#ifdef __OS_LINUX__
    if ( FERTN_OK!=FEFileTest(FileName) )
    {
        return NULL;
    }
#endif
    if ( NULL==(Hash=FEKVNew()) )
    {
        return NULL;
    }
    if ( FERTN_OK!=FEKVLoadFromFile(Hash,FileName) )
    {
        FEKVFree(Hash);
        Hash = NULL;
    }
    return Hash;
}

INT32 FEKVAnalyseLine(tFEKVStruct *kv,char *Line)
{
    INT32 iRtn;
    INT32 iPos;
    INT32 iKL;
    INT32 iVL;
    INT32 iLen;

    if ( (NULL==kv)||(NULL==Line) )
    {
        return FERTN_ERAPP_ARG;
    }
    iLen = strlen(Line);
    iPos = 0;
    iRtn = FERTN_ER;
    memset(kv,0,sizeof(tFEKVStruct));
    while( 1 )
    {
        if ( 0>=(iPos=FEStrGetOneWordLen(&iKL,Line,iLen \
            ,STR_KEYVALUE_SIGN,strlen(STR_KEYVALUE_SIGN))) )
        {
            iRtn = (0==iPos)?FERTN_ER:FERTN_OK;
            break;
        }
        if ( 0>FEStrGetOneWordLen(&iVL,Line+iPos,iLen-iPos \
            ,STR_KEYVALUE_SIGN,strlen(STR_KEYVALUE_SIGN)) )
        {
            break;
        }
        STRNCPY(kv->Key,Line,sizeof(kv->Key),iKL);
        STRNCPY(kv->Value,Line+iPos,sizeof(kv->Value),iVL);
        iRtn = FERTN_OK1;
        break;
    }
    return iRtn;
}

#ifdef __cplusplus
}
#endif

