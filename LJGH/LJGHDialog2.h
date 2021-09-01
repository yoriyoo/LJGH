#pragma once


// CLJGHDialog2 对话框

class CLJGHDialog2 : public CDialog
{
	DECLARE_DYNAMIC(CLJGHDialog2)

public:
	CLJGHDialog2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLJGHDialog2();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
