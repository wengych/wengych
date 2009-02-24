/*--------------------------------------------------------------------------*/
/*  MCNC.H                                                                  */
/*                                                                          */
/*  History                                                                 */
/*      12/21/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCNC_H__)
#define __MCNC_H__

#include "imcccore.h"
#include "mcutil.h"

#ifdef CONFCLI_EXPORTS
#define NODECONTROLLER_API DLLEXPORT
#else
#define NODECONTROLLER_API DLLIMPORT
#endif

//////////////////////////////////////////////////////////////////////////////
// class diagram
//
class MC_Node_Controller;

//////////////////////////////////////////////////////////////////////////////
// MC_Node_Controller
//
class NODECONTROLLER_API MC_Node_Controller : public MC_Attached_Server_Engine
{
public :
	MC_Node_Controller();
	virtual ~MC_Node_Controller();

public :
	static IMCC_Error initialize(
		HINSTANCE				instance_handle,
		IMCC_Device_Type		device_type,
		IMCC_OS_Type			os_type,
		IMCC_Net_Link_Type		net_link_type);

	static IMCC_Error shutdown(uint32 timeout);

	void heartbeat();

	IMCC_Device_Type	m_device_type;
	IMCC_OS_Type		m_os_type;
	IMCC_Net_Link_Type	m_net_link_type;

#if defined(WIN32)
    HWND				m_hWndTimer;
    UINT				m_idTimer;
    HINSTANCE			m_hInstance;
#endif

	static MC_Node_Controller* s_this;
};

#endif // __MCNC_H__
