/*--------------------------------------------------------------------------*/
/*  IMCCDEF.H                                                               */
/*  Cross platform related defines                                          */
/*                                                                          */
/*  History                                                                 */
/*      11/24/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/
#if !defined(__IMCCDEF_H__)
#define __IMCCDEF_H__

/**
/* basic include
*/

#if defined (WIN32) || defined (WIN31)
	#include <winsock2.h>
    #include <windows.h>
	#include <ws2tcpip.h>   
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <fcntl.h>

	#define DLLEXPORT __declspec(dllexport)
	#define DLLIMPORT __declspec(dllimport)

#elif defined(__MWERKS__) 
	#define MACOS
	#define DLLEXPORT
	#define DLLIMPORT

#elif defined(LINUX) || defined(UNIX)
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <errno.h>
	#include <limits.h>
	#include <signal.h>
    #include <sys/poll.h>
    #include <sys/types.h>
	#include <sys/stat.h>
    #include <pthread.h>
	#include <netdb.h>
	#include <arpa/inet.h>

	#define DLLEXPORT
	#define DLLIMPORT
#endif

/**
/* Primitive data types
*/
#if !defined(int8)
typedef char int8;
#endif

#if !defined(uint8)
typedef unsigned char uint8;
#endif

#if !defined(int16)
typedef short int16;
#endif

#if !defined(uint16)
typedef unsigned short uint16;
#endif

#if !defined(int32)
typedef long int32;
#endif

#if !defined(uint32)
typedef unsigned long uint32;
#endif

#if !defined(int64)
typedef LONGLONG int64;
#endif

#if !defined(uint64)
typedef ULONGLONG uint64;
#endif

#if !defined(float32)
typedef float float32;
#endif

#if !defined(float64)
typedef double float64;
#endif

#if !defined(boolean)
typedef uint8 boolean;
#endif

#if !defined(wchar)
typedef unsigned short wchar;
#endif

#if !defined(TRUE)
#define TRUE ((boolean)1)
#endif

#if !defined(FALSE)
#define FALSE ((boolean)0)
#endif

#if !defined(NULL)
#define NULL ((int32)0)
#endif

/**
/* basic ansi functions
*/
#if defined (WIN32) || defined (WIN31)
	typedef SOCKET	MC_SOCKET;
	#define MC_INVALID_SOCKET	INVALID_SOCKET
#elif defined(__MWERKS__) 

#elif defined(LINUX) || defined(UNIX)
	#define stricmp strcasecmp
	typedef int	MC_SOCKET;
	#define MC_INVALID_SOCKET	-1
#endif

#endif //__IMCCDEF_H__
