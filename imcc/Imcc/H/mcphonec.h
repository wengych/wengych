/*--------------------------------------------------------------------------*/
/*  MCPHONEC.H                                                              */
/*                                                                          */
/*  History                                                                 */
/*      07/16/2005     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2005 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCPHONEC_H__)
#define __MCPHONEC_H__

#include "imccdef.h"
#include "imcccore.h"
#include "mcdef.h"
#include "mcphonedef.h"

//////////////////////////////////////////////////////////////////////////////
// class define
//
class MC_Conference;

//////////////////////////////////////////////////////////////////////////////
// MC_Phone_Event_Handler
//
class MC_Phone_Event_Handler
{
public :
	virtual int on_phone_session_open_cfm(int result) = 0;
	
	virtual int on_phone_session_join_cfm(int result) = 0;

	virtual int on_phone_session_close_ind(int reason) = 0;

	virtual int on_phone_conf_status_ind(MCP_CONF_STATUS status) = 0;

	virtual int on_phone_record_ind(boolean record_status) = 0;

	virtual int on_phone_call_out_cfm(char* phone_num, int result) = 0;

	virtual int on_phone_call_ind(uint16 call_record_id) = 0;

	virtual int on_phone_call_leave_ind(uint16 call_record_id) = 0;

	virtual int on_phone_call_active_ind(uint16 call_record_id) = 0;

	virtual int on_phone_call_mute_ind(uint16 call_record_id) = 0;

	virtual int on_phone_call_name_ind(uint16 call_record_id) = 0;

	// agent special call back messages
	virtual int on_phone_agent_call_out_request(char* phone_num, uint32 pin_num) { return 0; }

	virtual int on_phone_agent_call_mute_request(uint32 user_id, boolean mute_status) { return 0; }

	virtual int on_phone_agent_call_kickoff_request(uint32 user_id) { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// MC_Phone_Mgr
//
class MC_Phone_Mgr
{
public :
	virtual int destroy() = 0;

	virtual int phone_session_open(uint8 flag, char* conf_num, char* host_pwd, boolean is_agent) = 0;
	
	virtual int phone_session_close() = 0;

	virtual int phone_session_join(MC_Session_ID sess_id, boolean is_agent) = 0;
	
	virtual int phone_session_leave() = 0;

	virtual int phone_session_restart() = 0;

	virtual int conf_close() = 0;

	virtual int record(boolean record_status) = 0;

	virtual int call_out(char* phone_num, uint32 pin_num, char* user_name) = 0;

	virtual int call_mute(uint16 call_record_id, boolean mute_status) = 0;

	virtual int call_kickoff(uint16 call_record_id) = 0;

	virtual int call_set_name(uint16 call_record_id, char* user_name) = 0;

	virtual MCP_User* get_phone_user(uint16 call_record_id) = 0;

	virtual MCP_CONF_STATUS get_phone_conf_status() = 0;

	virtual boolean get_phone_record_status() = 0;

	virtual void set_agent_node_id(IMCC_Node_ID agent_id) = 0;

	//agent special functions
	virtual int add_user(uint32 user_id, char* phone_num, uint32 pin_num, boolean mute_status) = 0;

	virtual int remove_user(uint32 user_id) = 0;

	virtual int change_user_mute_status(uint32 user_id, boolean mute_status) = 0;
};

//////////////////////////////////////////////////////////////////////////////
// mc_create_phone_mgr
//
MC_Phone_Mgr* mc_phone_mgr_create(MC_Conference* conf, 
		MC_Phone_Event_Handler* handler);

#endif /* __MCPHONEC_H__ */
