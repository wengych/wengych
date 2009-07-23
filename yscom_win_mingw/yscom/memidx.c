/***************************************************************************/
/**[File Name    ]memidx.c                                                **/
/**[File Path    ]$(TOPDIR)/src/libsrc/yscom                              **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for share memory ( hash )                   **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifdef __OS_WIN__
#include <winsock2.h>
#ifdef _WINDEF_
#ifndef __OS_WIN_WINDEF__
#define __OS_WIN_WINDEF__ 1
#endif
#endif
#endif
#include <mempkg.h>

#ifdef __cplusplus
extern "C"{
#endif
 
INT32 YSMPIdxSize()
{
    return YSMPIDX_ST_SIZE;
}

BOOL  YSMPIdxAdd(void *IBuf,INT32 HK,INT32 Pos,INT32 Len)
{
    tYSMPIdx IB;
    if ( !YSMPIdxSet(&IB,sizeof(IB),HK,Pos,Len) )
    {
        return FALSE;
    }
    return YSVarBinCat(IBuf,&IB,sizeof(IB));
}

BOOL  YSMPIdxSet(void *Buf,INT32 Size,INT32 HK,INT32 Pos,INT32 Len)
{
    if ( !YSMPIdxUpdateHK(Buf,Size,HK) )
    {
        return FALSE;
    }
    return YSMPIdxUpdateAddr(Buf,Size,Pos,Len);
}

BOOL  YSMPIdxUpdateHK(void *Buf,INT32 Size,INT32 HK)
{
    if ( (NULL==Buf)||(YSMPIDX_ST_SIZE>Size)||(0==HK) )
    {
        return FALSE;
    }
    YSMPIDX_MEM_HK_INT(Buf) = YSCAL_MAX(0,HK);
    FEEndianToNet(YSMPIDX_MEM_HK(Buf),INT32_SIZE);
    return TRUE;
}

BOOL  YSMPIdxUpdateAddr(void *Buf,INT32 Size,INT32 Pos,INT32 Len)
{
    if ( (NULL==Buf)||(YSMPIDX_ST_SIZE>Size) )
    {
        return FALSE;
    }
    YSMPIDX_MEM_A_INT(Buf) = YSCAL_MAX(0,Pos);
    FEEndianToNet(YSMPIDX_MEM_A(Buf),INT32_SIZE);
    YSMPIDX_MEM_L_INT(Buf) = YSCAL_MAX(0,Len);
    FEEndianToNet(YSMPIDX_MEM_L(Buf),INT32_SIZE);
    return TRUE;
}

BOOL  YSMPIdxUnPack(void *MH,INT32 Idx,void **IB,INT32 *PL)
{
    if ( !YSMPIsInit(MH)||(0>Idx)||(NULL==IB)||(NULL==PL) )
    {
        return FALSE;
    }
    if ( YSMP_MEM_MAX(MH)<=Idx )
    {
        return FALSE;
    }
    *IB = ((BYTE*)YSMP_MEM_IDX(MH))+Idx*YSMPIDX_ST_SIZE;
    *PL = YSMPIDX_ST_SIZE;
    return TRUE;
}

BOOL  YSMPIdxUnPackByPos(void *MH,INT32 Pos,void **IB,INT32 *PL)
{
    if ( !YSMPIsInit(MH)||(0>Pos)||(NULL==IB)||(NULL==PL) )
    {
        return FALSE;
    }
    if ( (YSMP_MEM_ILEN(MH)<=Pos)||(0!=(Pos%YSMPIDX_ST_SIZE)) )
    {
        return FALSE;
    }
    *IB = ((BYTE*)YSMP_MEM_IDX(MH))+Pos;
    *PL = YSMPIDX_ST_SIZE;
    return TRUE;
}

BOOL  YSMPIdxCmpHashKey(void *IB,INT32 Size,INT32 HK)
{
    INT32 H;
    if ( (NULL==IB)||(YSMPIDX_ST_SIZE>Size) )
    {
        return FALSE;
    }
    H = YSMPIDX_MEM_HK_INT(IB);
    FEEndianToHost(&H,INT32_SIZE);
    return RTNCODE_CMPBOOL(H==HK);
}

BOOL  YSMPIdxGetAddr(void *IB,INT32 Size,INT32 *PA,INT32 *PL)
{
    if ( (NULL==IB)||(YSMPIDX_ST_SIZE>Size)||(NULL==PA)||(NULL==PL) )
    {
        return FALSE;
    }
    *PA = YSMPIDX_MEM_A_INT(IB);
    *PL = YSMPIDX_MEM_L_INT(IB);
    FEEndianToHost(PA,INT32_SIZE);
    FEEndianToHost(PL,INT32_SIZE);
    return TRUE;
}

#ifdef __cplusplus
}
#endif
 
