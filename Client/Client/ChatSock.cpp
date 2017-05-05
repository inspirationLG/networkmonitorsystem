// ChatSock.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ChatSock.h"
#include"ClientDlg.h"

// CChatSock

CChatSock::CChatSock(CWnd *pwd)
{
	m_pMainDlg = pwd;
}

CChatSock::~CChatSock()
{
}


// CChatSock 成员函数


//int CChatSock::Receive(void* lpBuf, int nBufLen, int nFlags)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	return CSocket::Receive(lpBuf, nBufLen, nFlags);
//}


void CChatSock::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	((CClientDlg *)m_pMainDlg)->RevMsg();
	CSocket::OnReceive(nErrorCode);
}
