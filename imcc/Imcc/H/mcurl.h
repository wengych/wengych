/*--------------------------------------------------------------------------*/
/*  MCURL.H                                                                 */
/*  Utility class to wrap the URL api                                       */
/*                                                                          */
/*  History                                                                 */
/*      12/03/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#ifndef __MCURL_H__
#define __MCURL_H__

#include "imccdef.h"
#include "mcutil.h"

#if !defined(WIN32)
#error This MC URL facility can only be used in WIN32 programing
#endif

#ifndef __cplusplus
#error This MC URL facility can only be used in C++
#endif

#include <wininet.h>

#if defined(NET_EXPORTS)
#define NET_API DLLEXPORT
#else
#define NET_API DLLIMPORT
#endif

//////////////////////////////////////////////////////////////////////////////
// Const and data structure
//
#define MCURL_SUCCESS		0
#define MCURL_FAILURE		-1

#define MCURL_OPT_CONNECT_TIMEOUT	INTERNET_OPTION_CONNECT_TIMEOUT
#define MCURL_OPT_SEND_TIMEOUT		INTERNET_OPTION_DATA_SEND_TIMEOUT
#define MCURL_OPT_RECEIVE_TIMEOUT	INTERNET_OPTION_DATA_RECEIVE_TIMEOUT
#define MCURL_OPT_UNIT_BUFFER_SIZE	10001

#define MCURL_FLAG_KEEP_CONNECTION	INTERNET_FLAG_KEEP_CONNECTION
#define MCURL_FLAG_DONT_CACHE		INTERNET_FLAG_DONT_CACHE
#define MCURL_FLAG_RELOAD			INTERNET_FLAG_RELOAD 
#define MCURL_FLAG_SECURE			INTERNET_FLAG_SECURE 

#define MCURL_DEFAULT_HTTP_PORT		INTERNET_DEFAULT_HTTP_PORT
#define MCURL_DEFAULT_HTTPS_PORT	INTERNET_DEFAULT_HTTPS_PORT
#define MCURL_DEFAULT_SOCKS_PORT	INTERNET_DEFAULT_SOCKS_PORT 

//////////////////////////////////////////////////////////////////////////////
// MC_Sync_Url
//	Regarding to read_data(), if the return value is TRUE and the number of 
//	bytes read is zero or less than requested, it means the transfer has been 
//	completed and there are no more bytes to read on the handle. This is 
//	analogous to reaching EOF in a local file.
//
class MC_Sync_Url
{
public :
	virtual void destroy() = 0;

	virtual int open_url(
		char*				url, 
		char*				headers = NULL, 
		uint32				header_len = 0,
		uint32				flags = 0) = 0;

	virtual int post_url(	// for post
		char*				host, 
		char*				url_object, 
		char*				accept_types = "text/*",
		uint32				flag = 0,
		char*				headers = NULL, 
		uint32				header_len = 0,
		void*				post_data = NULL, 
		uint32				post_data_len = 0) = 0;

	virtual int close_url() = 0;

	virtual int query_data_available(
		uint32*				available) = 0;

	virtual int read_data(
		void*				buf, 
		uint32				max_buf_len, 
		uint32*				read_buf_len) = 0;

	virtual int get_error_code() = 0;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Async_Url_Event_Handler
//
class MC_Async_Url_Event_Handler
{
public :
	// if the return_buffers is valid, up layer is responsible to release the 
	// the allocated memory by invoking mc_delete_buffers(return_buffers).
	virtual int on_async_url_event(
		int						result, 
		MC_Buffers*				return_buffers) = 0;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Async_Url
//
class MC_Async_Url
{
public :
	virtual void destroy() = 0;

	virtual int connect(
		char*				host, 
		int					port = MCURL_DEFAULT_HTTP_PORT, 
		char*				user_name = NULL, 
		char*				password = NULL) = 0;

	virtual int open_url(
		char*				url_object, 
		char*				verb = "GET", 
		char*				accept_types = "text/*",
		uint32				flag = 0,
		char*				headers = NULL, 
		uint32				header_len = 0,
		void*				post_data = NULL, 
		uint32				post_data_len = 0) = 0;

	virtual int close_url() = 0;

	virtual int set_option(
		uint32				option, 
		void*				opt_buf, 
		uint32				opt_buf_len) = 0;

	virtual int query_option(
		uint32				option, 
		void*				opt_buf, 
		uint32*				opt_buf_len) = 0;

	virtual int set_cookie(
		char*				url_name, 
		char*				cookie_name, 
		char*				cookie_data) = 0;

	virtual int get_cookie(
		char*				url_name, 
		char*				cookie_name, 
		char*				cookie_data,
		uint32*				cookie_data_size) = 0;

	virtual int get_error_code() = 0;
};

//////////////////////////////////////////////////////////////////////////////
// Utility functions
//
NET_API MC_Sync_Url* mcnet_create_sync_url();

NET_API MC_Async_Url* mcnet_create_async_url(
		MC_Server_Engine*			engine, 
		MC_Async_Url_Event_Handler*	handler);

NET_API void mcnet_url_cleanup();

NET_API boolean mcnet_crack_url(
		char*				url, 
		char*				url_scheme,
		uint16				url_scheme_length,
		char*				url_host,
		uint16				url_host_length,
		uint16*				url_port,
		char*				url_path,
		uint16				url_path_length,
		char*				url_extra,
		uint16				url_extra_length);

#endif // __MCURL_H__
