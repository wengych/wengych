// ysClientDlg.h : 头文件
//

#pragma once


// CysClientDlg 对话框
class CysClientDlg : public CDialog
{
// 构造
public:
	CysClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YSCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

    void OnConnect();
    void OnSend();
    void OnExit();

    void OldSend();
    void NewSend();
    void OutputBusToFile(void*);
    BOOL GenerateHeadStruct(void*);
    void UpdateView(void*, int);


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
    void Connect();
};
