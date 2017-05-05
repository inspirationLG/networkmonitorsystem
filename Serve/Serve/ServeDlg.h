/*
��˶�� 2016.9.24
*/
// ServeDlg.h : ͷ�ļ�
//

#pragma once
#include"ChatSock.h"
#include"ListenSock.h"
// CServeDlg �Ի���
class CServeDlg : public CDialogEx
{
// ����
public:
	CServeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CListenSock * m_pListenSock;//���ڼ���
	CList<CChatSock*, CChatSock*>m_pChatSock; //����ͨ��
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int AcceptClient();
	int RevMsg(CChatSock* pSock);
	int SendMsgToOne(char * cSendID,char *pMsg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
