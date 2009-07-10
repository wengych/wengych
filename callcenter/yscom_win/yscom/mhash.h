/***************************************************************************/
/**[File Name    ]mhash.h                                                 **/
/**[File Path    ]$(TOPDIR)/libsrc/yscom                                  **/
/**[Library Name ]$(LIBDIR)/libyscom.so                                   **/
/**[Library Path ]$(APPDIR)/lib                                           **/
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

#define YSMHASH_HEAD_BASE       17
#define YSMHASH_HEAD_IDXSIZE    (INT32_SIZE+INT32_SIZE)
typedef struct tagMHashHead
{
    UCHAR Luck[INT32_SIZE];
    UCHAR Size[INT32_SIZE];
    UCHAR Status;
    UCHAR Type;
    UCHAR R[2];
    char  Ver[YSAPP_VER_LEN+1];
    UCHAR Len[INT32_SIZE];
    UCHAR ILen[INT32_SIZE];
    UCHAR CLen[INT32_SIZE];
    UCHAR Idx[YSMHASH_HEAD_BASE][2][INT32_SIZE];
}tYSMHashHead;
#define YSMHASHHEAD_ST_SIZE             (sizeof(tYSMHashHead))
#define YSMHASHHEAD_MEM_LUCK(h)         (((tYSMHashHead*)(h))->Luck)
#define YSMHASHHEAD_MEM_SIZE(h)         (((tYSMHashHead*)(h))->Size)
#define YSMHASHHEAD_MEM_STA(h)          (((tYSMHashHead*)(h))->Status)
#define YSMHASHHEAD_MEM_TYPE(h)         (((tYSMHashHead*)(h))->Type)
#define YSMHASHHEAD_MEM_VER(h)          (((tYSMHashHead*)(h))->Ver)
#define YSMHASHHEAD_MEM_LEN(h)          (((tYSMHashHead*)(h))->Len)
#define YSMHASHHEAD_MEM_ILEN(h)         (((tYSMHashHead*)(h))->ILen)
#define YSMHASHHEAD_MEM_CLEN(h)         (((tYSMHashHead*)(h))->CLen)
#define YSMHASHHEAD_MEM_IDX(h)          (((tYSMHashHead*)(h))->Idx)
#define YSMHASHHEAD_MEM_IDX_ADDR(h,n)   ((((tYSMHashHead*)(h))->Idx)[(n)][0])
#define YSMHASHHEAD_MEM_IDX_LEN(h,n)    ((((tYSMHashHead*)(h))->Idx)[(n)][1])

#define YSMHASHHEAD_INIT_LUCK(h)    \
    YSLUCK_INIT((*(INT32*)YSMHASHHEAD_MEM_LUCK((h))))
#define YSMHASHHEAD_INIT_LUCK_NOT(h) \
    YSLUCK_INIT_NOT((*(INT32*)YSMHASHHEAD_MEM_LUCK((h))))

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
    INT32 Len;
    INT32 ILen;
    INT32 CLen;
    INT32 IIdx[YSMHASH_HEAD_BASE][2];
}tYSMHashStruct;
#define YSMHASH_ST_SIZE                 (sizeof(tYSMHashStruct))
#define YSMHASH_MEM_LUCK(h)             (((tYSMHashStruct*)(h))->Luck)
#define YSMHASH_MEM_SIZE(h)             (((tYSMHashStruct*)(h))->Size)
#define YSMHASH_MEM_ST(h)               (((tYSMHashStruct*)(h))->SType)
#define YSMHASH_MEM_CT(h)               (((tYSMHashStruct*)(h))->CType)
#define YSMHASH_MEM_HEAD(h)             (((tYSMHashStruct*)(h))->Head)
#define YSMHASH_MEM_IDX(h)              (((tYSMHashStruct*)(h))->Idx)
#define YSMHASH_MEM_CTX(h)              (((tYSMHashStruct*)(h))->Ctx)
#define YSMHASH_MEM_IBUF(h)             (((tYSMHashStruct*)(h))->IBuf)
#define YSMHASH_MEM_CBUF(h)             (((tYSMHashStruct*)(h))->CBuf)
#define YSMHASH_MEM_SHM(h)              (((tYSMHashStruct*)(h))->Shm)
#define YSMHASH_MEM_DS(h)               (((tYSMHashStruct*)(h))->ds)
#define YSMHASH_MEM_MS(h)               (YSMHASH_MEM_DS((h)).shm_segsz)

#define YSMHASH_MEM_VER(h)              (((tYSMHashStruct*)(h))->Ver)
#define YSMHASH_MEM_LEN(h)              (((tYSMHashStruct*)(h))->Len)
#define YSMHASH_MEM_ILEN(h)             (((tYSMHashStruct*)(h))->ILen)
#define YSMHASH_MEM_CLEN(h)             (((tYSMHashStruct*)(h))->CLen)
#define YSMHASH_MEM_IIDX(h)             (((tYSMHashStruct*)(h))->IIdx)
#define YSMHASH_MEM_IIDX_ADDR(h,n)      ((YSMHASH_MEM_IIDX((h)))[(n)][0])
#define YSMHASH_MEM_IIDX_LEN(h,n)       ((YSMHASH_MEM_IIDX((h)))[(n)][1])

#define YSMHASH_INIT_LUCK(h)    \
    YSLUCK_INIT(YSMHASH_MEM_LUCK((h)))
#define YSMHASH_INIT_LUCK_NOT(h) \
    YSLUCK_INIT_NOT(YSMHASH_MEM_LUCK((h)))

#define YSMHASH_ST_MEM                  1
#define YSMHASH_ST_SHM                  2
#define YSMHASH_ST_STRUCT               3

#define YSMHASH_CT_DICT                 1

#define YSMHASH_ST_STR(MH) \
    ((YSMHASH_ST_MEM==YSMHASH_MEM_ST(MH))?"Memory" \
        :((YSMHASH_ST_SHM==YSMHASH_MEM_ST(MH))?"Shared memory" \
            :((YSMHASH_ST_STRUCT==YSMHASH_MEM_ST(MH))?"Struct":"Not init") \
        ) \
    )
#define YSMHASH_CT_STR(MH) \
    ((YSMHASH_CT_DICT==YSMHASH_MEM_CT(MH))?"Dict":"Unknown")

typedef struct tagYSMHashIdx
{
    BYTE HK[INT32_SIZE];
    BYTE Addr[INT32_SIZE]; 
    char Key[YSAPP_NAME_LEN+1];
}tYSMHashIdx;
#define YSMHASHIDX_ST_SIZE              (sizeof(tYSMHashIdx))
#define YSMHASHIDX_MEM_HK(h)            (((tYSMHashIdx*)(h))->HK)
#define YSMHASHIDX_MEM_A(h)             (((tYSMHashIdx*)(h))->Addr)
#define YSMHASHIDX_MEM_K(h)             (((tYSMHashIdx*)(h))->Key)

BOOL  YSMHashIsInit(void *MH);
BOOL  YSMHashPackBase(void *IBuf,INT32 Idx,INT32 Len);
BOOL  YSMHashPackIdx(void *IBuf,const char *Key,void *CBuf);
BOOL  YSMHashUnPackIdx(void *MH,INT32 Idx,tYSMHashIdx *IB);
void *YSMHashNew();
BOOL  YSMHashMallocBuf(void *MH,INT32 NewSize,BOOL Flag);

BOOL  YSMHashMemIsInit(void *Shm);
void *YSMHHashCloneFromMem(void *Mem,INT32 Len);

#ifdef __OS_LINUX__
BOOL  YSMHashShmUpdate(const char *Key,void *MH);
void *YSMHHashCloneFromShm(const char *Key);
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MHASH_H__ */ 

