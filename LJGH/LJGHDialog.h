#pragma once


// CLJGHDialog �Ի���

class CLJGHDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLJGHDialog)

public:
	CLJGHDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLJGHDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit6();
	//�ϰ������Ϣ
	int m_circlex;
	int m_circley;
	int m_circler;
	//�����Ϣ
	int m_startx;
	int m_starty;
	//�յ���Ϣ
	int m_finalx;
	int m_finaly;
};
