/*--------------------------------------------------------------------------*/
/*  MCCONFC.H                                                               */
/*                                                                          */
/*  History                                                                 */
/*      12/31/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCCONFC_H__)
#define __MCCONFC_H__

#include "imcccore.h"
#include "mcdef.h"
#include "mcreg.h"
#include "mcnc.h"
#include "mccoreref.h"
#include "mcurl.h"
#include "mcpingc.h"

#undef CONFCLI_API
#ifdef CONFCLI_EXPORTS
#define CONFCLI_API DLLEXPORT
#else
#define CONFCLI_API DLLIMPORT
#endif

#define MC_JOIN_CONF_MAX_UD_NUM			8
#define MC_PING_COUNT					4

//////////////////////////////////////////////////////////////////////////////
// Presence Structres
//
typedef struct _tag_sess_user_record
{
	uint32					user_data;
	IMCC_Node_ID			node_id;
	MC_Conf_Presence_Flag	user_presence_flag;
	MC_Conf_User_Status		user_status;
	MC_Conf_Capability		user_capability;
} MC_Sess_User_Record;

//////////////////////////////////////////////////////////////////////////////
// class diagram
//
class MC_Timer;
	class MC_Conference_Mgr;
	class MC_Conference;
	class MC_Session;

	class MC_Ping_Event_Handler;
	class MC_Ping_Mgr;

//////////////////////////////////////////////////////////////////////////////
// MC_Conference_Mgr
//
class CONFCLI_API MC_Conference_Mgr : public MC_Timer
{
	friend class MC_Conference;
public:
	MC_Conference_Mgr();
	virtual ~MC_Conference_Mgr();

public:
	virtual int initialize();
	virtual int cleanup(uint32 timeout);

	MC_Conference* get_conference(char* site_url, uint32 conf_id);

	static IMCC_Error imcc_callback(IMCC_User_Context context,
		IMCC_Msg_Type msg_type, void* msg);

	IMCC_Error on_conf_connect_ind(IMCC_Msg_Domain_Connect_Ind* msg);

	static MC_Conference_Mgr* s_this;

protected:
	void add_conference(MC_Conference* conf);
	void remove_conference(MC_Conference* conf);
	MC_Conference* get_conference(IMCC_Connection_Handle conn_h);
	MC_Conference* get_first_conference();

	MC_List<MC_Conference*>	m_conference_list;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Conference
//
class CONFCLI_API MC_Conference : public MC_Reg_Root, public MC_Ping_Event_Handler
{
public:
	MC_Conference(MC_Conference_Mgr* mgr);
	virtual ~MC_Conference();

	virtual void destroy();

public: // conference control functions
	int join_request(
		uint32					site_id,
		char*					site_url,
		uint32					conf_id,
		char*					conf_title,
		char*					user_name,
		uint32					user_log_id,
		MC_Conf_Capability		user_capability,
		boolean					be_public,
		char*					svr_addr,
		uint8					def_sess_num,
		MC_Conf_Session_Record*	def_sess_list,
		uint8					def_obj_num,
		IMCC_Reg_Object**		def_obj_list,
		uint16					auth_ticket_len,
		uint8*					auth_ticket);

	int terminate_request();
	int leave_request();

	int host_give_request(
		IMCC_Node_ID			receiver);

	int host_give_response(
		boolean					accept);

	int host_grab_request(
		char*					grab_key);

	int user_eject_request(
		IMCC_Node_ID			ejected_node_id);

	int lock_request(
		boolean					lock);

	int extend_request(
		IMCC_Time				time_requested);

	int time_inquire_request();

	int time_remaining_request(
		IMCC_Time				time_remaining,
		IMCC_Node_ID			dest_node_id);

	int user_message_send_request(
		IMCC_Node_ID			dest_node_id,
		uint16					msg_type,
		uint16					msg_data_length,
		uint8*					msg_data);

	int presence_change_request(
		MC_Conf_Presence_Flag	presence_flag,
		MC_Conf_User_Status		user_status,
		MC_Conf_Capability		user_capability
		);

	MC_Conf_User_Record* get_user_record(
		IMCC_Node_ID			user_node_id);

	MC_Session* get_session(
		MC_Session_ID			sess_id);

	boolean is_self_host();

	void get_host_id(IMCC_Node_ID& nid);

public :
	virtual void on_conf_join_cfm(
		IMCC_Result				result) {};

	virtual void on_conf_disconnect_ind(
		IMCC_Reason				reason)  {};

	virtual void on_conf_terminate_cfm() {}; 

	virtual void on_conf_terminate_ind(
		IMCC_Reason				reason) {};

	virtual void on_conf_host_give_cfm(
		IMCC_Result				result) {};

	virtual void on_conf_host_give_ind(
		IMCC_Node_ID			requestor_id) {};

	virtual void on_conf_host_grab_cfm(
		IMCC_Result				result) {};

	virtual void on_conf_host_change_ind(
		IMCC_Node_ID			old_host_id, 
		IMCC_Node_ID			grabber_id) {};

	virtual void on_conf_lock_report_ind(
		boolean					locked) {};

	virtual void on_conf_time_remaining_ind(
		IMCC_Time				rtime) {};

	virtual void on_conf_user_message_ind(
		uint16					msg_type,
		uint16					msg_data_length,
		uint8*					msg_data) {};

	virtual void on_conf_user_add_ind(
		MC_Conf_User_Record*	ur) {};

	virtual void on_conf_user_remove_ind(
		MC_Conf_User_Record*	ur) {};

	virtual void on_conf_user_modify_ind(
		IMCC_Roster_Update_Flag	update_flag, 
		MC_Conf_User_Record*	ur) {};

	virtual void on_session_invite_ind(
		MC_Session_ID			sess_id, 
		MC_Session_Type			sess_type, 
		uint8					sess_flag, 
		uint8					sess_info_length, 
		uint8*					sess_info) {};

	virtual void on_flow_control_rpt(
		char*					fc_msg) {};

	virtual void on_imcc_message(
		IMCC_Msg_Type			msg_type, 
		void*					msg) {};

	virtual void on_sys_log(
		uint16					log_level, 
		char*					msg) {};

	virtual void on_ping_progress_report(IMCC_Msg_Ping_Rpt* msg);

	virtual void on_ping_complete(char* best_server);

public :
	int cleanup();
	int connect_with_server();

	int session_register_request(MC_Session* session);
	int session_unregisger_request(MC_Session* session);
	int session_attach_request(MC_Session* session);
	int session_detach_request(MC_Session* session);
	int session_invite_request(MC_Session* session, uint16 num_of_node_ids,
		IMCC_Node_ID* node_id_list);

	static IMCC_Error MC_Conference::imcc_callback(
		IMCC_User_Context		context,
		IMCC_Msg_Type			msg_type, 
		void*					msg);

	void on_conf_connect_cfm(IMCC_Msg_Domain_Connect_Cfm* msg);
	void on_conf_disconnect_ind(IMCC_Msg_Domain_Disconnect_Ind* msg);
	void on_flow_control_alarm_ind(IMCC_Msg_Flow_Control_Alarm_Ind* msg);

	void on_conf_msg_data_ind(IMCC_Msg_Send_Data_Ind* msg);
	void on_conf_msg_conf_terminate_ind(uint8* msg, uint16 msg_length);
	void on_conf_msg_user_eject_ind(uint8* msg, uint16 msg_length);
	void on_conf_msg_lock_report_ind(uint8* msg, uint16 msg_length);
	void on_conf_msg_time_remaining_ind(uint8* msg, uint16 msg_length);
	void on_conf_msg_sess_invite_ind(uint8* msg, uint16 msg_length);
	void on_conf_msg_user_attach_cfm(IMCC_Msg_User_Attach_Cfm* msg);
	void on_conf_msg_user_detach_ind(IMCC_Msg_User_Detach_Ind* msg);
	void on_conf_msg_token_give_cfm(IMCC_Msg_Token_Give_Cfm* msg);
	void on_conf_msg_token_give_ind(IMCC_Msg_Token_Give_Ind* msg);
	void on_conf_msg_token_grab_cfm(IMCC_Msg_Token_Grab_Cfm* msg);
	void on_conf_msg_token_status_ind(IMCC_Msg_Token_Status_Change_Ind* msg);
	void on_conf_msg_table_insert_cfm(IMCC_Msg_Table_Insert_Cfm* msg);
	void on_conf_msg_table_insert_ind(IMCC_Msg_Table_Insert_Ind* msg);
	void on_conf_msg_table_update_ind(IMCC_Msg_Table_Update_Ind* msg);
	void on_conf_msg_table_delete_ind(IMCC_Msg_Table_Delete_Ind* msg);
	void on_conf_msg_roster_update_ind(IMCC_Msg_Roster_Update_Ind* msg);
	void on_conf_msg_parameter_update_ind(IMCC_Msg_Parameter_Update_Ind* msg);
	void on_conf_msg_reg_register_key_ind(IMCC_Msg_Registry_Register_Key_Ind* msg);
	void on_conf_msg_reg_register_obj_ind(IMCC_Msg_Registry_Register_Obj_Ind* msg);
	void on_conf_msg_reg_register_obj_cfm(IMCC_Msg_Registry_Register_Obj_Cfm* msg);

	char* get_site_url() { return m_site_url; }
	IMCC_Domain_ID get_conf_id() { return m_conf_id; }
	IMCC_Domain_Handle get_domain_h() { return m_domain_h; }
	IMCC_Connection_Handle	get_up_conn_h() { return m_conn_h; }
	IMCC_User_Handle get_user_h() { return m_user_h; }
	IMCC_Node_ID get_node_id() ;//{ return m_ur.node_id; }
	IMCC_Node_ID get_parent_node_id() { return m_parent_node; }
	IMCC_Node_ID get_top_node_id() { return m_top_node; }
	boolean is_conf_open_state() { return (m_state == _STATE_OPEN); }

protected:
	class _Roster : public MC_Reg_Roster
	{
	public :
		_Roster(MC_Conference* conf, MC_Reg_Key* parent_key, IMCC_Roster* roster);
		virtual ~_Roster();

		void destroy();
		void cleanup();

		void on_roster_update_ind(IMCC_Msg_Roster_Update_Ind* msg);
		MC_Conf_User_Record* get_user(IMCC_Node_ID nid);
	
	protected:
		class _MCU
		{
		public :
			_MCU(IMCC_MCU_ID mcu_id);
			virtual ~_MCU();

			void add_user(MC_Conf_User_Record* ur);
			void remove_user(IMCC_TERMINAL_ID tid);
			void remove_all();
			MC_Conf_User_Record* get_user(IMCC_TERMINAL_ID tid);

			IMCC_MCU_ID m_mcu_id;
			uint16 m_size;
			MC_Map<IMCC_TERMINAL_ID, MC_Conf_User_Record*> m_urs;
		};

		_MCU* get_mcu(IMCC_MCU_ID mcu_id, boolean create);
		void remove_mcu(IMCC_MCU_ID mcu_id);

		MC_Conference* m_conf;
		uint16 m_total_number;
		MC_Map<IMCC_MCU_ID, _MCU*> m_mcus;
	};

	class _Session_Table : public MC_Reg_Table
	{
		friend class MC_Conference;
	public :
		_Session_Table(MC_Conference* conf,	MC_Reg_Key* parent_key, IMCC_Table* table = NULL);
		virtual ~_Session_Table();
		void destroy();
		void cleanup();

		MC_Session* get_session(MC_Session_ID sess_id);
		int session_register_req(MC_Session* session);
		int session_unregister_req(MC_Session* session);
		int session_attach_req(MC_Session* session);
		int session_detach_req(MC_Session* session);

		void on_table_insert_cfm(IMCC_Msg_Table_Insert_Cfm* msg);
		void on_table_insert_ind(IMCC_Msg_Table_Insert_Ind* msg);
		void on_table_delete_ind(IMCC_Msg_Table_Delete_Ind* msg);

	protected:
		class _Session
		{
		public :
			_Session();
			virtual ~_Session();

			void encode(uint8* encode_buf, uint16& encode_buf_len);
			void decode(uint8* decode_buf, uint16 decode_buf_len);

			uint32			m_tag;
			MC_Session_Type	m_sess_type;
			uint8			m_sess_flag;
			uint8			m_sess_info_len;
			uint8*			m_sess_info;

			MC_Session*		m_session;
		};
		
		MC_Conference*		m_conf;
		MC_List<_Session*>	m_pending_sessions;
		MC_Array<_Session*>	m_sessions;
	};

	typedef enum {
		_STATE_IDLE = 0,
		_STATE_PINGING,
		_STATE_CONNECTING,
		_STATE_PREPARING,
		_STATE_OPEN,
		_STATE_CLOSING,
		_STATE_CLOSED
	} _State;

protected:
	MC_Conference_Mgr*		m_mgr;
	uint32					m_site_id;
	char					m_site_url[IMCC_MAX_SITE_URL_LEN];
	char					m_conf_title[IMCC_MAX_DOMAIN_DESC_LEN];
	IMCC_Domain_ID			m_conf_id;
	IMCC_Domain_Handle		m_domain_h;
	IMCC_Connection_Handle	m_conn_h;
	IMCC_User_Handle		m_user_h;
	_State					m_state;
	uint8					m_status_mask;
	char					m_svr_ip[IMCC_MAX_IP_ADDR];
	IMCC_User_Data_1		m_ud[MC_JOIN_CONF_MAX_UD_NUM];
	uint8					m_num_ud;
	
	MC_Conf_User_Record		m_ur;
	IMCC_Node_ID			m_parent_node;
	IMCC_Node_ID			m_top_node;

	MC_Conf_Privilege		m_privilege;

	MC_Reg_Key*				m_startup;
	MC_Reg_Token*			m_token_host;
	_Roster*				m_conf_roster;
	_Session_Table*			m_sess_table;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Session
//
class CONFCLI_API MC_Session: public MC_Timer
{
public :
	MC_Session(MC_Conference* conf);
	virtual ~MC_Session();

public :
	int create_request(
		MC_Session_Type			sess_type,
		uint8					sess_flag,
		uint8					sess_info_len,
		uint8*					sess_info,
		MC_Conf_Presence_Flag	presence_flag,
		MC_Conf_User_Status		user_status,
		MC_Conf_Capability		user_capability,
		uint8					presence_data_length,
		uint8*					user_presence_data);
	
	int join_request(
		MC_Session_ID			sess_id,
		MC_Session_Type			sess_type,
		uint8					sess_flag,
		uint8					sess_info_len,
		uint8*					sess_info,
		MC_Conf_Presence_Flag	presence_flag,
		MC_Conf_User_Status		user_status,
		MC_Conf_Capability		user_capability,
		uint8					presence_data_length,
		uint8*					user_presence_data);

	int terminate_request();
	
	int leave_request();

	int invite_request(
		uint16					num_of_node_ids,
		IMCC_Node_ID*			node_id_list);

	int presence_change_request(
		IMCC_Roster_Update_Flag	update_flag,
		MC_Conf_Presence_Flag	presence_flag,
		MC_Conf_User_Status		user_status,
		MC_Conf_Capability		user_capability,
		uint8					presence_data_length,
		uint8*					user_presence_data);

	MC_Sess_User_Record* get_sess_user(IMCC_Node_ID nid);

public :
	virtual void on_session_create_cfm(
		IMCC_Result				result) {};

	virtual void on_session_join_cfm(
		IMCC_Result				result) {};

	virtual void on_session_terminate_ind(
		IMCC_Reason				reason) {};

	virtual void on_imcc_message(
		IMCC_Msg_Type			msg_type, 
		void*					msg) {};

	virtual void on_flow_control_alarm_ind(
		IMCC_Priority			priority,
		uint16					delay_time,
		uint32					delay_buf_size,
		boolean					alarm_status) {};

public :
	// upper applicaiton need create the user record object
	virtual MC_Sess_User_Record* on_sess_user_add_ind(
		IMCC_Node_ID			node_id,
		MC_Conf_Presence_Flag	user_presence_flag,
		MC_Conf_User_Status		user_status,
		MC_Conf_Capability		user_capability,
		uint8					presence_data_length,
		uint8*					user_presence_data);

	// upper applicaiton need delete the user record object
	virtual void on_sess_user_remove_ind(
		MC_Sess_User_Record*	ur);

	// upper applicaiton need keep the user record object
	virtual void on_sess_user_modify_ind(
		MC_Sess_User_Record*	ur,
		IMCC_Roster_Update_Flag	update_flag,
		uint8					presence_data_length,
		uint8*					user_presence_data);

public :
	void cleanup();

	static IMCC_Error MC_Session::imcc_callback(IMCC_User_Context context,
		IMCC_Msg_Type msg_type, void* msg);

	void on_user_attach_cfm(IMCC_Msg_User_Attach_Cfm* msg);
	void on_user_detach_ind(IMCC_Msg_User_Detach_Ind* msg);

	void on_session_key_reg_ind(IMCC_Msg_Registry_Register_Key_Ind* msg);
	void on_session_key_reg_cfm(IMCC_Msg_Registry_Register_Key_Cfm* msg);
	void on_session_obj_reg_ind(IMCC_Msg_Registry_Register_Obj_Ind* msg);
	void on_session_obj_reg_cfm(IMCC_Msg_Registry_Register_Obj_Cfm* msg);
	void on_session_roster_update_ind(IMCC_Msg_Roster_Update_Ind* msg);
	
	void on_session_register_cfm(IMCC_Result result, MC_Session_ID sess_id);
	void on_session_unregister_ind();

	MC_Session_Type	get_sess_type() { return m_sess_type; }
	MC_Session_ID get_sess_id() { return m_sess_id; }
	void set_sess_id(MC_Session_ID sess_id) { m_sess_id = sess_id; }
	uint8 get_sess_flag() { return m_sess_flag; }
	boolean is_public() 
	{ return ((m_sess_flag&MC_SESS_FLAG_PUBLIC)==MC_SESS_FLAG_PUBLIC); }
	boolean has_roster()
	{ return ((m_sess_flag&MC_SESS_FLAG_HAS_ROSTER)==MC_SESS_FLAG_HAS_ROSTER); }
	uint8 get_sess_info_length() { return m_sess_info_len; }
	uint8* get_sess_info() { return m_sess_info; }
	boolean is_creator() { return m_is_creator; }
	MC_Reg_Key*	get_startup_key() { return m_startup; }
	IMCC_User_Handle get_user_h() { return m_user_h; }
	MC_Conference* get_owner_conference() { return m_conf; }

protected:
	class _Roster : public MC_Reg_Roster
	{
	public :
		_Roster(MC_Session* sess, MC_Reg_Key* parent_key, IMCC_Roster* roster);
		virtual ~_Roster();

		void destroy();
		void cleanup();

		void on_roster_update_ind(IMCC_Msg_Roster_Update_Ind* msg);
		MC_Sess_User_Record* get_user(IMCC_Node_ID nid);
	
	protected:
		class _MCU
		{
		public :
			_MCU(IMCC_MCU_ID mcu_id);
			virtual ~_MCU();

			void add_user(MC_Sess_User_Record* ur);
			void remove_user(IMCC_TERMINAL_ID tid);
			void remove_all();
			MC_Sess_User_Record* get_user(IMCC_TERMINAL_ID tid);

			IMCC_MCU_ID m_mcu_id;
			uint16 m_size;
			MC_Map<IMCC_TERMINAL_ID, MC_Sess_User_Record*> m_urs;
		};

		_MCU* get_mcu(IMCC_MCU_ID mcu_id, boolean create);
		void remove_mcu(IMCC_MCU_ID mcu_id);

		MC_Session* m_sess;
		uint16 m_total_number;
		MC_Map<IMCC_MCU_ID, _MCU*> m_mcus;
	};

protected :
	MC_Conference*	m_conf;
	MC_Session_Type	m_sess_type;
	MC_Session_ID	m_sess_id;
	uint8			m_sess_flag;
	uint8			m_sess_info_len;
	uint8*			m_sess_info;
	boolean			m_is_creator;

	IMCC_User_Handle	m_user_h;
	MC_Reg_Key*			m_startup;

	_Roster*				m_roster;
	MC_Conf_Presence_Flag	m_presence_flag;
	MC_Conf_User_Status		m_user_status;
	MC_Conf_Capability		m_user_capability;
	uint8					m_presence_data_length;
	uint8*					m_user_presence_data;
};

//////////////////////////////////////////////////////////////////////////////
// Utilities
//
void encode_reg_object(IMCC_Reg_Object*& obj, MC_Byte_Stream& os);
void decode_reg_object(IMCC_Reg_Object*& obj, MC_Byte_Stream& is);

#endif //__MCCONFC_H__

