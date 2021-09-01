// LJGHDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LJGH.h"
#include "LJGHDialog.h"
#include "afxdialogex.h"


// CLJGHDialog �Ի���

IMPLEMENT_DYNAMIC(CLJGHDialog, CDialogEx)

CLJGHDialog::CLJGHDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLJGHDialog::IDD, pParent)
	, m_circlex(0)
	, m_circley(0)
	, m_circler(0)
	, m_startx(0)
	, m_starty(0)
	, m_finalx(0)
	
	, m_finaly(0)
{

}

CLJGHDialog::~CLJGHDialog()
{
}

void CLJGHDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_circlex);
	DDX_Text(pDX, IDC_EDIT2, m_circley);
	DDX_Text(pDX, IDC_EDIT3, m_circler);
	DDX_Text(pDX, IDC_EDIT4, m_startx);
	DDX_Text(pDX, IDC_EDIT5, m_starty);
	DDX_Text(pDX, IDC_EDIT6, m_finalx);

	DDX_Text(pDX, IDC_EDIT7, m_finaly);
}


BEGIN_MESSAGE_MAP(CLJGHDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CLJGHDialog::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT6, &CLJGHDialog::OnEnChangeEdit6)
END_MESSAGE_MAP()


// CLJGHDialog ��Ϣ�������


void CLJGHDialog::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CLJGHDialog::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
