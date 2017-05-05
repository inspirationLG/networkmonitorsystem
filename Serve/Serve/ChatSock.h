#pragma once

// CChatSock ÃüÁîÄ¿±ê

class CChatSock : public CSocket
{
public:
	CChatSock(CWnd*pCWnd);
	virtual ~CChatSock();

	CWnd *m_pMainCWnd;
	virtual void OnReceive(int nErrorCode);
	char csID[10];
};


