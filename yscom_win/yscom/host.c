/***************************************************************************/
/**[File Name    ]host.c                                                  **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for host                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/

#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif

#define YSHOSTSTRUCT_FIELD_NAME     "NAME"
#define YSHOSTSTRUCT_FIELD_TERM     "TERM"
#define YSHOSTSTRUCT_FIELD_IP       "IP"
#define YSHOSTSTRUCT_FIELD_PORT     "PORT"

tYSVSFieldInfo lcYSHostInfoField[] = 
{
     {VARTYPE_MEM_VT_STRING     ,1  ,YSHOSTSTRUCT_FIELD_NAME}
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSHOSTSTRUCT_FIELD_TERM}
    ,{VARTYPE_MEM_VT_STRING     ,1  ,YSHOSTSTRUCT_FIELD_IP}
    ,{VARTYPE_MEM_VT_INT32      ,1  ,YSHOSTSTRUCT_FIELD_PORT}
};
#define YSHOSTSTRUCT_ST_NUM (sizeof(lcYSHostInfoField)/YSVSFIELDINFO_ST_SIZE)      
BOOL  YSHostArrayToStruct(void *Host,void *Array);
#define YSHostGetFieldIdx(n,l) \
    YSVarStructFieldGetIdx(lcYSHostInfoField,YSHOSTSTRUCT_ST_NUM,(n),(l))

char *YSHostCalAppName(char *Str,INT32 Size,const char *Name,const char *Term)
{
    if ( (YSAPP_NAME_LEN<Size)||(NULL==Name)||(NULL==Term) )
    {
        return NULL;
    }
    memset(Str,0,Size);
    snprintf(Str,Size,"%s:%s",Name,Term);
    return Str;
}

#ifdef __OS_LINUX__
char *YSHostGetFileName(char *Str,INT32 Size,const char *FileName)
{
    if ( (NULL==Str)||(MAXPATH>Size)||(NULL==FileName) )
    {
        return NULL;
    }
    if ( 0==strlen(FileName) )
    { 
        return NULL;
    }
    YSAPP_LOAD_HOST_FILE_CAL(Str,Size,YSAppArgsGetCfgDir(),FileName);
    return Str;
}
#endif

INT32 YSHostGetFiledLen()
{
    return YSHOSTSTRUCT_ST_NUM;
}

BOOL  YSHostArrayToStruct(void *Hash,void *Array)
{
    void *V;
    BOOL bRtn;
    char Key[YSAPP_NAME_LEN+1];
    char *K[2];
    void *Arr;
    void *Arr2;

    if ( !YSVarIsInit2(Hash,VARTYPE_MEM_VT_HASH) \
        ||!YSVarIsInit2(Array,VARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    V = NULL;
    Arr = NULL;
    Arr2 = NULL;
    bRtn = FALSE;
    while( 1 )
    {
        if ( NULL==(V=FEVarArrayToStruct(Array \
            ,lcYSHostInfoField,YSHOSTSTRUCT_ST_NUM)) )
        {
            break;
        }
        memset(Key,0,sizeof(Key));
        memset(K,0,sizeof(K));
        if ( NULL==(K[0]=YSVarStringGet(YSVarStructGetByKey(V \
            ,YSHOSTSTRUCT_FIELD_NAME,strlen(YSHOSTSTRUCT_FIELD_NAME)))) )
        {
            break;
        }
        if ( NULL==(K[1]=YSVarStringGet(YSVarStructGetByKey(V \
            ,YSHOSTSTRUCT_FIELD_TERM,strlen(YSHOSTSTRUCT_FIELD_TERM)))) )
        {
            break;
        }
        snprintf(Key,sizeof(Key),"%s:%s",K[0],K[1]);
        if ( !YSVarCpyKey(V,Key) )
        {
            break;
        }
        if ( NULL==(Arr=YSVarHashGet(Hash,K[0])) )
        {
            if ( NULL==(Arr2=YSVarArrayNew_Key(0,K[0])) )
            {
                break;
            }
            if ( !YSVarHashAdd(Hash,Arr2) )
            {
                break;
            }
            Arr = Arr2;
            Arr2 = NULL;
        }
        if ( !YSVarArrayAdd(Arr,V) )
        {
            break;
        }
        V = NULL;
        bRtn = TRUE;
        break;
    }
    YSVarArrayFree(Arr2);
    Arr2 = NULL;
    YSVarStructFree(V);
    V = NULL;
    return bRtn;
}

INT32 YSHostLoadFromFile(void *Hash,const char *FileName)
{
    return FEIniLoadFromFile(Hash,FileName,YSHostArrayToStruct);
}
 
void *YSHostLoadFromFile2(const char *Key,const char *FileName)
{
    return FEIniLoadFromFile2(Key,FileName,YSHostArrayToStruct);
}
 
#ifdef __cplusplus
}
#endif

