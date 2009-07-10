/***************************************************************************/
/**[File Name    ]varinfo.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/12/20                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for variant type name                       **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagFEVarTypeInfo
{
    BYTE  VT;
    char  Name[FEVARNAMELEN-1];
}tFEVarTypeInfo;
#define FEVARTYPE_INFO_ST_SIZE      (sizeof(tFEVarTypeInfo))
#define FEVARTYPE_INFO_MEM_VT(v)     (((tFEVarTypeInfo*)(v))->VT)
#define FEVARTYPE_INFO_MEM_N(v)     (((tFEVarTypeInfo*)(v))->Name)
static const tFEVarTypeInfo gstFEVarTypeInfo[] = 
{
     {VARTYPE_MEM_VT_NOT      ,"unknown"      }
    ,{VARTYPE_MEM_VT_BOOL     ,"Bool"         }
    ,{VARTYPE_MEM_VT_BYTE     ,"Byte"         }
    ,{VARTYPE_MEM_VT_INT16    ,"Int16"        }
    ,{VARTYPE_MEM_VT_INT32    ,"Int32"        }
    ,{VARTYPE_MEM_VT_INT64    ,"Int64"        }
    ,{VARTYPE_MEM_VT_DOUBLE   ,"Double"       }
    ,{VARTYPE_MEM_VT_BIN      ,"Bin"          }
    ,{VARTYPE_MEM_VT_STRING   ,"String"       }
    ,{VARTYPE_MEM_VT_OBJECT   ,"Object"       }
    ,{VARTYPE_MEM_VT_STRUCT   ,"Struct"       }

    ,{VARTYPE_MEM_VT_P1       ,"P1"           }
    ,{VARTYPE_MEM_VT_P2       ,"P2"           }
    ,{VARTYPE_MEM_VT_P3       ,"P3"           }
    ,{VARTYPE_MEM_VT_P4       ,"P4"           }

    ,{VARTYPE_MEM_VT_ARRAY    ,"Array"        }
    ,{VARTYPE_MEM_VT_FIFO     ,"Fifo"         }
    ,{VARTYPE_MEM_VT_FILO     ,"Filo"         }
    ,{VARTYPE_MEM_VT_CICLE    ,"Circle"       }
    ,{VARTYPE_MEM_VT_HASH     ,"Hash"         }
    ,{VARTYPE_MEM_VT_LINK     ,"Link"         }
    ,{VARTYPE_MEM_VT_TREE     ,"Tree"         }
    ,{VARTYPE_MEM_VT_XML      ,"Xml"          }
};
#define FEVARTYPE_INFO_V_SIZE             \
    (sizeof(gstFEVarTypeInfo)/FEVARTYPE_INFO_ST_SIZE)

BYTE  FEVarTypeInfoGetVT(const char *Name)
{
    BYTE bRtn;
    INT32 i;
    bRtn = VARTYPE_MEM_VT_NOT;
    for ( i=0;i<FEVARTYPE_INFO_V_SIZE;i++ )
    {
        if ( !strcmp(FEVARTYPE_INFO_MEM_N( \
            &(gstFEVarTypeInfo[i])),Name) )
        {
            bRtn = FEVARTYPE_INFO_MEM_VT(&(gstFEVarTypeInfo[i]));
            break;
        } 
    }
    return bRtn;
}

char *FEVarTypeInfoGetName(const BYTE VT)
{
    char *pcRtn;
    INT32 i;
    pcRtn = FEVARTYPE_INFO_MEM_N(&(gstFEVarTypeInfo[0]));
    for ( i=0;i<FEVARTYPE_INFO_V_SIZE;i++ )
    {
        if ( VT==FEVARTYPE_INFO_MEM_VT(&(gstFEVarTypeInfo[i])) )
        {
            pcRtn = FEVARTYPE_INFO_MEM_N(&(gstFEVarTypeInfo[i]));
            break;
        } 
    }
    return pcRtn;
}

BOOL  FEVarTypeInfoIs(const BYTE VT)
{
    BOOL bRtn;
    INT32 i;
    bRtn = FALSE;
    for ( i=0;i<FEVARTYPE_INFO_V_SIZE;i++ )
    {
        if ( VT==FEVARTYPE_INFO_MEM_VT(&(gstFEVarTypeInfo[i])) )
        {
            bRtn = TRUE;
            break;
        } 
    }
    return bRtn;
}

BOOL  FEVarTypeInfoIsName(const char *Name)
{
    BOOL bRtn;
    INT32 i;
    bRtn = FALSE;
    for ( i=0;i<FEVARTYPE_INFO_V_SIZE;i++ )
    {
        if ( !strcmp(FEVARTYPE_INFO_MEM_N( \
            &(gstFEVarTypeInfo[i])),Name) )
        {
            bRtn = TRUE;
            break;
        } 
    }
    return bRtn;
}

#ifdef __cplusplus
}
#endif

