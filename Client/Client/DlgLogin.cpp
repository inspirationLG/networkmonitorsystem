// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "DlgLogin.h"
#include "afxdialogex.h"
#include"StructType.h"

// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PASS, m_PWD);
	DDX_Control(pDX, IDC_EDIT_ID, m_ID);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &CDlgLogin::OnBnClickedButtonLog)
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������


void CDlgLogin::OnBnClickedButtonLog()
{
	CString m_csID;
	CString m_csPWD;
	m_ID.GetWindowText(m_csID); 
	m_PWD.GetWindowText(m_csPWD);
	LOGIN LoginDate;
	memset(&LoginDate, '\0', sizeof(LoginDate));
	LoginDate.nType = 0;

	memcpy(LoginDate.cID, m_csID, m_csID.GetLength());
	memcpy(LoginDate.cPWD, m_csPWD, m_csPWD.GetLength());

	m_pChatSock->Send((void *)&LoginDate, sizeof(LoginDate));
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
