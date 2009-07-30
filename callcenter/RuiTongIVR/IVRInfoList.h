#pragma once

typedef struct _tagLINESTRUCT
{
    //int nType;
    //int State;
    //char CallerID[32];
    ////˫����Ƶ�ź�
    //char Dtmf[32];
    //int nTimeElapse;
    std::string szType;
    int iChannel;
    std::string szPhone;
    std::string szChannelStat;
}LINESTRUCT,*PLINESTRUCT;


class CIVRInfoList : public CListCtrl
{
	DECLARE_DYNAMIC(CIVRInfoList)

public:
	CIVRInfoList();
	virtual ~CIVRInfoList();

	// Attributes
public:
	CImageList m_cImageListSmall;


public:
	//���ô˺�����ʾ��Ϣ
	void InitChannel(int lineNum);
	//���õڼ���ͨ������Ϣ
	void SetItemStat(int line,LINESTRUCT* pLine);
	void  SetItemStat(int line,const std::string& phone,const std::string& channelStat);
protected:
	//��ʼ���б�ͷ
	void InitListCtrlCols( );
	//��ʼ��ͼ���б�
	void InitImageList(void);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysInfoList)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:
	DECLARE_MESSAGE_MAP()
};


