// ChatSock.cpp : ʵ���ļ�
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


// CChatSock ��Ա����


//int CChatSock::Receive(void* lpBuf, int nBufLen, int nFlags)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//	return CSocket::Receive(lpBuf, nBufLen, nFlags);
//}


void CChatSock::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CClientDlg *)m_pMainDlg)->RevMsg();
	CSocket::OnReceive(nErrorCode);
}
