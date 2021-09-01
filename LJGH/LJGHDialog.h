#pragma once


// CLJGHDialog 对话框

class CLJGHDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLJGHDialog)

public:
	CLJGHDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLJGHDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit6();
	//障碍物的信息
	int m_circlex;
	int m_circley;
	int m_circler;
	//起点信息
	int m_startx;
	int m_starty;
	//终点信息
	int m_finalx;
	int m_finaly;
};
