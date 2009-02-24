/*--------------------------------------------------------------------------*/
/*  MCSVRMGR.H                                                              */
/*                                                                          */
/*  History                                                                 */
/*      04/17/2004     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2004 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCSVRMGR_H__)
#define __MCSVRMGR_H__

#include "mcdef.h"

typedef struct
{
	uint8	sess_type;
	boolean	allowed;
	uint16	max_sess_user_num;
	uint32	max_sess_duration;
	char*	sess_info;
} IMCC_SM_Sess_License;

typedef struct
{
	uint32	conf_id;
	uint32	result;
	char	top_svr_ip[IMCC_MAX_IP_ADDR];
	char	conf_key[IMCC_MAX_CONF_KEY_LENGTH];
	char	host_key[IMCC_MAX_REG_TOKEN_GRAB_KEY_LEN];
	uint16	max_conf_user_num;
	uint16	mac_conf_duration;
	uint8	num_sess_licenses;
	IMCC_SM_Sess_License*	sess_licenses;
} IMCC_SM_QCRL_RSP;

#define IMCC_SM_MSG_QCSR		"qcsr"	//query conf status request
#define IMCC_SM_MSG_QCSC		"qcsc"	//query conf status confirm
#define IMCC_SM_MSG_CSCN		"cscn"	
#define IMCC_SM_MSG_LOG			"log"	//log request

typedef enum {
	IMCC_SM_MSG_QCS_RET = 0, //query conf status return
} IMCC_SM_Msg_Type;

typedef struct 
{
	uint32				site_id; 
	uint32				conf_id;
	IMCC_Conf_Status	conf_status;
	char*				top_svr_ip;
	char*				host_key;
} IMCC_SM_Msg_QCS_Rsp;

#ifdef __cplusplus
extern "C"
{
#endif

typedef int (* IMCC_SM_Callback_Proc)(
	int						msg_type,
	void*					msg);

void imcc_sm_init(
		char*					svr_ip,
		uint32					svr_id,
		uint16					svr_type,
		IMCC_SM_Callback_Proc	cb_proc);

void imcc_sm_cleanup(
		uint32				timeout);

void imcc_sm_query_conf_status(
		char*				site_url, 
		uint32				site_id,
		uint32				conf_id);

void imcc_sm_notify_conf_status(
		char*				site_url, 
		uint32				site_id,
		uint32				conf_id, 
		IMCC_Conf_Status	conf_status,
		uint32				flag);

// server logging
void imcc_log_server_status_change(
		IMCC_Svr_Status		svr_status,
		uint16				reason);

void imcc_log_conf_start(
		char*				site_url, 
		uint32				site_id,
		uint32				conf_id,
		char*				conf_title);

void imcc_log_conf_open(
		char*				site_url, 
		uint32				site_id,
		uint32				conf_id,
		char*				conf_title,
		char*				parent_svr_ip);

void imcc_log_conf_close(
		char*				site_url, 
		uint32				site_id,
		uint32				conf_id,
		uint16				reason);

void imcc_log_conf_user_join(
		char*				site_url, 
		uint32				site_id,
		uint32				conf_id,
		uint32				user_id,
		char*				user_name,
		uint32				node_id,
		char*				cli_private_ip,
		char*				cli_proxy_ip);

void imcc_log_conf_user_leave(
		char*				site_url, 
		uint32				site_id,
		uint32				conf_id,
		uint32				node_id,
		uint32				user_id,
		uint16				reason);

boolean imcc_routing_get_path(
		char*				dest_ip, 
		char*				bind_ip,
		char*				to_ip);

void imcc_routing_init();

#ifdef __cplusplus
}
#endif

#endif //__MCSVRMGR_H__