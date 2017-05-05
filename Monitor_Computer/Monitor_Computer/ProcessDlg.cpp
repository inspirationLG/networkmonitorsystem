// ProcessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor_Computer.h"
#include "ProcessDlg.h"
#include "afxdialogex.h"


// CProcessDlg 对话框

IMPLEMENT_DYNAMIC(CProcessDlg, CDialogEx)

CProcessDlg::CProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROCESS, pParent)
{

}

CProcessDlg::~CProcessDlg()
{
}

void CProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProcessDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProcessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CProcessDlg 消息处理程序


void CProcessDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//获取ListCtrl的宽度
	CRect rect;
	m_ProcessList.GetClientRect(&rect);
	int nColInterval = rect.Width();

	//设置ListCtrl的样式
	m_ProcessList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//插入列索引、列名、列的文字格式，列宽
	m_ProcessList.InsertColumn(0, _T("ID"), LVCFMT_RIGHT, int(nColInterval*0.1));
	m_ProcessList.InsertColumn(1, _T("PROCESS"), LVCFMT_LEFT, int(nColInterval*0.1));
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
