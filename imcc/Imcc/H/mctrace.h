/*--------------------------------------------------------------------------*/
/*  MCTRACE.H                                                               */
/*                                                                          */
/*  History                                                                 */
/*      11/24/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#ifndef __MCTRACE_H__
#define __MCTRACE_H__

#define MC_TRACE_MAX_MSG_LEN		512

#define TRACE_LEVEL_ERROR			0
#define TRACE_LEVEL_WARNING			1
#define TRACE_LEVEL_INFO			2
#define TRACE_LEVEL_DEBUG			3
#define TRACE_LEVEL_FUNC			4
#define TRACE_LEVEL_DEBUG2			5

//////////////////////////////////////////////////////////////////////////////
// Basic functions
//
#ifdef __cplusplus
extern "C" {
#endif

void mc_trace_reconfig();
void mc_trace_write(int trace_level, char* trace_msg);
int mc_trace_level();

extern int g_mc_trace_level;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "mcts.h"

//////////////////////////////////////////////////////////////////////////////
// MC_Function_Tracer
//
class MC_Function_Tracer
{
public :
	MC_Function_Tracer(char* str)
	{
		m_str = str;
		if(mc_trace_level() >= TRACE_LEVEL_FUNC)
		{
			char tmp_buf[MC_TRACE_MAX_MSG_LEN] = "";
			MC_Text_Stream ts(tmp_buf, MC_TRACE_MAX_MSG_LEN);
			mc_trace_write(TRACE_LEVEL_FUNC, ts << "Enter " << m_str);
		}
	}

	virtual ~MC_Function_Tracer()
	{
		if(mc_trace_level() >= TRACE_LEVEL_FUNC)
		{
			char tmp_buf[MC_TRACE_MAX_MSG_LEN] = "";
			MC_Text_Stream ts(tmp_buf, MC_TRACE_MAX_MSG_LEN);
			mc_trace_write(TRACE_LEVEL_FUNC, ts << "Leave " << m_str);
		}
	}

	char* m_str;
};

//////////////////////////////////////////////////////////////////////////////
// MACROS
//
#define MCTRACE(level, str) \
{ \
	if(mc_trace_level() >= level) \
	{	\
		char tmp_buf[MC_TRACE_MAX_MSG_LEN] = ""; \
		MC_Text_Stream tmp_ts(tmp_buf, MC_TRACE_MAX_MSG_LEN); \
		mc_trace_write(level, tmp_ts << str); \
	}	\
}

#define MCFUNCTRACE(str) \
\
	char tmp_func_trace_buf[MC_TRACE_MAX_MSG_LEN] = ""; \
	MC_Text_Stream tmp_ts_123(tmp_func_trace_buf, MC_TRACE_MAX_MSG_LEN); \
	MC_Function_Tracer my_func_tracer(tmp_ts_123 << str);

#define TRACE_ERR(str)		MCTRACE(TRACE_LEVEL_ERROR, m_obj_key<<": "<<str)
#define TRACE_WARNING(str)	MCTRACE(TRACE_LEVEL_WARNING, m_obj_key<<": "<<str)
#define TRACE_INFO(str)		MCTRACE(TRACE_LEVEL_INFO, m_obj_key<<": "<<str)
#define TRACE_DEBUG(str)	MCTRACE(TRACE_LEVEL_DEBUG, m_obj_key<<": "<<str)
#define TRACE_FUNC(str)		MCFUNCTRACE(m_obj_key<<": "<<str)
#define TRACE_DEBUG2(str)	MCTRACE(TRACE_LEVEL_DEBUG2, m_obj_key<<": "<<str)
#define TRACE_INFO2(str)	MCTRACE(TRACE_LEVEL_INFO, str)
#define TRACE_ERR2(str)		MCTRACE(TRACE_LEVEL_ERROR, str)

//////////////////////////////////////////////////////////////////////////////
// obsolete
#define DECLARE_MCTRACE_MODULE_X(module) \
	int g_trace_moudle_##module = -1;

#endif

#endif //__MCTRACE_H__