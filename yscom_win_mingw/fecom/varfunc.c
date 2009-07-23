/***************************************************************************/
/**[File Name    ]varfunc.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define array of var func                                **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagFEVarFunc
{
    BYTE VT;
    BYTE FT;
    void *Func;
}tFEVarFunc;
#define FEVARFUNC_ST_SIZE           (sizeof(tFEVarFunc))
#define FEVARFUNC_MEM_VT(v)         (((tFEVarFunc*)(v))->VT)
#define FEVARFUNC_MEM_FT(v)         (((tFEVarFunc*)(v))->FT)
#define FEVARFUNC_MEM_F(v)          (((tFEVarFunc*)(v))->Func)
static tFEVarFunc gstFuncListVT[] =
{
/****************************************************************************/
/**  free Function                                                         **/
/****************************************************************************/
     {VARTYPE_MEM_VT_NOT      ,FEVARTYPE_FREE_SUBFIX  ,NULL               }

    ,{VARTYPE_MEM_VT_BOOL     ,FEVARTYPE_FREE_SUBFIX  ,FEVarSTypeFree     }
    ,{VARTYPE_MEM_VT_BYTE     ,FEVARTYPE_FREE_SUBFIX  ,FEVarSTypeFree     }
    ,{VARTYPE_MEM_VT_INT16    ,FEVARTYPE_FREE_SUBFIX  ,FEVarSTypeFree     }
    ,{VARTYPE_MEM_VT_INT32    ,FEVARTYPE_FREE_SUBFIX  ,FEVarSTypeFree     }
    ,{VARTYPE_MEM_VT_INT64    ,FEVARTYPE_FREE_SUBFIX  ,FEVarSTypeFree     }
    ,{VARTYPE_MEM_VT_DOUBLE   ,FEVARTYPE_FREE_SUBFIX  ,FEVarSTypeFree     }
    ,{VARTYPE_MEM_VT_BIN      ,FEVARTYPE_FREE_SUBFIX  ,FEVarBinFree       }
    ,{VARTYPE_MEM_VT_STRING   ,FEVARTYPE_FREE_SUBFIX  ,FEVarStringFree    }
    ,{VARTYPE_MEM_VT_OBJECT   ,FEVARTYPE_FREE_SUBFIX  ,FEVarObjectFree    }
    ,{VARTYPE_MEM_VT_STRUCT   ,FEVARTYPE_FREE_SUBFIX  ,FEVarStructFree    }

    ,{VARTYPE_MEM_VT_P1       ,FEVARTYPE_FREE_SUBFIX  ,FEVarPointer4Free  }
    ,{VARTYPE_MEM_VT_P2       ,FEVARTYPE_FREE_SUBFIX  ,FEVarPointer4Free  }
    ,{VARTYPE_MEM_VT_P3       ,FEVARTYPE_FREE_SUBFIX  ,FEVarPointer4Free  }
    ,{VARTYPE_MEM_VT_P4       ,FEVARTYPE_FREE_SUBFIX  ,FEVarPointer4Free  }

    ,{VARTYPE_MEM_VT_ARRAY    ,FEVARTYPE_FREE_SUBFIX  ,FEVarArrayFree     }
    ,{VARTYPE_MEM_VT_FIFO     ,FEVARTYPE_FREE_SUBFIX  ,FEVarFifoFree      }
    ,{VARTYPE_MEM_VT_FILO     ,FEVARTYPE_FREE_SUBFIX  ,FEVarFiloFree      }
    ,{VARTYPE_MEM_VT_CICLE    ,FEVARTYPE_FREE_SUBFIX  ,NULL               }
    ,{VARTYPE_MEM_VT_HASH     ,FEVARTYPE_FREE_SUBFIX  ,FEVarHashFree      }
    ,{VARTYPE_MEM_VT_LINK     ,FEVARTYPE_FREE_SUBFIX  ,FEVarLinkFree      }
    ,{VARTYPE_MEM_VT_TREE     ,FEVARTYPE_FREE_SUBFIX  ,NULL               }
    ,{VARTYPE_MEM_VT_XML      ,FEVARTYPE_FREE_SUBFIX  ,NULL               }
         
/****************************************************************************/
/**  Clone Function                                                        **/
/****************************************************************************/
    ,{VARTYPE_MEM_VT_NOT      ,FEVARTYPE_CLONE_SUBFIX  ,NULL              }
                                                        
    ,{VARTYPE_MEM_VT_BOOL     ,FEVARTYPE_CLONE_SUBFIX  ,FEVarSTypeClone   }
    ,{VARTYPE_MEM_VT_BYTE     ,FEVARTYPE_CLONE_SUBFIX  ,FEVarSTypeClone   }
    ,{VARTYPE_MEM_VT_INT16    ,FEVARTYPE_CLONE_SUBFIX  ,FEVarSTypeClone   }
    ,{VARTYPE_MEM_VT_INT32    ,FEVARTYPE_CLONE_SUBFIX  ,FEVarSTypeClone   }
    ,{VARTYPE_MEM_VT_INT64    ,FEVARTYPE_CLONE_SUBFIX  ,FEVarSTypeClone   }
    ,{VARTYPE_MEM_VT_DOUBLE   ,FEVARTYPE_CLONE_SUBFIX  ,FEVarSTypeClone   }
    ,{VARTYPE_MEM_VT_BIN      ,FEVARTYPE_CLONE_SUBFIX  ,FEVarBinClone     }
    ,{VARTYPE_MEM_VT_STRING   ,FEVARTYPE_CLONE_SUBFIX  ,FEVarStringClone  }
    ,{VARTYPE_MEM_VT_OBJECT   ,FEVARTYPE_CLONE_SUBFIX  ,FEVarObjectClone  }
    ,{VARTYPE_MEM_VT_STRUCT   ,FEVARTYPE_CLONE_SUBFIX  ,FEVarStructClone  }

    ,{VARTYPE_MEM_VT_P1       ,FEVARTYPE_CLONE_SUBFIX  ,FEVarPointer4Clone}
    ,{VARTYPE_MEM_VT_P2       ,FEVARTYPE_CLONE_SUBFIX  ,FEVarPointer4Clone}
    ,{VARTYPE_MEM_VT_P3       ,FEVARTYPE_CLONE_SUBFIX  ,FEVarPointer4Clone}
    ,{VARTYPE_MEM_VT_P4       ,FEVARTYPE_CLONE_SUBFIX  ,FEVarPointer4Clone}

    ,{VARTYPE_MEM_VT_ARRAY    ,FEVARTYPE_CLONE_SUBFIX  ,FEVarArrayClone   }
    ,{VARTYPE_MEM_VT_FIFO     ,FEVARTYPE_CLONE_SUBFIX  ,FEVarFifoClone    }
    ,{VARTYPE_MEM_VT_FILO     ,FEVARTYPE_CLONE_SUBFIX  ,FEVarFiloClone    }
    ,{VARTYPE_MEM_VT_CICLE    ,FEVARTYPE_CLONE_SUBFIX  ,NULL              }
    ,{VARTYPE_MEM_VT_HASH     ,FEVARTYPE_CLONE_SUBFIX  ,FEVarHashClone    }
    ,{VARTYPE_MEM_VT_LINK     ,FEVARTYPE_CLONE_SUBFIX  ,FEVarLinkClone    }
    ,{VARTYPE_MEM_VT_TREE     ,FEVARTYPE_CLONE_SUBFIX  ,NULL              }
    ,{VARTYPE_MEM_VT_XML      ,FEVARTYPE_CLONE_SUBFIX  ,NULL              }
/****************************************************************************/
/**  Clone Value Function                                                  **/
/****************************************************************************/
    ,{VARTYPE_MEM_VT_NOT      ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
                                                        
    ,{VARTYPE_MEM_VT_BOOL     ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_BYTE     ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_INT16    ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_INT32    ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_INT64    ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_DOUBLE   ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_BIN      ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_STRING   ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_OBJECT   ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_STRUCT   ,FEVARTYPE_CLONEV_SUBFIX ,FEVarStructCloneValue}

    ,{VARTYPE_MEM_VT_P1       ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_P2       ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_P3       ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_P4       ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }

    ,{VARTYPE_MEM_VT_ARRAY    ,FEVARTYPE_CLONEV_SUBFIX ,FEVarArrayCloneValue}
    ,{VARTYPE_MEM_VT_FIFO     ,FEVARTYPE_CLONEV_SUBFIX ,FEVarFifoCloneValue}
    ,{VARTYPE_MEM_VT_FILO     ,FEVARTYPE_CLONEV_SUBFIX ,FEVarFiloCloneValue}
    ,{VARTYPE_MEM_VT_CICLE    ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_HASH     ,FEVARTYPE_CLONEV_SUBFIX ,FEVarHashCloneValue}
    ,{VARTYPE_MEM_VT_LINK     ,FEVARTYPE_CLONEV_SUBFIX ,FEVarLinkCloneValue}
    ,{VARTYPE_MEM_VT_TREE     ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_XML      ,FEVARTYPE_CLONEV_SUBFIX ,NULL              }
/****************************************************************************/
/**  Show Function                                                         **/
/****************************************************************************/
    ,{VARTYPE_MEM_VT_NOT      ,FEVARTYPE_SHOW_SUBFIX  ,NULL               }

    ,{VARTYPE_MEM_VT_BOOL     ,FEVARTYPE_SHOW_SUBFIX  ,FEVarSTypeShow     }
    ,{VARTYPE_MEM_VT_BYTE     ,FEVARTYPE_SHOW_SUBFIX  ,FEVarSTypeShow     }
    ,{VARTYPE_MEM_VT_INT16    ,FEVARTYPE_SHOW_SUBFIX  ,FEVarSTypeShow     }
    ,{VARTYPE_MEM_VT_INT32    ,FEVARTYPE_SHOW_SUBFIX  ,FEVarSTypeShow     }
    ,{VARTYPE_MEM_VT_INT64    ,FEVARTYPE_SHOW_SUBFIX  ,FEVarSTypeShow     }
    ,{VARTYPE_MEM_VT_DOUBLE   ,FEVARTYPE_SHOW_SUBFIX  ,FEVarSTypeShow     }
    ,{VARTYPE_MEM_VT_BIN      ,FEVARTYPE_SHOW_SUBFIX  ,FEVarBinShow       }
    ,{VARTYPE_MEM_VT_STRING   ,FEVARTYPE_SHOW_SUBFIX  ,FEVarStringShow    }
    ,{VARTYPE_MEM_VT_OBJECT   ,FEVARTYPE_SHOW_SUBFIX  ,FEVarObjectShow    }
    ,{VARTYPE_MEM_VT_STRUCT   ,FEVARTYPE_SHOW_SUBFIX  ,FEVarStructShow    }

    ,{VARTYPE_MEM_VT_P1       ,FEVARTYPE_SHOW_SUBFIX  ,FEVarPointer4Show  }
    ,{VARTYPE_MEM_VT_P2       ,FEVARTYPE_SHOW_SUBFIX  ,FEVarPointer4Show  }
    ,{VARTYPE_MEM_VT_P3       ,FEVARTYPE_SHOW_SUBFIX  ,FEVarPointer4Show  }
    ,{VARTYPE_MEM_VT_P4       ,FEVARTYPE_SHOW_SUBFIX  ,FEVarPointer4Show  }

    ,{VARTYPE_MEM_VT_ARRAY    ,FEVARTYPE_SHOW_SUBFIX  ,FEVarArrayShow     }
    ,{VARTYPE_MEM_VT_FIFO     ,FEVARTYPE_SHOW_SUBFIX  ,FEVarFifoShow      }
    ,{VARTYPE_MEM_VT_FILO     ,FEVARTYPE_SHOW_SUBFIX  ,FEVarFiloShow      }
    ,{VARTYPE_MEM_VT_CICLE    ,FEVARTYPE_SHOW_SUBFIX  ,NULL               }
    ,{VARTYPE_MEM_VT_HASH     ,FEVARTYPE_SHOW_SUBFIX  ,FEVarHashShow      }
    ,{VARTYPE_MEM_VT_LINK     ,FEVARTYPE_SHOW_SUBFIX  ,FEVarLinkShow      }
    ,{VARTYPE_MEM_VT_TREE     ,FEVARTYPE_SHOW_SUBFIX  ,NULL               }
    ,{VARTYPE_MEM_VT_XML      ,FEVARTYPE_SHOW_SUBFIX  ,NULL               }
/****************************************************************************/
/**  Pack Function (Value)                                                 **/
/****************************************************************************/
    ,{VARTYPE_MEM_VT_NOT      ,FEVARTYPE_PACK_SUBFIX   ,NULL              }
                                                         
    ,{VARTYPE_MEM_VT_BOOL     ,FEVARTYPE_PACK_SUBFIX   ,FEVarSTypePack    }
    ,{VARTYPE_MEM_VT_BYTE     ,FEVARTYPE_PACK_SUBFIX   ,FEVarSTypePack    }
    ,{VARTYPE_MEM_VT_INT16    ,FEVARTYPE_PACK_SUBFIX   ,FEVarSTypePack    }
    ,{VARTYPE_MEM_VT_INT32    ,FEVARTYPE_PACK_SUBFIX   ,FEVarSTypePack    }
    ,{VARTYPE_MEM_VT_INT64    ,FEVARTYPE_PACK_SUBFIX   ,FEVarSTypePack    }
    ,{VARTYPE_MEM_VT_DOUBLE   ,FEVARTYPE_PACK_SUBFIX   ,FEVarSTypePack    }
    ,{VARTYPE_MEM_VT_BIN      ,FEVARTYPE_PACK_SUBFIX   ,FEVarBinPack      }
    ,{VARTYPE_MEM_VT_STRING   ,FEVARTYPE_PACK_SUBFIX   ,FEVarStringPack   }
#if 0
    ,{VARTYPE_MEM_VT_OBJECT   ,FEVARTYPE_PACK_SUBFIX   ,FEVarObjectPack   }
#endif
    ,{VARTYPE_MEM_VT_STRUCT   ,FEVARTYPE_PACK_SUBFIX   ,FEVarStructPack   }

#if 0
    ,{VARTYPE_MEM_VT_P1       ,FEVARTYPE_PACK_SUBFIX   ,FEVarPointer4Pack }
    ,{VARTYPE_MEM_VT_P2       ,FEVARTYPE_PACK_SUBFIX   ,FEVarPointer4Pack }
    ,{VARTYPE_MEM_VT_P3       ,FEVARTYPE_PACK_SUBFIX   ,FEVarPointer4Pack }
    ,{VARTYPE_MEM_VT_P4       ,FEVARTYPE_PACK_SUBFIX   ,FEVarPointer4Pack }
#endif
                                                         
    ,{VARTYPE_MEM_VT_ARRAY    ,FEVARTYPE_PACK_SUBFIX   ,FEVarArrayPack    }
#if 0
    ,{VARTYPE_MEM_VT_FIFO     ,FEVARTYPE_PACK_SUBFIX   ,FEVarFiloPack     }
    ,{VARTYPE_MEM_VT_FILO     ,FEVARTYPE_PACK_SUBFIX   ,FEVarFiloPack     }
    ,{VARTYPE_MEM_VT_CICLE    ,FEVARTYPE_PACK_SUBFIX   ,NULL              }
#endif
    ,{VARTYPE_MEM_VT_HASH     ,FEVARTYPE_PACK_SUBFIX   ,FEVarHashPack     }
#if 0
    ,{VARTYPE_MEM_VT_LINK     ,FEVARTYPE_PACK_SUBFIX   ,FEVarLinkPack     }
    ,{VARTYPE_MEM_VT_TREE     ,FEVARTYPE_PACK_SUBFIX   ,NULL              }
    ,{VARTYPE_MEM_VT_XML      ,FEVARTYPE_PACK_SUBFIX   ,NULL              }
#endif
/****************************************************************************/
/**  UnPack Function (Value)                                               **/
/****************************************************************************/
    ,{VARTYPE_MEM_VT_NOT      ,FEVARTYPE_UNPACK_SUBFIX ,NULL              }
                                                         
    ,{VARTYPE_MEM_VT_BOOL     ,FEVARTYPE_UNPACK_SUBFIX ,FEVarSTypeUnPack  }
    ,{VARTYPE_MEM_VT_BYTE     ,FEVARTYPE_UNPACK_SUBFIX ,FEVarSTypeUnPack  }
    ,{VARTYPE_MEM_VT_INT16    ,FEVARTYPE_UNPACK_SUBFIX ,FEVarSTypeUnPack  }
    ,{VARTYPE_MEM_VT_INT32    ,FEVARTYPE_UNPACK_SUBFIX ,FEVarSTypeUnPack  }
    ,{VARTYPE_MEM_VT_INT64    ,FEVARTYPE_UNPACK_SUBFIX ,FEVarSTypeUnPack  }
    ,{VARTYPE_MEM_VT_DOUBLE   ,FEVARTYPE_UNPACK_SUBFIX ,FEVarSTypeUnPack  }
    ,{VARTYPE_MEM_VT_BIN      ,FEVARTYPE_UNPACK_SUBFIX ,FEVarBinUnPack    }
    ,{VARTYPE_MEM_VT_STRING   ,FEVARTYPE_UNPACK_SUBFIX ,FEVarStringUnPack }
#if 0
    ,{VARTYPE_MEM_VT_OBJECT   ,FEVARTYPE_UNPACK_SUBFIX ,FEVarObjectUnPack }
#endif
    ,{VARTYPE_MEM_VT_STRUCT   ,FEVARTYPE_UNPACK_SUBFIX ,FEVarStructUnPack }

#if 0
    ,{VARTYPE_MEM_VT_P1       ,FEVARTYPE_UNPACK_SUBFIX ,FEVarPointer4Pack }
    ,{VARTYPE_MEM_VT_P2       ,FEVARTYPE_UNPACK_SUBFIX ,FEVarPointer4Pack }
    ,{VARTYPE_MEM_VT_P3       ,FEVARTYPE_UNPACK_SUBFIX ,FEVarPointer4Pack }
    ,{VARTYPE_MEM_VT_P4       ,FEVARTYPE_UNPACK_SUBFIX ,FEVarPointer4Pack }
                                                         
#endif
                                                         
    ,{VARTYPE_MEM_VT_ARRAY    ,FEVARTYPE_UNPACK_SUBFIX ,FEVarArrayUnPack  }
#if 0
    ,{VARTYPE_MEM_VT_FIFO     ,FEVARTYPE_UNPACK_SUBFIX ,FEVarFiloUnPack   }
    ,{VARTYPE_MEM_VT_FILO     ,FEVARTYPE_UNPACK_SUBFIX ,FEVarFiloUnPack   }
    ,{VARTYPE_MEM_VT_CICLE    ,FEVARTYPE_UNPACK_SUBFIX ,NULL              }
#endif
    ,{VARTYPE_MEM_VT_HASH     ,FEVARTYPE_UNPACK_SUBFIX ,FEVarHashUnPack   }
#if 0
    ,{VARTYPE_MEM_VT_LINK     ,FEVARTYPE_UNPACK_SUBFIX ,FEVarLinkUnPack   }
    ,{VARTYPE_MEM_VT_TREE     ,FEVARTYPE_UNPACK_SUBFIX ,NULL              }
    ,{VARTYPE_MEM_VT_XML      ,FEVARTYPE_UNPACK_SUBFIX ,NULL              }
#endif
};
#define FEVARFUNCVT_ST_NUM        (sizeof(gstFuncListVT)/FEVARFUNC_ST_SIZE)

void *FEVarFuncGetFunc(void *List,INT32 Num,BYTE VT,BYTE FT)
{
    INT32 i;
    tFEVarFunc *FL;
    void *Func;
    if ( NULL==List )
    {
        return NULL;
    }
    FL = (tFEVarFunc*)List;
    Func = NULL;
    for ( i=0;i<Num;i++ )
    {
        if ( (VT==FEVARFUNC_MEM_VT(FL+i))&&(FT==FEVARFUNC_MEM_FT(FL+i)) )
        {
            Func = FEVARFUNC_MEM_F(FL+i);
            break;
        }
    }
    return Func;
}

void *FEVarFuncVTGetFunc(BYTE VT,BYTE FT)
{
    return FEVarFuncGetFunc(gstFuncListVT,FEVARFUNCVT_ST_NUM,VT,FT);
}

#ifdef __cplusplus
}
#endif

