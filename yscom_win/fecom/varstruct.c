/***************************************************************************/
/**[File Name    ]varstruct.c                                             **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for var struct                              **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif


#define FEVARSTRUCT_INFO_POS    (0)
#define FEVARSTRUCT_INFO_LEN_P  (0)
#define FEVARSTRUCT_INFO_LEN_L  (INT32_SIZE)
#define FEVARSTRUCT_INFO_LEN    (FEVARTYPE_INFO_LEN+FEVARSTRUCT_INFO_LEN_L)
#define FEVARSTRUCT_VALUE_POS   (FEVARSTRUCT_INFO_LEN)
#define FEVARSTRUCT_VALUE_LEN   0

void *FEVarStructNew(INT32 n)
{
    INT32 i;
    INT32 N;
    void *Var;
    void *V;
    BOOL bRtn;

    N = FECAL_MAX(1,n);
    if ( STRUCTSIZE_MAX<N )
    {
        return NULL;
    }
    if ( NULL==(Var=FEVarRootNew()) )
    {
        return NULL;
    }
    FEVarTypeVTSet(Var,VARTYPE_MEM_VT_STRUCT);
    FEVarRootSetMax(Var,N);
    bRtn = FALSE;
    V = NULL;
    while( 1 )
    {
        if ( NULL==(V=malloc(FEVARP4_ST_SIZE*N)) )
        {
            break;
        }
        for ( i=0;i<N;i++ )
        {
            FEVarStructInitPointer(((tFEVarPointer4*)V)+i);
        }
        FEVarRootSetValue(Var,V);
        V = NULL;
        FEVarRootSetSize(Var,N);
        FEVarRootSetLen(Var,N);
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        if ( NULL!=V )
        {
            free(V);
            V = NULL;
        }
        FEVarStructFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarStructNew_Key(INT32 N,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarStructNew(N)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarStructFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void  FEVarStructFree(void *Var)
{
    FEVarStructVFree(Var);
    FEVarStructNFree(Var);
}

void FEVarStructVFree(void *Var)
{
    INT32 i;
    INT32 Len;
    void *V;
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) )
    {
        return ;
    }
    Len = FEVarRootGetLen(Var);
    if ( NULL==(V=FEVarRootGetValue(Var)) )
    {
        return ;
    }
    for ( i=0;i<Len;i++ )
    {
        FEVarFree( FEVarPointer4GetP0(((tFEVarPointer4*)V)+i) );
        FEVarStructInitPointer(((tFEVarPointer4*)V)+i);
    }
    FEVarRootSetSize(Var,0);
    FEVarRootSetValue(Var,NULL);
    free( V );
}

void  FEVarStructShow(void *Var,INT32 T,void *Buf)
{   
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,VARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarStructNShow1(Var,T,Buf);
    FEVarStructVShow(Var,T,Buf);
    FEVarTypeNShow2(Var,T,Buf);
}

void  FEVarStructVShow(void *Var,INT32 T,void *Buf)
{   
    INT32 Len;
    INT32 i;
 
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) )
    {
        return;
    }
    if ( !FEVarTypeIsInit2(Buf,VARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    Len = FEVarRootGetLen(Var);
    for ( i=0;i<Len;i++ )
    {
        FEVarShow(FEVarStructGet(Var,i),T+1,Buf);
    }
}

BOOL  FEVarStructPackInfo(void *Var,void *Buf)
{
    return FEPackFuncInt32(Buf,FEVarRootGetSize(Var));
}

BOOL  FEVarStructPack(void *Var,void *Buf)
{
    BOOL bRtn;
    INT32 PL;
    INT32 L;
    void *V;
 
    INT32 Idx;
    INT32 Len;
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) \
        ||!FEVarTypeIsInit2(Buf,VARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    L = FEVarBinGetLen(Buf);
    bRtn = FALSE;
    while( 1 )
    {
        PL = FEVARSTRUCT_INFO_LEN + FEVARSTRUCT_VALUE_LEN;
        /* VarType */
        if ( !FEVarTypePack(Buf,Var,PL,FEVarStructPackInfo) )
        {
            break;
        }
        Len = FEVarRootGetSize(Var);
        for ( Idx=0;Idx<Len;Idx++ )
        {
            if ( NULL==(V=FEVarStructGet(Var,Idx)) )
            {
                if ( FALSE==(bRtn=FEPackFuncByte(Buf,VARTYPE_MEM_VT_NOT)) )
                {
                    break;
                }
                continue;
            }
            if ( FALSE==(bRtn=FEVarPack(V,Buf)) )
            {
                break;
            }
        }
        break;
    }
    if ( !bRtn )
    {
        FEVarBinCut(Buf,L,0);
    }
 
    return bRtn;
}

INT32 FEVarStructUnPack(void **VVar,void *Buf,INT32 P)
{
    INT32 iRtn;
    INT32 PL;
    tFEVarType VarType;
    void *V;
    INT32 VL;
    void *Var;
    void *N;
 
    INT32 Size;
    INT32 Idx;

    iRtn = RTNCODE_ERVAR_UNPACK;
    if ( NULL==VVar )
    {
        return iRtn;
    }
    if ( NULL==(V=FEVarBinGet(Buf)) )
    {
        return iRtn;
    }
    if ( VARTYPE_MEM_VT_STRUCT!=((BYTE*)V)[P] )
    {
        return iRtn;
    }
    if ( RTNCODE_OK>(iRtn=FEVarTypeUnPack(&PL,&VarType,Buf,P+BYTE_SIZE)) )
    {
        return iRtn;
    }
    VL = PL;
    PL = iRtn;

    *VVar = NULL;
    Var = NULL;
    N = NULL;
    iRtn = RTNCODE_ERVAR_UNPACK;
    while( 1 )
    {
        if ( !FEUnPackFuncInt32(Buf,PL+FEVARSTRUCT_INFO_LEN_P,&Size) )
        {
            break;
        }
        if ( NULL==(Var=FEVarStructNew(Size)) )
        {
            break;
        }
        if ( !FEVarTypeUnPackSetType(Var,&VarType) )
        {
            break;
        }
        PL += FEVARSTRUCT_VALUE_POS;
        for ( Idx=0;Idx<Size;Idx++ )
        {
            if ( VARTYPE_MEM_VT_NOT==((BYTE*)V)[PL] )
            {
                PL ++;
                continue;
            }
            if ( 0>(iRtn=FEVarUnPack(&N,Buf,PL)) )
            {
                break;
            }
            PL = iRtn;
            if ( !FEVarStructSet(Var,Idx,N) )
            {
                break;
            }
            N = NULL;
        }
        if ( Idx<Size )
        {
            iRtn = RTNCODE_ERVAR_UNPACK;
            break;
        }
        iRtn = RTNCODE_OK;
        break;
    }
    if ( RTNCODE_OK==iRtn )
    {
        iRtn = PL;
        *VVar = Var;
        Var = NULL;
    }
    FEVarFree(N);
    N = NULL;
    FEVarStructFree(Var);
    Var = NULL;
    return iRtn;
}

void  FEVarStructInitPointer(void *Var)
{   
   FEVarPointer4Init(Var,FEVARSTRUCT_NODE_P_NUM);
   FEVarPointer4SetFlag(Var,0);
}   

INT32 FEVarStructGetSize(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) )
    {
        return FALSE;
    }
    return FEVarRootGetSize(Var);
}

BOOL  FEVarStructIsIdxOfRange(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) )
    {
        return FALSE;
    }
    return RTNCODE_CMPBOOL( (0<=Idx)&&(FEVarRootGetSize(Var)>Idx) );
}

void *FEVarStructGetNode(void *Var,INT32 Idx)
{
    void *V;
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) )
    {
        return NULL;
    }
    if ( !FEVarStructIsIdxOfRange(Var,Idx) )
    {
        return NULL;
    }
    if ( NULL==(V=FEVarRootGetValue(Var)) )
    {
        return NULL;
    }
    return ((tFEVarPointer4*)V)+Idx;
}

void *FEVarStructGet(void *Var,INT32 Idx)
{
    void *Node;
    if ( NULL==(Node=FEVarStructGetNode(Var,Idx)) )
    {
        return NULL;
    }
    return FEVarPointer4GetP0(Node);
}

BOOL  FEVarStructSet(void *Var,INT32 Idx,void *V)
{
    void *Node;
    if ( NULL==(Node=FEVarStructGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4Set2P0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarStructReplace(void *Var,INT32 Idx,void *V)
{
    void *Node;
    if ( NULL==(Node=FEVarStructGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

void *FEVarStructGetNodeByKey(void *Var,const char *Key,INT32 Len)
{
    BOOL bRtn;
    void *Node;
    INT32 Idx;
    INT32 Size;
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) \
        || (NULL==Key) || (0>=Len) )
    {
        return FALSE;
    }
    bRtn = FALSE;
    Size = FEVarRootGetSize(Var);
    for ( Idx=0;Idx<Size;Idx++ )
    {
        if ( NULL==(Node=FEVarStructGetNode(Var,Idx)) )
        {
            continue;
        }
        if ( FEVarCmpKey(FEVarPointer4GetP0(Node),Key,Len) )
        {
            bRtn = TRUE;
            break;
        }
    }
    if ( !bRtn )
    {
        Node = NULL;
    }
 
    return Node;
}

void *FEVarStructGetByKey(void *Var,const char *Key,INT32 Len)
{
    BOOL bRtn;
    void *V;
    INT32 Idx;
    INT32 Size;
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) \
        || (NULL==Key) || (0>=Len) )
    {
        return FALSE;
    }
    bRtn = FALSE;
    Size = FEVarRootGetSize(Var);
    for ( Idx=0;Idx<Size;Idx++ )
    {
        if ( NULL==(V=FEVarStructGet(Var,Idx)) )
        {
            continue;
        }
        if ( FEVarCmpKey(V,Key,Len) )
        {
            bRtn = TRUE;
            break;
        }
    }
    if ( !bRtn )
    {
        V = NULL;
    }
 
    return V;
}

BOOL  FEVarStructSetByKey(void *Var,const char *Key,INT32 Len,void *V)
{
    void *Node;
    if ( NULL==(Node=FEVarStructGetNodeByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4Set2P0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarStructReplaceByKey(void *Var,const char *Key,INT32 Len,void *V)
{
    void *Node;
    if ( NULL==(Node=FEVarStructGetNodeByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

void *FEVarStructClone(void *Var)
{
    void *N;
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarStructNew(FEVarStructGetSize(Var))) )
    {
        return NULL;
    }
    if ( !FEVarStructCloneValue(N,Var) )
    {
        FEVarStructFree(N);
        N = NULL;
    }
    if ( !FEVarTypeClone(N,Var) )
    {
        FEVarStructFree(N);
        N = NULL;
    }
    return N;
}

BOOL  FEVarStructCloneValue(void *N,void *Var)
{
    INT32 i;
    INT32 S;
    void *V;
    void *VV;
    BOOL bRtn;
 
    if ( !FEVarTypeIsInit2(N,VARTYPE_MEM_VT_STRUCT) )
    {
        return FALSE;
    }
    if ( !FEVarTypeIsInit2(Var,VARTYPE_MEM_VT_STRUCT) )
    {
        return TRUE;
    }
    bRtn = TRUE;
    V = NULL;
    while( 1 )
    {
        S = FEVarRootGetSize(Var);
        if ( FEVarRootGetSize(N)!=S )
        {
            bRtn = FALSE;
            break;
        }
        for ( i=0;i<S;i++ )
        {
            if ( NULL==(VV=FEVarStructGet(Var,i)) )
            {
                continue;
            }
            if ( NULL==(V=FEVarClone(VV)) )
            {
                bRtn = FALSE;
                break;
            }
            if ( !FEVarStructReplace(N,i,V) )
            {
                bRtn = FALSE;
                break;
            }
            V = NULL;
        }
        break;
    }
    FEVarFree(V);
    V = NULL;
    return bRtn;
}

INT32 FEVarStructFieldGetIdx(void *Set,INT32 Size,const char *Name,INT32 Len)
{
    INT32 Idx;
    if ( (NULL==Set)||(0>=Size)||(NULL==Name)||(0>=Len) )
    {
        return RTNCODE_ER;
    }
    for ( Idx=0;Idx<Size;Idx++ )
    {
        if ( !FEStrCmp( \
    FEVARSTRUCTFIELDINFO_MEM_N(((tFEVarStructFieldInfo*)Set)+Idx) \
    ,strlen(FEVARSTRUCTFIELDINFO_MEM_N(((tFEVarStructFieldInfo*)Set)+Idx)) \
            ,Name,Len) )
        {
            break;
        }
    }
    return (Idx>=Size)?RTNCODE_ER:Idx;
}

void *FEVarArrayToStruct(void *Array,void *Set,INT32 Size)
{
    void *Key;
    void *Var;
    void *Arr;
    void *V;
    INT32 Len;
    INT32 Idx;
    BOOL Flag;
    char F[BUFSIZE_1024];
    tFEVarStructFieldInfo *pSet;
    if ( !FEVarIsInit2(Array,VARTYPE_MEM_VT_ARRAY)||(NULL==Set)||(0>=Size) )
    {
        return NULL;
    }
    if ( 0==(Len=FEVarArrayGetLen(Array)) )
    {
        return NULL;
    }
    if ( NULL==(Var=FEVarStructNew(Size)) )
    {
        return NULL;
    }
    pSet = (tFEVarStructFieldInfo*)Set;
    Flag = TRUE;
    memset(F,0,sizeof(F));
    while( 0<Len )
    {
        if ( NULL==(V=FEVarArrayRemove(Array,0)) )
        {
            Flag = FALSE;
            break;
        }
        Len --;
        Key = FEVarGetKey(V);
        if ( RTNCODE_ER==(Idx=FEVarStructFieldGetIdx(pSet \
            ,Size,Key,strlen(Key))) )
        {
            Flag = FALSE;
            break;
        }
        if ( VARTYPE_MEM_VT_ARRAY==FEVARSTRUCTFIELDINFO_MEM_T(pSet+Idx) )
        {
            if ( NULL==(Arr=FEVarStructGet(Var,Idx)) )
            {
                if ( NULL==(Arr=FEVarArrayNew_Key(0,(char *)Key)) )
                {
                    Flag = FALSE;
                    break;
                }
                if ( !FEVarStructSet(Var,Idx,Arr) )
                {
                    FEVarArrayFree(Arr);
                    Flag = FALSE;
                    break;
                }
            }
            if ( !FEVarArrayAdd(Arr,V) )
            {
                Flag = FALSE;
                break;
            }
        }
        else 
        {
            if ( FEVARSTRUCTFIELDINFO_MEM_T(pSet+Idx)!=FEVarGetType(V) )
            {
                Flag = FALSE;
                break;
            } 
            if ( !FEVarStructSet(Var,Idx,V) )
            {
                Flag = FALSE;
                break;
            }
        }
        V = NULL;
        F[Idx] = 1;
    }
    FEVarFree(V);
    V = NULL;
    if ( Flag )
    {
        Len = FECAL_MIN(sizeof(F),Size);
        for ( Idx=0;Idx<Len;Idx++ )
        {
            if ( 0==FEVARSTRUCTFIELDINFO_MEM_F(pSet+Idx) )
            {
                continue;
            }
            if ( 0==F[Idx] )
            {
                Flag = FALSE;
                break;
            }
        }/* for ( Idx=0;Idx<Len;Idx++ ) */
    }

    if ( !Flag )
    {
        FEVarHashFree(Var);
        Var = NULL;
    }
    return Var;
}

#ifdef __cplusplus
}
#endif

