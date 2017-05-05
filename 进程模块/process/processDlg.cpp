
// processDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "process.h"
#include "processDlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CprocessDlg �Ի���




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


// CprocessDlg ��Ϣ�������

BOOL CprocessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ȡListCtrl�Ŀ��
	CRect rect;
	m_ProcessList.GetClientRect(&rect);
	int nColInterval = rect.Width();

	//����ListCtrl����ʽ
	m_ProcessList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT  );

	//�������������������е����ָ�ʽ���п�
	m_ProcessList.InsertColumn(0, _T("ID"), LVCFMT_RIGHT, int(nColInterval*0.1));
	m_ProcessList.InsertColumn(1, _T("PROCESS"), LVCFMT_LEFT, int(nColInterval*0.1));


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CprocessDlg::OnPaint()
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
HCURSOR CprocessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprocessDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();

	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 procList;
	procList.dwSize=sizeof(PROCESSENTRY32);
	BOOL bRet=Process32First(hSnapshot,&procList);
	int m_ProcessCount = 0; //������
	CString id,threads;

	while(bRet)
	{
		//m_ProcessList  //ΪCListCtrl�ؼ�����
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
