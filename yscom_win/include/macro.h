/***************************************************************************/
/**[File Name    ]macro.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define macro                                            **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef MACRO_H__
#define MACRO_H__

#include <define.h>
#include <rtncode.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __OS_WIN__
#define __OS_WIN__      1
#define snprintf    _snprintf
#endif

#define CALCULATE_MIN(N1,N2)            (((N1)>=(N2))?(N2):(N1))
#define CALCULATE_MAX(N1,N2)            (((N1)>=(N2))?(N1):(N2))

#define STRCPY(d,s,size,len)  strncpy((d),(s),CALCULATE_MIN((size),(len)))
#define STRNCPY(d,s,size,len) strncpy((d),(s),CALCULATE_MIN((size-1),(len)))
#define MEMCPY(d,s,size,len)  memcpy((d),(s),CALCULATE_MIN((size),(len)))
#define MEMNCPY(d,s,size,len) memcpy((d),(s),CALCULATE_MIN((size-1),(len)))

#define LUCK_NUM                    0x19790131
#define LUCK_NUM2                   0x31017919
#define LUCK_INIT(v)                ((v)=FELUCK_NUM)
#define LUCK_INIT2(v)               ((v)=FELUCK_NUM2)
#define LUCK_INIT_NOT(v)            ((v)=0)
#define LUCK_ISINIT(v) (RTNCODE_CMPBOOL((LUCK_NUM==(v))||(LUCK_NUM2==(v))))

/****************************************************************************/
/** Var Array                                                              **/
/****************************************************************************/
#define ARRAYSIZE_MIN               8
#define ARRAYSIZE_MAX               0x00FFFFFF
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Endian                                                                 **/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MACRO_H__ */ 

