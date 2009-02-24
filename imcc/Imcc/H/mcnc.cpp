/*--------------------------------------------------------------------------*/
/*  MCNC.CPP                                                                */
/*                                                                          */
/*  History                                                                 */
/*      12/21/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#include "mcnc.h"
#include "mcreg.h"
#include "mcurl.h"

MC_Node_Controller* MC_Node_Controller::s_this = NULL;

#define TIMER_WNDCLASS "CenWaveTimerClass"

// 2008-01-29
// wengyc
// Deal with problem occured by _CRT_DEBUG_NEW
#ifndef _GNET_NO_DEBUG_NEW

#ifdef _DEBUG
#include <crtdbg.h>
#define new _CRT_DEBUG_NEW
#define _CRT_DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#endif // _GNET_NO_DEBUG_NEW

//uint32 g_last_tick_cnt = 0;
//uint32 g_timer_cnt = 0;

/////////////////////////////////////////////////////////////////////////////
// MyTimerWindowProc
//
LRESULT CALLBACK MyTimerWindowProc(HWND hWnd, UINT uMsg, 
    WPARAM wParam,LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_TIMER :
        {
            MC_Node_Controller* pNC = (MC_Node_Controller*)
                GetWindowLong(hWnd, 0);

			//uint32 now = get_tick_count();
			//char buf[123];
			//sprintf(buf, "tick=%lu", now);
			//OutputDebugString(buf);

			if(pNC)
				pNC->heartbeat();
        }
        break;

    default :
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////////////
// MC_Node_Controller
//
MC_Node_Controller::MC_Node_Controller()
: MC_Attached_Server_Engine("NC")
{
	MC_ASSERT(s_this == NULL);
	s_this = this;

    m_hWndTimer = NULL;
    m_idTimer = 0;
    m_hInstance = NULL;
}

MC_Node_Controller::~MC_Node_Controller()
{
	s_this = NULL;
	MC_ASSERT(m_hWndTimer == NULL);
}

IMCC_Error MC_Node_Controller::initialize(
		HINSTANCE				hInstance,
		IMCC_Device_Type		device_type,
		IMCC_OS_Type			os_type,
		IMCC_Net_Link_Type		net_link_type)
{
	if(s_this != NULL)
		return IMCC_ERROR_ALREADY_REGISTERED;

	s_this = new MC_Node_Controller();
	MC_ASSERT(s_this);

	set_reg_timer_engine(s_this);

    s_this->m_hInstance = hInstance;
    WNDCLASS wc;
    wc.style = 0;
    wc.lpfnWndProc = (WNDPROC)MyTimerWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(MC_Node_Controller*);
    wc.hInstance = (HINSTANCE)hInstance;
    wc.hIcon = (HICON)NULL;
    wc.hCursor = (HCURSOR)NULL;
    wc.hbrBackground = (HBRUSH)NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TIMER_WNDCLASS;

    RegisterClass(&wc);

    s_this->m_hWndTimer = CreateWindow(TIMER_WNDCLASS,
        NULL, WS_POPUP, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);
    if(s_this->m_hWndTimer)
    {
        SetWindowLong(s_this->m_hWndTimer, 0, (LONG)s_this);
        s_this->m_idTimer = ::SetTimer(s_this->m_hWndTimer, 101, 3, NULL);
    }
	else
        return IMCC_ERROR_UNKNOWN_ERROR;
    
	s_this->m_device_type = device_type;
	s_this->m_os_type = os_type;
	s_this->m_net_link_type = net_link_type;

	imcc_initialize(device_type, os_type, net_link_type);

	imcc_flow_control_config(IMCC_PRIORITY_SCREEN, 8000, 1024*1024);
	imcc_flow_control_config(IMCC_PRIORITY_VIDEO, 12000, 0);
	imcc_flow_control_config(IMCC_PRIORITY_AUDIO, 8000, 0);

	return IMCC_ERROR_SUCCESS;
}

IMCC_Error MC_Node_Controller::shutdown(uint32 timeout)
{
	if(!s_this) 
		return IMCC_ERROR_SUCCESS;

    if(s_this->m_idTimer)
        ::KillTimer(s_this->m_hWndTimer, s_this->m_idTimer);
    s_this->m_idTimer = NULL;

    if(s_this->m_hWndTimer)
        DestroyWindow(s_this->m_hWndTimer);
    s_this->m_hWndTimer = NULL;

    if(s_this->m_hInstance)
        UnregisterClass(TIMER_WNDCLASS, s_this->m_hInstance);
    s_this->m_hInstance = NULL;

	imcc_cleanup(timeout);
	set_reg_timer_engine(NULL);

	mcnet_url_cleanup();

	delete s_this;
	return IMCC_ERROR_SUCCESS;
}

void MC_Node_Controller::heartbeat()
{
	imcc_nc_heartbeat();
	MC_Attached_Server_Engine::heartbeat();
}
