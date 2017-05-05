/*
林硕豪 2016.9.24
*/
// ServeDlg.h : 头文件
//

#pragma once
#include"ChatSock.h"
#include"ListenSock.h"
// CServeDlg 对话框
class CServeDlg : public CDialogEx
{
// 构造
public:
	CServeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CListenSock * m_pListenSock;//用于监听
	CList<CChatSock*, CChatSock*>m_pChatSock; //用于通信
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
