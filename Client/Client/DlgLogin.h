#pragma once
#include "afxwin.h"
#include"ChatSock.h"

// CDlgLogin �Ի���

class CDlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLogin();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_PWD;
	CEdit m_ID;
	CChatSock *m_pChatSock;
	afx_msg void OnBnClickedButtonLog();
};
