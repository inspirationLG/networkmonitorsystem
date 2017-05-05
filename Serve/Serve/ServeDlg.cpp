
// ServeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Serve.h"
#include "ServeDlg.h"
#include "afxdialogex.h"
#include"Struct.h"
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#pragma warning(disable:4996)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServeDlg �Ի���



CServeDlg::CServeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERVE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CServeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CServeDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CServeDlg ��Ϣ�������

BOOL CServeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_pListenSock = new CListenSock(this);
	if(m_pListenSock == NULL) {
		MessageBox(_T("��ʼ������ʧ��"));
		delete m_pListenSock;
		m_pListenSock = NULL;
		return 0;
	}
	if (m_pListenSock->Create(6000) == NULL) {
		MessageBox(_T("��ʧ��"));
		return 0;
	}
	m_pListenSock->Listen();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CServeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CServeDlg::AcceptClient()
{
	CChatSock*pSock = new CChatSock(this);
	if (!m_pListenSock->Accept(*pSock)) {
		MessageBox(_T("���ӿͻ���ʧ��"));
		delete pSock;
		pSock = NULL;
	}
	else
	{
		m_pChatSock.AddTail(pSock);
	}

	return 0;
	
}


int CServeDlg::RevMsg(CChatSock* pSock)
{
	int iBuffSize = 2000; //����һ�ν��ܶ೤������
	int DateMsg[2000]; //������ʱ�����洢���ܵ�����

	int iRes = pSock->Receive((char *)DateMsg, iBuffSize);//��������
	if (iRes != SOCKET_ERROR)
	{

		//���ܵ�½��Ϣ
		if (DateMsg[0] == 0)
		{
			LOGIN *m_login;
			m_login = (LOGIN *)DateMsg;
			strcpy(pSock->csID, m_login->cID);//

			MessageBox(_T("hahaha"));
		}
		//���ܡ�����
		else if (DateMsg[0] == 1)
		{
			DATECHAT *m_chat;
			m_chat = (DATECHAT *)DateMsg;

			if (!m_chat->RevID)
			{
				if (!(SendMsgToOne(m_chat->RevID, (char *)DateMsg)))
				{
					//������Ϣ�Ľ��
					//�����ļ������е��˺ţ�������˺��Ƿ����
					//������ڣ�����Ϣ�ݴ棬������½ʱ����
					//���򣬷���ʧ�ܸ��ͻ���
				}
			}
		}
	}
	//if (DateMsg[0] == 0)
	//{
	//	/*LOGIN *m_login;
	//	m_login = (LOGIN *)DateMsg;*/
	//	//(Ҫ��������ж���ʲô��˼����������)
	//	strcpy(pSock->csID,(LOGIN *)DateMsg);

	//	//MessageBox(_T("hahaha"));
	//}
	////���ܡ�����
	//else if (DateMsg[0] == 1)
	//{
	//	if (!((DATECHAT *)DateMsg)->RevID) {
	//		SendMsgToOne(((DATECHAT *)DateMsg)->RevID,DateMsg);
	//	}
	//	//DATECHAT *m_chat; 
	//	//m_chat = (DATECHAT *)DateMsg;

	//	//if (!m_chat->RevID)
	//	//{
	//	//	if (!(SendMsgToOne(m_chat->RevID, (char *)DateMsg)))
	//	//	{
	//	//		
	//	//		//������Ϣ�Ľ��
	//	//		//�����ļ������е��˺ţ�������˺��Ƿ����
	//	//		//������ڣ�����Ϣ�ݴ棬������½ʱ����
	//	//		//���򣬷���ʧ�ܸ��ͻ���
	//	//	}
	//	}
	//}
	return 0;
}


int CServeDlg::SendMsgToOne(char * cSendID,char * pMsg)
{
	//��ȡͷָ��
	POSITION pPos = m_pChatSock.GetHeadPosition();
	CChatSock * pSock;
	while (pPos) {
		//��ȡ��̬�������һ������
		pSock = m_pChatSock.GetAt(pPos);
		 
		if (strcpy(pSock->csID,cSendID))
		{
			pSock->Send(pMsg, sizeof(&pMsg) + 1);
			return 1;
		}
		m_pChatSock.GetNext(pPos);
	}
	return 0;
} 


void CServeDlg::OnBnClickedButton1()
{
	CHAR szComputerName[MAX_PATH] = { 0 };
	WSAData data;
	if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
	{
		return;
	}
	//�õ�������
	if (gethostname(szComputerName, MAX_PATH) == SOCKET_ERROR)
	{
		return;
	}
	//�õ�����ʵ��
	struct hostent *p = gethostbyname(szComputerName);
	if (p == NULL)
	{
		return;
	}
	//ȡ�õ�ַ
	CString a;
	a = inet_ntoa(*(struct in_addr *)p->h_addr_list[0]);//��ip�����ַ�����ʽ
	MessageBox(a);

}


void CServeDlg::OnBnClickedButton2()
{
	//BOOL bException = FALSE;
	//BYTE szCpu[32] = { 0 };
	//UINT  uCpuID = 0U;
	//char szBuf[256] = { 0 };
	////CString szBuf;
	//UINT s1 = 0U;
	//UINT s2 = 0U;

	//__try
	//{
	//	_asm
	//	{
	//		mov eax, 01h
	//			xor edx, edx
	//			cpuid
	//			mov s1, edx
	//			mov s2, eax
	//	}
	//	sprintf(szBuf, "%08X%08X", s1, s2);
	//}
	//__except (EXCEPTION_EXECUTE_HANDLER)
	//{
	//	bException = TRUE;
	//}
	//if (!bException)
	//{
	//	//CString strCpuID = szBuf;
	//	CString tem = CA2CT(szBuf);
	//	//tem.Format("%s", szBuf);
	//	MessageBox(tem);
	//}


	unsigned long s1, s2, s3, s4;
	__asm
	{
		mov eax, 00h
			xor edx, edx
			cpuid
			mov s1, edx
			mov s2, eax
	}
	__asm
	{
		mov eax, 01h
			xor ecx, ecx
			xor edx, edx
			cpuid
			mov s3, edx
			mov s4, ecx
	}

	CString st;
	st.Format(L"%08X%08X%08X%08X", s1, s2, s3, s4);
	MessageBox(st);
}
