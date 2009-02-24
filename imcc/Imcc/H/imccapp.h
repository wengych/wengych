#if !defined(IMCCAPP_H_INCLUDE_)
#define IMCCAPP_H_INCLUDE_

typedef	void *	HIMCCINSTANCE;

#define	CMR_APPWND_CLASS_NAME				"CenWaveClassroomMgr"
#define	CMR_NOTIFICATION_MESSAGE_STRING		"CenWaveNotificationMsg"

#define 	CMR_ENTER_MUTEX  "CenWaveClassEnterMutex"

// PostMessage(hNotificationWnd, CMR_NOTIFICATION_MESSAGE, CMR_NOTIFYMSG_PARAM, lParam)
#define	CMR_NOTIFYMSG_PARAM_HWND			1	// lParam is the window handle
#define	CMR_NOTIFYMSG_PARAM_LEAVING			2	// lParam is not used			
#define	CMR_NOTIFYMSG_PARAM_IE_CLOSE		WM_USER+101	// lParam is not used			


#define WEBVIEW_SEMP_NAME                       "CenWaveIeHlprSemp"
#define WEBVIEW_EVENT_NAME                      "CenWaveIeHlprEvent"
#define WEBVIEW_NOTIFY_MSG_NAME                 "CenWaveIeHlprNotifyMsgName"
#define WEBVIEW_NOTIFY_MSG_CLOSE                 "CenWaveIeHlprNotifyMsgClose"

#define WEBVIEW_HIDEWND_CLASS_NAME              "CenWaveWebViewHideWndCLassName"
#define IEHLPR_HIDEWND_CLASS_NAME               "CenWaveIeHlprHideWndCLassName"


#define CWSHELL_EVENT			"CWShellEvent"
#define CLASSCONS_EVENT			"ClassconsEvent"
#define NEWCLASSCONS_EVENT		"RunNewClassconsEvent"
#define NEWCLASSCONSBACK_EVENT		"RunNewClassconsBackEvent"


class IClassMgrCtrl
{
public:
	virtual void SetInfoBegin() = 0;
	virtual BOOL SetInfo(LPCSTR lpszInfoName, LPCSTR lpszInfoValue) = 0;
	virtual void SetInfoDone() = 0;
};


#endif // end of IMCCAPP_H_INCLUDE_