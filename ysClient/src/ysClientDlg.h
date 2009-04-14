// ysClientDlg.h : 头文件
//

#pragma once


// CysClientDlg 对话框
class CysClientDlg : public CDialog
{
    typedef CAutoPtr<CStatic> StaticPtr;
    typedef CAutoPtr<CEdit> EditPtr;
    typedef CAutoPtrArray<CStatic> StaticAutoPtrArray;
    typedef CAutoPtrArray<CEdit> EditAutoPtrArray;
public:
	CysClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YSCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

    void OnPrepareRequest();
    void OnSend();
    void OnExit();

    void OldSend();
    void NewSend();
    void OutputBusToFile(void*);
    BOOL GenerateHeadStruct(void*);
    void UpdateView(void*, int, void* bus = NULL);
    void UpdateViewOut(void*, void*);
    void UpdateViewIn(void* var_array);


// 实现
protected:
	HICON m_hIcon;
    SOCKET m_hSocket;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    // Connect to ys server
    void PrepareRequest();

    StaticAutoPtrArray m_pStaticIn;
    EditAutoPtrArray m_pEditIn;

    StaticAutoPtrArray m_pStaticOut;
    EditAutoPtrArray m_pEditOut;
};
