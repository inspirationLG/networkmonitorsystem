#pragma once

// CChatSock ����Ŀ��

class CChatSock : public CSocket
{
public:
	CChatSock(CWnd*pCWnd);
	virtual ~CChatSock();

	CWnd *m_pMainCWnd;
	virtual void OnReceive(int nErrorCode);
	char csID[10];
};


