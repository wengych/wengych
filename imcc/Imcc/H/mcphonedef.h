/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  MCPHONEDEF.H                                                            */
/*                                                                          */
/*  History                                                                 */
/*      08/10/2005     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2005 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#if !defined(__MCPHONEDEF_H__)
#define __MCPHONEDEF_H__

#include "imccdef.h"
#include "mcassert.h"
#include "mcmisc.h"
#include "mcbs.h"

#define MAX_PHONE_NUM_LEN		32
#define MAX_PHONE_CONF_NUM_LEN	16
#define MAX_PHONE_PASS_CODE_LEN	16
#define MAX_PHONE_USER_NAME_LEN	64

typedef enum {
	MCPCS_IDLE = 0,			// conference not start
	MCPCS_OPEN_PENDING,		// conference is starting
	MCPCS_OPEN_FAILED,		// conference start failed
	MCPCS_OPEN,				// conference started successfully. ready to use
	MCPCS_CLOSED,			// conference is alrady closed
} MCP_CONF_STATUS;

typedef enum {
	MCPUT_VISIT = 0,
	MCPUT_ATTENDEE,
	MCPUT_HOST,
} MCP_USER_TYPE;

typedef enum {
	MCPUMS_SPEAK = 0,
	MCPUMS_MUTE,
} MCP_USER_MUTE_STATUS;

#define MCP_SESS_FLAG_ALONE	0x0
#define MCP_SESS_FLAG_MIX	0x1

//////////////////////////////////////////////////////////////////////////////
// MCP_User
//
class MCP_User
{
public :
	MCP_User() {}
	virtual ~MCP_User() {}

	void encode(MC_Byte_Stream& os)
	{
		os<<m_phone_user_id<<m_phone_user_type<<m_pin_num<<m_phone_num;
	}

	void decode(MC_Byte_Stream& is)
	{
		is>>m_phone_user_id>>m_phone_user_type>>m_pin_num;
		is.read_string(m_phone_num, MAX_PHONE_NUM_LEN);
	}

	uint16	m_record_id;
	uint32	m_phone_user_id;
	uint8	m_phone_user_type;
	uint8	m_mute_status;
	uint32	m_pin_num;
	char	m_phone_num[MAX_PHONE_NUM_LEN];
	char	m_phone_user_name[MAX_PHONE_USER_NAME_LEN];
	uint32	m_context;
};

#endif // __MCPHONEDEF_H__