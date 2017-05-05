// ListenSock.cpp : 实现文件
//

#include "stdafx.h"
#include "Serve.h"
#include "ListenSock.h"
#include"ServeDlg.h"

// CListenSock

CListenSock::CListenSock(CWnd*pCWnd)
{
	m_pMainCWnd = pCWnd;
}

CListenSock::~CListenSock()
{
}


// CListenSock 成员函数


void CListenSock::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	((CServeDlg *)m_pMainCWnd)->AcceptClient();
		CSocket::OnAccept(nErrorCode);
	
}
