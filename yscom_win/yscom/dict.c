/***************************************************************************/
/**[File Name    ]dict.c                                                  **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for dict                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/

#include <mhash.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagYSDictStruct
{
    char Name[MAXKEYBUF+1];
    INT32 VT;
    INT32 Max;
    INT32 Min;
    void *View;
}tYSDictStruct;
#define YSDICTSTRUCT_ST_SIZE            (sizeof(tYSDictStruct))
#define YSDICTSTRUCT_MEM_NAME(D)        (((tYSDictStruct*)(D))->Name)
#define YSDICTSTRUCT_MEM_VT(D)          (((tYSDictStruct*)(D))->VT)
#define YSDICTSTRUCT_MEM_MAX(D)         (((tYSDictStruct*)(D))->Max)
#define YSDICTSTRUCT_MEM_MIN(D)         (((tYSDictStruct*)(D))->Min)
#define YSDICTSTRUCT_MEM_VIEW(D)        (((tYSDictStruct*)(D))->View)

INT32 YSDictAnalyseLine(tYSDictStruct *Dict,char *Line);
void *YSDictStructNew();
void  YSDictStructFree(void *V);
void  YSDictStructShow(void *V,INT32 T,void *Buf);
void *YSDictStructClone(void *V);
BOOL  YSDictStructToMem(void *Dict,void *IBuf,void *CBuf,void *IBufFunc);
INT32 YSDictMemToStruct(void **Dict,const char *Key,void *Ctx,INT32 Len);
/***************************************************************************/
/** VarName             FE_Byte         0       0                         **/
/** VarName             FE_Int16        0       0                         **/
/** VarName             FE_Int32        0       0                         **/
/** VarName             FE_Int64        0       0                         **/
/** VarName             FE_Double       0       0                         **/
/** VarName             FE_Double      Int     Int                        **/
/** VarName             FE_Bin         Int      0                         **/
/** VarName             FE_String      Int      0                         **/
/** VarName             FE_Array/F/F/L Int      0                         **/
/***************************************************************************/


INT32 YSDictAnalyseLine(tYSDictStruct *Dict,char *Line)
{
    INT32 iRtn;
    INT32 iPos;
    INT32 iPos2;
    INT32 iL;
    INT32 iLen;
    char Tmp[BUFSIZE_256];
 
    if ( (NULL==Dict)||(NULL==Line) )
    {
        iRtn = YSRTN_ERAPP_ARG;
        return iRtn;
    }
    iLen = strlen(Line);
    iPos = 0;
    iRtn = YSRTN_ER;
    memset(Dict,0,YSDICTSTRUCT_ST_SIZE);
    while( 1 )
    {
        if ( 0>=(iPos=FEStrGetOneWordLen(&iL,Line,iLen \
            ,STR_KEYVALUE_SIGN,strlen(STR_KEYVALUE_SIGN))) )
        {
            iRtn = (0==iPos)?YSRTN_ER:YSRTN_OK;
            if ( YSRTN_OK==iRtn )
            {
            }
            else
            {
            }
            break;
        }
        STRNCPY(YSDICTSTRUCT_MEM_NAME(Dict) \
            ,Line \
            ,sizeof(YSDICTSTRUCT_MEM_NAME(Dict)) \
            ,iL);

        if ( 0>(iPos2=FEStrGetOneWordLen(&iL,Line+iPos,iLen-iPos \
            ,STR_KEYVALUE_SIGN,strlen(STR_KEYVALUE_SIGN))) )
        {
            iRtn = YSRTN_ERAPP_LOADDICT;
            break;
        }
        memset(Tmp,0,sizeof(Tmp));
        STRNCPY(Tmp,Line+iPos,sizeof(Tmp),iL);
        iPos += iPos2;
        if ( 0==(YSDICTSTRUCT_MEM_VT(Dict) =\
             YSVarTypeInfoGetVT(Tmp)) )
        {
            iRtn = YSRTN_ERAPP_LOADDICT;
            break;
        }
        
        if ( 0>(iPos2=FEStrGetOneWordLen(&iL,Line+iPos,iLen-iPos \
            ,STR_KEYVALUE_SIGN,strlen(STR_KEYVALUE_SIGN))) )
        {
            iRtn = YSRTN_ERAPP_LOADDICT;
            break;
        }
        memset(Tmp,0,sizeof(Tmp));
        STRNCPY(Tmp,Line+iPos,sizeof(Tmp),iL);
        iPos += iPos2;
        YSDICTSTRUCT_MEM_MAX(Dict) = atoi(Tmp);
        YSDICTSTRUCT_MEM_MAX(Dict) = FECAL_MAX(0,YSDICTSTRUCT_MEM_MAX(Dict));

        if ( 0>(iPos2=FEStrGetOneWordLen(&iL,Line+iPos,iLen-iPos \
            ,STR_KEYVALUE_SIGN,strlen(STR_KEYVALUE_SIGN))) )
        {
            iRtn = YSRTN_ERAPP_LOADDICT;
            break;
        }
        memset(Tmp,0,sizeof(Tmp));
        STRNCPY(Tmp,Line+iPos,sizeof(Tmp),iL);
        iPos += iPos2;
        YSDICTSTRUCT_MEM_MIN(Dict) = atoi(Tmp);
        YSDICTSTRUCT_MEM_MIN(Dict) = FECAL_MAX(0,YSDICTSTRUCT_MEM_MIN(Dict));

        YSDICTSTRUCT_MEM_VIEW(Dict) = NULL;
        iRtn = YSRTN_OK1;
        break;
    }
    return iRtn;
}

INT32 YSDictLoadFromFile(void *Hash,const char *Ver)
{
    INT32 iRtn;
    FILE *fp;
    void *V;
    void *Dict;
    tYSDictStruct stDict;
    char acLine[BUFSIZE_2048];
    char FileName[MAXPATH+1];
    char Tmp[YSAPP_TMP_LEN];
    BOOL Flag;
 
    if ( NULL==Hash )
    {
        iRtn = YSRTN_ERAPP_ARG;
        return iRtn;
    }

#ifdef __OS_LINUX__
    if ( NULL==YSDictGetFileName(FileName,sizeof(FileName),Ver) )
    {
        iRtn = YSRTN_ERAPP_LOADDICT;
        return iRtn;
    }
#else
    memset(FileName,0,sizeof(FileName));
    snprintf(FileName,sizeof(FileName),"%s",Ver);
#endif
    fp = NULL;
    V = NULL;
    Dict = NULL;
    iRtn = YSRTN_OK;
    Flag = FALSE;
    if ( NULL==(fp=fopen(FileName,"r")) )
    {
        iRtn = YSRTN_ERFILE_OPEN;
        return iRtn;
    }
    while( 1 )
    {
        memset(acLine,0,sizeof(acLine));
        if ( NULL==fgets(acLine,sizeof(acLine)-1,fp) )
        {
            if ( feof(fp) )
            {
                iRtn = YSRTN_OK;
                break;
            }
            iRtn = YSRTN_ERFILE_READ;
            break;
        }/* if ( NULL==fgets(acLine,sizeof(acLine)-1,fp) ) */
        FEStrTrimChangeLine(acLine);
        FEStrTrimSigns(acLine,STR_TRIMLINE_SIGN);
        if ( '#'==acLine[0] )
        {
            /* Mask Line */
            if ( !Flag )
            {
                memset(Tmp,0,sizeof(Tmp));
                memcpy(Tmp,acLine,YSAPP_VER_DEFINE_LEN);
                FEStrToUpper(Tmp);
                if ( !strncmp(YSAPP_VER_DEFINE,Tmp \
                    ,YSAPP_VER_DEFINE_LEN) )
                {
                    if ( !strcmp(acLine+YSAPP_VER_DEFINE_LEN,Ver) )
                    {
                        Flag = TRUE;
                    }/* if ( !strcmp(acLine+YSAPP_VER_DEFINE_LEN,Ver) ) */
                }
            }/* if ( !Flag ) */
            continue;
        }
        if ( 2>strlen(acLine) )
        {
            /* Space Line */
            continue;
        }
        memset(&stDict,0,sizeof(stDict));
        if (YSRTN_OK1!=(iRtn=YSDictAnalyseLine(&stDict,acLine)) )
        {
            if ( YSRTN_OK==iRtn )
            {
                continue;
            }
            break;
        }
        if ( NULL==(Dict=YSDictStructClone(&stDict)) )
        {
            iRtn = YSRTN_ERAPP_LOADDICT;
            break;
        }
        if ( NULL==(V=YSVarObjectSave2(YSDICTSTRUCT_MEM_NAME(Dict) \
            ,Dict,YSDictStructClone,YSDictStructFree,YSDictStructShow,NULL)) )
        {
            iRtn = YSRTN_ERVAR_NEW;
            break;
        }
        Dict = NULL;
        if ( !YSVarHashAdd(Hash,V) )
        {
            iRtn = YSRTN_ERVAR_ADD;
            break;
        }
        V = NULL;
    }/* while( 1 ) */
    fclose(fp);
    if ( !Flag && (YSRTN_OK==iRtn) )
    {
        iRtn = YSRTN_ERAPP_LOADDICT;
    }
    if ( YSRTN_OK!=iRtn )
    {
        YSVarStringFree(V);
        V = NULL;
    }
    return iRtn;
}

void *YSDictLoadFromFile2(const char *Ver)
{
    void *Hash;
    BOOL Flag;

    if ( NULL==(Hash=YSDictNew()) )
    {
        return NULL;
    }
    Flag = FALSE;
    while( 1 )
    {
        if ( !YSDictSetVer(Hash,Ver) )
        {
            break;
        }
        if ( YSRTN_OK!=YSDictLoadFromFile(Hash,Ver) )
        {
            break;
        }
        Flag = TRUE;
        break;
    }
    if ( !Flag )
    {
        YSDictFree(Hash);
        Hash = NULL;
    }
    return Hash;
}

void *YSDictNew()
{
    return YSVarHashNew(17);
}

void  YSDictFree(void *Dict)
{
    YSVarHashFree(Dict);
}

void  YSDictShow(void *Dict,INT32 T,void *Buf)
{
    YSVarHashShow(Dict,T,Buf);
}

BOOL  YSDictSetVer(void *Dict,const char *Ver)
{
    char Key[YSAPP_VER_MAXLEN];
    if ( NULL==YSDictGetVerString(Key,sizeof(Key),Ver) )
    {
        return FALSE;
    }
    return YSVarCpyKey(Dict,Key);
}

char *YSDictGetVerString(char *Str,INT32 Size,const char *Ver)
{
    if ( (NULL==Str)||(YSAPP_VER_MAXLEN>Size)||(NULL==Ver) )
    {
        return NULL;
    }
    if ( 0==strlen(Ver) )
    {
        return NULL;
    }
    YSAPP_DICT_VER_CAL(Str,Size,Ver);
    return Str;
}

#ifdef __OS_LINUX__
char *YSDictGetFileName(char *Str,INT32 Size,const char *Ver)
{
    if ( (NULL==Str)||(MAXPATH>Size)||(NULL==Ver) )
    {
        return NULL;
    }
    if ( 0==strlen(Ver) )
    {
        return NULL;
    }
    YSAPP_LOAD_DICT_FILE_CAL(Str,Size,YSAppArgsGetCfgDir(),Ver);
    return Str;
}
#endif

void *YSDictStructNew()
{
    void *V;
    if ( NULL==(V=malloc(YSDICTSTRUCT_ST_SIZE)) )
    {
        return NULL;
    }
    memset(V,0,YSDICTSTRUCT_ST_SIZE);
    return V;
}

void  YSDictStructFree(void *V)
{
    if ( NULL==V )
    {
        return;
    }
    free(V);
}

void  YSDictStructShow(void *V,INT32 T,void *Buf)
{
    char Log[BUFSIZE_128];
    char Tab[BUFSIZE_64];
    INT32 L;

    if ( (NULL==V)||!YSVarIsInit2(Buf,VARTYPE_MEM_VT_STRING) )
    {
        return;
    }
    memset(Tab,0,sizeof(Tab));
    YSVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);
 
    L = 0;
    snprintf(Log+L,sizeof(Log) \
        ,"%s<Dict VT=\"%d\" Max=\"%d\" Min=\"%d\">%s</Dict>" \
        ,Tab \
        ,YSDICTSTRUCT_MEM_VT(V) \
        ,YSDICTSTRUCT_MEM_MAX(V) \
        ,YSDICTSTRUCT_MEM_MIN(V) \
        ,YSDICTSTRUCT_MEM_NAME(V));
    L += strlen(Log+L);
    YSVarStringCat(Buf,Log,L);
}

void *YSDictStructClone(void *V)
{
    void *Dict;
    if ( NULL==(Dict=YSDictStructNew()) )
    {
        return NULL;
    }
    memset(Dict,0,YSDICTSTRUCT_ST_SIZE);
    memcpy(Dict,V,YSDICTSTRUCT_ST_SIZE);
    return Dict;
}

BOOL  YSDictStructToMem(void *Dict,void *IBuf,void *CBuf,void *IBufFunc)
{
    INT32 IL;
    INT32 Pos;
    char Ctx[YSAPP_TMP_LEN];
    BOOL bRtn;
    if ( (NULL==Dict) || (NULL==IBufFunc)  \
        || !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        || !YSVarIsInit2(CBuf,VARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    IL = YSVarBinGetLen(IBuf);
    bRtn = FALSE;
    while( 1 )
    {
        if ( !(BOOL)((funcarg3int)IBufFunc)(IBuf \
            ,YSDICTSTRUCT_MEM_NAME(Dict),CBuf) )
        {
            break;
        }
        memset(Ctx,0,sizeof(Ctx));
        Pos = 0;
        Ctx[Pos] = YSDICTSTRUCT_MEM_VT(Dict);
        Pos ++;
        *(INT32 *)(Ctx+Pos) = YSDICTSTRUCT_MEM_MAX(Dict);
        FEEndianToNet(Ctx+Pos,INT32_SIZE);
        Pos += INT32_SIZE;
        *(INT32 *)(Ctx+Pos) = YSDICTSTRUCT_MEM_MIN(Dict);
        FEEndianToNet(Ctx+Pos,INT32_SIZE);
        Pos += INT32_SIZE;
        if ( !YSVarBinCat(CBuf,Ctx,Pos) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSVarBinSetLen(IBuf,IL);
    }
    return bRtn;
}

BOOL  YSDictHashToMem(void *Var,void *IBuf,void *CBuf \
    ,void *IdxFunc,void *IBufFunc)
{   
    INT32 i;
    INT32 Size;
    INT32 LIdx;
    INT32 LLen;
    void *Link;
    void *Dict;

    INT32 IL;
    INT32 CL;
    INT32 NS;

    BOOL bRtn;

    if ( (NULL==IdxFunc) || (NULL==IBufFunc) \
        || !YSVarIsInit2(Var,VARTYPE_MEM_VT_HASH) \
        || !YSVarIsInit2(IBuf,VARTYPE_MEM_VT_BIN) \
        || !YSVarIsInit2(CBuf,VARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    Size = YSVarHashGetBase(Var);
    IL = YSVarBinGetLen(IBuf);
    CL = YSVarBinGetLen(CBuf);
    bRtn = TRUE;
    LLen = YSVarHashGetLen(Var);
    NS = YSMHASHHEAD_ST_SIZE+LLen*YSMHASH_HEAD_IDXSIZE;
    YSVarBinMalloc2(IBuf,NS);
    NS = LLen*YSDICTSTRUCT_ST_SIZE;
    YSVarBinMalloc2(CBuf,NS);
    for ( i=0;i<Size;i++ )
    {
        if ( NULL==(Link=YSVarHashGetLinkByIdx(Var,i)) )
        {
            bRtn = FALSE;
            break;
        }
        LLen = YSVarLinkGetLen(Link);
        if ( !(BOOL)((funcarg3int)IdxFunc)(IBuf,(void *)i,(void *)LLen) )
        {
            bRtn = FALSE;
            break;
        }
        for ( LIdx=0;LIdx<LLen;LIdx++ )
        {
            if ( NULL==(Dict=YSVarObjectGet(YSVarLinkGet(Link,LIdx))) )
            {
                bRtn = FALSE;
                break;
            }
            if ( !YSDictStructToMem(Dict,IBuf,CBuf,IBufFunc) )
            {
                bRtn = FALSE;
                break;
            }
        } 
    }
    if ( !bRtn )
    {
        YSVarBinSetLen(IBuf,IL);
        YSVarBinSetLen(CBuf,CL);
    }
    return bRtn;
}

INT32 YSDictMemToStruct(void **Dict,const char *Key,void *Ctx,INT32 Len)
{
    BOOL bRtn;
    INT32 Pos;

    if ( (NULL==Dict)||(NULL==Key)||(NULL==Ctx) )
    {
        return YSRTN_ER;
    }
    if ( (0==strlen(Key))||(BYTE_SIZE+INT32_SIZE+INT32_SIZE>Len) )
    {
        return YSRTN_ER;
    }
    
    bRtn = FALSE;
    *Dict = NULL;
    while( 1 )
    {
        if ( NULL==(*Dict=YSDictStructNew()) )
        {
            break;
        }
        MEMNCPY(YSDICTSTRUCT_MEM_NAME(*Dict),Key \
            ,sizeof(YSDICTSTRUCT_MEM_NAME(*Dict)),strlen(Key));
        Pos = 0;
        YSDICTSTRUCT_MEM_VT((*Dict)) = ((BYTE*)Ctx)[Pos];
        Pos ++;

        YSDICTSTRUCT_MEM_MAX(*Dict) = *(INT32 *)(((BYTE*)Ctx)+Pos);
        FEEndianToNet((void *)&(YSDICTSTRUCT_MEM_MAX(*Dict)),INT32_SIZE);
        Pos += INT32_SIZE;

        YSDICTSTRUCT_MEM_MIN(*Dict) = *(INT32 *)(((BYTE*)Ctx)+Pos);
        FEEndianToNet((void *)&(YSDICTSTRUCT_MEM_MIN(*Dict)),INT32_SIZE);
        Pos += INT32_SIZE;

        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        YSDictStructFree(*Dict);
        *Dict = NULL;
        Pos = YSRTN_ER;
    }
    return Pos;
}

BOOL  YSDictMemToHash(void **Var,void *MHS,void *IdxFunc)
{
    INT32 Pos;
    INT32 Len;
    INT32 Cnt;
    tYSMHashIdx tIdx;
    void *Ctx;
    INT32 CPos;
    void *Dict;
    void *Obj;
    BOOL bRtn;
    if ( (NULL==Var)||!YSMHashIsInit(MHS)||(NULL==IdxFunc) )
    {
        return FALSE;
    }
    if ( NULL==(*Var=YSVarHashNew_Key(YSMHASH_HEAD_BASE,YSMHASH_MEM_VER(MHS))) )
    {
        return FALSE;
    }
    Len = YSMHASH_MEM_LEN(MHS);
    Ctx = YSMHASH_MEM_CTX(MHS);
    Cnt = 0;
    CPos = 0;
    Dict = NULL;
    Obj = NULL;
    bRtn = TRUE;
    while( Cnt<Len )
    {
        memset(&tIdx,0,sizeof(tIdx));
        if ( !(BOOL)(((funcarg3int)IdxFunc)(MHS,(void *)Cnt,&tIdx)) )
        {
            bRtn = FALSE;
            break;
        }
        if ( 0>(Pos=YSDictMemToStruct(&Dict,YSMHASHIDX_MEM_K(&tIdx) \
                ,((BYTE*)Ctx)+CPos,YSMHASH_MEM_CLEN(MHS)-CPos)) )
        {
            bRtn = FALSE;
            break;
        }
        CPos += Pos;
        if ( NULL==(Obj=YSVarObjectSave2(YSMHASHIDX_MEM_K(&tIdx) \
            ,Dict,YSDictStructClone,YSDictStructFree,YSDictStructShow,NULL)) )
        {
            bRtn = FALSE;
            break;
        }
        Dict = NULL;
        if ( !YSVarHashAdd(*Var,Obj) )
        {
            bRtn = FALSE;
            break;
        }
        Obj = NULL;
        Cnt ++;
    }
    if ( !bRtn )
    {
        YSDictStructFree(Dict);
        Dict = NULL;
        YSVarObjectFree(Obj);
        Obj = NULL;
        YSVarHashFree(*Var);
        *Var = NULL;
    }
    return bRtn;
}

#ifdef __cplusplus
}
#endif

