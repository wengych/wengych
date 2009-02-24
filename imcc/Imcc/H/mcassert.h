/*--------------------------------------------------------------------------*/
/*  MCASSERT.H                                                              */
/*                                                                          */
/*  History                                                                 */
/*      11/24/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#ifndef __MCASSERT_H__
#define __MCASSERT_H__

#include "mctrace.h"

#if defined(_DEBUG)
	#include <assert.h>
	#define MC_ASSERT(x)	assert(x)
	#define MC_ASSERTX(x)	assert(x)
#else
	#define MC_ASSERT(x) \
	if(!(x)) \
	{ \
		char tmp_buf[MC_TRACE_MAX_MSG_LEN] = ""; \
		MC_Text_Stream ts(tmp_buf, MC_TRACE_MAX_MSG_LEN); \
		mc_trace_write(TRACE_LEVEL_ERROR, ts<<" assert "<< #x \
			<<"at file "<< __FILE__<<", line "<< __LINE__);\
	}

	#define MC_ASSERTX(x) \
	if(!(x)) \
	{ \
		char tmp_buf[MC_TRACE_MAX_MSG_LEN] = ""; \
		MC_Text_Stream ts(tmp_buf, MC_TRACE_MAX_MSG_LEN); \
		mc_trace_write(TRACE_LEVEL_ERROR, ts<<" assert "<< #x \
			<<"at file "<< __FILE__<<", line "<< __LINE__);\
		throw 123; \
	}
#endif

#ifdef SHARING_CORE
	#undef MC_ASSERT
	#define MC_ASSERT(x)	
	#undef MC_ASSERTX
	#define MC_ASSERTX(x)	
#endif


#endif //__MCASSERT_H__