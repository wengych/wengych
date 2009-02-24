/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  MCPHONEPDUC.H                                                           */
/*                                                                          */
/*  History                                                                 */
/*      08/10/2005     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2005 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#if !defined(__MCPHONEPDUC_H__)
#define __MCPHONEPDUC_H__

#include "mcphonedef.h"

//////////////////////////////////////////////////////////////////////////////
// registry define
//
// session_startup
//		|----"status" (parameter, uint8)
//		|----"call_list" (table)

#define MCP_REG_STATUS		"STATUS"
#define MCP_REG_CALL_LIST	"CALL_LIST"

#define MCP_CONF_STATUS_MASK		0x0f
#define MCP_CONF_RECORD_STATUS_MASK	0x80

#define MCP_REG_CL_FI_CNT	3

typedef enum {
	MCP_REG_CL_MUTE_STATUS = 0,
	MCP_REG_CL_PHONE_USER_NAME,
	MCP_REG_CL_PHONE_INFO,
} MCP_REG_CL_FI;

//////////////////////////////////////////////////////////////////////////////
// MCP_Sess_Info
//
class MCP_Sess_Info
{
public :
	MCP_Sess_Info() {}
	virtual ~MCP_Sess_Info() {}

	void encode(MC_Byte_Stream& os)
	{
		os<<conf_num<<host_pwd<<sess_flag;
	}

	void decode(MC_Byte_Stream& is)
	{
		is.read_string(conf_num, MAX_PHONE_CONF_NUM_LEN);
		is.read_string(host_pwd, MAX_PHONE_PASS_CODE_LEN);
		is >> sess_flag;
	}

	char conf_num[MAX_PHONE_CONF_NUM_LEN];
	char host_pwd[MAX_PHONE_PASS_CODE_LEN];
	uint8  sess_flag;
};

//////////////////////////////////////////////////////////////////////////////
// message define
//
typedef enum 
{
	MCPPT_RESTART_REQ = 1,
	MCPPT_CONF_CLOSE_REQ,
	MCPPT_CONF_REC_REQ,
	MCPPT_CALL_REQ,
	MCPPT_CALL_CFM,
	MCPPT_CALL_MUTE_REQ,
	MCPPT_CALL_KICKOFF_REQ,
	MCPPT_CALL_SETNAME_REQ,
	MCPPT_CALL_ACTIVE_IND,
} MCP_PDU_TYPE;

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu
//
class MCP_Pdu
{
public :
	virtual void encode(MC_Byte_Stream& os) = 0;
	virtual void decode(MC_Byte_Stream& is) = 0;
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Restart_Req
//
class MCP_Pdu_Restart_Req : public MCP_Pdu
{
public :
	MCP_Pdu_Restart_Req() {}
	virtual ~MCP_Pdu_Restart_Req() {}

	void encode(MC_Byte_Stream& os)
	{
		os<<conf_num<<host_pwd;
	}

	void decode(MC_Byte_Stream& is)
	{
		is.read_string(conf_num, MAX_PHONE_CONF_NUM_LEN);
		is.read_string(host_pwd, MAX_PHONE_PASS_CODE_LEN);
	}

	char conf_num[MAX_PHONE_CONF_NUM_LEN];
	char host_pwd[MAX_PHONE_PASS_CODE_LEN];
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Conf_Close_Req
//
class MCP_Pdu_Conf_Close_Req : public MCP_Pdu
{
public :
	MCP_Pdu_Conf_Close_Req() {}
	virtual ~MCP_Pdu_Conf_Close_Req() {}

	void encode(MC_Byte_Stream& os)
	{
		os << tag;
	}

	void decode(MC_Byte_Stream& is)
	{
		is >> tag;
	}

	uint16 tag; //0: stop the assocation, 1: stop phone conference
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Call_Req
//
class MCP_Pdu_Call_Req : public MCP_Pdu
{
public :
	MCP_Pdu_Call_Req() {}
	virtual ~MCP_Pdu_Call_Req() {}

	void encode(MC_Byte_Stream& os)
	{
		os << phone_num << pin_num << user_name;
	}

	void decode(MC_Byte_Stream& is)
	{
		is.read_string(phone_num, MAX_PHONE_NUM_LEN);
		is >> pin_num;
		is.read_string(user_name, MAX_PHONE_USER_NAME_LEN);
	}

	char	phone_num[MAX_PHONE_NUM_LEN];
	uint32	pin_num;
	char	user_name[MAX_PHONE_USER_NAME_LEN];
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Call_Cfm
//
class MCP_Pdu_Call_Cfm : public MCP_Pdu
{
public :
	MCP_Pdu_Call_Cfm() {}
	virtual ~MCP_Pdu_Call_Cfm() {}

	void encode(MC_Byte_Stream& os)
	{
		os << phone_num << result;
	}

	void decode(MC_Byte_Stream& is)
	{
		is.read_string(phone_num, MAX_PHONE_NUM_LEN);
		is >> result;
	}

	char		phone_num[MAX_PHONE_NUM_LEN];
	uint16		result;
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Call_Mute_Req
//
class MCP_Pdu_Call_Mute_Req : public MCP_Pdu
{
public :
	MCP_Pdu_Call_Mute_Req() {}
	virtual ~MCP_Pdu_Call_Mute_Req() {}

	void encode(MC_Byte_Stream& os)
	{
		os << rec_id << phone_num << mute_status;
	}

	void decode(MC_Byte_Stream& is)
	{
		is >> rec_id;
		is.read_string(phone_num, MAX_PHONE_NUM_LEN);
		is >> mute_status;
	}

	uint16	rec_id;
	char	phone_num[MAX_PHONE_NUM_LEN];
	boolean	mute_status;
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Call_Kickoff_Req
//
class MCP_Pdu_Call_Kickoff_Req : public MCP_Pdu
{
public :
	MCP_Pdu_Call_Kickoff_Req() {}
	virtual ~MCP_Pdu_Call_Kickoff_Req() {}

	void encode(MC_Byte_Stream& os)
	{
		os << rec_id << phone_num;
	}

	void decode(MC_Byte_Stream& is)
	{
		is >> rec_id;
		is.read_string(phone_num, MAX_PHONE_NUM_LEN);
	}

	uint16	rec_id;
	char	phone_num[MAX_PHONE_NUM_LEN];
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Call_Set_Name_Req
//
class MCP_Pdu_Call_Set_Name_Req : public MCP_Pdu
{
public :
	MCP_Pdu_Call_Set_Name_Req() {}

	virtual ~MCP_Pdu_Call_Set_Name_Req() {}

	void encode(MC_Byte_Stream& os)
	{
		os << rec_id << phone_num << user_name;
	}

	void decode(MC_Byte_Stream& is)
	{
		is >> rec_id;
		is.read_string(phone_num, MAX_PHONE_NUM_LEN);
		is.read_string(user_name, MAX_PHONE_USER_NAME_LEN);
	}

	uint16	rec_id;
	char	phone_num[MAX_PHONE_NUM_LEN];
	char	user_name[MAX_PHONE_USER_NAME_LEN];
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Conf_Record_Req
//
class MCP_Pdu_Conf_Record_Req : public MCP_Pdu
{
public :
	MCP_Pdu_Conf_Record_Req() {}
	virtual ~MCP_Pdu_Conf_Record_Req() {}

	void encode(MC_Byte_Stream& os)
	{
		os << record_status;
	}

	void decode(MC_Byte_Stream& is)
	{
		is >> record_status;
	}

	boolean	record_status;
};

//////////////////////////////////////////////////////////////////////////////
// MCP_Pdu_Call_Active_Ind
//
class MCP_Pdu_Call_Active_Ind : public MCP_Pdu
{
public :
	MCP_Pdu_Call_Active_Ind() {}
	virtual ~MCP_Pdu_Call_Active_Ind() {}

	void encode(MC_Byte_Stream& os)
	{
		os << rec_id << active_status;
	}

	void decode(MC_Byte_Stream& is)
	{
		is >> rec_id >> active_status;
	}

	uint16	rec_id;
	boolean	active_status;
};

#endif //__MCPHONEPDUC_H__
