#pragma once


// CLJGHDialog2 �Ի���

class CLJGHDialog2 : public CDialog
{
	DECLARE_DYNAMIC(CLJGHDialog2)

public:
	CLJGHDialog2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLJGHDialog2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
