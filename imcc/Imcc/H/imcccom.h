#if !defined (IMCCCOM_H_INCLUDE_)
#define IMCCCOM_H_INCLUDE_


typedef	struct tagRGB_COLOR
{
	BYTE	red;
	BYTE	green;
	BYTE	blue;
}RGB_COLOR;

#define		WM_LOADFILE		WM_USER+102

typedef	void *	HCOMINSTANCE;
typedef	long  CENWAVE_IID;

#define		CENWAVE_IID_CLASSMGR			0

#define		CENWAVE_IID_PRESENTATION		1
#define		CENWAVE_IID_COURSE				6
#define		CENWAVE_IID_DOCUMENT			11
#define		CENWAVE_IID_WHITEBOARD			12
#define		CENWAVE_IID_WEB					16
#define		CENWAVE_IID_VIDEO				21
#define		CENWAVE_IID_REMOTEVIDEO			22

#define		CENWAVE_IID_AUDIO				26
#define		CENWAVE_IID_SCREENSHARING		31
#define		CENWAVE_IID_CHAT				36
#define		CENWAVE_IID_QA					41
#define		CENWAVE_IID_TEST				46
#define		CENWAVE_IID_ATTENDEE			51
#define		CENWAVE_IID_CLASSINFO			52
#define		CENWAVE_IID_FILETRASFER			53
#define		CENWAVE_IID_POLL				54
#define		CENWAVE_IID_BULLETIN			55
#define		CENWAVE_IID_PHONE				56
#define		GNET_IID_NOTE					57
#define		GNET_IID_QUIZ					58

#define		CENWAVE_IID_AUDIOWIZARD			60

#define		CENWAVE_IID_ALL					0xFFFFFFFF

typedef	BOOL (WINAPI *COMPONENT_ENUM_PROC)(CENWAVE_IID ComID, LPARAM lParam);

#define	COM_CAP_USEPANEL		0x00000001
#define	COM_CAP_USEVIEW			0x00000002
#define	COM_CAP_MULTIINSTANCE	0x00000004	// Support multiple instance in one process
#define	COM_CAP_CREATESESSION	0x00000008  // This component can create session by itself

#define	COM_FLAG_NEEDONDDL	0x00000001	// Need on demand download

#define	CONSOLE_TOOLBAR_CHANGED		0x00000001
#define	CONSOLE_MENUBAR_CHANGED		0x00000002
#define	CONSOLE_STATUSBAR_CHANGED	0x00000003
#define	CONSOLE_LOGOBAR_CHANGED		0x00000004

#define	COM_TOOLBAR_WND_TAG			0x98923

#define PROG_TYPE_CLASS 	0x00000001
#define PROG_TYPE_CONF		0x00000002
#define CLASSMGR_CMD_ID_PCMOUT			286

typedef enum
{
	LAYOUT_MODEL_OLD   = 0x0001,
	LAYOUT_MODEL_NOMAL ,
	LAYOUT_MODEL_NOMAL_SUB_LARGE,	
	LAYOUT_MODEL_QA,
	LAYOUT_MODEL_QA_SUB_LARGE,
	
	LAYOUT_MODEL_CONF_MAIN,	
	LAYOUT_MODEL_CONF_V1,
	LAYOUT_MODEL_CONF_V4,
	LAYOUT_MODEL_CONF_V1_V5,
	LAYOUT_MODEL_CONF_V1_V7,		
	LAYOUT_MODEL_CONF_V9,
	LAYOUT_MODEL_CONF_V1_V9,
	LAYOUT_MODEL_CONF_V16,	
	
	LAYOUT_MODEL_LCD_CONF_V1,
	LAYOUT_MODEL_LCD_CONF_V2,
	LAYOUT_MODEL_LCD_CONF_V1_V2,
	LAYOUT_MODEL_LCD_CONF_V1_V3,
	LAYOUT_MODEL_LCD_CONF_V6,
	LAYOUT_MODEL_LCD_CONF_V12,

	LAYOUT_MODEL_CONF_SUB_V4,
	LAYOUT_MODEL_CONF_SUB_V4_1_3,	
	LAYOUT_MODEL_CONF_SUB_V16,
	LAYOUT_MODEL_CONF_V1_V4
	
}LAYOUT_MODEL;

#define	SEND_CMD_ERRORCODE_OK				0
#define	SEND_CMD_ERRORCODE_NOCOM		1
#define	SEND_CMD_ERRORCODE_NOTSUPPORT	2
#define	SEND_CMD_ERRORCODE_ERROR		3

#define	COMN_CMD_ID_BASE 256

#define CLASSMGR_CMD_ID_GETCONFINFO       256
#define CLASSMGR_CMD_ID_CLASS_VIDEOLARGE 257 
#define CLASSMGR_CMD_ID_SETPHONE2MGRHANDLE 258 
#define CLASSMGR_CMD_ID_SENDFILE_LOG	 259 //inputbuf1:send file path ;inputbuf2 : send file name 

// Define Cmd IDs of presentation component
#define	PS_CMD_ID_OPENFILE			257
#define	PS_CMD_ID_SAVEFILE			258
#define	PS_CMD_ID_SAVEALL			259
#define PS_CMD_ID_CLOSEFILE			260
#define PS_CMD_ID_CLOSEALL			261
#define PS_CMD_ID_ISFULLSCREEN	262
#define PS_CMD_ID_FULLSCREEN		263
#define PS_CMD_ID_EXITFULLSCREEN	264
#define PS_CMD_ID_ZOOM					265
#define PS_CMD_ID_FIRSTDOC			266
#define PS_CMD_ID_NEXTDOC			267
#define PS_CMD_ID_PREVIOUSDOC	268
#define PS_CMD_ID_LASTDOC			269
#define PS_CMD_ID_FIRSTPAGE			270
#define PS_CMD_ID_NEXTPAGE			271
#define PS_CMD_ID_PREVIOUSPAGE	272
#define PS_CMD_ID_LASTPAGE			273
#define PS_CMD_ID_NEXTSTEP			274
#define PS_CMD_ID_LASTSTEP			275

// Used for Video Snapshot
// lParam = (LPSTR) UserName
// lpInputBuffer1 is BITMAPINFO *
// lpInputBuffer2 is pBits
#define PS_CMD_ID_SNAPSHOT			276

// Define Cmd IDs of whiteboard component
// WB_CMD_ID_xxx is same as PS_CMD_ID_xxx.


// Define Cmd IDs of chat component

// Please put parameters information here
#define CHAT_CMD_ID_SENDMSG			256
#define CHAT_CMD_ID_SENDINFOMSG	257
// Only the host can do this
#define CHAT_CMD_ID_CLEARMSG		258
// Paste the text from the clipboard, then send
#define CHAT_CMD_ID_PASTESEND		259
// Export chat messages to a file
#define CHAT_CMD_ID_EXPORT				260

#define CHAT_CMD_ID_PRIVATECHAT	261

#define VIDEO_CMD_ID_SETVIDEO			256
#define VIDEO_CMD_ID_SETAUDIO			257
#define VIDEO_CMD_ID_SETVIDEOCYCLE	258
#define VIDEO_CMD_ID_ISVIDEOCYCLE		259


// Audio Commands
#define	AUDIO_CMD_ID_AUDIOWIZARD		256
// Input1 points IAudioWizardCallback
// Input2 points hParentWnd
#define AUDIO_CMD_ID_SETOUTVOLUME		257
// wParam is volume (0-100)
#define AUDIO_CMD_ID_SETINVOLUME			258
// wParam is volume (0-100)
#define AUDIO_CMD_ID_SETAUDIOINDEVICE	259
// lParam is the audio device name

#define AUDIO_CMD_ID_ENTERTWOWAYPRIVATECHAT		260
// EnterPrivateChat(IMCC_Node_ID WithWhom), lParam is WithWhom

#define AUDIO_CMD_ID_LEAVETWOWAYPRIVATECHAT		261
// LeavePrivateChat(IMCC_Node_ID WithWhom), lParam is WithWhom

#define AUDIO_CMD_ID_GETPRIVATECHATSTATUS			262
// lpOutputBuffer = &NodeID; dwBufferSize = sizeof(IMCC_Node_ID); lpdwOutputBufferSize = &dwBufferSize;

#define AUDIO_CMD_ID_FILLPCM					263
// lpInputBuffer1 is WAVEFORMATEX *
// dwInputBufferSize1 is sizeof(WAVEFORMATEX);
// lpInputBuffer2 is PCM data
// dwInputBufferSize2 is data size

#define AUDIO_CMD_ID_GETBITRATE					264
// wParam is bitrate
#define AUDIO_CMD_ID_SETBITRATE					265
// *(LPDWORD)lpInputBuffer1 = bitrate

#define  BULLETIN_CMD_ID_ADDSTRING      2008


#define  PHONE_CMD_ID_STARTCONF         256
#define  PHONE_CMD_ID_JOINCONF			257
#define  PHONE_CMD_ID_RESTARTCONF		258
#define  PHONE_CMD_ID_USERADDINI		259
#define  PHONE_CMD_ID_LEAVECONF			260
#define  PHONE_CMD_ID_CALLOUT			261
#define  PHONE_CMD_ID_CALLIN			262
#define  PHONE_CMD_ID_RECORD			263
#define  PHONE_CMD_ID_MUTE				264
#define  PHONE_CMD_ID_KICKOFF			265
#define  PHONE_CMD_ID_SETNAME			266
#define  PHONE_CMD_ID_GETPHONEUSER		   267
#define  PHONE_CMD_ID_GETPHONECONFSTATUS   268
#define  PHONE_CMD_ID_GETPHONERECORDSTATUS 269
#define  PHONE_CMD_ID_CLOSECONF            270
#define  PHONE_CMD_ID_NOPENCALLIN          271
#define	 PHONE2_CMD_ID_ADDUSER			   272
#define	 PHONE2_CMD_ID_REMOVEUSER		   273
#define	 PHONE2_CMD_ID_CHANGE_USER_MUTE_STATUS	   274
#define  PHONE2_CMD_ID_SETPHONE2EVENTHANDLER       275
#define  PHONE2_CMD_ID_SETAGENTID       276


#define CLASSINFO_CMD_ID_REFRESHCONFTIP    272

#define PHONE_CMD_ID_HASNAMECALLOUT		   273

#define CLASSINFO_CMD_ID_REFRESHCONFPIN    274

#define FILETRANSFER_CMD_ID_ON             275   

#define VIDEO_CMD_ID_OPENFILE              277      

#define ATTENDEE_CMD_ID_CLOSEMIC           278
#define ATTENDEE_CMD_ID_OPENMIC            279
#define ATTENDEE_CMD_ID_BEONVCHAT          300


/*
WPARAM: 1 Change Video Render Mode
		0 Resore Video Render Mode
*/
#define VIDEO_CMD_ID_CHANGERENDERMOD       301

/*
WPARAM: equal to the WM_DISPLAYCHANGE 's WPARAM
LPARAM: equal to the WM_DISPLAYCHANGE 's LPARAM
*/
#define VIDEO_CMD_ID_DISPLAYCHANGED			302
#define VIDEO_CMD_ID_SETCONFMONINFO			324

#define CLASSMGR_CMD_ID_ISPURETEXTCONF       303

//wParam
typedef enum
{
	SHARE_EVENT_STARTSHARE = 1,
	SHARE_EVENT_STOPSHARE,
	SHARE_EVENT_SWITCHOFF,
	SHARE_EVENT_SWITCHON,
	SHARE_EVENT_BEFORESTARTSHARE
}SHARE_EVENT;

#define CLASSMGR_CMD_ID_SHAREEVENT			280
#define CLASSMGR_CMD_ID_ISPHONECONF		281

#define CHAT_CMD_ID_SAVECONTENT             401      


class	IAudioWizardCallback
{
public:
	virtual BOOL	OnWizardBegin(HWND hWizardWnd) = 0;
	virtual void	OnWizardEnd(BOOL bOK) = 0;

	virtual void	OnBeginTestingSpeaker() = 0;
	virtual void	OnEndTestingSpeaker() = 0;
	virtual void	OnBeginTestingMic() = 0;
	virtual void	OnEndTestingMic() = 0;
};

typedef enum
{
	RECORD_STATE_START =0x0001,
	RECORD_STATE_PAUSE ,
	RECORD_STATE_STOP 
}RECORD_STATE;
	
#define RECORD_STATE_STOP 3

#define CUSTOMER_TYPE_PKU   0x00000001
#define CUSTOMER_TYPE_GNET  0x00000002
#define CUSTOMER_TYPE_KAHUA 0x00000003

typedef struct 
{
	char szSavePath[MAX_PATH];
	BOOL bFlagFullScreen;
}RECORD_INIT, *PRECORD_INIT;


class  IComEventHandler;

typedef struct tagCOMPONENT_INFO
{	
	DWORD	dwSize;
	CENWAVE_IID ComID;
	char	szComponentTitleName[128];	
	char	szComponentName[64]; 
	DWORD	dwCaps;
	DWORD	dwFlags;
	MC_Session_Type	SessionType;	// Session type is defined by IMCC
	DWORD	SessionTag;				// Session tag is a private data defined by the application
	DWORD	dwData;
	DWORD	dwReserved;	
}COMPONENT_INFO;

typedef struct	tagCOM_VISUAL_LAYOUT
{
	HWND 		hParentWnd;
	RECT		rcPos;
	HWND		hViewWnd;
	void		*pThis;	// This pointer is reserved
	int			nLayout;
//	HWND        hParentWnd2;
}COM_VISUAL_LAYOUT;

typedef struct tagCOM_CREATE_INFO
{
	DWORD		dwSize;
	COM_VISUAL_LAYOUT	VisualLayout;
	// For internal components, pIComMgr is the real CClassComMgr
	// Otherwise, pIComMgr should be cast to IComMgr *;
	void		*pIComMgr;	
	IComEventHandler *pIComEventHandler;
}COM_CREATE_INFO;

typedef	struct	tagCOM_INSTANCE_INFO
{
	CENWAVE_IID		ComID;
	HINSTANCE		hDllInstance;
	HCOMINSTANCE	hComInstance;
	COM_CREATE_INFO	ComCreateInfo;
	COMPONENT_INFO	ComponentInfo; 
	MC_Session_ID	SessionID;
}COM_INSTANCE_INFO;

typedef enum
{
	VIDEO_CODESTREAM_50K  =  0x00000001,
	VIDEO_CODESTREAM_75K  ,
	VIDEO_CODESTREAM_100K ,
	VIDEO_CODESTREAM_150K ,
	VIDEO_CODESTREAM_200K ,
	VIDEO_CODESTREAM_250K ,
	VIDEO_CODESTREAM_300K ,
	VIDEO_CODESTREAM_350K ,
	VIDEO_CODESTREAM_400K ,
	VIDEO_CODESTREAM_450K ,
	VIDEO_CODESTREAM_500K ,
	VIDEO_CODESTREAM_550K ,
	VIDEO_CODESTREAM_600K ,
	VIDEO_CODESTREAM_650K ,
	VIDEO_CODESTREAM_700K ,
	VIDEO_CODESTREAM_750K ,
	VIDEO_CODESTREAM_800K ,
	VIDEO_CODESTREAM_850K ,
	VIDEO_CODESTREAM_900K ,
	VIDEO_CODESTREAM_950K ,
	VIDEO_CODESTREAM_1000K 
}ENUM_VIDEO_CODESTREAM;


typedef enum
{
	VIDEO_WIDTH_160  =  0x00000001,
	VIDEO_WIDTH_176,
	VIDEO_WIDTH_320,
	VIDEO_WIDTH_352,
	VIDEO_WIDTH_640,
	VIDEO_WIDTH_704
}ENUM_VIDEO_WIDTH;



typedef struct tagCONF_LIMIT_INFO
{
	DWORD  dwConfType;
	DWORD  dwVideoMaxNum;
	DWORD  dwAudioMaxNum;
	DWORD  dwVideoFrameRate;
	DWORD  dwVideoCodeStream;
	DWORD  dwVideoWidth;	
	DWORD  dwVideoMaxCodeStream;
	DWORD  dwVideoPublicFlag;
}CONF_LIMIT_INFO;

typedef void     (CALLBACK* CBAuidoData)(char * pBuf,DWORD dwBufSize);

class IConsoleUIMgr
{
public:
	virtual	BOOL	GetToolBar(void **ppConsoleToolBar) = 0;
	virtual BOOL	GetStatusBar(void **ppStatusBarCtrl) = 0;
	virtual	void	CalcLayout(DWORD dwUIChangeFlag, void *pCtrl) = 0;
	virtual	RGB_COLOR *GetUserColorTable(UINT &nItems) = 0;
	virtual RGB_COLOR  GetMyColor() = 0;
	virtual RGB_COLOR  GetUserColor(IMCC_Node_ID UserID) = 0;
};

class IRoomMgr
{
public:
	virtual	BOOL	IsHost() = 0;
	virtual	BOOL	IsPresenter() = 0;
	virtual BOOL    IsAssistant() = 0;
	virtual BOOL    IsHasAssistant() = 0;
	virtual	IMCC_Node_ID 	GetHost() = 0;
	virtual	IMCC_Node_ID 	GetPresenter() = 0;
	virtual  void   GetConfPtr(void ** ppConf) = 0;

};

class IImccUser
{
public:
	virtual	MC_Conf_User_Record *GetUserRecord() = 0;
	virtual	BOOL	IsPresenter() = 0;
	virtual	BOOL	IsHost() = 0;
	virtual	BOOL	IsMyself() = 0;
};
class IUserMgr
{
public:
	virtual	int			GetUserCount() = 0;
	virtual IImccUser *	GetUser(int nIndex) = 0;
	virtual IImccUser *	GetUser(IMCC_Node_ID node_id) = 0;
};
class IComMgr
{
public:
	virtual	 BOOL	GetUIMgr(IConsoleUIMgr **ppIConsoleUIMgr) = 0;
	virtual	 BOOL	GetRoomMgr(IRoomMgr **ppIRoomMgr) = 0;
	virtual	 BOOL	GetUserMgr(IUserMgr **ppIUserMgr) = 0;
//	virtual  BOOL   GetConf(void ** ppConf) = 0;
	virtual	 HWND	GetFrameWnd(HCOMINSTANCE hComInstance) = 0; // The main window
	virtual	 void	ExitMe(HCOMINSTANCE hComInstance) = 0;		// Please unload me
	virtual	 void	YieldTime(HCOMINSTANCE hComInstance) = 0;		// I'm very busy.
	virtual	 BOOL	SwitchMeOn(HCOMINSTANCE hComInstance) = 0;

	virtual  void   PlusInVideoCamara(BOOL bPlusIn)		   = 0;  
	virtual  void   ShowClassInfoPage(int nCmdShow)        = 0;
	
	virtual	 void   SetAudioDataCBFunc(CBAuidoData pCBAuidoData) = 0;
	virtual	 void   SendFileTransfer(IMCC_Cache_ID cache_id) = 0;
	virtual	 void   SendFileTransferRequest(IMCC_Node_ID nodeId,IMCC_Cache_ID cache_id) = 0;
	virtual  DWORD  GetRecordState() = 0;

	virtual	 BOOL	SwitchOffCom(CENWAVE_IID ComID, HCOMINSTANCE hComInstance) = 0;
	virtual  BOOL	SwitchOnCom(CENWAVE_IID ComID, HCOMINSTANCE hComInstance ,BOOL bUpdate = TRUE) = 0;
	virtual  DWORD   GetCustomerType() = 0;
	virtual  DWORD   GetCurrentLayoutModel()=0;
	
	//virtual  void EnterAssistant(IMCC_Node_ID nodeId) = 0;
	virtual  void   SetUserAudioVolumn(IMCC_Node_ID nodeID , DWORD dwCur, DWORD dwMin = 0,DWORD dwMax= 100) = 0;
	virtual  void	EnableVideoFullScreen(BOOL  bFlag)     = 0;
	virtual  BOOL   IsVideoFullScreen() = 0;

	virtual  BOOL  UpdatePrivilegeToOne(IMCC_Node_ID NodeId,DWORD dwMask,DWORD dwPrivilege) = 0;
	virtual  BOOL  UpdatePrivilegeToAll(DWORD dwMask,DWORD dwPrivilege) = 0;	

	// Private CmdID defined by the component should be >256, otherwise they are common command 

	// Return value:
	// 0 = OK, otherwise, the following error code indicate
	// 1 = the component of ComID does not exist
	// 2 = the component rejects the command
	// ...
	// Above 256, it is error code defined by the component
	virtual LRESULT  SendCmdToCom(CENWAVE_IID ComID, DWORD CmdID, WPARAM wParam, LPARAM lParam,
								LPBYTE lpInputBuffer1, DWORD dwInputBufferSize1,
								LPBYTE lpInputBuffer2, DWORD dwInputBufferSize2,
								LPBYTE lpOutputBuffer, LPDWORD lpdwOutputBufferSize, LRESULT *pResult)=0;

   virtual   BOOL   IsUseSlaveScreen() = 0;
   virtual   BOOL   IsPureTextConf() = 0;
   virtual   char   GetWebConfig(DWORD dwPos) = 0;
 
};

class IComEventHandler
{
public:
	virtual	CENWAVE_IID			GetComID() = 0;
	virtual	COMPONENT_INFO *	GetComponentInfo()  = 0;

	virtual	 BOOL	OnBeforeChangePresenter(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) = 0;
	virtual	 BOOL	OnEndChangePresenter(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) = 0;
	virtual	 BOOL	OnBeforeChangeHost(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) = 0;
	virtual	 BOOL	OnEndChangeHost(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) = 0;
	virtual	 void	OnPreDomainExit(DWORD dwEstimateTime) = 0;
	virtual	 void	OnDomainIsExiting() = 0;
	virtual	 void	OnDomainReady(void *pConf) = 0;
	virtual	 void	OnDomainUser(BOOL bEnter, MC_Conf_User_Record*	ur) = 0;
	virtual	 BOOL	OnSwitchOff() = 0; // The component can reject switch off by return FALSE
	virtual	 BOOL	OnSwitchOn() = 0; 
	virtual  BOOL	OnShowControlMenu(LPRECT lprc) = 0;
	virtual  DWORD	OnWindowMessage(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) = 0;
	virtual  MC_Session *OnSessionInvite(void *pConf, MC_Session_ID sess_id, MC_Session_Type sess_type, uint8 sess_flag, uint8 sess_info_length, uint8* sess_info) = 0;
	virtual  MC_Session *OnSessionCreate(void *pConf) = 0; //Create session by yourself
	virtual  void	 OnSetPrivilege(DWORD) = 0;  
//	virtual  void    OnContentViewShow(DWORD dwMod,int nCmdShow) = 0;
	virtual  void    OnLayoutModalChange(DWORD layoutModelFrom,DWORD layoutModelTo) = 0;
	virtual  void    OnCalcLayout() = 0;
	virtual  void    OnCalcContentViewLayout() = 0;


	//FileTransfer
	virtual void OnSendFileTransfer(IMCC_Cache_ID cache_id) = 0;

	//
	//Record
	//
	virtual void     OnRecordInit(LPCTSTR lpszFileSavePath) = 0;
	virtual void     OnRecordStart() = 0;
	virtual void     OnRecordPause() = 0;
	virtual void     OnRecordStop()	 = 0;
	virtual void     OnSetAudioDataCBFunc(CBAuidoData pCBAuidoData) = 0;

	//audio
	virtual void	 OnUserAudioVolumn(IMCC_Node_ID	nodeID,DWORD dwCur, DWORD dwMin = 0,DWORD dwMax = 100) = 0;

	//video
	virtual HWND     GetComponentView(CENWAVE_IID comID) = 0;
	
    virtual void     OnEnterDualMonitor(BOOL bFlag)	= 0;

	virtual void	 OnPrivilegeChange(IMCC_Node_ID NodeID, DWORD dwPrivilege) = 0;   

	// Private CmdID defined by the component should be >256, otherwise they are common command 
	
	// Return value:
	// 0 = OK, otherwise, see the following error code
	// 1 = not defined
	// 2 = the command is rejected
	// Above 256, it is error code defined by the component
	virtual LRESULT  OnReceiveCmdToCom(CENWAVE_IID FromComID, DWORD CmdID, WPARAM wParam, LPARAM lParam,
								LPBYTE lpInputBuffer1, DWORD dwInputBufferSize1,
								LPBYTE lpInputBuffer2, DWORD dwInputBufferSize2,
								LPBYTE lpOutputBuffer, LPDWORD lpdwOutputBufferSize, LRESULT *pResult) = 0;

};

#define  BEGIN_CENWAVECOM_MAP(name) COMPONENT_INFO name[] = {
#define  CENWAVECOM_OBJECT(ComID, dwCaps, dwFlags, SessionType, SessionTag, szTitle, szName) { sizeof(COMPONENT_INFO), ComID, szTitle, szName, dwCaps, dwFlags, SessionType, SessionTag, 0, 0 } ,
#define  END_CENWAVECOM_MAP()	};

class CComCtrlBase : public IComEventHandler
{
public:
	CComCtrlBase() { memset(&m_ComCreateInfo, 0, sizeof(m_ComCreateInfo)); memset(&m_ComInfo, 0, sizeof(m_ComInfo)); };
	virtual ~CComCtrlBase()
	{ 
	};

	virtual BOOL		CreateCtrlView(COM_CREATE_INFO *ComCreateInfo) = 0;

	virtual	CENWAVE_IID			GetComID() { return m_ComInfo.ComID; };
	virtual	COMPONENT_INFO *	GetComponentInfo() { return &m_ComInfo; };

	virtual	 BOOL	OnBeforeChangePresenter(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) { return TRUE; };
	virtual	 BOOL	OnEndChangePresenter(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) { return TRUE; };
	virtual	 BOOL	OnBeforeChangeHost(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) { return TRUE; };
	virtual	 BOOL	OnEndChangeHost(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) { return TRUE; };
	virtual	 void	OnPreDomainExit(DWORD dwEstimateTime) { return ; };
	virtual	 void	OnDomainIsExiting() { return ; };
	virtual	 void	OnDomainReady(void *pConf)  { return ; };
	virtual	 void	OnDomainUser(BOOL bEnter, MC_Conf_User_Record*	ur) { return ;};
	virtual	 BOOL	OnSwitchOff() { return TRUE; };
	virtual	 BOOL	OnSwitchOn()  { return TRUE; }; 
	virtual  BOOL	OnShowControlMenu(LPRECT lprc) { return TRUE; }; 
	virtual  DWORD	OnWindowMessage(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) { bHandled = FALSE; return 0; };
	virtual  MC_Session *OnSessionInvite(void *pConf, MC_Session_ID sess_id, MC_Session_Type sess_type, uint8 sess_flag, uint8 sess_info_length, uint8* sess_info) { return NULL; };
	virtual  MC_Session *OnSessionCreate(void *pConf) { return NULL; };
	virtual  void	OnSetPrivilege(DWORD) {};
	virtual void OnNotifyOtherPrivilegeChange(IMCC_Node_ID nodeid,DWORD dwPrivilege){ return;};
	//virtual  void    OnContentViewShow(DWORD dwMod,int nCmdShow){};
	virtual  void   OnLayoutModalChange(DWORD layoutModelFrom,DWORD layoutModelTo){};
	virtual  void   OnCalcLayout() {};
	virtual  void   OnCalcContentViewLayout() {};

	//FileTransfer
	virtual void OnSendFileTransfer(IMCC_Cache_ID cache_id){}

	//audio 
	virtual void OnUserAudioVolumn(IMCC_Node_ID	nodeID,DWORD dwCur, DWORD dwMin = 0,DWORD dwMax = 100){};
	
	//record
	virtual void     OnRecordInit(LPCTSTR lpszFileSavePath) {};
	virtual void     OnRecordStart() {};
	virtual void     OnRecordPause() {};
	virtual void     OnRecordStop()	 {};
	virtual void     OnSetAudioDataCBFunc(CBAuidoData pCBAuidoData) {};


	//video
	virtual HWND     GetComponentView(CENWAVE_IID comID){return (HWND)NULL;}	
	
	virtual void     OnEnterDualMonitor(BOOL bFlag){}
	virtual void	 OnPrivilegeChange(IMCC_Node_ID NodeID, DWORD dwPrivilege){};                                
	
	virtual LRESULT  OnReceiveCmdToCom(CENWAVE_IID FromComID, DWORD CmdID, WPARAM wParam, LPARAM lParam,
								LPBYTE lpInputBuffer1, DWORD dwInputBufferSize1,
								LPBYTE lpInputBuffer2, DWORD dwInputBufferSize2,
								LPBYTE lpOutputBuffer, LPDWORD lpdwOutputBufferSize, LRESULT *pResult)
	{
		return SEND_CMD_ERRORCODE_NOTSUPPORT; // The command is rejected
	}

	virtual BOOL IsHost(IMCC_Node_ID	nodeID = 0)
	{
		IComMgr *pIComMgr = (IComMgr *)m_ComCreateInfo.pIComMgr;
		if (pIComMgr)
		{
			IRoomMgr *pIRoomMgr = NULL;
			pIComMgr->GetRoomMgr(&pIRoomMgr);
			if (pIRoomMgr)
			{
				if (0 == nodeID)
					return pIRoomMgr->IsHost();
				else
					return (pIRoomMgr->GetHost() == nodeID);
			}
		}

		return FALSE;
	}

	virtual BOOL IsPresenter(IMCC_Node_ID	nodeID = 0)
	{
		IComMgr *pIComMgr = (IComMgr *)m_ComCreateInfo.pIComMgr;
		if (pIComMgr)
		{
			IRoomMgr *pIRoomMgr = NULL;
			pIComMgr->GetRoomMgr(&pIRoomMgr);
			if (pIRoomMgr)
			{
				if (0 == nodeID)
					return pIRoomMgr->IsPresenter();
				else
					return (pIRoomMgr->GetPresenter() == nodeID);
			}
		}

		return FALSE;
	}

	virtual BOOL IsAssistant()
	{
		IComMgr *pIComMgr = (IComMgr *)m_ComCreateInfo.pIComMgr;
		if (pIComMgr)
		{
			IRoomMgr *pIRoomMgr = NULL;
			pIComMgr->GetRoomMgr(&pIRoomMgr);
			if (pIRoomMgr)
				return pIRoomMgr->IsAssistant();
		}
		return FALSE;
	}

	virtual BOOL IsHasAssistant()
	{
		IComMgr *pIComMgr = (IComMgr *)m_ComCreateInfo.pIComMgr;
		if (pIComMgr)
		{
			IRoomMgr *pIRoomMgr = NULL;
			pIComMgr->GetRoomMgr(&pIRoomMgr);
			if (pIRoomMgr)
				return pIRoomMgr->IsHasAssistant();
		}
		return FALSE;
	}

public:
	COMPONENT_INFO		m_ComInfo;
	COM_CREATE_INFO		m_ComCreateInfo;
};

// component DLL exports these functions
extern "C"
{
BOOL 	WINAPI  GetComponentInfo(CENWAVE_IID ComID, COMPONENT_INFO *pComInfo); 
BOOL 	WINAPI 	EnumComponent(LPARAM lParam, COMPONENT_ENUM_PROC fnProc);
BOOL	WINAPI	IsComponentSupported(CENWAVE_IID ComID);
void 	WINAPI	DeleteComponentInstance(HCOMINSTANCE hComInstance);
HCOMINSTANCE WINAPI CreateComponentInstance(CENWAVE_IID ComID, COM_CREATE_INFO *ComCreateInfo); 
}

typedef BOOL 	(WINAPI  *GetComponentInfo_API)(CENWAVE_IID ComID, COMPONENT_INFO *pComInfo); 
typedef BOOL 	(WINAPI  *EnumComponent_API)(LPARAM lParam, COMPONENT_ENUM_PROC fnProc);
typedef BOOL	(WINAPI	 *IsComponentSupported_API)(CENWAVE_IID ComID);
typedef void 	(WINAPI	 *DeleteComponentInstance_API)(HCOMINSTANCE hComInstance);
typedef HCOMINSTANCE (WINAPI *CreateComponentInstance_API)(CENWAVE_IID ComID, COM_CREATE_INFO *ComCreateInfo); 

#endif //IMCCCOM_H_INCLUDE_
