/***************************************************************************/
/**[File Name    ]fecom.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define common for fe                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef FECOM_H__
#define FECOM_H__

#include <fedef.h>
#include <fevar.h>
#ifdef __OS_LINUX__
#include <feunit.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

INT32 FEHashCalSize(INT32  Size);
INT32 FEHashCalKey(const char *key,INT32 len);
INT32 FEHashGetIdx(INT32 HK,INT32 Size);

/****************************************************************************/
/** des.c                                                                  **/
/****************************************************************************/
void  DESDivKeys(const UCHAR *key,
    const INT32 divnum,
    UCHAR *divdata,
    UCHAR *out_key);
INT32 DESEncrypt(const UCHAR *key,
    const INT32 divnum,
    UCHAR *divdata,
    const INT32 ilen_in,
    UCHAR *in,
    UCHAR *out);
INT32 DESDecrypt(const UCHAR *key,
    const INT32 divnum,
    UCHAR *divdata,
    const INT32 ilen_in,
    UCHAR *in,
    UCHAR *out);
INT32 DESMac(const UCHAR *key,
        const INT32 divnum,
        UCHAR *divdata,
        const INT32 ilen_in,
        UCHAR *in,
        UCHAR *mac,
        INT32 iFlag);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** md5.c                                                                  **/
/****************************************************************************/
INT32 MD5String(char *string,UCHAR digest[16]);
INT32 MD5Buffer(char *buffer,UINT32 len,UCHAR digest[16]);
INT32 MD5File(char *filename,UCHAR digest[16]);
/****************************************************************************/
/****************************************************************************/

INT32 FE2BytesUni2Gbk(char *uniStr,INT32 uniLen \
    ,char *gbStr,INT32 *GbLen,INT32 gbSize);
INT32 FE2BytesGbk2Uni(char *gbStr,INT32 gbLen \
    ,char *uniStr,INT32 *uniLen,INT32 uniSize);

INT32 FE2BytesUniToUTF8BigEndian(BYTE *Unicode,INT32 ULen \
    ,BYTE *UTF8,INT32 *PLen,INT32 Size);
INT32 FE2BytesUTF8ToUniBigEndian(BYTE *UTF8,INT32 ULen \
    ,BYTE *Unicode,INT32 *PLen,INT32 Size);
INT32 FE4BytesUniToUTF8BigEndian(BYTE *Unicode,INT32 ULen \
    ,BYTE *UTF8,INT32 *PLen,INT32 Size);
INT32 FE4BytesUTF8ToUniBigEndian(BYTE *UTF8,INT32 ULen \
    ,BYTE *Unicode,INT32 *PLen,INT32 Size);

INT32 FEGbkfilter(char *TS,char *SS);

/****************************************************************************/
/** string.c                                                               **/
/****************************************************************************/
INT32 FEPathSplit(const char *Path);
BOOL  FECharIsSetBit(UCHAR C,INT32 Idx);
BOOL  FECharSetBit(UCHAR *C,INT32 Idx,BOOL Flag);
BOOL  FEGetEnv(char *Str,INT32 Size,const char *Key);
INT32 FEStrIsNumber(char *str,INT32 len);
INT32 FEStrIsHex(char *str,INT32 len);
char *FEStrTrimSign(char *str,char sign);
char *FEStrTrimRightSigns(char *str,char *signs);
char *FEStrTrimLeftSigns(char *str,char *signs);
char *FEStrTrimSigns(char *str,char *signs);
char *FEStrTrimChangeLine(char *str);
#define FEStrTrim(str)  FEStrTrimSigns((str),STR_TRIMLINE_SIGN)
char *FEStrToUpper(char *pcLine);
char *FEStrToLower(char *pcLine);
char *FEStrDelChar(char *pcLine,char ch);
INT32 FEStrByte2Hex(char *str,INT32 size,BYTE ch);
INT32 FEStrHex2Byte(BYTE *ch,char *str);
INT32 FEStrBytes2Hex(char *hex,INT32 size,char *bytes,INT32 len);
INT32 FEStrHex2Bytes(char *bytes,INT32 size,char *hex,INT32 len);
INT32 FEStr2Char(char *ch,char *pc,INT32 len);
void  FEStrESC(char *pcLine);
INT32 FEStrGetOneWordLen(INT32 *piWordLen \
    ,char *str,INT32 len,char *sign,INT32 signlen);
INT32 FEStrGetOneWord(INT32 *piWordLen,char *pcWord,INT32 size \
    ,char *str,INT32 len,char *sign,INT32 signlen);
INT32 FEStrFindSign(char *str,char ch);
INT32 FEStrFindLastSign(char *str,char ch);
void  FEEndianConversion(void *E,INT32 Size);
void  FEEndianToHost(void *E,INT32 Size);
void  FEEndianToNet(void *E,INT32 Size);
#define FEEndianLittle2Big(E,Size) FEEndianConversion((E),(Size))
#define FEEndianBig2Little(E,Size) FEEndianConversion((E),(Size))

char *FESetTrace(char *Buf,INT32 Size \
    ,const char *file,const INT32 line,const char *func);
#define FESETTRACE(Buf,Size) \
    FESetTrace((Buf),(Size),__FILE__,__LINE__,__func__)

INT32 FEHexToBufLine(char *Hex,INT32 Size,INT32 MaxLine \
    ,const char *Log,INT32 Len);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** keyvalue.c                                                             **/
/****************************************************************************/
void *FEKVNew();
void  FEKVFree(void *V);
INT32 FEKVLoadFromFile(void *Hash,const char *FileName);
void *FEKVLoadFromFile2(const char *FileName);
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FECOM_H__ */ 

