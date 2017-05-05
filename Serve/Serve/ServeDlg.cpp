
// ServeDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CServeDlg 对话框



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


// CServeDlg 消息处理程序

BOOL CServeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_pListenSock = new CListenSock(this);
	if(m_pListenSock == NULL) {
		MessageBox(_T("初始化监听失败"));
		delete m_pListenSock;
		m_pListenSock = NULL;
		return 0;
	}
	if (m_pListenSock->Create(6000) == NULL) {
		MessageBox(_T("绑定失败"));
		return 0;
	}
	m_pListenSock->Listen();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CServeDlg::AcceptClient()
{
	CChatSock*pSock = new CChatSock(this);
	if (!m_pListenSock->Accept(*pSock)) {
		MessageBox(_T("连接客户端失败"));
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
	int iBuffSize = 2000; //定义一次接受多长的数据
	int DateMsg[2000]; //定义临时变量存储接受的数据

	int iRes = pSock->Receive((char *)DateMsg, iBuffSize);//接收数据
	if (iRes != SOCKET_ERROR)
	{

		//接受登陆信息
		if (DateMsg[0] == 0)
		{
			LOGIN *m_login;
			m_login = (LOGIN *)DateMsg;
			strcpy(pSock->csID, m_login->cID);//

			MessageBox(_T("hahaha"));
		}
		//接受。。。
		else if (DateMsg[0] == 1)
		{
			DATECHAT *m_chat;
			m_chat = (DATECHAT *)DateMsg;

			if (!m_chat->RevID)
			{
				if (!(SendMsgToOne(m_chat->RevID, (char *)DateMsg)))
				{
					//离线信息的解决
					//遍历文件内所有的账号，看这个账号是否存在
					//如果存在，将消息暂存，当它登陆时发送
					//否则，返回失败给客户端
				}
			}
		}
	}
	//if (DateMsg[0] == 0)
	//{
	//	/*LOGIN *m_login;
	//	m_login = (LOGIN *)DateMsg;*/
	//	//(要对其进行判定是什么意思？？？？？)
	//	strcpy(pSock->csID,(LOGIN *)DateMsg);

	//	//MessageBox(_T("hahaha"));
	//}
	////接受。。。
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
	//	//		//离线信息的解决
	//	//		//遍历文件内所有的账号，看这个账号是否存在
	//	//		//如果存在，将消息暂存，当它登陆时发送
	//	//		//否则，返回失败给客户端
	//	//	}
	//	}
	//}
	return 0;
}


int CServeDlg::SendMsgToOne(char * cSendID,char * pMsg)
{
	//获取头指针
	POSITION pPos = m_pChatSock.GetHeadPosition();
	CChatSock * pSock;
	while (pPos) {
		//获取动态链表里的一个数据
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
	//得到主机名
	if (gethostname(szComputerName, MAX_PATH) == SOCKET_ERROR)
	{
		return;
	}
	//得到主机实体
	struct hostent *p = gethostbyname(szComputerName);
	if (p == NULL)
	{
		return;
	}
	//取得地址
	CString a;
	a = inet_ntoa(*(struct in_addr *)p->h_addr_list[0]);//把ip换成字符串形式
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
