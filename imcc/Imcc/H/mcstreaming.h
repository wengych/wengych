/*--------------------------------------------------------------------------*/
/*  MCSTREAMING.H                                                           */
/*                                                                          */
/*  History                                                                 */
/*      11/08/2005     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2005 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCSTREAMING_H__)
#define __MCSTREAMING_H__

#include "imccdef.h"
#include "imcccore.h"
#include "mcdef.h"

#if defined(STREAMING_EXPORTS)
#define STREAMING_API DLLEXPORT
#else
#define STREAMING_API DLLIMPORT
#endif

//////////////////////////////////////////////////////////////////////////////
// MCStreaming_Event_Handler
//
class MCStreaming_Event_Handler
{
public :
	virtual int on_session_join_cfm(int result) = 0;
	
	virtual int on_session_leave_ind(int reason) = 0;

	virtual int on_session_leave_cfm() = 0;

	virtual int on_send_data_ind(
		uint8*					user_data,
		uint16					user_data_length) = 0;

	virtual int on_header_update_ind(
		uint8*					user_data,
		uint16					user_data_length) = 0;
};

//////////////////////////////////////////////////////////////////////////////
// MCStreaming_Session
//
class MCStreaming_Session
{
public :
	virtual int release() = 0;

	virtual int session_join(
		uint32					site_id,
		char*					site_url,
		uint32					conf_id,
		char*					conf_title,
		char*					user_name,
		uint32					user_log_id,
		char*					svr_addr
		) = 0;
	
	virtual int session_leave(boolean terminate) = 0;

	virtual int send_data(
		uint8*					user_data,
		uint16					user_data_length) = 0;

	virtual int update_header(
		uint8*					user_data,
		uint16					user_data_length) = 0;

	virtual int flush_send_data() = 0;
};

//////////////////////////////////////////////////////////////////////////////
// utility functions
//
STREAMING_API int mcstreaming_init(HINSTANCE hInstance);
STREAMING_API int mcstreaming_shutdown(uint32 timeout);
STREAMING_API MCStreaming_Session* mcstreaming_session_new(MCStreaming_Event_Handler* handler);

#endif /* __MCSTREAMING_H__ */
