/***************************************************************************/
/**[File Name    ]inifile.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
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

#define FEINI_VALUE_NULL        "<NULL>"

typedef struct tagFEIniArgs
{
    INT32 Flag;
    char  Label[BUFSIZE_1024];
}tFEIniArgs;

INT32 FEIniAnalyse(void *fp,tFEIniArgs *Flag,void **Array);
void *FEIniAnalyseLine(char *Line);

void *FEIniNew()
{
    return FEVarHashNew(17);
}

void  FEIniFree(void *V)
{
    FEVarFree(V);
}

INT32 FEIniLoadFromFile(void *Hash,const char *FileName,void *Func)
{
    INT32 iRtn;
    INT32 iRtn2;
    INT32 i;
    INT32 L;
    FILE *fp;
    void *V;
    void *VV;
    void *Array;
    tFEIniArgs st;
    if ( !FEVarIsInit2(Hash,VARTYPE_MEM_VT_HASH) )
    {
        return RTNCODE_ERAPP_ARG;
    }
#ifdef __OS_LINUX__
    if ( RTNCODE_OK!=(iRtn=FEFileTest(FileName)) )
    {
        return iRtn;
    }
#endif
    if ( NULL==(fp=fopen(FileName,"r")) )
    {
        return RTNCODE_ERFILE_OPEN;
    }
    V = NULL;
    Array = NULL;
    iRtn = RTNCODE_OK;
    memset(&st,0,sizeof(st));
    while( 1 )
    {
        FEVarArrayFree(Array);
        Array = NULL;
        if (RTNCODE_OK1!=(iRtn2=FEIniAnalyse(fp,&st,&Array)) )
        {
            iRtn = iRtn2;
            break;
        }
        if ( NULL==Func )
        {
            if ( 0>=(L=FEVarArrayGetLen(Array)) )
            {
                iRtn = RTNCODE_ERVAR_NEW;
                continue;
            }
            if ( NULL==(V=FEVarStructNew(L)) )
            {
                iRtn = RTNCODE_ERVAR_NEW;
                break;
            }
            if ( !FEVarMoveKey(V,FEVarGetKey(Array)) )
            {
                iRtn = RTNCODE_ERVAR_NEW;
                break;
            }
            for ( i=0;i<L;i++ )
            {
                if ( NULL==(VV=FEVarArrayRemove(Array,0)) )
                {
                    iRtn = RTNCODE_ERVAR_NEW;
                    break;
                }
                if ( !FEVarStructSet(V,i,VV) )
                {
                    iRtn = RTNCODE_ERVAR_NEW;
                    break;
                }
            }
            if ( !FEVarHashAdd(Hash,V) )
            {
                iRtn = RTNCODE_ERVAR_ADD;
                break;
            }
            V = NULL;
        }/* if ( NULL==Func ) */
        else if ( !(BOOL)(((funcarg2int)Func)(Hash,Array)) )
        {
            iRtn = RTNCODE_ERVAR_NEW;
            break;
        }
    }
    fclose(fp);
    FEVarFree(V);
    V = NULL;
    FEVarArrayFree(Array);
    Array = NULL;
    return iRtn;
}

void *FEIniLoadFromFile2(const char *Key,const char *FileName,void *Func)
{
    void *Hash;
#ifdef __OS_LINUX__
    if ( RTNCODE_OK!=FEFileTest(FileName) )
    {
        return NULL;
    }
#endif
    if ( NULL==(Hash=FEIniNew()) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( 0<strlen(Key) )
        {
            if ( !FEVarCpyKey(Hash,Key,strlen(Key)) )
            {
                FEIniFree(Hash);
                Hash = NULL;
            }
        }
    }
    if ( RTNCODE_OK!=FEIniLoadFromFile(Hash,FileName,Func) )
    {
        FEIniFree(Hash);
        Hash = NULL;
    }
    return Hash;
}

INT32 FEIniAnalyse(void *fp,tFEIniArgs *pt,void **Array)
{
    INT32 iRtn;
    void *V;
    INT32 LL;
    char Line[BUFSIZE_2048];
    if ( (NULL==pt)||(NULL==Array) )
    {
        return RTNCODE_ERAPP_ARG;
    }
    if ( (2<pt->Flag)||(0>pt->Flag) )
    {
        return RTNCODE_ERAPP_ARG;
    }
    if ( (1==pt->Flag)&&(NULL!=pt->Label) )
    {
        if ( NULL==(*Array=FEVarArrayNew_Key(0,pt->Label)) )
        {
            return RTNCODE_ERAPP_ARG;
        }
        memset(pt->Label,0,sizeof(pt->Label));
    }
    else if ( NULL==(*Array=FEVarArrayNew(0)) )
    {
        return RTNCODE_ERAPP_ARG;
    }
    V = NULL;
    while( 1 )
    {
        memset(Line,0,sizeof(Line));
        if ( NULL==fgets(Line,sizeof(Line)-1,fp) )
        {
            if ( feof((FILE*)fp) )
            {
                iRtn = (0==pt->Flag)?RTNCODE_OK:RTNCODE_OK1;
                pt->Flag = 0;
                break;
            }
            iRtn = RTNCODE_ERFILE_READ;
            break;
        }/* if ( NULL==fgets(Line,sizeof(Line)-1,fp) ) */
        FEStrTrimChangeLine(Line);
        FEStrTrimSigns(Line,STR_TRIMLINE_SIGN);
        if ( '#'==Line[0] )
        {
            /* Mask Line */
            continue;
        }
        if ( 2>(LL=strlen(Line)) )
        {
            /* Space Line */
            continue;
        }
        if ( ('['==Line[0])&&(']'==Line[LL-1]) )
        {
            pt->Flag ++;
            if ( 1==pt->Flag )
            {
                if ( !FEVarCpyKey(*Array,Line+1,LL-1-1) )
                {
                    iRtn = RTNCODE_ER;
                    break;
                }
                memset(pt->Label,0,sizeof(pt->Label));
                continue;
            }
            memset(pt->Label,0,sizeof(pt->Label));
            STRNCPY(pt->Label,Line+1,sizeof(pt->Label),LL-1-1);
        }
        if ( 2==pt->Flag )
        {

            pt->Flag = 1;
            iRtn = RTNCODE_OK1;
            break;
        }
        if ( NULL==(V=FEIniAnalyseLine(Line)) )
        {
            break;
        }
        if ( !FEVarArrayAdd(*Array,V) )
        {
            break;
        }
        V = NULL;
    }
    FEVarFree(V);
    V = NULL;
    if ( RTNCODE_OK1!=iRtn )
    {
        FEVarArrayFree(*Array);
        *Array = NULL;
    }
    return iRtn;
}

void *FEIniAnalyseLine(char *Line)
{
    void *V;
    INT32 i;
    INT32 j;
    INT32 iPos;
    INT32 iKL;
    INT32 iVL;
    INT32 iLen;
    char Tmp[TMP_BUFFER];

    if ( NULL==Line )
    {
        return NULL;
    }
    V = NULL;
    iLen = strlen(Line);
    iPos = 0;
    while( 1 )
    {
        if ( 0>=(iPos=FEStrGetOneWordLen(&iKL,Line,iLen \
            ,STR_KEYVALUE_SIGN,strlen(STR_KEYVALUE_SIGN))) )
        {
            break;
        }
        if ( 0>FEStrGetOneWordLen(&iVL,Line+iPos,iLen-iPos \
            ,STR_KEYVALUE_SIGN,strlen(STR_KEYVALUE_SIGN)) )
        {
            break;
        }
        memset(Tmp,0,sizeof(Tmp));
        i = iPos;
        j = 0;
        if ( '['==Line[iPos] )
        {
            i ++;
            for ( ;i<iPos+iVL;i++ )
            {
                if ( ']'==Line[i] )
                {
                    i ++;
                    break;
                }
                Tmp[j++] = Line[i];
            }
        }
        if ( !FEStrCmp(FEINI_VALUE_NULL,strlen(FEINI_VALUE_NULL) \
            ,Line+i,iPos+iVL-i) )
        {
            i = iPos+iVL;
            j = iVL;
        }
        FEStrToUpper(Tmp);
        if ( !strcmp("BOOL",Tmp) )
        {
            memset(Tmp,0,sizeof(Tmp));
            STRNCPY(Tmp,Line+i,sizeof(Tmp),iPos+iVL-i);
            FEStrToUpper(Tmp);
            V = FEVarBoolSave(RTNCODE_CMPBOOL(strcmp(Tmp,TRUE_STR)));
        }
        else if ( !strcmp("INT",Tmp) )
        {
            V = FEVarInt32Save(atoi(Line+i));
        }
        else if ( !strcmp("INT64",Tmp) )
        {
#ifdef __OS_LINUX__
            V = FEVarInt64Save((INT64)atoll(Line+i));
#else
            V = FEVarInt64Save((INT64)atol(Line+i));
#endif
        }
        else if ( !strncmp("DOUBLE",Tmp,strlen("DOUBLE")) )
        {
            memset(Tmp,' ',strlen("DOUBLE"));
            FEStrTrimSign(Tmp,' ');
            if ( NULL!=(V=FEVarDoubleSave(atof(Line+i))) )
            {
                FEVarDoubleSetDP(V,atoi(Tmp)/100,atoi(Tmp)%100);
            }
        }
        else
        {
            V = FEVarStringSave(Line+i,iVL-j);
        }
        break;
    }
    if ( NULL!=V )
    {
        if ( !FEVarCpyKey(V,Line,iKL) )
        {
            FEVarFree(V);
            V = NULL;
        }
    }
    return V;
}

#ifdef __cplusplus
}
#endif

