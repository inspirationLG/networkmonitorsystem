
// processDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "process.h"
#include "processDlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CprocessDlg 对话框




CprocessDlg::CprocessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CprocessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprocessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ProcessList);
}

BEGIN_MESSAGE_MAP(CprocessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CprocessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CprocessDlg 消息处理程序

BOOL CprocessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//获取ListCtrl的宽度
	CRect rect;
	m_ProcessList.GetClientRect(&rect);
	int nColInterval = rect.Width();

	//设置ListCtrl的样式
	m_ProcessList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT  );

	//插入列索引、列名、列的文字格式，列宽
	m_ProcessList.InsertColumn(0, _T("ID"), LVCFMT_RIGHT, int(nColInterval*0.1));
	m_ProcessList.InsertColumn(1, _T("PROCESS"), LVCFMT_LEFT, int(nColInterval*0.1));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CprocessDlg::OnPaint()
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
HCURSOR CprocessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprocessDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 procList;
	procList.dwSize=sizeof(PROCESSENTRY32);
	BOOL bRet=Process32First(hSnapshot,&procList);
	int m_ProcessCount = 0; //进程数
	CString id,threads;

	while(bRet)
	{
		//m_ProcessList  //为CListCtrl控件变量
		m_ProcessList.InsertItem(m_ProcessCount,procList.szExeFile);
		id.Format(_T("%d"),procList.th32ProcessID);
		m_ProcessList.SetItem(m_ProcessCount,1,LVIF_TEXT,id,0,0,0,0);
		threads.Format(_T("%d"),procList.cntThreads);
		m_ProcessList.SetItem(m_ProcessCount,2,LVIF_TEXT,threads,0,0,0,0);
		m_ProcessCount++;
		bRet=Process32Next(hSnapshot,&procList);
	}
	CloseHandle(hSnapshot);
}
