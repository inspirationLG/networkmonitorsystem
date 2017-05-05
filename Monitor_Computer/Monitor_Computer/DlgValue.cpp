// DlgValue.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor_Computer.h"
#include "DlgValue.h"
#include "afxdialogex.h"


// CDlgValue 对话框

IMPLEMENT_DYNAMIC(CDlgValue, CDialogEx)

CDlgValue::CDlgValue(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VALUE, pParent)
{

}

CDlgValue::~CDlgValue()
{
}

void CDlgValue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgValue, CDialogEx)
END_MESSAGE_MAP()


// CDlgValue 消息处理程序
