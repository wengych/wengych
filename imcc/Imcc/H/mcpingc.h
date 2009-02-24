/*--------------------------------------------------------------------------*/
/*  MCPINGC.H                                                               */
/*                                                                          */
/*  History                                                                 */
/*      12/31/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCPINGC_H__)
#define __MCPINGC_H__

#include "imcccore.h"
#include "mcdef.h"
#include "mcutil.h"

#undef CONFCLI_API
#ifdef CONFCLI_EXPORTS
#define CONFCLI_API DLLEXPORT
#else
#define CONFCLI_API DLLIMPORT
#endif

//////////////////////////////////////////////////////////////////////////////
// class diagram
//
class MC_Ping_Event_Handler;
class MC_Ping_Mgr;

//////////////////////////////////////////////////////////////////////////////
// MC_Ping_Event_Handler
//
class MC_Ping_Event_Handler
{
public:
	virtual void on_ping_progress_report(IMCC_Msg_Ping_Rpt* msg) = 0;
	virtual void on_ping_complete(char* best_server) = 0;
};

int CONFCLI_API mc_ping_request(char* server_list, 
								MC_Ping_Event_Handler* evt_handler,
								boolean ignore_single_server);
int CONFCLI_API mc_ping_cancel();

//////////////////////////////////////////////////////////////////////////////
// MC_Ping_Mgr
//

#if 0
class MC_Ping_Mgr
{
public :
	MC_Ping_Mgr();
	virtual ~MC_Ping_Mgr();

	int ping_request(char* server_list, MC_Ping_Event_Handler* evt_handler,
		boolean ignore_single_server);
	int ping_cancel();

public :
	static MC_Ping_Mgr* s_this;
	void on_ping_progress_report(IMCC_Msg_Ping_Rpt* msg);
	void on_ping_complete(char* best_server);

protected :
	int parse_server_list(char* server_list);
	int ping_next();
	
	typedef struct
	{
		boolean			m_primary;
		char			m_server_addr[IMCC_MAX_IP_ADDR];
		uint32			m_latency;
		uint32			m_down_thruput;
		uint32			m_up_thruput;
	} _Server;

protected :
	MC_List<_Server*>	m_ping_server_list;
	_Server*			m_best_server;
	_Server*			m_pinging_server;
	MC_Ping_Event_Handler* m_evt_handler;
	uint8				m_ping_flag;
};

#else

class MC_Ping_Mgr : public MC_Timer
{
public :
	MC_Ping_Mgr();
	virtual ~MC_Ping_Mgr();

	int ping_request(char* server_list, MC_Ping_Event_Handler* evt_handler,
		boolean ignore_single_server);
	int ping_cancel();

	void on_timer();

public :
	static MC_Ping_Mgr* s_this;
	void on_ping_progress_report(IMCC_Msg_Ping_Rpt* msg);
	void on_ping_complete(char* best_server);

protected :
	int parse_server_list(char* server_list);
	int ping_next();
	
	typedef enum 
	{
		PS_IDLE = 0,
		PS_TESTING,
		PS_COMPLETED
	} PING_STATE;

	typedef struct
	{
		IMCC_Ping_Handle	m_hping;
		boolean			m_primary;
		char			m_server_addr[IMCC_MAX_IP_ADDR];
		uint32			m_latency;
		PING_STATE		m_state;
	} _Server;

protected :
	MC_List<_Server*>	m_ping_server_list;
	_Server*			m_best_server;
	MC_Ping_Event_Handler* m_evt_handler;
	uint32				m_last_ping_tick;
};
#endif

#endif //__MCPINGC_H__

