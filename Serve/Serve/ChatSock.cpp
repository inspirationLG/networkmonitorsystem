// ChatSock.cpp : 实现文件
//

#include "stdafx.h"
#include "Serve.h"
#include "ChatSock.h"
#include"ServeDlg.h"

// CChatSock

CChatSock::CChatSock(CWnd*pCWnd)
{
	m_pMainCWnd = pCWnd;
}

CChatSock::~CChatSock()
{
}


// CChatSock 成员函数


void CChatSock::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	AsyncSelect(FD_READ);

	((CServeDlg *)m_pMainCWnd)->RevMsg(this);
	CSocket::OnReceive(nErrorCode);
}
