// ProcessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor_Computer.h"
#include "ProcessDlg.h"
#include "afxdialogex.h"


// CProcessDlg �Ի���

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


// CProcessDlg ��Ϣ�������


void CProcessDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


BOOL CProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//��ȡListCtrl�Ŀ��
	CRect rect;
	m_ProcessList.GetClientRect(&rect);
	int nColInterval = rect.Width();

	//����ListCtrl����ʽ
	m_ProcessList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//�������������������е����ָ�ʽ���п�
	m_ProcessList.InsertColumn(0, _T("ID"), LVCFMT_RIGHT, int(nColInterval*0.1));
	m_ProcessList.InsertColumn(1, _T("PROCESS"), LVCFMT_LEFT, int(nColInterval*0.1));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
