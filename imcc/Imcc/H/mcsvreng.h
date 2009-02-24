/*--------------------------------------------------------------------------*/
/*  MCSVRENG.H                                                              */
/*  Utility: Server Engine                                                  */
/*                                                                          */
/*  History                                                                 */
/*      11/26/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCSVRENG_H__)
#define __MCSVRENG_H__

/**
/* Platform definition and platform specific definitions
*/
#include "imccdef.h"
#include "mcobject.h"
#include "mcthread.h"
#include "mcarray.h"
#include "mclist.h"
#include "mcsdp.h"

#ifndef __cplusplus
#error This IMCC basic facility can only be used in C++
#endif

#if defined(UTIL_EXPORTS)
#define UTIL_EXPORT DLLEXPORT
#else
#define UTIL_EXPORT DLLIMPORT
#endif

#pragma warning( disable : 4251) 

/////////////////////////////////////////////////////////////////////////////
// Class diagram
//
class MC_Object;
	class MC_Poller;

class MC_ObjectX;
	class MC_Timer;

class MC_Server_Engine;
	class MC_Attached_Server_Engine;
	class MC_Attached_Server_EngineEx;
	class MC_Detached_Server_Engine;
	class MC_Detached_Server_EngineEx;

//////////////////////////////////////////////////////////////////////////////
// MC_Timer
//
#define MC_TIMER_TIMER_BIT		0x1
#define MC_TIMER_SCHEDULE_BIT	0x2

class UTIL_EXPORT MC_Timer : public MC_ObjectX
{
	friend class MC_Server_Engine;

public :
    MC_Timer(MC_Server_Engine* engine);
    virtual ~MC_Timer();

	virtual int set_timer(uint32 time_elapse);
	virtual void kill_timer();

	virtual int schedule(uint32 time_elapse, boolean reset = FALSE);
	virtual void schedule_cancel();

	virtual void on_timer() {}
	virtual void on_schedule() {}

	MC_Server_Engine* get_engine() { return m_engine; }

protected :
	MC_Server_Engine*	m_engine;
	uint32				m_timer_elapse;
	uint32				m_timer_start;
	uint32				m_schedule_elapse;
	uint32				m_schedule_start;
	uint8				m_timer_flag;

	MC_Timer*			m_prev;
	MC_Timer*			m_next;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Poller
//
#if defined(WIN32) && defined(_SERVER)
	#define MC_OP_READ		0
	#define MC_OP_WRITE		1
	#define MC_OP_ACCEPT	2

	#define MC_POLLER_NUM_RBUF		2
	#define MC_POLLER_NUM_WBUF		2
	#define MC_POLLER_BUF_LENGTH	4096
	#define MC_POLLER_HEAD_LENGTH	32

	typedef struct _MC_OVERLAPPED
	{
		OVERLAPPED		ol;
		MC_Poller*		poller;
		uint8			op_code;
		boolean			busy_flag;
		uint32			bytes_xfered;
		uint32			flags;
		sockaddr_in		addr;
		int				addr_len;
		WSABUF			wsabuf;
		uint16			buf_offset;
		uint8			buf[MC_POLLER_BUF_LENGTH];
	} MC_OVERLAPPED;
#endif

class UTIL_EXPORT MC_Poller : public MC_Object
{
	friend class MC_Detached_Server_EngineEx;
#if defined(WIN32) && defined(_SERVER)
	friend class MC_Detached_Server_EngineEx_WinSvr;
#endif

public :
    MC_Poller();
    virtual ~MC_Poller();
	virtual boolean overlap();

    virtual void set_sock_fd(MC_SOCKET sock_fd) { m_sock_fd = sock_fd; }
    virtual void set_mask(int32 mask) { m_mask = mask; }
    virtual void attach_engine(MC_Detached_Server_EngineEx* engine);
    virtual void detach_engine();

	virtual void on_poller_event(int32 revents, void* opt_data) {}

protected :
	MC_Detached_Server_EngineEx* m_engine;
	MC_SOCKET	m_sock_fd;
	int32		m_mask;
	int			m_se_index;

#if defined(WIN32) && defined(_SERVER)
	MC_OVERLAPPED	m_read_ol;
	MC_OVERLAPPED	m_write_ol;
#endif
};

//////////////////////////////////////////////////////////////////////////////
// MC_Server_Engine
//	Server engine prototype
//
#define MC_SVRENGINE_MAX_NAME_LEN	32
#define MC_POST_MSG_DELETE		0xFFFFFFFF
class UTIL_EXPORT MC_Server_Engine
{
public :
	MC_Server_Engine(char* engine_name);
	virtual ~MC_Server_Engine();

	static MC_Server_Engine* get_engine(char* engine_name);
	static int post_message(char* engine_name, MC_Object* actor, uint32 msg_type, void* msg_data);

	virtual int init(uint32 option_data);
	virtual int destroy(uint32 time_out);
	virtual int wakeup();

	virtual int set_timer(MC_Timer* timer_obj, uint32 time_elapse);
	virtual void kill_timer(MC_Timer* timer_obj);
	virtual int schedule(MC_Timer* schedule_obj, uint32 time_elapse, boolean reset);
	virtual void schedule_cancel(MC_Timer* schedule_obj);

	virtual int post_message(MC_Object* actor, uint32 msg_type, void* msg_data);
	virtual int post_deleting_object(MC_Object* actor);

	virtual char* get_engine_name() { return m_engine_name; }

protected:
	void check_out_timer();
	void pump_out_messages();

	struct _Message
	{
		MC_Object*	actor;
		uint32		msg_type;
		void*		msg_data;

		_Message*	next;
	};

	_Message* new_message();
	void free_message(_Message* msg);

protected:
	uint32		m_magic;
	char		m_engine_name[MC_SVRENGINE_MAX_NAME_LEN];

	uint32		m_timer_last_tick_cnt;
	MC_Timer*	m_timer_head; 
	MC_Timer*	m_timer_tail; 
	MC_Timer*	m_timer_last_tail; 
	MC_Critical_Section m_timer_cs;

	struct	_Message*	m_msgq_head; 
	struct	_Message*	m_msgq_tail; 
	struct	_Message*	m_msg_free_list;
	struct	MC_Plex*	m_msg_blocks;
	uint32				m_msg_size;
	MC_Critical_Section m_msg_cs;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Attached_Server_Engine
//	Server engine attached to an external thread and need driven by the 
//	external heartbeat
//
class UTIL_EXPORT MC_Attached_Server_Engine : public MC_Server_Engine
{
public :
	MC_Attached_Server_Engine(char* engine_name);
	virtual ~MC_Attached_Server_Engine();

	virtual void heartbeat();
};

//////////////////////////////////////////////////////////////////////////////
// MC_Attached_Server_EngineEx
//	Server engined attached to an external thread with heartbeat driven 
//	internally
//	
class UTIL_EXPORT MC_Attached_Server_EngineEx : public MC_Server_Engine
{
public :
	MC_Attached_Server_EngineEx(char* engine_name);
	virtual ~MC_Attached_Server_EngineEx();

	virtual void run();
	virtual int stop(uint32 timeout);
	virtual int wakeup(); 

protected:
	boolean is_self_thread();

	MC_Event	m_wait_event;
	boolean		m_stop_flag;

#if defined(WIN32)
    uint32			m_thread_id;
#elif defined(LINUX) || defined(UINX)
    THREAD_HANDLE	m_thread_handle;
#endif
};

//////////////////////////////////////////////////////////////////////////////
// MC_Detached_Server_Engine 
//	Server engined running in a detached thread
//
class UTIL_EXPORT MC_Detached_Server_Engine : public MC_Server_Engine
, public MC_Thread
{
public :
	MC_Detached_Server_Engine(char* engine_name);
	virtual ~MC_Detached_Server_Engine();

	void start();
    virtual uint32 thread_run();

	virtual int stop(uint32 timeout);
	virtual int wakeup(); 

protected:
	MC_Event	m_wait_event;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Detached_Server_EngineEx
//	Server engined running in a detached thread with poller support
//	
class UTIL_EXPORT MC_Detached_Server_EngineEx : public MC_Server_Engine
, public MC_Thread
{
public :
	MC_Detached_Server_EngineEx(char* engine_name);
	virtual ~MC_Detached_Server_EngineEx();

	virtual int init(uint32 option_data);
	virtual int destroy(uint32 time_out);

	void start();
    virtual uint32 thread_run();

	virtual int stop(uint32 timeout);
	virtual int wakeup(); 

	virtual int attach_poller(MC_Poller* poller_obj);
	virtual int detach_poller(MC_Poller* poller_obj);
	virtual boolean overlap() { return FALSE; }

protected:
	virtual boolean poller_wait_event();

#if defined(WIN32)
	WSAEVENT*			m_wsaevents;
#elif defined(UNIX) || defined(LINUX)
	int					m_epfd;
#endif

	MC_Poller**			m_poller_objects;
	int					m_poller_num_allocaed;
	int					m_poller_num_used;
	int					m_poller_num_grow;
	int					m_poller_num_loop_cnt;
};

#if defined(WIN32) && defined(_SERVER)
//////////////////////////////////////////////////////////////////////////////
// MC_Detached_Server_EngineEx_WinSvr
//
//	
class UTIL_EXPORT MC_Detached_Server_EngineEx_WinSvr : public MC_Detached_Server_EngineEx
{
public :
	MC_Detached_Server_EngineEx_WinSvr(char* engine_name);
	virtual ~MC_Detached_Server_EngineEx_WinSvr();

	virtual int init(uint32 option_data);
	virtual int destroy(uint32 time_out);

	virtual int attach_poller(MC_Poller* poller_obj);
	virtual int detach_poller(MC_Poller* poller_obj);

	virtual boolean overlap() { return TRUE; }
protected:
	virtual boolean poller_wait_event();

	HANDLE				m_hiocp;
	OVERLAPPED			m_wakeup_ol;
	//MC_Poller*		m_poller_header;
};
#endif

//////////////////////////////////////////////////////////////////////////////
// inline functions
//	
inline boolean MC_Poller::overlap() { return m_engine->overlap(); }

#endif // __MCSVRENG_H__
