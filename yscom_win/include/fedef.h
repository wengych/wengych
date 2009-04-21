/***************************************************************************/
/**[File Name    ]fedef.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define const variable                                   **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef FEDEF_H__
#define FEDEF_H__

#include <define.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FELOG_LEVEL_ALL         LOG_LEVEL_ALL  
#define FELOG_LEVEL_DEBUG       LOG_LEVEL_DEBUG
#define FELOG_LEVEL_INFO        LOG_LEVEL_INFO 
#define FELOG_LEVEL_WARN        LOG_LEVEL_WARN 
#define FELOG_LEVEL_ERROR       LOG_LEVEL_ERROR
#define FELOG_LEVEL_FATAL       LOG_LEVEL_FATAL
#define FELOG_LEVEL_OFF         LOG_LEVEL_OFF  

/***************************************************************************/
/**  define variable in environment                                       **/
/***************************************************************************/
#define FEENV_APPDIR            ENV_APPDIR     
#define FEENV_HOME              ENV_HOME       
#define FEENV_LOGLEVEL          ENV_LOGLEVEL   
#define FEENV_LOGFILE           ENV_LOGFILE    
#define FEENV_LOGLISTFILE       ENV_LOGLISTFILE
#define FEENV_LOGDIR            ENV_LOGDIR     
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  define logfile                                                       **/
/**  logpath:                                                             **/
/**    1. user define                                                     **/
/**    2. $APPDIR/log                                                     **/
/**    3. $APPDIR                                                         **/
/**    4. $HOME/log                                                       **/
/**    5. $HOME                                                           **/
/**  logfile:                                                             **/
/**    1. user define (.log, .trace)                                      **/
/**    2. output      (.log, .trace)                                      **/
/**  default log level is "FELOG_LEVEL_ERROR"                             **/
/***************************************************************************/
/** LOGFILEPATH=$(LOGDIR)/output                                         **/
/** LOGDIR=$(APPDIR)/log                                                 **/
#define FEENV_DEFAULT_DIR               ENV_DEFAULT_DIR         
#define FEENV_LOGDIR_DEFAULT            ENV_LOGDIR_DEFAULT      
#define FEENV_LOGFILE_DEFAULT           ENV_LOGFILE_DEFAULT     
#define FEENV_LOGLISTFILE_DEFAULT       ENV_LOGLISTFILE_DEFAULT 
#define FEENV_LOGLEVEL_DEFAULT          ENV_LOGLEVEL_DEFAULT    
/***************************************************************************/
/***************************************************************************/

#define FEFILE_MAX_BUFFER           FILE_MAX_BUFFER
#define FEVARNAMELEN                VARNAMELEN

/***************************************************************************/
/**  define character set                                                 **/
/***************************************************************************/
#define FECHARSET_ASCII         CHARSET_ASCII 
#define FECHARSET_BIN           CHARSET_BIN   
#define FECHARSET_UCS2          CHARSET_UCS2  
#define FECHARSET_GBK           CHARSET_GBK   
#define FECHARSET_UTF8          CHARSET_UTF8  
#define FECHARSET_UTF16         CHARSET_UTF16 

/***************************************************************************/
/***************************************************************************/
#define FETIME_HOUR_IN_DAY        TIME_HOUR_IN_DAY 
#define FETIME_MIN_IN_HOUR        TIME_MIN_IN_HOUR 
#define FETIME_SEC_IN_MIN         TIME_SEC_IN_MIN  
#define FETIME_MIN_IN_DAY         TIME_MIN_IN_DAY  
#define FETIME_SEC_IN_HOUR        TIME_SEC_IN_HOUR 
#define FETIME_SEC_IN_DAY         TIME_SEC_IN_DAY  
#define FETIME_ISMON(m)           TIME_ISMON(m)    )
#define FETIME_ISDAY_(d)          TIME_ISDAY_(d)   )
#define FETIME_ISHOUR(h)          TIME_ISHOUR(h)   
#define FETIME_ISMIN(m)           TIME_ISMIN(m)    
#define FETIME_ISSEC(s)           TIME_ISSEC(s)    
/***************************************************************************/
/***************************************************************************/

#ifdef __DEBUG__
#define FEDEBUG_STEP \
    fprintf(stderr,"%s,%d %s\n",__FILE__,__LINE__,__func__)
#define FEDEBUG_PSTEP \
    fprintf(stderr,"%s,%d %s --%d\n" \
        ,__FILE__,__LINE__,__func__,(INT32)pthread_self())
#endif

#define FEDEBUG_TRACE(Buf) \
    sprintf(Buf,"%s,%d %s",__FILE__,__LINE__,__func__)
#define FEDEBUG_TRACES  __FILE__,__LINE__,__func__


#define FECAL_MIN(N1,N2)            CALCULATE_MIN(N1,N2) 
#define FECAL_MAX(N1,N2)            CALCULATE_MAX(N1,N2)
#define FECAL_RANGE(n,min,max)      CALCULATE_RANGE((n),(min),(max))

#define FELUCK_NUM                  LUCK_NUM  
#define FELUCK_NUM2                 LUCK_NUM2 
#define FELUCK_INIT                 LUCK_INIT
#define FELUCK_INIT2                LUCK_INIT2
#define FELUCK_INIT_NOT             LUCK_INIT_NOT
#define FELUCK_ISINIT               LUCK_ISINIT

/****************************************************************************/
/** Var Array                                                              **/
/****************************************************************************/
#define FEARRAYSIZE_MIN             ARRAYSIZE_MIN
#define FEARRAYSIZE_MAX             ARRAYSIZE_MAX
#define FEARRAYSIZE_GETMIN(Size)   (FECAL_MIN(0,(Size)))
#define FEARRAYSIZE_GETMAX(Max) \
    ((0==FECAL_MAX(0,(Max))) \
    ?FEARRAYSIZE_MAX \
    :FECAL_MIN(FECAL_MIN(1,(Max)),FEARRAYSIZE_MAX))
#define FEARRAYSIZE_GETSIZE(Max,Size) \
    (FECAL_MIN(FEARRAYSIZE_GETMAX((Max)),FECAL_MAX(1,(Size))))
#define FEARRAYSIZE_ISREALLOC(Max,Size) \
    RTNCODE_CMP(FEARRAYSIZE_GETMAX((Max))>=FECAL_MAX(0,(Size)))
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FEDEF_H__ */ 

