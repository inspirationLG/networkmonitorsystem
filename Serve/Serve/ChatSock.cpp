// ChatSock.cpp : ʵ���ļ�
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


// CChatSock ��Ա����


void CChatSock::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	AsyncSelect(FD_READ);

	((CServeDlg *)m_pMainCWnd)->RevMsg(this);
	CSocket::OnReceive(nErrorCode);
}
