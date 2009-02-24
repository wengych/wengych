#pragma once
#include "stdafx.h"
#include "imcc_header/imcccom.h"

class CRoomMgr : public IRoomMgr
{
public:
	CRoomMgr() : m_pConf(NULL) {}
	BOOL	IsHost() {
		return TRUE;
	}
	BOOL	IsPresenter() {
		return TRUE;
	}
	BOOL	IsAssistant() {
		return TRUE;
	}
	BOOL	IsHasAssistant() {
		return TRUE;
	}
	IMCC_Node_ID	GetHost() {
		return 0;
	}
	IMCC_Node_ID	GetPresenter() {
		return 0;
	}
	void	GetConfPtr(void ** ppConf) {
		*ppConf = m_pConf;
	}
private:
	MC_Conference* m_pConf;
};
