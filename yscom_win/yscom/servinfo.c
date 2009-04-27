/***************************************************************************/
/**[File Name    ]servinfo.c                                              **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for service info                            **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <yscom.h>

/** Service struct of file **/
#define YSSERVSTRUCT_FIELD_NAME         "SERV_NAME"
#define YSSERVSTRUCT_FIELD_TYPE         "SERV_TYPE"
#define YSSERVSTRUCT_FIELD_VER          "SERV_VER"
#define YSSERVSTRUCT_FIELD_APPNAME      "APP_NAME"
#define YSSERVSTRUCT_FIELD_FUNC         "SERV_FUNC"
#define YSSERVSTRUCT_FIELD_LIB          "SERV_LIB"
#define YSSERVSTRUCT_FIELD_DICTVER      "DICT_VER"
#define YSSERVSTRUCT_FIELD_IN           "SERV_IN"
#define YSSERVSTRUCT_FIELD_OUT          "SERV_OUT"

tYSVSFieldInfo lcYSServInfoField[] =
{
     {VARTYPE_MEM_VT_STRING     ,1  ,YSSERVSTRUCT_FIELD_NAME}
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSSERVSTRUCT_FIELD_TYPE}
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSSERVSTRUCT_FIELD_VER}
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSSERVSTRUCT_FIELD_APPNAME}
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSSERVSTRUCT_FIELD_FUNC}
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSSERVSTRUCT_FIELD_LIB}
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSSERVSTRUCT_FIELD_DICTVER}
    ,{VARTYPE_MEM_VT_ARRAY      ,0  ,YSSERVSTRUCT_FIELD_IN}
    ,{VARTYPE_MEM_VT_ARRAY      ,0  ,YSSERVSTRUCT_FIELD_OUT}
};
#define YSSERVSTRUCT_ST_NUM (sizeof(lcYSServInfoField)/YSVSFIELDINFO_ST_SIZE)

#ifdef __cplusplus
extern "C"{
#endif

BOOL  YSServArrayToStruct(void *Hash,void *Array);
#define YSSERVVSGET_FUNC(v1,v2) YSVarStructGetByKey((v1),(v2),strlen(v2))

#ifdef __OS_LINUX__
char *YSServGetFileName(char *Str,INT32 Size,const char *Ver)
{
    if ( (NULL==Str)||(MAXPATH>Size)||(NULL==Ver) )
    {
        return NULL;
    }
    if ( 0==strlen(Ver) )
    {
        return NULL;
    }
    YSAPP_LOAD_SERV_FILE_CAL(Str,Size,YSAppArgsGetCfgDir(),Ver);
    return Str;
}
#endif

char *YSServGetVerString(char *Str,INT32 Size,const char *Ver)
{
    if ( (NULL==Str)||(YSAPP_VER_MAXLEN>Size)||(NULL==Ver) )
    {
        return NULL;
    }
    if ( 0==strlen(Ver) )
    {
        return NULL;
    }
    YSAPP_SERV_VER_CAL(Str,Size,Ver);
    return Str;
}

INT32 YSServGetFiledLen()
{
    return YSSERVSTRUCT_ST_NUM;
}

char *YSServGetFieldName(INT32 Idx)
{
    if ( (0>Idx)||(YSSERVSTRUCT_ST_NUM<=Idx) )
    {
        return NULL;
    }
    return YSVSFIELDINFO_MEM_N(lcYSServInfoField+Idx);
}

BOOL  YSServArrayToStruct(void *Hash,void *Array)
{
    void *V;
    BOOL bRtn;

    if ( !YSVarIsInit2(Hash,VARTYPE_MEM_VT_HASH) \
        ||!YSVarIsInit2(Array,VARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    bRtn = FALSE;
    V = NULL;
    while( 1 )
    {
        if ( NULL==(V=FEVarArrayToStruct(Array \
            ,lcYSServInfoField,YSSERVSTRUCT_ST_NUM)) )
        {
            break;
        }
        if ( !YSVarCpyKey(V,YSVarStringGet(YSVarStructGetByKey(V \
            ,YSSERVSTRUCT_FIELD_NAME,strlen(YSSERVSTRUCT_FIELD_NAME)))) )
        {
            break;
        }
        if ( !YSVarHashAdd(Hash,V) )
        {
            break;
        }
        V = NULL;
        bRtn = TRUE;
        break;
    }
    YSVarStructFree(V);
    V = NULL;
    return bRtn;
}

INT32 YSServLoadFromFile(void *Hash,const char *FileName)
{
    return FEIniLoadFromFile(Hash,FileName,YSServArrayToStruct);
}
 
void *YSServLoadFromFile2(const char *Ver,const char *FileName)
{
    return FEIniLoadFromFile2(Ver,FileName,YSServArrayToStruct);
}
 
void *YSServVSGetName(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_NAME);
}

void *YSServVSGetType(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_TYPE);
}

void *YSServVSGetVer(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_VER);
}

void *YSServVSGetAppName(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_APPNAME);
}

void *YSServVSGetFunc(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_FUNC);
}

void *YSServVSGetLib(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_LIB);
}

void *YSServVSGetDictVer(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_DICTVER);
}

void *YSServVSGetDictIn(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_IN);
}

void *YSServVSGetDictOut(void *Var)
{
    return YSSERVVSGET_FUNC(Var,YSSERVSTRUCT_FIELD_OUT);
}

INT32 YSServVSType(const char *Type)
{
    INT32 iRtn;
    if ( NULL==Type )
    {
        return RTNCODE_ER;
    }
    iRtn = RTNCODE_ER;
    if ( !FEStrCmp(YSAPP_SERV_CFG_TYPE_SYNC_STR \
        ,strlen(YSAPP_SERV_CFG_TYPE_SYNC_STR),Type,strlen(Type)) )
    {
        iRtn = YSAPP_SERV_CFG_TYPE_SYNC;
    }
    else if ( !FEStrCmp(YSAPP_SERV_CFG_TYPE_ASYNC_STR \
        ,strlen(YSAPP_SERV_CFG_TYPE_ASYNC_STR),Type,strlen(Type)) )
    {
        iRtn = YSAPP_SERV_CFG_TYPE_ASYNC;
    }
    else if ( !FEStrCmp(YSAPP_SERV_CFG_TYPE_ASYNC2_STR \
        ,strlen(YSAPP_SERV_CFG_TYPE_ASYNC_STR),Type,strlen(Type)) )
    {
        iRtn = YSAPP_SERV_CFG_TYPE_ASYNC2;
    }
    return iRtn;
}

#ifdef __cplusplus
}
#endif

