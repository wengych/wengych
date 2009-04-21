/***************************************************************************/
/**[File Name    ]mempkg.h                                                **/
/**[File Path    ]$(TOPDIR)/libsrc/yscom                                  **/
/**[Library Name ]$(LIBDIR)/libyscom.so                                   **/
/**[Library Path ]$(SRCDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define head for share memory                            **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef MHASH_H__
#define MHASH_H__

#include <yscom.h>

#ifdef __cplusplus
extern "C" {
#endif

#define YSMP_HEAD_BASE       17
#define YSMP_HEAD_IDXSIZE    (INT32_SIZE+INT32_SIZE)
typedef struct tagMHashHead
{
    UCHAR Luck[INT32_SIZE];
    UCHAR Size[INT32_SIZE];
    UCHAR Status;
    UCHAR Type;
    UCHAR R[2];
    char  Ver[YSAPP_VER_LEN+1];
    UCHAR Max[INT32_SIZE];
    UCHAR Len[INT32_SIZE];
    UCHAR ILen[INT32_SIZE];
    UCHAR CLen[INT32_SIZE];
    UCHAR Idx[YSMP_HEAD_BASE][2][INT32_SIZE];
}tYSMPHead;
#define YSMPHEAD_ST_SIZE             (sizeof(tYSMPHead))
#define YSMPHEAD_MEM_LUCK(h)         (((tYSMPHead*)(h))->Luck)
#define YSMPHEAD_MEM_SIZE(h)         (((tYSMPHead*)(h))->Size)
#define YSMPHEAD_MEM_STA(h)          (((tYSMPHead*)(h))->Status)
#define YSMPHEAD_MEM_TYPE(h)         (((tYSMPHead*)(h))->Type)
#define YSMPHEAD_MEM_VER(h)          (((tYSMPHead*)(h))->Ver)
#define YSMPHEAD_MEM_MAX(h)          (((tYSMPHead*)(h))->Max)
#define YSMPHEAD_MEM_LEN(h)          (((tYSMPHead*)(h))->Len)
#define YSMPHEAD_MEM_ILEN(h)         (((tYSMPHead*)(h))->ILen)
#define YSMPHEAD_MEM_CLEN(h)         (((tYSMPHead*)(h))->CLen)
#define YSMPHEAD_MEM_IDX(h)          (((tYSMPHead*)(h))->Idx)
#define YSMPHEAD_MEM_IDX_ADDR(h,n)   ((((tYSMPHead*)(h))->Idx)[(n)][0])
#define YSMPHEAD_MEM_IDX_LEN(h,n)    ((((tYSMPHead*)(h))->Idx)[(n)][1])

#define YSMPHEAD_INIT_LUCK(h)    \
    YSLUCK_INIT((*(INT32*)YSMPHEAD_MEM_LUCK((h))))
#define YSMPHEAD_INIT_LUCK_NOT(h) \
    YSLUCK_INIT_NOT((*(INT32*)YSMPHEAD_MEM_LUCK((h))))

typedef struct tagMHashStruct
{
    INT32 Luck;
    INT32 Size;
    UCHAR SType;
    UCHAR CType;
    void *Head;
    void *Idx;
    void *Ctx;
    void *IBuf;
    void *CBuf;
    void *Shm;
#ifdef __OS_LINUX__
    struct shmid_ds ds;
#endif
    char Ver[YSAPP_VER_LEN+1];
    INT32 Max;
    INT32 Len;
    INT32 ILen;
    INT32 CLen;
    INT32 IIdx[YSMP_HEAD_BASE][2];
}tYSMPStruct;
#define YSMP_ST_SIZE                 (sizeof(tYSMPStruct))
#define YSMP_MEM_LUCK(h)             (((tYSMPStruct*)(h))->Luck)
#define YSMP_MEM_SIZE(h)             (((tYSMPStruct*)(h))->Size)
#define YSMP_MEM_ST(h)               (((tYSMPStruct*)(h))->SType)
#define YSMP_MEM_CT(h)               (((tYSMPStruct*)(h))->CType)
#define YSMP_MEM_HEAD(h)             (((tYSMPStruct*)(h))->Head)
#define YSMP_MEM_IDX(h)              (((tYSMPStruct*)(h))->Idx)
#define YSMP_MEM_CTX(h)              (((tYSMPStruct*)(h))->Ctx)
#define YSMP_MEM_IBUF(h)             (((tYSMPStruct*)(h))->IBuf)
#define YSMP_MEM_CBUF(h)             (((tYSMPStruct*)(h))->CBuf)
#define YSMP_MEM_SHM(h)              (((tYSMPStruct*)(h))->Shm)
#define YSMP_MEM_DS(h)               (((tYSMPStruct*)(h))->ds)
#define YSMP_MEM_MS(h)               (YSMP_MEM_DS((h)).shm_segsz)

#define YSMP_MEM_VER(h)              (((tYSMPStruct*)(h))->Ver)
#define YSMP_MEM_MAX(h)              (((tYSMPStruct*)(h))->Max)
#define YSMP_MEM_LEN(h)              (((tYSMPStruct*)(h))->Len)
#define YSMP_MEM_ILEN(h)             (((tYSMPStruct*)(h))->ILen)
#define YSMP_MEM_CLEN(h)             (((tYSMPStruct*)(h))->CLen)
#define YSMP_MEM_IIDX(h)             (((tYSMPStruct*)(h))->IIdx)
#define YSMP_MEM_IIDX_ADDR(h,n)      ((YSMP_MEM_IIDX((h)))[(n)][0])
#define YSMP_MEM_IIDX_LEN(h,n)       ((YSMP_MEM_IIDX((h)))[(n)][1])

#define YSMP_INIT_LUCK(h)    \
    YSLUCK_INIT(YSMP_MEM_LUCK((h)))
#define YSMP_INIT_LUCK_NOT(h) \
    YSLUCK_INIT_NOT(YSMP_MEM_LUCK((h)))

#define YSMP_ST_MEM                  1
#define YSMP_ST_SHM                  2
#define YSMP_ST_STRUCT               3

#define YSMP_CT_ISHASH(v)            (VARTYPE_MEM_VT_HASH==(v))
#define YSMP_CT_ISARRAY(v)           (VARTYPE_MEM_VT_ARRAY==(v))
#define YSMP_CT_IS(v) \
    ( !YSMP_CT_ISHASH((v))||!YSMP_CT_ISARRAY((v)) )

#define YSMP_ST_STR(MH) \
    ((YSMP_ST_MEM==YSMP_MEM_ST(MH))?"Memory" \
        :((YSMP_ST_SHM==YSMP_MEM_ST(MH))?"Shared memory" \
            :((YSMP_ST_STRUCT==YSMP_MEM_ST(MH))?"Struct":"Not init") \
        ) \
    )
#define YSMP_CT_STR(v) \
    ((VARTYPE_MEM_VT_HASH==(v))?"Hash" \
        :((VARTYPE_MEM_VT_ARRAY==(v))?"Array":"Unknow") \
    )

typedef struct tagYSMPIdx
{
    BYTE HK[INT32_SIZE];
    BYTE Addr[INT32_SIZE]; 
    BYTE Len[INT32_SIZE];
}tYSMPIdx;
#define YSMPIDX_ST_SIZE              (sizeof(tYSMPIdx))
#define YSMPIDX_MEM_HK(h)            (((tYSMPIdx*)(h))->HK)
#define YSMPIDX_MEM_A(h)             (((tYSMPIdx*)(h))->Addr)
#define YSMPIDX_MEM_L(h)             (((tYSMPIdx*)(h))->Len)
#define YSMPIDX_MEM_HK_INT(h)        (*(INT32*)YSMPIDX_MEM_HK(h))
#define YSMPIDX_MEM_A_INT(h)         (*(INT32*)YSMPIDX_MEM_A(h))
#define YSMPIDX_MEM_L_INT(h)         (*(INT32*)YSMPIDX_MEM_L(h))

/** mp.c **/
BOOL  YSMPPackBase(void *IBuf,INT32 Idx,INT32 Len);
BOOL  YSMPPackIdx(void *IBuf,INT32 HK,INT32 Pos,INT32 Len);
BOOL  YSMPPackIdx2(void *Buf,INT32 Size,INT32 HK,INT32 Pos,INT32 Len);
BOOL  YSMPUnPackIdx(void *MH,INT32 Idx,tYSMPIdx *IB);
BOOL  YSMPUnPackIdx2(void *MH,INT32 Idx,void **IB,INT32 *PL);
BOOL  YSMPUpdateIdxHK(void *Buf,INT32 Size,INT32 HK);
BOOL  YSMPUpdateIdxAddr(void *Buf,INT32 Size,INT32 Pos,INT32 Len);
BOOL  YSMPUnPackIdxByPos(void *MH,INT32 Pos,tYSMPIdx *IB);
BOOL  YSMPUnPackIdxByPos2(void *MH,INT32 Pos,void **IB,INT32 *PL);
BOOL  YSMPMallocBuf(void *MH,INT32 NewSize,BOOL Flag);

/** mpmem.c **/
BOOL  YSMPMemIsInit(void *Shm);
void *YSMPCloneFromMem(void *Mem,INT32 Len);

/** mpshm.c **/
#ifdef __OS_LINUX__
BOOL  YSMPShmUpdate(const char *Key,void *MH);
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MHASH_H__ */ 

