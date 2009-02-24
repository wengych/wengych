/*--------------------------------------------------------------------------*/
/*  IMCCCORE.H                                                              */
/*                                                                          */
/*  Version 0.1(11/24/2003 refered on IMTC MCS API specificaiton 0.10)		*/
/*                                                                          */
/*  History                                                                 */
/*      11/24/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__IMCCCORE_H__)
#define __IMCCCORE_H__

/**
/* Platform definition and platform specific definitions
*/
#include "imccdef.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
/* General Const and Data Struccture
*****************************************************************************/

#define IMCC_MAX_ERR_MSG_LENGTH		256

/**
/* General IMCC Error Code
*/
typedef	enum
{
	IMCC_ERROR_SUCCESS				=	0,
	IMCC_ERROR_ALREADY_REGISTERED	=	1,
	IMCC_ERROR_NOT_REGISTERED		=	2,
	IMCC_ERROR_DOMAIN_ALREADY_EXIST =	3,
	IMCC_ERROR_DOMAIN_NOT_EXIST		=	4,
	IMCC_ERROR_DOMAIN_NUM_OVERFLOW	=	5,
	IMCC_ERROR_DOMAIN_MERGING		=	6,
	IMCC_ERROR_DOMAIN_CLOSEING		=	7,
	IMCC_ERROR_CONNECTION_NOT_EXIST	=	8,
	IMCC_ERROR_TOO_MANY_CONNECTIONS	=	9,
	IMCC_ERROR_INVALID_PARAMETERS	=	10,
	IMCC_ERROR_DATA_SIZE_EXCEEDED	=	11,
	IMCC_ERROR_NOT_AUTHORISED		=	12,
	IMCC_ERROR_TRANSMIT_BUFFER_FULL	=	13,
	IMCC_ERROR_VERSION_NOT_SUPPORTED=	14,
	IMCC_ERROR_NETLAYER_FAIL		=	15,
	IMCC_ERROR_INSUFICIENT_MEMORY	=	16,
	IMCC_ERROR_USER_CLOSEING		=	17,
	IMCC_ERROR_UNKNOWN_ERROR		=	18,
	IMCC_ERROR_INVALID_STATE		=	19,
	IMCC_ERROR_NET_FAILED			=	20,
}IMCC_Error;

/**
/* IMCC Reason Code
*/
typedef	enum
{
	IMCC_REASON_USER_INITIATED		=	0,
	IMCC_REASON_USER_EJECTED,
	IMCC_REASON_TOKEN_PURGED,
	IMCC_REASON_SYS_SHUTTINGDOWN,
	IMCC_REASON_NETWORK_ERROR,
	IMCC_REASON_TIME_OUT,
	IMCC_REASON_UNKNOWN,
}IMCC_Reason;

/**
/* IMCC Result Code
*/
typedef	enum
{
	IMCC_RESULT_SUCCESSFUL				= 0,
	IMCC_RESULT_USER_REJECTED			= 1,
	IMCC_RESULT_NETWORK_ERROR			= 2,
	IMCC_RESULT_VERSION_NOT_MATCH		= 3,
	IMCC_RESULT_PROTOCOL_NOT_RIGHT		= 4,
	IMCC_RESULT_TOO_MANY_CONNECTIONS	= 5,
	IMCC_RESULT_EXPIRED					= 6,
	IMCC_RESULT_DOMAIN_TERMINATED		= 7,
	IMCC_RESULT_SERVER_CONN_FAILED		= 8,
	IMCC_RESULT_SYS_SHUTINGDOWN			= 9,
	IMCC_RESULT_DOMAIN_MERGING			= 10,
	IMCC_RESULT_NO_SUCH_USER			= 11,
	IMCC_RESULT_CHANNEL_NOT_AVAILABLE	= 12,
	IMCC_RESULT_TOKEN_NOT_POSSESSED		= 13,
	IMCC_RESULT_TOKEN_NOT_AVAILABLE		= 14,
	IMCC_RESULT_TOKEN_AUTH_FAIL			= 15,
	IMCC_RESULT_TOO_MANY_TOKENS			= 16,
	IMCC_RESULT_REG_KEY_NOT_EXIST		= 17,
	IMCC_RESULT_REG_KEY_ALREADY_EXIST	= 18,
	IMCC_RESULT_REG_PARENT_KEY_NOT_EXIST= 19,
	IMCC_RESULT_REG_OBJECT_ALREADY_EXIST= 20,
	IMCC_RESULT_REG_OBJECT_NOT_EXIST	= 21,
	IMCC_RESULT_REG_TABLE_ID_TOO_LARGE	= 22,
	IMCC_RESULT_REG_TABLE_ID_DUPLICATED	= 23,
	IMCC_RESULT_POOL_NOT_AVAILABLE		= 24,
	IMCC_RESULT_POOL_ALREADY_GRABBBED	= 25,
	IMCC_RESULT_UNKNOWN					= 26,
}IMCC_Result;

//////////////////////////////////////////////////////////////////////////////
// Transport IP Address
//
#define IMCC_IPv4			0x01
#define IMCC_IPv6			0x02

typedef struct
{
	uint8	ip_family;
	uint16	port;
	union
	{
		uint8	ipv4[4];
		uint8	ipv6[16];
	} addr;
} IMCC_IP_Adress;

/**
/* IMCC version. Current version is 0.1
*/
typedef struct
{
   uint8  major_version;
   uint8  minor_version;
} IMCC_Version;

#define IMCC_MAJOR_VER	0
#define IMCC_MINOR_VER	1

/**
/* IMCC Time
/* number of seconds elapsed since midnight (00:00:00), January 1, 1970, 
/* coordinated universal time (UTC).
*/
typedef uint32		IMCC_Time;

/**
/* IMCC User Data
*/
typedef struct _tag_user_data {
	uint16			data_length;
	uint8*			data;
} IMCC_User_Data;

#define IMCC_MAX_USER_DATA_NAME_LEN	16
typedef struct _tag_user_data_1 {
	char			data_name[IMCC_MAX_USER_DATA_NAME_LEN];
	uint16			data_length;
	uint8*			data;
} IMCC_User_Data_1;

typedef struct _tag_user_data_2 {
	uint16			data_index;
	uint16			data_length;
	uint8*			data;
} IMCC_User_Data_2;

/*****************************************************************************
/* IMCC Net address
*****************************************************************************/
#define IMCC_MAX_IP_ADDR		64
#define IMCC_DEFAULT_FTP_PORT	21		// default for FTP servers
#define IMCC_DEFAULT_HTTP_PORT	80		// default for HTTP servers
#define IMCC_DEFAULT_HTTPS_PORT	443		// default for HTTPS servers
#define IMCC_DEFAULT_SOCKS_PORT	1080	// default for SOCKS firewall servers
#define IMCC_DEFAULT_TCP_PORT	1124	// default for IMCC TCP servers
#define IMCC_DEFAULT_UDP_PORT	1124	// default for IMCC UDP servers

typedef enum {
	IMCC_Net_Prot_Unknown = 0,
	IMCC_Net_Prot_UDP = 1,
	IMCC_Net_Prot_TCP = 2,
	IMCC_Net_Prot_HTTP = 3,
	IMCC_Net_Prot_TCPS = 4,
	IMCC_Net_Prot_HTTPS = 5,
} IMCC_Net_Prot;

typedef enum {
	IMCC_Net_Link_Unknown	= 0,
	IMCC_Net_Link_LAN		= 1,
	IMCC_Net_Link_DSL		= 2,
	IMCC_Net_Link_Dialup	= 3,
	IMCC_Net_Link_Wireless	= 4,
} IMCC_Net_Link_Type;

typedef struct _tag_net_addr
{
	uint8		private_ip[4];
	uint16		private_port;
	uint8		nat_ip[4];
	uint16		nat_port;
} IMCC_Net_Addr;

/*****************************************************************************
/* IMCC Node Attribute
*****************************************************************************/
typedef uint16	IMCC_MCU_ID;
typedef uint16	IMCC_TERMINAL_ID;
typedef uint32	IMCC_Node_ID;
typedef char*	IMCC_Node_Name;

/*typedef struct {
	IMCC_MCU_ID			mcu_id;
	IMCC_TERMINAL_ID	terminal_id;
} IMCC_Node_ID;*/

typedef enum {
	IMCC_MCU			= 0,
	IMCC_PROXY			= 1,
	IMCC_TERMINAL		= 2,
	IMCC_GATEWAY		= 3,
	IMCC_UNKNOWN		= 0xff,
} IMCC_Node_Type;

typedef enum {
	IMCC_DEV_UNKNOWN	= 0,
	IMCC_DEV_PC			= 1,
	IMCC_DEV_PDA		= 2,
	IMCC_DEV_PHONE		= 3,
} IMCC_Device_Type;

typedef enum {
	IMCC_OS_UNKNOWN		= 0,
	IMCC_OS_WIN95		= 1,
	IMCC_OS_WIN98		= 2,
	IMCC_OS_WINNT		= 3,
	IMCC_OS_WIN2k		= 4,
	IMCC_OS_WINXP		= 5,

	IMCC_OS_MACOS		= 10,
} IMCC_OS_Type;

#define IMCC_MAX_NODE_NAME_LEN	64

typedef struct _tag_node_profile
{
	IMCC_Node_ID	node_id;
	char			node_name[IMCC_MAX_NODE_NAME_LEN];
	uint32			node_alt_id;
	uint8			node_type;
	uint8			device_type;
	uint8			os_type;
	uint8			net_link_type;
	IMCC_Net_Addr	net_addr;
} IMCC_Node_Profile;

/*****************************************************************************
/* options
*****************************************************************************/
#define IMCC_OPT_MAC_CONN_NUM			0x0001	//buf: uint32*
#define IMCC_OPT_NID					0x0002	//buf: uint32*
#define IMCC_OPT_NTYPE					0x0003	//buf: uint16*
#define IMCC_OPT_EXP_TIME				0x0004	//buf: uint32*
#define IMCC_DOMAIN_OPT_ENABLE_UDP		0x0101	//buf: boolean*
#define IMCC_DOMAIN_OPT_INDEX			0x0102	//buf: uint16*
#define IMCC_DOMAIN_OPT_ENABLE_UDP_AUTOCTRL		0x0103	//buf: boolean*
#define IMCC_DOMAIN_OPT_ENABLE_MULTICAST	0x0104	//buf: boolean*

/*****************************************************************************
/* IMCC Data Delievry: Realtime multipoint communication switch
*****************************************************************************/
typedef char*		IMCC_Site_Url;
typedef uint32		IMCC_Site_ID;
typedef uint32		IMCC_Domain_ID;
typedef char*		IMCC_Domain_Desc;
typedef uint32		IMCC_Handle;
typedef IMCC_Handle	IMCC_Domain_Handle;
typedef IMCC_Handle	IMCC_Connection_Handle;
typedef IMCC_Handle	IMCC_Ping_Handle;
typedef IMCC_Handle	IMCC_User_Handle;
typedef uint8		IMCC_Channel_ID;
typedef uint16		IMCC_MI_ID;

#define IMCC_MAX_SITE_URL_LEN		256
#define IMCC_MAX_DOMAIN_DESC_LEN	256
#define IMCC_MAX_CHANNEL_ID			255
#define IMCC_MAX_STATIC_CHANNEL_ID	0x40

typedef enum {
	IMCC_PRIORITY_CORE_CTRL = 0,
	IMCC_PRIORITY_APP_CTRL,
	IMCC_PRIORITY_CHAT,
	IMCC_PRIORITY_AUDIO,
	IMCC_PRIORITY_SCREEN,
	IMCC_PRIORITY_CACHE,
	IMCC_PRIORITY_VIDEO,
} IMCC_Priority;

#define IMCC_MAX_PRIORITY			7
#define IMCC_MAX_PDU_SIZE			2048
#define IMCC_MAX_CACHE_SIZE			0x8000 //(32k)

typedef uint8 IMCC_Packet_Type;

#define IMCC_PC_CORE_CTL			127
#define IMCC_PC_CORE_REG			126

#define IMCC_CHANNEL_0				1	// General domain scope control channel
#define IMCC_CHANNEL_1				2	// MCU scope control channel

/*****************************************************************************
/* IMCC Registry: Real time communication DB
*****************************************************************************/

typedef char*	IMCC_Reg_Key_Name;		// "DS101\docs\mydoc1\mypage1\"
typedef uint16	IMCC_Reg_Key_ID;
typedef char*	IMCC_Reg_Object_Name;	// "image1"
typedef uint32	IMCC_Reg_Object_ID;

#define IMCC_MAX_REG_KEY_NAME_LENGTH	512
#define IMCC_MAX_REG_OBJ_NAME_LENGTH	32

typedef enum {
	IMCC_REG_PARAMETER = 0,
	IMCC_REG_TOKEN,
	IMCC_REG_ROSTER,
	IMCC_REG_TABLE,
	IMCC_REG_HANDLE,
	IMCC_REG_COUNTER,
	IMCC_REG_QUEUE,
	IMCC_REG_EDIT,
	IMCC_REG_CACHE,
	IMCC_REG_POOL,
	IMCC_REG_CHANNEL,
} IMCC_Reg_Obj_Type;

typedef	enum
{
	IMCC_PERMISSION_INHERIT		= 0,
	IMCC_PERMISSION_OWNER		= 1,
	IMCC_PERMISSION_EVERYONE	= 2,
} IMCC_Reg_Permission;

typedef struct _tag_reg_key_attr
{
	IMCC_Reg_Permission		permission;
	IMCC_Channel_ID			monitor_channel;	// 0: inherit, 0xffff: none
	IMCC_Node_ID			owner_node_id;		// 0: inherit, 0xffffffffxxxx: none
} IMCC_Reg_Key_Attr;

typedef struct _tag_reg_object
{
    IMCC_Reg_Obj_Type	obj_type;
    char				obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32				obj_tag;
	IMCC_Reg_Object_ID	obj_id;
	uint8				obj_ddf;		// Object Data Delivery Flag
	IMCC_Node_ID		obj_creater;
} IMCC_Reg_Object;

#define IMCC_OBJECT_DDF_MASK_PRIORITY			0x3
#define IMCC_OBJECT_DDF_MASK_UNIFORM			0x4
#define IMCC_OBJECT_DDF_MASK_CREATER_DEPENDANT	0x8

//////////////////////////////////////////////////////////////////////////////
// token
typedef IMCC_Reg_Object_ID	IMCC_Token_ID;

typedef enum {
	IMCC_TOKEN_FREE =	0,
	IMCC_TOKEN_GRABBED,
	IMCC_TOKEN_INHIBITED,
	IMCC_TOKEN_GIVING,
	IMCC_TOKEN_GIVEN
} IMCC_Token_Status;

#define IMCC_MAX_REG_TOKEN_GRAB_KEY_LEN	32

typedef struct _tag_token
{
    IMCC_Reg_Obj_Type	obj_type;
    char				obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32				obj_tag;
	IMCC_Reg_Object_ID	obj_id;
	uint8				obj_ddf;
	IMCC_Node_ID		obj_creater;
	IMCC_Token_Status	status;
	IMCC_Node_ID		grabber;
	char				grab_key[IMCC_MAX_REG_TOKEN_GRAB_KEY_LEN];
} IMCC_Token;

//////////////////////////////////////////////////////////////////////////////
// Pool
typedef IMCC_Reg_Object_ID	IMCC_Pool_ID;

typedef struct _tag_pool
{
    IMCC_Reg_Obj_Type	obj_type;
    char				obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32				obj_tag;
	IMCC_Reg_Object_ID	obj_id;
	uint8				obj_ddf;
	IMCC_Node_ID		obj_creater;
	uint16				pool_size;
} IMCC_Pool;

//////////////////////////////////////////////////////////////////////////////
// table
typedef IMCC_Reg_Object_ID	IMCC_Table_ID;
typedef uint16				IMCC_Table_Record_ID;

typedef struct
{
    IMCC_Reg_Obj_Type	obj_type;
    char				obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32				obj_tag;
	IMCC_Reg_Object_ID	obj_id;
	uint8				obj_ddf;
	IMCC_Node_ID		obj_creater;
	uint16				max_num_of_records;
} IMCC_Table;

typedef struct
{
	IMCC_Table_Record_ID	record_id;
	uint32				record_tag;
	uint8				record_fields_count;
	IMCC_User_Data*		record_fields;
} IMCC_Table_Record;

//////////////////////////////////////////////////////////////////////////////
// roster
typedef IMCC_Reg_Object_ID		IMCC_Roster_ID;
typedef IMCC_Reg_Object			IMCC_Roster;
typedef uint16					IMCC_Roster_Presence_Flag;
typedef uint32					IMCC_Roster_Presence_Status;
typedef uint32					IMCC_Roster_Presence_Capability;

#define IMCC_ROSTER_PRESENCE_PUBLIC	0x1
#define IMCC_ROSTER_PRESENCE_GLOBAL	0x1
#define IMCC_ROSTER_PRESENCE_LOCAL	0x2

typedef struct
{
	IMCC_TERMINAL_ID			terminal_id;
	IMCC_Roster_Presence_Flag	presence_flag;
	IMCC_Roster_Presence_Status	presence_status;
	IMCC_Roster_Presence_Capability	presence_capability;
	uint8						presence_data_len;
	uint8*						presence_data;
} IMCC_Roster_Record;

//////////////////////////////////////////////////////////////////////////////
// parameter
typedef IMCC_Reg_Object_ID		IMCC_Parameter_ID;

#define IMCC_MAX_PRAMATER_LENGTH	1024

typedef struct
{
    IMCC_Reg_Obj_Type	obj_type;
    char				obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32				obj_tag;
	IMCC_Reg_Object_ID	obj_id;
	uint8				obj_ddf;
	IMCC_Node_ID		obj_creater;
	uint16				param_length;
	uint8*				param;
} IMCC_Parameter;

//////////////////////////////////////////////////////////////////////////////
// counters
typedef IMCC_Reg_Object_ID	IMCC_Counters_ID;

#define IMCC_MAX_NUM_OF_COUNTERS	1024

typedef struct 
{
    IMCC_Reg_Obj_Type		obj_type;
    char					obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32					obj_tag;
	IMCC_Reg_Object_ID		obj_id;
	uint8					obj_ddf;
	IMCC_Node_ID			obj_creater;
	uint16					num_of_counter;
	int32					default_value;
} IMCC_Counters;

//////////////////////////////////////////////////////////////////////////////
// edit
typedef IMCC_Reg_Object_ID	IMCC_Edit_ID;
typedef IMCC_Reg_Object		IMCC_Edit;

#define IMCC_EDIT_BEGIN		0x0
#define IMCC_EDIT_END		0xffffffff

//////////////////////////////////////////////////////////////////////////////
// queue
typedef IMCC_Reg_Object_ID	IMCC_Queue_ID;

typedef struct 
{
    IMCC_Reg_Obj_Type		obj_type;
    char					obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32					obj_tag;
	IMCC_Reg_Object_ID		obj_id;
	uint8					obj_ddf;
	IMCC_Node_ID			obj_creater;
	uint16					max_num_of_items;
} IMCC_Queue;

typedef struct {
	IMCC_Node_ID			item_sender_id;
	uint16					item_sequence_number;
	uint32					item_tag;
	uint16					item_data_length;
	uint8*					item_data;
} IMCC_Queue_Item;

//////////////////////////////////////////////////////////////////////////////
// cache
typedef IMCC_Reg_Object_ID	IMCC_Cache_ID;
typedef IMCC_Reg_Object		IMCC_Cache;

//////////////////////////////////////////////////////////////////////////////
// channel resource
typedef IMCC_Reg_Object_ID	IMCC_Channel_Rsc_ID;

typedef struct 
{
    IMCC_Reg_Obj_Type		obj_type;
    char					obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32					obj_tag;
	IMCC_Reg_Object_ID		obj_id;
	uint8					obj_ddf;
	IMCC_Node_ID			obj_creater;
	uint8					num_of_channels;
	IMCC_Channel_ID			base_channel_id;
} IMCC_Channel_Rsc;

/*****************************************************************************
/* IMCC call back proc
*****************************************************************************/

typedef enum
{
	IMCC_MT_Sys_Cmd					= 0,
	IMCC_MT_Error_Report			= 1,

	IMCC_MT_Domain_Connect_Ind		= 2,
	IMCC_MT_Domain_Connect_Cfm		= 3,
	IMCC_MT_Domain_Disconnect_Ind	= 4,

	IMCC_MT_User_Attach_Cfm			= 5,
	IMCC_MT_User_Detach_Ind			= 6,

	IMCC_MT_Channel_Join_Cfm		= 7,
	IMCC_MT_Send_Data_Ind			= 8,

	IMCC_MT_Flow_Control_Alarm_Ind	= 10,
	IMCC_MT_Flow_Control_Rpt		= 11,

	IMCC_MT_Reg_Register_Key_Cfm	= 20,
	IMCC_MT_Reg_Register_Key_Ind	= 21,
	IMCC_MT_Reg_Retrieve_Key_Cfm	= 22,
	IMCC_MT_Reg_Delete_Key_Ind		= 23,

	IMCC_MT_Reg_Register_Obj_Cfm	= 24,
	IMCC_MT_Reg_Register_Obj_Ind	= 25,
	IMCC_MT_Reg_Retrieve_Obj_Cfm	= 26,
	IMCC_MT_Reg_Delete_Obj_Ind		= 27,

	IMCC_MT_Token_Give_Cfm			= 30,
	IMCC_MT_Token_Give_Ind			= 31,
	IMCC_MT_Token_Grab_Cfm			= 32,
	IMCC_MT_Token_Inhibit_Cfm		= 33,
	IMCC_MT_Token_Please_Ind		= 34,
	IMCC_MT_Token_Release_Cfm		= 35,
	IMCC_MT_Token_Status_Change_Ind	= 36,

	IMCC_MT_Table_Insert_Cfm		= 37,
	IMCC_MT_Table_Insert_Ind		= 38,
	IMCC_MT_Table_Update_Ind		= 39,
	IMCC_MT_Table_Delete_Ind		= 40,
	
	IMCC_MT_Roster_Update_Ind		= 41,
	IMCC_MT_Handle_Allocate_Cfm		= 42,	
	IMCC_MT_Parameter_Update_Ind	= 43,
	IMCC_MT_Edit_Update_Ind			= 44,
	
	IMCC_MT_Counter_Update_Ind		= 45,
	IMCC_MT_Counter_Set_Size_Ind	= 46,

	IMCC_MT_Queue_Set_Size_Ind		= 47,
	IMCC_MT_Queue_Add_Item_Ind		= 48,
	IMCC_MT_Queue_Update_Item_Ind	= 49,
	IMCC_MT_Queue_Remove_Item_Ind	= 50,

	IMCC_MT_Cache_Set_Data_Ind		= 51,
	IMCC_MT_Cache_Data_Ready_Ind	= 52,
	IMCC_MT_Cache_Set_Data_First_Ind= 53,
	IMCC_MT_Cache_Get_Data_Cfm		= 54,
	IMCC_MT_Cache_Set_Data_Cfm		= 55,

	IMCC_MT_Pool_Grab_Cfm			= 56,
	IMCC_MT_Pool_Release_Ind		= 57,

	IMCC_MT_Ping_Report				= 60,
} IMCC_Msg_Type;

typedef void*	IMCC_User_Context;

typedef IMCC_Error (* IMCC_Callback_Proc)(
	IMCC_User_Context		context,
	IMCC_Msg_Type			msg_type,
	void*					msg);

/**
/* IMCC_Msg_Sys_Cmd
/* This notification message is issued to the Node Controller that an 
/* system command is received.
*/
typedef struct _tag_Msg_Sys_Cmd
{
	uint16		msg_len;
	uint8*		msg_data;
} IMCC_Msg_Sys_Cmd;

/**
/* IMCC_Msg_Error_Status_Report
/* This notification message is issued to the Node Controller that an 
/* internal warning/error condition has occurred.
*/
#define IMCC_MAX_ERR_RPT_MSG_LEN	128
typedef struct _tag_Msg_Error_Status_Report
{
	uint32		error_code;
	uint32		reason;
	char		message[IMCC_MAX_ERR_RPT_MSG_LEN];
} IMCC_Msg_Error_Status_Report;

typedef enum {
	IMCC_Error_Unknown			= 0,
	IMCC_Error_Listen_Failed	= 1, // message:transport_addr
} IMCC_Error_Code;

/*****************************************************************************
* IMCC NC management functions
*****************************************************************************/

/** 
/* imcc_initialize:
/* By calling this function, an application initializes the local IMCC
/* Provider for further IMCC services
/* node_id should be 0 if this node is a terminal so that server will dynamically 
/* assign a domainwise unique node id for it.
*/
IMCC_Error imcc_initialize(
	IMCC_Device_Type		device_type,			/* INPUT  */
	IMCC_OS_Type			os_type,				/* INPUT  */
	IMCC_Net_Link_Type		net_link_type			/* INPUT  */
);

/** 
/* imcc_cleanup:
/* Node controller application issues this function call when it is
/* terminating gracefully, IMCC Provider will free all the resources 
/* within this call
*/
IMCC_Error imcc_cleanup(
	uint32					time_out				/* INPUT  */
);

/** 
/* imcc_register_nc_applicaiton:
/* By calling this function applicaiton will register it as the node controller
/* for all the domain connections with prot type as specified.
/* The control_sap_callback provides the entry point of a IMCC_Callback_Proc()
/* function which the IMCC Provider will call to deliver messages to the 
/* Node Controller asynchronously. 
*/
IMCC_Error imcc_register_nc_applicaiton(
	IMCC_Callback_Proc		control_sap_callback	/* INPUT  */
);

/** 
/* imcc_unregister_nc_applicaiton:
/* By calling this function applicaiton will unregister it from IMCC provider.
*/
IMCC_Error imcc_unregister_nc_applicaiton();

/** 
/* imcc_nc_heartbeat:
/* Heartbeat to drive callbacks so that callback can be initiated in the node
/* controller thread context
*/
IMCC_Error imcc_nc_heartbeat();

/**
/* imcc_listen:
/* A Node controller application calla this function in order to 
/* indicate that the IMCC Provider should listen for incoming connections on 
/* the specified local transport address.
/* transport_addr format is defined as: protocol_type://host:port
*/
IMCC_Error imcc_listen(
	char*					transport_addr			/* INPUT  */
);

/** 
/* imcc_listen_cancel:
/* A Node Controller calls this function in order to indicate that the
/* specified local transport address should be removed from the list of
/* listening local transport addresses. Incoming connections on the specified
/* local transport address should thus subsequently be ignored
/* transport_addr format is defined as: protocol_type://host:port
*/
IMCC_Error imcc_listen_cancel(
	char*					transport_addr			/* INPUT  */
);

/** 
/* imcc_flow_control_config:
/* A Node Controller calls this function in order to config the flow control
/* alarm buffer size and alarm delay time
*/
IMCC_Error imcc_flow_control_config(
	IMCC_Priority			priority,				/* INPUT  */
	uint16					alarm_delay_time,		/* INPUT  */
	uint32					alarm_buffer_size		/* INPUT  */
);

/**
/* imcc_get_option:
/* Used by a node controller applicaiton to get options for the core module 
*/
IMCC_Error imcc_get_option(
	uint16					option,					/* INPUT  */
	uint8*					buffer,					/* INPUT  */
	uint32*					buffer_length			/* INPUT  */
);

/**
/* imcc_ping_request
/* Used by a node controller applicaiton to check the connection preformence
*/
#define PING_OPT_LATENCY		0x1
#define PING_OPT_UP_THRUPUT		0x2
#define PING_OPT_DOWN_THRUPUT	0x4

IMCC_Error imcc_ping_request(
	char*					calling_addr,			/* INPUT  */
	char*					called_addr,			/* INPUT  */
	uint8					ping_flag,				/* INPUT  */
	IMCC_Ping_Handle*		hping					/* OUTPUT */
);

IMCC_Error imcc_ping_cancel(
	IMCC_Ping_Handle		hping					/* INPUT  */
);

/**
/* IMCC_Msg_Ping_Rpt
*/
typedef struct _tag_Msg_Ping_Rpt
{
	char					calling_addr[IMCC_MAX_IP_ADDR];
	char					called_addr[IMCC_MAX_IP_ADDR];
	uint32					latency;
	uint32					down_thruput;
	uint32					up_thruput;
} IMCC_Msg_Ping_Rpt;

/*****************************************************************************
/* IMCC domain management related functions and messages
/*	imcc_domain_create
/*	imcc_domain_delete
/*	imcc_domain_query
/*	imcc_domain_get_user_context
/*
/*	imcc_domain_connect_request
/*	imcc_domain_connect_response  
/*	imcc_domain_disconnect_request
/*
/*	IMCC_Msg_Domain_Connect_Ind
/*	IMCC_Msg_Domain_Connect_Cfm
/*	IMCC_Msg_Domain_Disconnect_Ind
/****************************************************************************/

/**
/* imcc_domain_create:
/* Used by a node controller applicaiton to create a local domain element
*/
IMCC_Error imcc_domain_create(
	uint32					site_id,				/* INPUT  */
	IMCC_Site_Url			site_url,				/* INPUT  */
	IMCC_Domain_ID			domain_id,				/* INPUT  */
	IMCC_Domain_Desc		domain_desc,			/* INPUT  */
	IMCC_User_Context		user_context,			/* INPUT  */
	IMCC_Domain_Handle*		domain_h				/* OUTPUT */
);

/**
/* imcc_domain_delete:
/* Used by a node controller applicaiton to delete a local domain element
*/
IMCC_Error imcc_domain_delete(
	IMCC_Domain_Handle		domain_h				/* INPUT  */
);

/**
/* imcc_domain_query:
/* Used by a node controller applicaiton to query a local domain element
*/
IMCC_Error imcc_domain_query(
	uint32					site_id,				/* INPUT  */
	IMCC_Domain_ID			domain_id,				/* INPUT  */
	IMCC_Domain_Handle*		domain_h				/* OUTPUT */
);

/**
/* imcc_domain_get_user_context:
/* Used by a node controller applicaiton to get the user context attached to
/* a local domain element
*/
IMCC_Error imcc_domain_get_user_context(
	IMCC_Domain_Handle		domain_h,				/* INPUT  */
	IMCC_User_Context*		user_context			/* OUtPUT */
);

/**
/* imcc_domain_set_option:
/* Used by a node controller applicaiton to set options for the domain 
*/
IMCC_Error imcc_domain_set_option(
	IMCC_Domain_Handle		domain_h,				/* INPUT  */
	uint16					option,					/* INPUT  */
	uint8*					buffer,					/* INPUT  */
	uint32					buffer_length			/* INPUT  */
);

/**
/* imcc_domain_get_option:
/* Used by a node controller applicaiton to get options for the domain 
*/
IMCC_Error imcc_domain_get_option(
	IMCC_Domain_Handle		domain_h,				/* INPUT  */
	uint16					option,					/* INPUT  */
	uint8*					buffer,					/* INPUT  */
	uint32*					buffer_length			/* INPUT  */
);

/**
/* imcc_domain_connect_request:
/* Used by a node controller applicaiton to connect local domain provider 
/* to a remote one.
*/
IMCC_Error imcc_domain_connect_request(
	IMCC_Domain_Handle		domain_h,				/* INPUT  */
	char*					node_name,				/* INPUT  */
	uint32					node_alt_id,			/* INPUT  */
	char*					calling_addr,			/* INPUT  */
	char*					called_addr,			/* INPUT  */
	uint8					num_of_user_data,		/* INPUT  */
	IMCC_User_Data_1*		user_data,				/* INPUT  */
	IMCC_Connection_Handle*	conn_h					/* OUTPUT */
);

/**
/* IMCC_MT_Domain_Connect_Ind
/* This notification message is issued to the Node Controller at the node
/* addressed by a imcc_domain_connect_request() call. The Node Controller
/* should respond with a imcc_domain_connect_response() in order to indicate
/* whether it accepts or rejects the request.
*/
typedef struct _tag_Msg_Domain_Connect_Ind
{
	IMCC_Connection_Handle	conn_h;
	uint32					site_id;
	char					site_url[IMCC_MAX_SITE_URL_LEN];
	IMCC_Domain_ID			domain_id;
	char					domain_desc[IMCC_MAX_DOMAIN_DESC_LEN];
	IMCC_Node_Profile		calling_node_profile;
	uint8					num_of_user_data;
	IMCC_User_Data_1*		user_data_list;
} IMCC_Msg_Domain_Connect_Ind;

/**
/* imcc_domain_connect_response:
/* MCU Node Controller calls this function after it has received a 
/* IMCC_MT_Domain_Connect_Ind message in order to indicate 
/* whether it accepts or rejects the connection request
*/
IMCC_Error imcc_domain_connect_response(
	IMCC_Connection_Handle	conn_h,					/* INPUT  */
	IMCC_Domain_Handle		domain_h,				/* INPUT  */
	uint8					num_of_user_data,		/* INPUT  */
	IMCC_User_Data_1*		user_data,				/* INPUT  */
	IMCC_Result				result					/* INPUT  */
);

/**
/* IMCC_MT_Domain_Connect_Cfm
/* This notification message informs a Node Controller whether a previously
/* issued imcc_domain_connect_request() was successful. 
*/
typedef struct _tag_Msg_Domain_Connect_Cfm
{
	IMCC_Connection_Handle	conn_h;
	IMCC_Result				result;
	IMCC_Node_ID			node_id;
	uint8					num_of_user_data;
	IMCC_User_Data_1*		user_data_list;
	IMCC_Net_Addr			net_addr;
} IMCC_Msg_Domain_Connect_Cfm;

/**
/* imcc_domain_disconnect_request
/* This function is used by a Node Controller to disconnect the local domain 
/* provider to the remote portion
*/
IMCC_Error imcc_domain_disconnect_request(
	IMCC_Connection_Handle	conn_h					/* INPUT  */
);

/**
/* IMCC_MT_Domain_Disconnect_Ind
/* This message is issued:
/* 1. to parent MCU Node Controller whenever a sub node is disconnected 
/*    from a domain.
/* 2. to local Node Controller when local node abnormally disconnected 
/*    from a domain.
*/
typedef struct _tag_Msg_Domain_Disconnect_Ind
{
	IMCC_Connection_Handle	conn_h;
	IMCC_Reason				reason;
	char					disconn_msg[256];
} IMCC_Msg_Domain_Disconnect_Ind;

/**
/* imcc_connection_set_user_context:
/* Used by a node controller applicaiton to attach a user context to the specified 
/* connection
*/
IMCC_Error imcc_connection_set_user_context(
	IMCC_Connection_Handle	conn_h,					/* INPUT  */
	uint32					user_context			/* INPUT  */
);

/**
/* imcc_connection_get_context:
/* Used by a node controller applicaiton to get the user context attached to the 
/* specified connection
*/
IMCC_Error imcc_connection_get_user_context(
	IMCC_Connection_Handle	conn_h,					/* INPUT  */
	uint32*					user_context			/* INPUT  */
);

/**
/* IMCC_Msg_Flow_Control_Alarm_Ind
/* This notification message is issued to the Node Controller about the flow 
/* control status
*/
typedef struct _tag_Msg_Flow_Control_Alarm_Ind
{
	IMCC_Connection_Handle	conn_h;
	IMCC_Priority			priority;
	uint16					delay_time;		// in mini seconds
	uint32					delay_buf_size;	// number of bytes
	boolean					alarm_status;
} IMCC_Msg_Flow_Control_Alarm_Ind;

/**
/* IMCC_Msg_Flow_Control_Rpt
*/
#define IMCC_MAX_FC_RPT_MSG_LEN	1024
typedef struct _tag_Msg_Flow_Control_Rpt
{
	IMCC_Connection_Handle	conn_h;
	char					rpt_buf[IMCC_MAX_FC_RPT_MSG_LEN];
} IMCC_Msg_Flow_Control_Rpt;

/*****************************************************************************
/* IMCC User Applicaiton related functions and messages
/*	imcc_user_attach_request
/*	imcc_user_detach_request
/*
/*	IMCC_MT_User_Attach_Cfm
*****************************************************************************/

/**
/* imcc_user_attach_request:
/* This function is called by a user applicaiton in order to attach it 
/* to the specified domain. It will also automatically subscribe to the 
/* specified primary channel. If primary_chan_id is 0, IMCC will assign a 
/* domainwise unique channel ID for it. 
/* IMCC_MT_User_Attach_Cfm message will be returned to indicate whether 
/* this request is successful or not.
/* 
*/
IMCC_Error imcc_user_attach_request(
	IMCC_Domain_Handle		domain_h,				/* INPUT  */
	IMCC_Channel_ID			primary_chan_id,		/* INPUT  */
	IMCC_User_Context		user_context,			/* INPUT  */
	IMCC_Callback_Proc		app_sap_callback,		/* INPUT  */
	IMCC_User_Handle*		user_handle				/* OUTPUT */
);

/**
/* IMCC_MT_User_Attach_Cfm
/* This notification message informs a user application whether a previous
/* call to imcc_user_attach_request() was successful
*/
typedef struct _tag_Msg_User_Attach_Cfm
{
	IMCC_Result				result;
	IMCC_Channel_ID			primary_chan_id;
} IMCC_Msg_User_Attach_Cfm;

/**
/* imcc_user_detach_request:
/* This function is called by a user applicaiton in order to detach it 
/* from the specified domain.
*/
IMCC_Error imcc_user_detach_request(
	IMCC_User_Handle		user_h					/* INPUT  */
);

/**
/* IMCC_MT_User_Detach_Ind
/* This notification message informs a user application when user is detached 
/* due to system internal reason.
*/
typedef struct _tag_Msg_User_Detach_Ind
{
	IMCC_User_Handle		user_h;
	IMCC_User_Context		user_context;
	IMCC_Reason				reason;
} IMCC_Msg_User_Detach_Ind;

/**
/* imcc_user_expel_request:
/* This function is called by a user applicaiton in order to expel a specified 
/* user.
*/
IMCC_Error imcc_user_expel_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Node_ID			expeled_node_id			/* INPUT  */
);

/*****************************************************************************
* IMCC data delievry related funcitons and messages
*	imcc_channel_join_request
*	imcc_channel_leave_request
*	imcc_send_data_request
*
*	IMCC_Msg_Channel_Join_Cfm
*	IMCC_Msg_Send_Data_Ind
*****************************************************************************/

/**
/* imcc_channel_join_request:
/* This function is called by a user applications to subscribe to a channel,
/* meaning that it will receive data traveling on that channel. 
/* IMCC_MT_Channel_Join_Cfm message will be returned to indicate whether 
/* this request is successful or not.
*/
IMCC_Error imcc_channel_join_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Channel_ID			channel_id				/* OUTPUT */
);

/**
/* IMCC_MT_Channel_Join_Cfm
/* This notification message informs a user application whether a previous
/* call to imcc_channel_join_request() was successful
*/
typedef struct _tag_Msg_Channel_Join_Cfm
{
	IMCC_Result				result;
	IMCC_Channel_ID			requested_id;
	IMCC_Channel_ID			channel_id;
} IMCC_Msg_Channel_Join_Cfm;

/**
/* imcc_channel_leave_request:
/* This function is called by a user applications to remove itself from a
/* previously joined channel.
/* No associated confirm meesage will be issued.
*/
IMCC_Error imcc_channel_leave_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Channel_ID			channel_id				/* INPUT  */
);

/**
/* imcc_send_data_request:
/* This function will send data to the IMCC provider for distribution to all
/* IMCC applications attached and joined to the specified channel or node. 
/* For multicast data delievery, dest_node_id need be input as 0.
*/
IMCC_Error imcc_send_data_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Node_ID			dest_node_id,			/* INPUT  */
	IMCC_Channel_ID			dest_chan_id,			/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	boolean					is_uniform,				/* INPUT  */
	boolean					is_reliable,			/* INPUT  */
	boolean					is_key_packet,			/* INPUT  */
	IMCC_Packet_Type		packet_type,			/* INPUT  */
	uint16					user_header_ext_profile,/* INPUT  */
	uint16					user_header_ext_length,	/* INPUT  */
	uint8*					user_header_ext,		/* INPUT  */
	uint8*					user_data,				/* INPUT  */
	uint32					user_data_length		/* INPUT  */
);

/**
/* IMCC_MT_Send_Data_Ind
/* This notification message informs a user application when there is a data
/* received.
*/
typedef struct _tag_Msg_Send_Data_Ind
{
	IMCC_Node_ID			src_node_id;
	IMCC_Node_ID			dest_node_id;
	IMCC_Channel_ID			dest_chan_id;
	IMCC_Priority			priority;
	boolean					is_uniform;
	boolean					is_reliable;
	boolean					is_key_packet;
	IMCC_Packet_Type		packet_type;
	uint16					user_header_ext_profile;
	uint16					user_header_ext_length;
	uint8*					user_header_ext;
	uint8*					user_data;
	uint32					user_data_length;
} IMCC_Msg_Send_Data_Ind;

/**
/* imcc_flow_control_flush_req:
*/
IMCC_Error imcc_flow_control_flush_req(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Node_ID			dest_node_id,			/* INPUT  */
	IMCC_Channel_ID			dest_chan_id,			/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	IMCC_Packet_Type		packet_type,			/* INPUT  */
	uint32					flag					/* INPUT  */
);

/*****************************************************************************
* IMCC token related funcitons and messages
*	imcc_token_give_request
*	imcc_token_give_response
*	imcc_token_grab_request
*	imcc_token_inhibit_request
*	imcc_token_please_request
*	imcc_token_release_request
*	imcc_motoken_set_size_request
*	imcc_motoken_grab_request
*	imcc_motoken_release_request
*
*	IMCC_Msg_Token_Give_Cfm
*	IMCC_Msg_Token_Give_Ind
*	IMCC_Msg_Token_Token_Grab_Cfm
*	IMCC_Msg_Token_Token_Inhibit_Cfm
*	IMCC_Msg_Token_Token_Please_Ind
*	IMCC_Msg_Token_Token_Release_Cfm
*	IMCC_Msg_MOToken_Token_Grab_Cfm
*****************************************************************************/

/** 
/* imcc_token_give_request
/* This function call will pass a grabbed token to another IMCC application
/* giving full ownership and control of that token to the receiving
/* application.  This function call is issued in response to an
/* IMCC_Token_Give_Ind notification message. Message IMCC_MT_Token_Give_Cfm
/* will be notified when the token has either successfully passed or if the 
/* token pass has failed.
*/
IMCC_Error imcc_token_give_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Token_ID			token_id,				/* INPUT  */
	IMCC_Node_ID 			receiver_id				/* INPUT  */
);

/**
/* IMCC_MT_Token_Give_Ind
/* This notification message is sent to the IMCC user application that is
/* designated as the recipient of an IMCC_Token_Give_Request() call.
*/
typedef struct _tag_Msg_Token_Give_Ind
{
	IMCC_Node_ID			requestor_id;
	IMCC_Token_ID			token_id;
} IMCC_Msg_Token_Give_Ind;

/** 
/* imcc_token_give_response
/* This function call will be initiated upon reception of an
/* IMCC_MT_Token_Give_Ind notification message.  The IMCC application can
/* choose to either accept or reject the token passing as desired. The result 
/* parameter can contain any of the following values:
/*		IMCC_RESULT_SUCCESSFUL
/*		IMCC_RESULT_USER_REJECTED
*/
IMCC_Error imcc_token_give_response(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Token_ID			token_id,				/* INPUT  */
	IMCC_Result 			result					/* INPUT  */
);

/**
/* IMCC_MT_Token_Give_Cfm
/* This notification message is sent to the IMCC user application in reply
/* to an IMCC_Token_Give_Request() call. The result member indicates whether 
/* the request was accepted or rejected.  
/* Following are possible values for result:
/*	IMCC_RESULT_SUCCESSFUL
/*	IMCC_RESULT_DOMAIN_MERGING
/*	IMCC_RESULT_NO_SUCH_USER
/*	IMCC_RESULT_TOKEN_NOT_POSSESSED
/*	IMCC_RESULT_USER_REJECTED
*/
typedef struct _tag_Msg_Token_Give_Cfm
{
	IMCC_Result				result;
	IMCC_Token_ID			token_id;
} IMCC_Msg_Token_Give_Cfm;

/** 
/* imcc_token_grab_request
/* This function call is used to request a token for exclusive use.  If the
/* token has already been grabbed or inhibited within the environment, then
/* this request will not be validated during the CONFIRM notification
/* message.  However, if the only current possessor of the token is the
/* user application requesting the token, and its current state is
/* inhibited, then the token state will be changed to grabbed. An
/* IMCC_MT_Token_Grab_Cfm notification message will be sent validating
/* whether the request was accepted or rejected.
*/
IMCC_Error imcc_token_grab_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Token_ID			token_id,				/* INPUT  */
	char*					grab_key				/* INPUT  */
);

/**
/* IMCC_MT_Token_Grab_Cfm
/* This notification message informs a user application whether a previous
/* call to imcc_token_grab_request() was successful
/* Following are possible values for result:
/*	IMCC_RESULT_SUCCESSFUL
/*	IMCC_RESULT_TOKEN_NOT_AVAILABLE
/*	IMCC_RESULT_TOO_MANY_TOKENS
*/
typedef struct _tag_Msg_Token_Grab_Cfm
{
	IMCC_Result				result;
	IMCC_Token_ID			token_id;
} IMCC_Msg_Token_Grab_Cfm;

/** 
/* imcc_token_inhibit_request
/* This function call is used to request a token for non-exclusive use.
/* Multiple IMCC applications in a domain can issue this function call and
/* will all succeed and hold the token in an inhibited state.  If a single
/* IMCC application inhibits a token, then this prevents any other IMCC
/* application from grabbing the specific token for exclusive use.  However,
/* if the local user application inhibits a token and is the sole inhibitor,
/* then the local user application can change the state to grabbed by
/* issuing an IMCC_Token_Grab_Request(). An IMCC_MT_Token_Inhibit_Cfm
/* notification message will be sent validating whether the request was
/* accepted or rejected.
*/
IMCC_Error imcc_token_inhibit_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Token_ID			token_id				/* INPUT  */
);

/**
/* IMCC_MT_Token_Inhibit_Cfm
/* This notification message informs a user application whether a previous
/* call to imcc_token_inhibit_request() was successful
/* Following are possible values for result:
/*	IMCC_RESULT_SUCCESSFUL
/*	IMCC_RESULT_TOKEN_NOT_AVAILABLE
/*	IMCC_RESULT_TOO_MANY_TOKENS
*/
typedef struct _tag_Msg_Token_Inhibit_Cfm
{
	IMCC_Result				result;
	IMCC_Token_ID			token_id;
} IMCC_Msg_Token_Inhibit_Cfm;

/** 
/* imcc_token_please_request
/* The function call is issued by an IMCC application to request possession
/* of a grabbed or inhibited token from another IMCC application. No confirm
/* message will result from this function call.  However, it would be
/* polite for the IMCC application receiving this request to respond with an
/* IMCC_Token_Give_Request() which either denies or grants the token pass
/* request.
*/
IMCC_Error imcc_token_please_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Token_ID			token_id				/* INPUT  */
);

/**
/* IMCC_MT_Token_Please_Ind
/* This notification message indicates to a user application that another
/* user application has called imcc_token_please_request(),thus requesting to 
/* transfer the specified token ownershp to the specified application.
*/
typedef struct _tag_Msg_Token_Please_Ind
{
	IMCC_Node_ID			requestor_id;
	IMCC_Token_ID			token_id;
} IMCC_Msg_Token_Please_Ind;

/** 
/* imcc_token_release_request:
/* This function call will release a currently held token to the IMCC
/* provider.  
*/
IMCC_Error imcc_token_release_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Token_ID			token_id				/* INPUT  */
);

/**
/* IMCC_MT_Token_Status_Change_Ind
/* This notification message will be sent to all the IMCC user applications
/* which monitoring this token status when the token's status changed
*/
typedef struct _tag_Msg_Token_Status_Change_Ind
{
	IMCC_Token_ID			token_id;
	IMCC_Token_Status		status;
	IMCC_Node_ID			grabber_id;
} IMCC_Msg_Token_Status_Change_Ind;

/*****************************************************************************
* IMCC pool related funcitons and messages
*	imcc_pool_set_size_request
*	imcc_pool_grab_request
*	imcc_pool_release_request
*
*	IMCC_Msg_Pool_Grab_Cfm
*	IMCC_Msg_Pool_Release_Ind
*****************************************************************************/

IMCC_Error imcc_pool_set_size_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Pool_ID			pool_id,				/* INPUT  */
	uint16					new_size
);

IMCC_Error imcc_pool_grab_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Pool_ID			pool_id					/* INPUT  */
);

typedef struct _tag_Msg_Pool_Grab_Cfm
{
	IMCC_Pool_ID			pool_id;
	IMCC_Result				result;
} IMCC_Msg_Pool_Grab_Cfm;

IMCC_Error imcc_pool_release_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Pool_ID			pool_id					/* INPUT  */
);

typedef struct _tag_Msg_Pool_Release_Ind
{
	IMCC_Pool_ID			pool_id;
} IMCC_Msg_Pool_Release_Ind;

/*****************************************************************************
*	imcc_table_insert_record_request
*	imcc_table_update_record_request
*	imcc_table_delete_record_request
*	imcc_roster_update_request
*
*	IMCC_MT_Table_Insert_Cfm
*	IMCC_MT_Table_Insert_Ind
*	IMCC_MT_Table_Update_Ind
*	IMCC_MT_Table_Delete_Ind
*	IMCC_MT_Roster_Update_Ind
*****************************************************************************/

/**
/* imcc_table_insert_request
/* This function is called by a user application to insert a new table record 
/* into a registry table object.
*/
IMCC_Error imcc_table_insert_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	boolean					uniform,				/* INPUT  */
	IMCC_Table_ID			table_id,				/* INPUT  */
	uint16					num_of_records,			/* INPUT  */
	IMCC_Table_Record*		records					/* INPUT  */
);

/**
/* IMCC_MT_Table_Insert_Cfm
/* This notification message confirms the result of the previous call 
/* imcc_table_insert_request().
*/
typedef struct 
{
	IMCC_Table_Record_ID	record_id;
	uint32					record_tag;
	IMCC_Result				result;
} IMCC_Table_Insert_Cfm;

typedef struct _tag_Msg_Table_Insert_Cfm
{
	IMCC_Table_ID			table_id;
	uint16					num_of_cfms;
	IMCC_Table_Insert_Cfm*	cfms;
} IMCC_Msg_Table_Insert_Cfm;

/**
/* IMCC_MT_Table_Insert_Ind
/* This notification message indicate that a new table record has been inserted.
*/
typedef struct _tag_Msg_Table_Insert_Ind
{
	IMCC_Table_ID			table_id;
	uint16					num_of_records;
	IMCC_Table_Record*		records;
} IMCC_Msg_Table_Insert_Ind;

/**
/* imcc_table_update_request
/* This function is called by a user application to update a table record 
/* in a registry table object.
*/
IMCC_Error imcc_table_update_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	boolean					uniform,				/* INPUT  */
	IMCC_Table_ID			table_id,				/* INPUT  */
	IMCC_Table_Record_ID	record_id,				/* INPUT  */
	uint8					upt_rec_fields_count,	/* INPUT  */
	IMCC_User_Data_2*		upt_rec_fields			/* INPUT  */
);

/**
/* IMCC_MT_Table_Update_Ind
/* This notification message indicate that a table record has been updated.
*/
typedef struct _tag_Msg_Table_Update_Ind
{
	IMCC_Table_ID			table_id;
	IMCC_Table_Record_ID	record_id;
	uint8					upt_rec_fields_count;
	IMCC_User_Data_2*		upt_rec_fields;
} IMCC_Msg_Table_Update_Ind;

/**
/* imcc_table_delete_request
/* This function is called by a user application to delete a table record 
/* in a registry table object.
*/
IMCC_Error imcc_table_delete_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	boolean					uniform,				/* INPUT  */
	IMCC_Table_ID			table_id,				/* INPUT  */
	IMCC_Table_Record_ID	record_id				/* INPUT  */
);

/**
/* IMCC_MT_Table_Delete_Ind
/* This notification message indicate that a table record has been removed.
*/
typedef struct _tag_Msg_Table_Delete_Ind
{
	IMCC_Table_ID			table_id;
	IMCC_Table_Record_ID	record_id;
} IMCC_Msg_Table_Delete_Ind;

/*****************************************************************************
*	imcc_roster_update_request
*
*	IMCC_MT_Roster_Update_Ind
*****************************************************************************/
typedef uint8 IMCC_Roster_Update_Flag;
#define IMCC_ROSTER_UPDATE_ACTION_MASK	0x03
#define IMCC_ROSTER_ADD					0x00
#define IMCC_ROSTER_REMOVE				0x01
#define IMCC_ROSTER_MODIFY				0x02

#define IMCC_ROSTER_UPDATE_DATA_MASK	0x1c
#define IMCC_ROSTER_UPDATE_PF			0x04
#define IMCC_ROSTER_UPDATE_PS			0x08
#define IMCC_ROSTER_UPDATE_PC			0x10
#define IMCC_ROSTER_UPDATE_PD			0x20

#define IMCC_ROSTER_UPDATE_REFRESH_MASK	0x80

/**
/* imcc_roster_update_request
/* This function is called by a user application to update roster object.
*/

IMCC_Error imcc_roster_update_request(
	IMCC_User_Handle			user_h,					/* INPUT  */
	IMCC_Roster_ID				roster_id,				/* INPUT  */
	IMCC_Roster_Update_Flag		update_flag,			/* INPUT  */
	IMCC_Roster_Presence_Flag	presence_flag,			/* INPUT  */
	IMCC_Roster_Presence_Status	presence_status,		/* INPUT  */
	IMCC_Roster_Presence_Capability	presence_capability,	/* INPUT  */
	uint8						presence_data_len,		/* INPUT  */
	uint8*						presence_data			/* INPUT  */
);

/**
/* IMCC_MT_Roster_Update_Ind
/* This notification message indicate that specified roster has been updated.
*/
typedef struct _tag_roster_update_record
{
	IMCC_Roster_Update_Flag		update_flag;
	IMCC_TERMINAL_ID			terminal_id;
	IMCC_Roster_Presence_Flag	presence_flag;
	IMCC_Roster_Presence_Status	presence_status;
	IMCC_Roster_Presence_Capability	presence_capability;
	uint8						presence_data_length;
	uint8*						presence_data;
} IMCC_Roster_Update_Record;

typedef struct _tag_Msg_Roster_Update_Ind
{
	IMCC_Roster_ID				roster_id;
	IMCC_MCU_ID					mcu_id;
	uint16						roster_size;
	uint16						num_of_records;
	IMCC_Roster_Update_Record*	records;
} IMCC_Msg_Roster_Update_Ind;


/*****************************************************************************
* IMCC other resource related funcitons and messages
*	imcc_handle_allocate_request
*	imcc_handle_free_request
*	imcc_parameter_update_request
*	imcc_counter_set_size_request
*	imcc_counter_update_request
*	imcc_edit_update_request
*	imcc_queue_set_size_request
*	imcc_queue_add_item_request
*	imcc_queue_remove_item_request
*	imcc_cache_set_data_request
*	imcc_cache_set_data_first_request
*	imcc_cache_set_data_cancel_request
*	imcc_cache_get_data_request
*	imcc_cache_get_data_first_request
*	imcc_cache_get_data_cancel_request
*
*	IMCC_MT_Handle_Allocate_Cfm
*	IMCC_MT_Parameter_Update_Ind
*	IMCC_MT_Counter_Update_Ind
*	IMCC_MT_Counter_Set_Size_Ind
*	IMCC_MT_Edit_Update_Ind
*	IMCC_MT_Queue_Set_Size_Ind
*	IMCC_MT_Queue_Add_Item_Ind
*	IMCC_MT_Queue_Remove_Item_Ind
*	IMCC_MT_Cache_Set_Data_Ind
*	IMCC_MT_Cache_Data_Ready_Ind
*	IMCC_MT_Cache_Set_Data_First_Ind
*	IMCC_MT_Cache_Get_Data_Cfm
*	IMCC_MT_Cache_Set_Data_Cfm
*****************************************************************************/

/** 
/* imcc_handle_allocate_request
/* A user application calls this function in order to request that a 
/* numerical value (or a list of numerical values) be assigned to it that is 
/* globally unique within the scope of a single domain. 
*/
IMCC_Error imcc_handle_allocate_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	uint16					num_of_handles			/* INPUT  */
);

/** 
/* imcc_handle_free_request
/* A user application calls this function in order to free a block of allocated 
/* handle
*/
IMCC_Error imcc_handle_free_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Handle				first_handle,			/* INPUT  */
	uint16					num_of_handles			/* INPUT  */
);

/**
/* IMCC_MT_Handle_Allocate_Cfm
/* This notification message confirm the result of previous call  
/* imcc_handle_allocate_request().
*/
typedef struct _tag_Msg_Handle_Allocate_Cfm
{
	IMCC_Result				result;
	uint16					num_of_handles;	
	IMCC_Handle				first_handle;
} IMCC_Msg_Handle_Allocate_Cfm;

/**
/* imcc_parameter_update_request
/* This function is called by a user application to update the value of 
/* a registry parameter object.
*/
IMCC_Error imcc_parameter_update_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	boolean					uniform,				/* INPUT  */
	IMCC_Parameter_ID		parameter_id,			/* INPUT  */
	uint16					data_len,				/* INPUT  */
	uint8*					data					/* INPUT  */
);

/**
/* IMCC_MT_Parameter_Update_Ind
/* This notification message indicate that a parameter object has been updated.
*/
typedef struct _tag_Msg_Parameter_Update_Ind
{
	IMCC_Parameter_ID		parameter_id;
	uint16					data_len;
	uint8*					data;
} IMCC_Msg_Parameter_Update_Ind;

/**
/* imcc_counters_update_request
/* This function is called by a user application to update(reset, increase or 
/* decrease) the value of a registry counter elements.
/*
/* If the highest bit of the index of the IMCC_Counters_Update_Item is set, it 
/* request to reset the value of the counter element with the requested value.
*/
typedef struct 
{
	uint16	index;
	int32	value;
} IMCC_Counters_Update_Item;

#define IMCC_COUNTERS_UPDATE_RESET 0x8000

IMCC_Error imcc_counters_update_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	IMCC_Counters_ID		counters_id,			/* INPUT  */
	uint16					num_of_update_items,	/* INPUT  */
	IMCC_Counters_Update_Item* update_items			/* INPUT  */
);

/**
/* IMCC_MT_Counters_Update_Ind
/* This notification message indicate that a counter has been updated.
*/
typedef struct _tag_Msg_Counters_Update_Ind
{
	IMCC_Counters_ID		counters_id;
	uint16					num_of_update_items;
	IMCC_Counters_Update_Item* update_items;
} IMCC_Msg_Counters_Update_Ind;

/**
/* imcc_edit_update_request
/* This function is called by a user application to reset/insert/replace/append 
/* the content of a edit object.
*/
IMCC_Error imcc_edit_update_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	boolean					uniform,				/* INPUT  */
	IMCC_Edit_ID			edit_id,				/* INPUT  */
	uint32					begin_position,			/* INPUT  */
	uint32					end_position,			/* INPUT  */
	uint8*					edit_data,				/* INPUT  */
	uint32					edit_data_length		/* INPUT  */
);

/**
/* IMCC_MT_Edit_Update_Ind
/* This notification message indicate that a edit object has been updated.
*/
typedef struct _tag_Msg_Edit_Update_Ind
{
	IMCC_Edit_ID			edit_id;
	uint32					begin_position;
	uint32					end_position;
	uint8*					edit_data;
	uint32					edit_data_length;
} IMCC_Msg_Edit_Update_Ind;

/**
/* imcc_queue_add_item_request
/* This function is called by a user application to push a new item 
/* back into a specified queue object.
*/
IMCC_Error imcc_queue_add_item_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	boolean					uniform,				/* INPUT  */
	IMCC_Queue_ID			queue_id,				/* INPUT  */
	uint8					num_of_items,			/* INPUT  */
	IMCC_Queue_Item**		items					/* INPUT  */
);

/**
/* IMCC_MT_Queue_Add_Item_Ind
/* This notification message indicate that a item is added into the specified 
/* queue.
*/
typedef struct _tag_Msg_Queue_Add_Item_Ind
{
	IMCC_Queue_ID			queue_id;
	uint8					num_of_items;
	IMCC_Queue_Item**		items;
} IMCC_Msg_Queue_Add_Item_Ind;


/**
/* imcc_queue_remove_item_request
/* This function is called by a user application to remove a specified item
/* from the specified queue object.
*/
IMCC_Error imcc_queue_remove_item_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Priority			priority,				/* INPUT  */
	boolean					uniform,				/* INPUT  */
	IMCC_Queue_ID			queue_id,				/* INPUT  */
	IMCC_Node_ID			item_sender_id,			/* INPUT  */
	uint16					item_sequence_number	/* INPUT  */
);

/**
/* IMCC_MT_Queue_Remove_Item_Ind
/* This notification message indicate that a item is removed from the specified 
/* queue.
*/
typedef struct _tag_Msg_Queue_Remove_Item_Ind
{
	IMCC_Queue_ID			queue_id;
	IMCC_Node_ID			item_sender_id;
	uint16					item_sequence_number;
} IMCC_Msg_Queue_Remove_Item_Ind;

/**
/* imcc_cache_set_data_request
/* This function is called by a user application to updload the cache data
*/
IMCC_Error imcc_cache_set_data_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Cache_ID			cache_id,				/* INPUT  */
	uint16					cache_data_index,		/* INPUT  */
	uint32					cache_data_tag,			/* INPUT  */
	uint32					cache_data_len,			/* INPUT  */
	uint8*					cache_data				/* INPUT  */
);

/**
/* IMCC_MT_Cache_Set_Data_Ind
/* This notification message indicate that a cache data is registered to specified 
/* cache
*/
typedef struct _tag_Msg_Cache_Set_Data_Ind
{
	IMCC_Cache_ID			cache_id;
	uint16					cache_data_index;
	uint32					cache_data_tag;
} IMCC_Msg_Cache_Set_Data_Ind;

/**
/* IMCC_MT_Cache_Data_Ready_Ind
/* This notification message indicate that a cache data is ready for download
*/
typedef struct _tag_Msg_Cache_Data_Ready_Ind
{
	IMCC_Cache_ID			cache_id;
	uint16					num_of_cache_indices;
	uint16*					cache_data_index_list;
} IMCC_Msg_Cache_Data_Ready_Ind;

/**
/* imcc_cache_set_data_first_request
/* This function is called by a user application to adjust the specified 
/* pending set-caches to the top
*/
IMCC_Error imcc_cache_set_data_first_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Cache_ID			cache_id,				/* INPUT  */
	uint8					user_data_len,			/* INPUT  */
	uint8*					user_data,				/* INPUT  */
	uint8					num_of_cache_indices,	/* INPUT  */
	uint16*					cache_data_index_list	/* INPUT  */
);

/**
/* imcc_cache_set_data_cancel_request
/* This function is called by a user application to cancel the specified 
/* pending set-caches to the top
*/
IMCC_Error imcc_cache_set_data_cancel_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Cache_ID			cache_id,				/* INPUT  */
	uint16					cache_data_index		/* INPUT  */
);

/**
/* IMCC_MT_Cache_Set_Data_First_Ind
/* This notification message indicate that the specified cache data is 
/* adjusted to the top in the uploading/downloading order
*/
typedef struct _tag_Msg_Cache_Set_Data_First_Ind
{
	IMCC_Cache_ID			cache_id;
	uint8					user_data_length;
	uint8*					user_data;
	uint8					num_of_cache_indices;
	uint16*					cache_data_index_list;
} IMCC_Msg_Cache_Set_Data_First_Ind;

/**
/* imcc_cache_get_data_request
/* This function is called by a user application to get the specified 
/* cache data. it is valid only after applicaiton received message
/* IMCC_MT_Cache_Data_Ready_Ind about the specified cache data
*/
IMCC_Error imcc_cache_get_data_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Cache_ID			cache_id,				/* INPUT  */
	uint16					cache_data_index		/* INPUT  */
);

/**
/* IMCC_MT_Cache_Get_Data_Cfm
/* This notification message indicate that a cache data was downloaded
*/
typedef struct _tag_Msg_Cache_Get_Data_Cfm
{
	IMCC_Result				result;
	IMCC_Cache_ID			cache_id;
	uint16					cache_data_index;
	uint32					cache_data_length;
	uint8*					cache_data;
} IMCC_Msg_Cache_Get_Data_Cfm;

/**
/* IMCC_MT_Cache_Set_Data_Cfm
/* This notification message indicate that a cache data was successfully 
/* uploaded
*/
typedef struct _tag_Msg_Cache_Set_Data_Cfm
{
	IMCC_Result				result;
	IMCC_Cache_ID			cache_id;
	uint16					cache_data_index;
} IMCC_Msg_Cache_Set_Data_Cfm;

/**
/* imcc_cache_get_data_first_request
/* This function is called by a user application to adjust the specified 
/* local pending get-caches to the top
*/
IMCC_Error imcc_cache_get_data_first_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Cache_ID			cache_id,				/* INPUT  */
	uint8					num_of_cache_indices,	/* INPUT  */
	uint16*					cache_data_index_list	/* INPUT  */
);

/**
/* imcc_cache_data_get_cancel_request
/* This function is called by a user application to cancel a pending
/* get_caches issued by previous calls of imcc_cache_data_get_request().
/* if cache_data_index is 0, all the pending get_caches of cache with id 
/* as specified.
*/
IMCC_Error imcc_cache_data_get_cancel_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Cache_ID			cache_id,				/* INPUT  */
	uint16					cache_data_index		/* INPUT  */
);

/*****************************************************************************
/* IMCC General Registry Services related functions and messages
/*	imcc_registry_register_key_request
/*	imcc_registry_retrieve_key_request
/*	imcc_registry_delete_key_request
/*
/*	imcc_registry_register_obj_request
/*	imcc_registry_retrieve_obj_request
/*	imcc_registry_delete_obj_request
/*
/*	IMCC_Msg_Registry_Register_Key_Cfm
/*	IMCC_Msg_Registry_Register_Key_Ind
/*	IMCC_Msg_Registry_Retrieve_Key_Cfm
/*	IMCC_Msg_Registry_Delete_Key_Ind
/*
/*	IMCC_Msg_Registry_Register_Obj_Cfm
/*	IMCC_Msg_Registry_Register_Obj_Ind
/*	IMCC_Msg_Registry_Retrieve_Obj_Cfm
/*	IMCC_Msg_Registry_Delete_Obj_Ind
*****************************************************************************/

/**
/* imcc_registry_register_key_request
/* This function is called by a user application in order to register a 
/* registry key entry to be associated with a particular registry key.
*/
IMCC_Error imcc_registry_register_key_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Reg_Key_Name		key_name,				/* INPUT  */
	IMCC_Reg_Key_Attr		key_attr				/* INPUT  */
);

/**
/* IMCC_MT_Reg_Register_Key_Cfm
/* This notification message confirm if the previous call  
/* imcc_registry_register_key_request() is success or failed
*/
typedef struct _tag_Msg_Registry_Register_Key_Cfm
{
	char					key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID			key_id;
	IMCC_Result				result;
} IMCC_Msg_Registry_Register_Key_Cfm;

/**
/* IMCC_MT_Reg_Register_Key_Ind
/* This notification message indicate that a registry key has been 
/* registered to be associated with a particular registry key name.
*/
typedef struct _tag_Msg_Registry_Register_Key_Ind
{
	char					key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID			key_id;
	IMCC_Reg_Key_Attr		key_attr;
} IMCC_Msg_Registry_Register_Key_Ind;

/**
/* imcc_registry_retrieve_key_request
/* This function is called by a user application in order to determine the
/* contents of a specific key entry of the registry.
*/
IMCC_Error imcc_registry_retrieve_key_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Reg_Key_Name		key_name				/* INPUT  */
);

/**
/* IMCC_MT_Reg_Retrieve_Key_Cfm
/* This notification message return a user application in reply to a previous
/* call to imcc_registry_retrieve_key_request().
*/
typedef struct _tag_Msg_Registry_Retrieve_Key_Cfm
{
	char					key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID			key_id;
	IMCC_Reg_Key_Attr		key_attr;
	IMCC_Result				result;
} IMCC_Msg_Registry_Retrieve_Key_Cfm;

/**
/* imcc_registry_delete_key_request
/* This function may be called by a user application to remove a registry 
/* key entry. 
*/
IMCC_Error imcc_registry_delete_key_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Reg_Key_Name		key_name,				/* INPUT  */
	IMCC_Reg_Key_ID			key_id					/* INPUT  */
);

/**
/* IMCC_MT_Reg_Delete_Key_Ind
/* This notification message indicate that a registry key entry was deleted.
*/
typedef struct _tag_Msg_Registry_Delete_Key_Ind
{
	char					key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID			key_id;
} IMCC_Msg_Registry_Delete_Key_Ind;


/**
/* imcc_registry_register_obj_request
/* This function is called by a user application in order to register a 
/* registry object entry to be associated with a particular registry key.
*/
IMCC_Error imcc_registry_register_obj_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Reg_Key_Name		key_name,				/* INPUT  */
	IMCC_Reg_Key_ID			key_id,					/* INPUT  */
	uint16					number_of_objects,		/* INPUT  */
    IMCC_Reg_Object**		objects					/* INPUT  */
);

/**
/* IMCC_MT_Reg_Register_Obj_Cfm
/* This notification message confirm if the previous call  
/* imcc_registry_register_obj_request() is success or failed
*/
typedef struct
{
	IMCC_Reg_Obj_Type		obj_type;
	char					obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	uint32					obj_tag;
	IMCC_Reg_Object_ID		obj_id;
	IMCC_Result				result;
} IMCC_Reg_Object_Cfm;

typedef struct _tag_Msg_Registry_Register_Obj_Cfm
{
	char					key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID			key_id;
	uint16					num_of_reg_object_cfms;
	IMCC_Reg_Object_Cfm*	reg_object_cfms;
} IMCC_Msg_Registry_Register_Obj_Cfm;

/**
/* IMCC_MT_Reg_Register_Obj_Ind
/* This notification message indicate that a registry object has been 
/* registered to be associated with a particular registry key.
*/
typedef struct _tag_Msg_Registry_Register_Obj_Ind
{
	char					key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID			key_id;
	uint16					number_of_objects;
    IMCC_Reg_Object**		objects;
} IMCC_Msg_Registry_Register_Obj_Ind;

/**
/* imcc_registry_retrieve_obj_request
/* This function is called by a user application in order to determine the
/* contents of a specific object entry of the registry.
*/
IMCC_Error imcc_registry_retrieve_obj_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Reg_Key_Name		key_name,				/* INPUT  */
	IMCC_Reg_Key_ID			key_id,					/* INPUT  */
	IMCC_Reg_Object_Name	obj_name				/* INPUT  */
);

/**
/* IMCC_MT_Reg_Retrieve_Obj_Cfm
/* This notification message return a user application in reply to a previous
/* call to imcc_registry_retrieve_obj_request().
*/
typedef struct _tag_Msg_Registry_Retrieve_Obj_Cfm
{
	char					key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID			key_id;
	char					obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	IMCC_Reg_Object*		object;
	IMCC_Result				result;
} IMCC_Msg_Registry_Retrieve_Obj_Cfm;

/**
/* imcc_registry_delete_obj_request
/* This function may be called by a user application to remove a obj_registry 
/* entry. 
*/
IMCC_Error imcc_registry_delete_obj_request(
	IMCC_User_Handle		user_h,					/* INPUT  */
	IMCC_Reg_Key_Name		key_name,				/* INPUT  */
	IMCC_Reg_Key_ID			key_id,					/* INPUT  */
	IMCC_Reg_Object_Name	obj_name,				/* INPUT  */
	IMCC_Reg_Object_ID		obj_id					/* INPUT  */
);

/**
/* IMCC_MT_Reg_Delete_Obj_Ind
/* This notification message indicate that a registry obj entry was deleted.
*/
typedef struct _tag_Msg_Registry_Delete_Obj_Ind
{
	char					key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID			key_id;
	char					obj_name[IMCC_MAX_REG_OBJ_NAME_LENGTH];
	IMCC_Reg_Object_ID		obj_id;
} IMCC_Msg_Registry_Delete_Obj_Ind;

/*****************************************************************************
* IMCC Filter related funcitons and messages
*	imcc_filter_attach_request
*	imcc_filter_detach_request
*****************************************************************************/

typedef void* IMCC_FC_Queue;
typedef void* IMCC_FC_Packet;

typedef boolean (* IMCC_Filter_FC_Alarm_Handler)(
	IMCC_Priority			priority,
	uint16					flag,
	IMCC_FC_Queue			queue);

void imcc_filter_alarm_handler_attach_request(
	IMCC_Priority			priority,
	IMCC_Filter_FC_Alarm_Handler handler);

void imcc_filter_alarm_handler_detach_request(
	IMCC_Priority			priority,
	IMCC_Filter_FC_Alarm_Handler handler);

uint32 IMCC_Queue_Get_Buffer_Size(
	IMCC_FC_Queue			queue);

uint32 IMCC_Queue_Get_Delay_Time(
	IMCC_FC_Queue			queue);

IMCC_FC_Packet IMCC_Queue_Get_Head(
	IMCC_FC_Queue			queue);

IMCC_FC_Packet IMCC_Queue_Get_Tail(
	IMCC_FC_Queue			queue);

IMCC_FC_Packet IMCC_Queue_Get_Next(
	IMCC_FC_Queue			queue,
	IMCC_FC_Packet			packet);

IMCC_FC_Packet IMCC_Queue_Get_Previous(
	IMCC_FC_Queue			queue,
	IMCC_FC_Packet			packet);

IMCC_FC_Packet IMCC_Queue_Erase_Packet(
	IMCC_FC_Queue			queue,
	IMCC_FC_Packet			packet,
	uint8					return_flag);	//0: return next packet, 
											//1: return previous packet

uint8* IMCC_Packet_Get_Data(
	IMCC_FC_Packet			packet);

uint32 IMCC_Packet_Get_Length(
	IMCC_FC_Packet			packet);

uint8* IMCC_Packet_Get_Domain(
	IMCC_FC_Packet			packet);

/*****************************************************************************
* IMCC time utilities
*****************************************************************************/
uint32 imcc_server_time();

// usage:
// uint32 ltime = imcc_local_time(server_time);
// struct tm *mytime = localtime(ltime);
// 
uint32 imcc_local_time(uint32 server_time);


#ifdef __cplusplus
}
#endif

#endif /* __IMCCCORE_H__ */

