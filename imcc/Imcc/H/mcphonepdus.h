/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  MCPHONEPDUS.H                                                           */
/*                                                                          */
/*  History                                                                 */
/*      08/10/2005     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2005 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#if !defined(__MCPHONEPDUS_H__)
#define __MCPHONEPDUS_H__

#include "imccdef.h"
#include "mcphonedef.h"
#include "mcts.h"

typedef enum 
{
	MCPMT_UNKNOWN = 0,
	MCPMT_LOGIN_REQ,
	MCPMT_LOGIN_CFM,
	MCPMT_KEEPALIVE,
	MCPMT_CONF_CREATE_REQ,
	MCPMT_CONF_CREATE_CFM,
	MCPMT_CONF_READY_IND,
	MCPMT_CONF_CLOSE_REQ,
	MCPMT_CONF_CLOSE_IND,
	MCPMT_CONF_REC_REQ,
	MCPMT_CONF_REC_IND,
	MCPMT_CALL_OUT_REQ,
	MCPMT_CALL_OUT_CFM,
	MCPMT_CALL_IND,
	MCPMT_CALL_MUTE_REQ,
	MCPMT_CALL_MUTE_IND,
	MCPMT_CALL_KICKOUT_REQ,
	MCPMT_CALL_LEAVE_IND,
	MCPMT_CALL_ACTIVE_IND,
} MCP_MSG_TYPE;

typedef struct
{
	char user_name[64];
	char password[128];
} MCP_Msg_Login_Req;

typedef struct 
{
	uint16 result;
} MCP_Msg_Login_Cfm;

typedef struct 
{
	uint32 rtt;
} MCP_Msg_Keep_Alive;

typedef struct 
{
	char conf_num[64];
	char host_pwd[128];
	uint32 conf_context;
} MCP_Msg_Conf_Create_Req;

typedef struct 
{
	char conf_num[64];
	uint32 conf_context;
	int result;
} MCP_Msg_Conf_Create_Cfm;

typedef struct 
{
	char conf_num[64];
	uint32 conf_context;
	int result;
} MCP_Msg_Conf_Ready_Ind;

typedef struct 
{
	char	conf_num[64];
	uint16	tag;	//0: stop the assocation, 1: stop phone conference
} MCP_Msg_Conf_Close_Req;

typedef struct 
{
	char	conf_num[64];
	uint32	conf_context;
	int		reason;
} MCP_Msg_Conf_Close_Ind;

typedef struct 
{
	char	conf_num[64];
	uint8	rec_status;
} MCP_Msg_Conf_Rec_Req;

typedef struct 
{
	char	conf_num[64];
	uint32	conf_context;
	uint8	rec_status;
} MCP_Msg_Conf_Rec_Ind;

typedef struct 
{
	char	conf_num[MAX_PHONE_CONF_NUM_LEN];
	char	phone_num[MAX_PHONE_NUM_LEN];
	uint32	pin_num;
	uint32	call_context;
	char	user_name[MAX_PHONE_USER_NAME_LEN];
} MCP_Msg_Call_Out_Req;

typedef struct 
{
	char	conf_num[64];
	uint32	conf_context;
	char	phone_num[32];
	uint32	call_context;
	int		result;
} MCP_Msg_Call_Out_Cfm;

typedef struct 
{
	char	conf_num[64];
	uint32	conf_context;
	char	phone_num[32];
	uint32	pin_num;
	uint8	mute_status;
	uint8	user_type;
	uint32	user_id;
	char	user_name[64]; // optional
} MCP_Msg_Call_Ind;

typedef struct 
{
	char	conf_num[64];
	uint32	conf_context;
	uint32	user_id;
	uint8	active_status;
} MCP_Msg_Call_Active_Ind;

typedef struct 
{
	char	conf_num[64];
	uint32	user_id;
	uint8	mute_status;
} MCP_Msg_Call_Mute_Req;

typedef struct 
{
	char	conf_num[64];
	uint32	conf_context;
	uint32	user_id;
	uint8	mute_status;
} MCP_Msg_Call_Mute_Ind;

typedef struct 
{
	char	conf_num[64];
	uint32	user_id;
} MCP_Msg_Call_Kickoff_Req;

typedef struct 
{
	char	conf_num[64];
	uint32	conf_context;
	uint32	user_id;
	uint8	reason;
} MCP_Msg_Call_Leave_Ind;

typedef struct
{
	MCP_MSG_TYPE msg_type;
	union {
		MCP_Msg_Login_Req		login_req;
		MCP_Msg_Login_Cfm		login_cfm;
		MCP_Msg_Keep_Alive		keep_alive;
		MCP_Msg_Conf_Create_Req	conf_create_req;
		MCP_Msg_Conf_Create_Cfm	conf_create_cfm;
		MCP_Msg_Conf_Ready_Ind	conf_ready_ind;
		MCP_Msg_Conf_Close_Req	conf_close_req;
		MCP_Msg_Conf_Close_Ind	conf_close_ind;
		MCP_Msg_Conf_Rec_Req	conf_rec_req;
		MCP_Msg_Conf_Rec_Ind	conf_rec_ind;
		MCP_Msg_Call_Out_Req	call_out_req;
		MCP_Msg_Call_Out_Cfm	call_out_cfm;
		MCP_Msg_Call_Ind		call_ind;
		MCP_Msg_Call_Mute_Req	call_mute_req;
		MCP_Msg_Call_Mute_Ind	call_mute_ind;
		MCP_Msg_Call_Kickoff_Req	call_kickoff_req;
		MCP_Msg_Call_Leave_Ind	call_leave_ind;
		MCP_Msg_Call_Active_Ind	call_active_ind;
	} msg;
} MCP_Msg;

//////////////////////////////////////////////////////////////////////////////
// xml interface
//
typedef void* MCP_XML_Msg;

MCP_XML_Msg mcp_xml_msg_create(char* xml_data);

boolean mcp_xml_msg_decode(MCP_XML_Msg h, MCP_Msg* msg);

boolean mcp_xml_msg_encode(MCP_XML_Msg h, MCP_Msg* msg);

void mcp_xml_msg_get_buf(MCP_XML_Msg h, char* buf, int buf_len);

void mcp_xml_msg_delete(MCP_XML_Msg h);

boolean mcp_msg_encode(MCP_Msg* msg, char* buf, int buf_len);

#endif //__MCPHONEPDUS_H__
