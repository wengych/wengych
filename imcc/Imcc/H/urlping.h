/*--------------------------------------------------------------------------*/
/*  MCURLPING.H                                                             */
/*  Url ping utility for download manager                                   */
/*                                                                          */
/*  History                                                                 */
/*      09/20/2004     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2004 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCURLPING_H__)
#define __MCURLPING_H__

#include "imccdef.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (* MCURL_Ping_Callpack)(
		int16		result,
		char*		fatest_site);

int mcurl_ping_init(
		HINSTANCE			hinstance,
		MCURL_Ping_Callpack	callback_proc);

int mcurl_ping_cleanup();

/**
 *  site_list format: site1;site2;... 
 *       http://192.168.0.1/client/kip;http://192.168.0.2/client/kip
 *  return code:
 *	     0: request succeed
 *       1: single site, don't need ping
 *       2: busy
 */
int mcurl_ping_request(
		char*				site_list);

int mcurl_ping_cancel();

#ifdef __cplusplus
}
#endif

#endif //__MCURLPING_H__