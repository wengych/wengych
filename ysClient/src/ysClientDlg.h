// ysClientDlg.h : ͷ�ļ�
//

#pragma once


// CysClientDlg �Ի���
class CysClientDlg : public CDialog
{
// ����
public:
	CysClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YSCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

    void OnConnect();
    void OnSend();
    void OnExit();

    void OldSend();
    void NewSend();
    void OutputBusToFile(void*);
    BOOL GenerateHeadStruct(void*);
    void UpdateView(void*, int);


// ʵ��
protected:
	HICON m_hIcon;
    SOCKET m_hSocket;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    // Connect to ys server
    void Connect();
};
