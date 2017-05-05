#pragma once

// CListenSock ÃüÁîÄ¿±ê

class CListenSock : public CSocket
{
public:
	CListenSock(CWnd*pCWnd);
	virtual ~CListenSock();
	virtual void OnAccept(int nErrorCode);

	CWnd * m_pMainCWnd;
};


