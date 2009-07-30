#pragma once

typedef struct _tagLINESTRUCT
{
    //int nType;
    //int State;
    //char CallerID[32];
    ////双音多频信号
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
	//调用此函数显示信息
	void InitChannel(int lineNum);
	//设置第几个通道的信息
	void SetItemStat(int line,LINESTRUCT* pLine);
	void  SetItemStat(int line,const std::string& phone,const std::string& channelStat);
protected:
	//初始化列表头
	void InitListCtrlCols( );
	//初始化图象列表
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


