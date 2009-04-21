/***************************************************************************/
/**[File Name    ]dict.c                                                  **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for dict                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/

#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif

#define YSDICT_FIELD_TYPE               "TYPE"
#define YSDICT_FIELD_NAME               "NAME"
#define YSDICT_FIELD_DEFAULT            "DEFAULT"

#define YSDICT_FIELD_INT_HASRANGE       "HASRANGE"
#define YSDICT_FIELD_INT_MAX            "MAX"
#define YSDICT_FIELD_INT_MIN            "MIN"

#define YSDICT_FIELD_STRING_PREFIX      "PREFIX"
#define YSDICT_FIELD_STRING_SUFFIX      "SUFFIX"
#define YSDICT_FIELD_STRING_LEN         "LEN"
#define YSDICT_FIELD_STRING_MIN         "MIN"

tYSVSFieldInfo lcYSDictInt[] = 
{
     {VARTYPE_MEM_VT_STRING     ,1  ,YSDICT_FIELD_TYPE              }
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSDICT_FIELD_NAME              }
    ,{VARTYPE_MEM_VT_INT32      ,1  ,YSDICT_FIELD_DEFAULT           }
    ,{VARTYPE_MEM_VT_BOOL       ,1  ,YSDICT_FIELD_INT_HASRANGE      }
    ,{VARTYPE_MEM_VT_INT32      ,1  ,YSDICT_FIELD_INT_MAX           }
    ,{VARTYPE_MEM_VT_INT32      ,1  ,YSDICT_FIELD_INT_MIN           }
};
#define YSDICTINT_NUM          (sizeof(lcYSDictInt)/YSVSFIELDINFO_ST_SIZE)
tYSVSFieldInfo lcYSDictString[] =
{
     {VARTYPE_MEM_VT_STRING     ,1  ,YSDICT_FIELD_TYPE              }
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSDICT_FIELD_NAME              }
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSDICT_FIELD_DEFAULT           }
    ,{VARTYPE_MEM_VT_INT32      ,1  ,YSDICT_FIELD_STRING_LEN        }
    ,{VARTYPE_MEM_VT_INT32      ,1  ,YSDICT_FIELD_STRING_MIN        }
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSDICT_FIELD_STRING_PREFIX     }
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSDICT_FIELD_STRING_SUFFIX     }
};
#define YSDICTSTRING_NUM        (sizeof(lcYSDictString)/YSVSFIELDINFO_ST_SIZE)
typedef struct tagYSDictFieldSets
{
    INT32 VT;
    INT32 Num;
    tYSVSFieldInfo *Info;
}tYSDictFieldSets;
#define YSDICTFIELDSETS_ST_SIZE     (sizeof(tYSDictFieldSets))

tYSDictFieldSets lcYSDictFieldSets[] =
{
     {VARTYPE_MEM_VT_BYTE       ,YSDICTINT_NUM      ,(void*)lcYSDictInt     }
    ,{VARTYPE_MEM_VT_INT16      ,YSDICTINT_NUM      ,(void*)lcYSDictInt     }
    ,{VARTYPE_MEM_VT_INT32      ,YSDICTINT_NUM      ,(void*)lcYSDictInt     }
    ,{VARTYPE_MEM_VT_INT64      ,YSDICTINT_NUM      ,(void*)lcYSDictInt     }
    ,{VARTYPE_MEM_VT_BIN        ,YSDICTSTRING_NUM   ,(void*)lcYSDictString  }
    ,{VARTYPE_MEM_VT_STRING     ,YSDICTSTRING_NUM   ,(void*)lcYSDictString  }
};
#define YSDICTFIELDSETS_NUM \
    (sizeof(lcYSDictFieldSets)/YSDICTFIELDSETS_ST_SIZE)      


INT32 YSDictTypeInfoIdxByVT(INT32 VT);
BOOL  YSDictArrayToStruct(void *Hash,void *Array);
#define YSDictGetFieldIdx(v,s,n,l)  YSVarStructFieldGetIdx((v),(s),(n),(l))

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

INT32 YSDictTypeInfoIdxByVT(INT32 VT)
{
    INT32 i;

    for ( i=0;i<YSDICTFIELDSETS_NUM;i++ )
    {
        if ( lcYSDictFieldSets[i].VT==VT )
        {
            break;
        }
    }
    return (YSDICTFIELDSETS_NUM>i)?i:RTNCODE_ER;
}

INT32 YSDictGetFieldLen(INT32 VT)
{
    INT32 Idx;
    if ( RTNCODE_ER==(Idx=YSDictTypeInfoIdxByVT(VT)) )
    {
        return Idx;
    }
    return lcYSDictFieldSets[Idx].Num;
}

BOOL  YSDictArrayToStruct(void *Hash,void *Array)
{
    INT32 VT;
    INT32 FIdx;
    void *V;
    BOOL bRtn;
    if ( !YSVarIsInit2(Hash,VARTYPE_MEM_VT_HASH) \
        ||!YSVarIsInit2(Array,VARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    if ( NULL==(V=YSVarArrayGetByKey(Array \
        ,YSDICT_FIELD_TYPE,strlen(YSDICT_FIELD_TYPE))) )
    {
        return FALSE;
    }
    if ( VARTYPE_MEM_VT_NOT==(VT=YSVarTypeInfoGetVT(YSVarStringGet(V))) )
    {
        return FALSE;
    }
    if ( RTNCODE_ER==(FIdx=YSDictTypeInfoIdxByVT(VT)) )
    {
        return FALSE;
    }
    V = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(V=YSVarArrayToStruct(Array \
            ,lcYSDictFieldSets[FIdx].Info,lcYSDictFieldSets[FIdx].Num)) )
        {
            break;
        }
        if ( !YSVarCpyKey(V,YSVarStringGet(YSVarStructGetByKey(V \
            ,YSDICT_FIELD_NAME,strlen(YSDICT_FIELD_NAME)))) )
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
    YSVarFree(V);
    V = NULL;
    return bRtn;
}

INT32 YSDictLoadFromFile(void *Hash,const char *FileName)
{
    return FEIniLoadFromFile(Hash,FileName,YSDictArrayToStruct);
}
 
void *YSDictLoadFromFile2(const char *Ver,const char *FileName)
{
    return FEIniLoadFromFile2(Ver,FileName,YSDictArrayToStruct);
}
 
#ifdef __cplusplus
}
#endif

