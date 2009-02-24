/*--------------------------------------------------------------------------*/
/*  MCDEF.H                                                                 */
/*                                                                          */
/*  History                                                                 */
/*      09/01/2004     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2004 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCDEF_H__)
#define __MCDEF_H__

#include "imccdef.h"
#include "imcccore.h"

//////////////////////////////////////////////////////////////////////////////
// data type and const
//
typedef uint32						MC_Conf_Privilege;
typedef IMCC_Roster_Presence_Status	MC_Conf_User_Status;
typedef IMCC_Roster_Presence_Flag	MC_Conf_Presence_Flag;
typedef IMCC_Roster_Presence_Capability MC_Conf_Capability;
typedef IMCC_Channel_ID				MC_Session_ID;
typedef uint8						MC_Session_Type;

#define MC_MAX_CONF_SESS_TYPE		127
#define MC_MAX_CONF_SESS_NUM		60
#define MC_CONF_SESS_ID_BASE		4


#define MC_CONF_PRESENCE_PUBLIC		0x1
#define MC_CONF_PRESENCE_RCV_RPT	0x2

#define IMCC_PC_NC_CTL				0
#define MC_SESS_TYPE_CHAT			1
#define MC_SESS_TYPE_AUDIO			2
#define MC_SESS_TYPE_VIDEO			3
#define MC_SESS_TYPE_DOCVIEW		4
#define MC_SESS_TYPE_APPSHARING		5
#define MC_SESS_TYPE_FILETRANSFER	6
#define MC_SESS_TYPE_QA				7
#define MC_SESS_TYPE_POLL			8
#define MC_SESS_TYPE_WEB			9
#define MC_SESS_TYPE_BULLETIN		10
#define MC_SESS_TYPE_PHONE			11
#define MC_SESS_TYPE_ATTENDEE		12
#define MC_SESS_TYPE_QUIZ			13

#define MC_SESS_FLAG_PUBLIC			0x1
#define MC_SESS_FLAG_HAS_ROSTER		0x2

#define MC_CONF_CTL_PRIORITY			IMCC_HIGH_PRIORITY		
#define IMCC_MAX_CONF_KEY_LENGTH		64
#define MC_MAX_CONF_USER_NAME_LENGTH	64

typedef enum {
	SS_CLOSED		= 0,
	SS_OPEN			= 1,
	SS_SUSPENDED	= 2,
} IMCC_Svr_Status;

typedef enum {
	CS_IDLE			= 0,
	CS_OPEN_PENDING	= 1,
	CS_OPEN			= 2,
	CS_LOCKED		= 3,
	CS_CLOSING		= 4,
	CS_CLOSED		= 5,
	CS_UNKNOWN		= 6,
} IMCC_Conf_Status;

typedef struct _tag_conf_user_record
{
	uint32					user_data;
	IMCC_Node_ID			node_id;
	MC_Conf_Presence_Flag	user_presence_flag;
	MC_Conf_User_Status		user_status;
	uint8					device_type;
	uint8					os_type;
	uint8					net_link_type;
	char					user_name[MC_MAX_CONF_USER_NAME_LENGTH];
	uint32					user_alt_id;
	MC_Conf_Capability		user_capability;
	IMCC_Net_Addr			net_addr;
} MC_Conf_User_Record;

typedef struct _tag_conf_sess_record
{
	uint32			sess_tag;
	MC_Session_Type	sess_type;
	MC_Session_ID	sess_id;
	uint8			sess_flag;
	uint8			sess_info_len;
	uint8*			sess_info;
} MC_Conf_Session_Record;

typedef enum {
	PING_RESULT_OK = 0,
	PING_RESULT_REDIRECT,
	PING_RESULT_SVR_NOT_START,
	PING_RESULT_BANDWIDTH_YELLOW,
	PING_RESULT_BANDWIDTH_RED,
	PING_RESULT_LICENSE_FAIL,
	PING_RESULT_AUTHTICATE_FAIL,
	PING_RESULT_NETWORK_FAIL,
	PING_RESULT_TIMEOUT,
	PING_RESULT_UNKNOWN,
} PING_RESULT;

//////////////////////////////////////////////////////////////////////////////
// Conference registry
//
/*
CONF_ROOT
	+----startup
	|        +----host(token)
	|        +----privilege(parameter)
	|        +----sess_list(table)
	|        |       +----index/sess_type/is_public/sess_info
	|
	|        +----conf_roster(roster)
	|        |       +----conf_user_record
	|
	+----sess1:13 (1/chat, 13/session id)
	|
	+----sess3:14 (3/video, 14/session id)
	|        +----sess_roster(roster)
	|
*/

#define MC_REG_KEY_CONF_STARTUP		"/startup"
#define MC_REG_TOKEN_CONF_HOST		"host"
#define MC_REG_TOKEN_CONF_SESS_LIST	"sess_list"
#define MC_REG_TOKEN_CONF_ROSTER	"roster"

#define MC_SYSLOG_INFO		0
#define MC_SYSLOG_WARNING	2
#define MC_SYSLOG_ERROR		3

#endif //__MCDEF_H__