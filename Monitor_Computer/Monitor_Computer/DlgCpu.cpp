// DlgCpu.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor_Computer.h"
#include "DlgCpu.h"
#include "afxdialogex.h"


// CDlgCpu 对话框

IMPLEMENT_DYNAMIC(CDlgCpu, CDialogEx)

CDlgCpu::CDlgCpu(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CPU, pParent)
{

}

CDlgCpu::~CDlgCpu()
{
}

void CDlgCpu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCpu, CDialogEx)
END_MESSAGE_MAP()


// CDlgCpu 消息处理程序
