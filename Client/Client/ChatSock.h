#pragma once

// CChatSock ÃüÁîÄ¿±ê

class CChatSock : public CSocket
{
public:
	CChatSock(CWnd *pwd);
	virtual ~CChatSock();
//	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void OnReceive(int nErrorCode);
	CWnd *m_pMainDlg;
};


