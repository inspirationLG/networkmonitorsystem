// ListenSock.cpp : ʵ���ļ�
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


// CListenSock ��Ա����


void CListenSock::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CServeDlg *)m_pMainCWnd)->AcceptClient();
		CSocket::OnAccept(nErrorCode);
	
}
