/*--------------------------------------------------------------------------*/
/*  MCREG.H                                                                 */
/*                                                                          */
/*  History                                                                 */
/*      12/19/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCREG_H__)
#define __MCREG_H__

#include "imcccore.h"
#include "mcutil.h"
#include "mccoreref.h"

#if defined(CONFCLI_EXPORTS) || defined(CONFSVR_EXPORTS)
#define REGISTRY_API DLLEXPORT
#else
#define REGISTRY_API DLLIMPORT
#endif

//////////////////////////////////////////////////////////////////////////////
// utilities
//
REGISTRY_API void set_reg_timer_engine(MC_Server_Engine* reg_timer_engine);

//////////////////////////////////////////////////////////////////////////////
// class diagram
//

class MC_Object;
	class MC_Reg_Object;
		class MC_Reg_Parameter;
		class MC_Reg_Token;
		class MC_Reg_Pool;
		class MC_Reg_Table;
		class MC_Reg_Roster;
		class MC_Reg_Counter;
		class MC_Reg_Edit;
		class MC_Reg_Queue;
		class MC_Reg_Cache;
		class MC_Reg_Channel_Rsc;
	class MC_Reg_Key;
		class MC_Reg_Root;

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Object
//
class REGISTRY_API MC_Reg_Object : public MC_Timer
{
public :
	MC_Reg_Object(MC_Reg_Key* parent_key);
	virtual ~MC_Reg_Object();

	// called by application to delete this object
	// if global is set as TRUE, it will issue an object_delete message to 
	// delete this object in the whole domain. 
	// if global is set as FALSE, only the local object will be deleted
	virtual void destroy(boolean global = FALSE);

	// called by parent key to notify application that this object is deleted
	virtual void on_destroy();
	
	IMCC_Reg_Obj_Type get_obj_type();
	void set_obj_type(IMCC_Reg_Obj_Type obj_type);
	char* get_obj_name();
	void set_obj_name(char* obj_name);
	uint32 get_obj_tag();
	void set_obj_tag(uint32 obj_tag);
	IMCC_Reg_Object_ID get_obj_id();
	void set_obj_id(IMCC_Reg_Object_ID obj_id);
	IMCC_Priority get_data_priority();
	void set_data_priority(IMCC_Priority pri);
	boolean is_uniform();
	void set_uniform(boolean uniform);
	MC_Reg_Key* get_parent_key() { return m_parent_key; }
	void set_user_context(uint32 user_context) { m_user_context = user_context; }
	uint32 get_user_context() { return m_user_context; }

	virtual operator IMCC_Reg_Object*() = 0;
	virtual IMCC_Reg_Object* get_obj_attr() = 0;
	virtual void on_register_object_cfm(IMCC_Reg_Object_ID obj_id);
	
protected :
	MC_Reg_Key*	m_parent_key;
	uint32		m_user_context;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Parameter
//
class REGISTRY_API MC_Reg_Parameter : public IMCC_Parameter, public MC_Reg_Object
{
public :
	MC_Reg_Parameter(MC_Reg_Key* parent_key, IMCC_Parameter* parameter);
	MC_Reg_Parameter(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = FALSE, 
		IMCC_Priority data_priority = IMCC_PRIORITY_APP_CTRL);
	
	virtual ~MC_Reg_Parameter();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Parameter*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Parameter*)this); }

	void set_param(uint16 param_length, uint8* param);
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Channel_Rsc
//
class REGISTRY_API MC_Reg_Channel_Rsc : public IMCC_Channel_Rsc, public MC_Reg_Object
{
public :
	MC_Reg_Channel_Rsc(MC_Reg_Key* parent_key, IMCC_Channel_Rsc* chan_rsc);
	MC_Reg_Channel_Rsc(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = TRUE, IMCC_Priority data_priority = IMCC_PRIORITY_APP_CTRL);
	virtual ~MC_Reg_Channel_Rsc();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Channel_Rsc*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Channel_Rsc*)this); }
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Token
//
class REGISTRY_API MC_Reg_Token : public IMCC_Token, public MC_Reg_Object
{
public :
	MC_Reg_Token(MC_Reg_Key* parent_key, IMCC_Token* token);
	MC_Reg_Token(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = TRUE, IMCC_Priority data_priority = IMCC_PRIORITY_APP_CTRL);
	virtual ~MC_Reg_Token();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Token*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Token*)this); }

	boolean is_available() { return (IMCC_Token::status == IMCC_TOKEN_FREE); } 
	boolean is_grabbed() { return (IMCC_Token::status == IMCC_TOKEN_GRABBED); }
	boolean is_grabber(IMCC_Node_ID node_id)  { return (IMCC_Token::grabber == node_id); }
	void set_grabber(IMCC_Node_ID node_id) { grabber = node_id; }
	void set_grab_key(char* grab_key);
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Pool
//
class REGISTRY_API MC_Reg_Pool : public IMCC_Pool, public MC_Reg_Object
{
public :
	MC_Reg_Pool(MC_Reg_Key* parent_key, IMCC_Pool* pool);
	MC_Reg_Pool(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = TRUE, IMCC_Priority data_priority = IMCC_PRIORITY_APP_CTRL);
	virtual ~MC_Reg_Pool();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Pool*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Pool*)this); }

	boolean is_grabber() { return m_is_grabber; }
	void set_grabber(boolean is_grabber) { m_is_grabber = is_grabber; }

	void set_pool_size(uint16 size) { this->pool_size = size; }

	boolean m_is_grabber;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Table
//
class REGISTRY_API MC_Reg_Table : public IMCC_Table, public MC_Reg_Object 
{
public :
	MC_Reg_Table(MC_Reg_Key* parent_key, IMCC_Table* table);
	MC_Reg_Table(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = TRUE, IMCC_Priority data_priority = IMCC_PRIORITY_APP_CTRL);
	virtual ~MC_Reg_Table();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Table*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()
	{ return (IMCC_Reg_Object*)((IMCC_Table*)this); }

	void set_max_num_of_records(uint16 max_num_of_records) 
	{ this->max_num_of_records = max_num_of_records; }
	uint16 get_max_num_of_records() { return max_num_of_records; }
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Roster
//
class REGISTRY_API MC_Reg_Roster : public IMCC_Roster, public MC_Reg_Object
{
public :
	MC_Reg_Roster(MC_Reg_Key* parent_key, IMCC_Roster* roster);
	MC_Reg_Roster(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = FALSE, IMCC_Priority data_priority = IMCC_PRIORITY_APP_CTRL);
	virtual ~MC_Reg_Roster();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Roster*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Roster*)this); }
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Counter
//
class REGISTRY_API MC_Reg_Counter : public IMCC_Counters, public MC_Reg_Object
{
public :
	MC_Reg_Counter(MC_Reg_Key* parent_key, IMCC_Counters* counter = NULL);
	MC_Reg_Counter(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = TRUE, IMCC_Priority data_priority = IMCC_PRIORITY_APP_CTRL);
	virtual ~MC_Reg_Counter();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Counters*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Counters*)this); }

	void set_default_value(int32 default_value) 
	{ this->default_value = default_value; }
	int32 get_default_value() { return default_value; }

	void set_num_of_counter(uint16 num_of_counter) 
	{ this->num_of_counter = num_of_counter; }
	uint16 get_num_of_counter() { return num_of_counter; }
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Edit
//
class REGISTRY_API MC_Reg_Edit : public IMCC_Edit, public MC_Reg_Object 
{
public :
	MC_Reg_Edit(MC_Reg_Key* parent_key, IMCC_Edit* edit);
	MC_Reg_Edit(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = FALSE, IMCC_Priority data_priority = IMCC_PRIORITY_CHAT);
	virtual ~MC_Reg_Edit();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Edit*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Edit*)this); }
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Queue
//
class REGISTRY_API MC_Reg_Queue : public IMCC_Queue, public MC_Reg_Object 
{
public :
	MC_Reg_Queue(MC_Reg_Key* parent_key, IMCC_Queue* queue);
	MC_Reg_Queue(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = FALSE, IMCC_Priority data_priority = IMCC_PRIORITY_CHAT);
	virtual ~MC_Reg_Queue();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Queue*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Queue*)this); }

	void set_max_num_of_items(uint16 max_num_of_items) 
	{ this->max_num_of_items = max_num_of_items; }
	uint16 get_max_num_of_items() { return max_num_of_items; }
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Cache
//
class REGISTRY_API MC_Reg_Cache : public IMCC_Cache, public MC_Reg_Object
{
public :
	MC_Reg_Cache(MC_Reg_Key* parent_key, IMCC_Cache* cache);
	MC_Reg_Cache(MC_Reg_Key* parent_key, char* obj_name, uint32 obj_tag = 0, 
		boolean uniform = FALSE, IMCC_Priority data_priority = IMCC_PRIORITY_CACHE);
	virtual ~MC_Reg_Cache();

	virtual operator IMCC_Reg_Object*()
	{ return (IMCC_Reg_Object*)((IMCC_Cache*)this); }

	virtual IMCC_Reg_Object* get_obj_attr()  
	{ return (IMCC_Reg_Object*)((IMCC_Cache*)this); }
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Key
//
class REGISTRY_API MC_Reg_Key : public MC_Timer
{
public :
	MC_Reg_Key(MC_Reg_Key* parent_key, char* key_name, IMCC_Reg_Key_ID key_id);
	virtual ~MC_Reg_Key();

	// called by application to delete this key
	// if global is set as TRUE, it will issue an key_delete message to 
	// delete this key in the whole domain. 
	// if global is set as FALSE, only the local key will be deleted
	// if a key is deleted, all its child keys and child objects will also be
	// deleted with notified by on_destroy()
	virtual void destroy(boolean global = FALSE);

	// called by parent key to notify application that this key is deleted
	virtual void on_destroy();

	char* get_key_name() { return m_key_name; }
	IMCC_Reg_Key_ID get_key_id() { return m_key_id; }
	MC_Reg_Key* get_parent_key() { return m_parent_key; }
	IMCC_Reg_Permission get_permission();
	IMCC_Channel_ID	get_monitor_channel_id();
	IMCC_Node_ID get_owner_node_id();
	boolean is_monitor_channel_inherit() { return (m_key_attr.monitor_channel == 0); }
	IMCC_Reg_Key_Attr* get_key_attr() { return &m_key_attr; }
	void set_permission(IMCC_Reg_Permission permission) { m_key_attr.permission = permission; }
	void set_monitor_channel_id(IMCC_Channel_ID chan_id) { m_key_attr.monitor_channel = chan_id; }
	void set_owner_node_id(IMCC_Node_ID node_id) { m_key_attr.owner_node_id = node_id; }
	void set_user_context(uint32 user_context) { m_user_context = user_context; }
	uint32 get_user_context() { return m_user_context; }

	MC_Reg_Key* get_child_key(char* key_name);
	void add_child_key(MC_Reg_Key* key);
	void remove_child_key(MC_Reg_Key* key);
	void on_child_key_destroy(MC_Reg_Key* key);
	void clear_child_keys();

	MC_Reg_Object* get_child_object(char* obj_name);
	MC_Reg_Object* get_child_object(IMCC_Reg_Object_ID obj_id);
	void add_child_object(MC_Reg_Object* obj);
	void remove_child_object(MC_Reg_Object* obj);
	void on_child_object_register_confirmed(MC_Reg_Object* obj);
	void on_child_object_destroy(MC_Reg_Object* obj);
	void clear_child_objects();

	void on_register_key_cfm(IMCC_Reg_Key_ID key_id);

	MC_Reg_Root* get_reg_root();
	boolean is_reg_root();

	void set_user_handle(IMCC_User_Handle user_h) { m_user_handle = user_h; }
	IMCC_User_Handle get_user_handle();

protected :
	char						m_key_name[IMCC_MAX_REG_KEY_NAME_LENGTH];
	IMCC_Reg_Key_ID				m_key_id;
	IMCC_Reg_Key_Attr			m_key_attr;
	MC_Reg_Key*					m_parent_key;
	MC_List<MC_Reg_Key*>		m_child_keys;
	MC_Array<MC_Reg_Object*>	m_child_objs;
	MC_List<MC_Reg_Object*>		m_pending_child_objs;

	uint32						m_user_context;
	IMCC_User_Handle			m_user_handle;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Reg_Root
//
class REGISTRY_API MC_Reg_Root : public MC_Reg_Key
{
	friend class MC_Reg_Key;
public :
	MC_Reg_Root();
	virtual ~MC_Reg_Root();

	MC_Reg_Key* create_key(char* key_name, IMCC_Reg_Key_ID key_id = 0);
	MC_Reg_Key* get_parent_key(char* key_name);
	MC_Reg_Key* get_key(char* key_name);
	MC_Reg_Key* get_key(IMCC_Reg_Key_ID key_id);
	MC_Reg_Key* get_key(char* key_name, IMCC_Reg_Key_ID key_id);
	MC_Reg_Object* get_object(IMCC_Reg_Object_ID obj_id);
	MC_Reg_Object* get_object(IMCC_Reg_Key_ID key_id, char* obj_name);
	MC_Reg_Object* get_object(char* key_name, char* obj_name);

	MC_Reg_Token* get_token(IMCC_Token_ID obj_id);
	MC_Reg_Pool* get_pool(IMCC_Pool_ID obj_id);
	MC_Reg_Table* get_table(IMCC_Table_ID obj_id);
	MC_Reg_Roster* get_roster(IMCC_Roster_ID obj_id);
	MC_Reg_Parameter* get_parameter(IMCC_Parameter_ID obj_id);
	MC_Reg_Counter* get_counter(IMCC_Counters_ID obj_id);
	MC_Reg_Edit* get_edit(IMCC_Edit_ID obj_id);
	MC_Reg_Queue* get_queue(IMCC_Queue_ID obj_id);
	MC_Reg_Cache* get_cache(IMCC_Cache_ID obj_id);
	MC_Reg_Channel_Rsc* get_channel_rsc(IMCC_Channel_Rsc_ID obj_id);

	boolean is_same_key(char* key1_name, char* key2_name);

protected :
	void register_key(MC_Reg_Key* key);
	void unregister_key(MC_Reg_Key* key);
	
protected :
	MC_Array<MC_Reg_Key*>	m_keys;
};

#endif // __MCREG_H__