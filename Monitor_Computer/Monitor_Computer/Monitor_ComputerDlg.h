
// Monitor_ComputerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include"DlgCpu.h"
#include"DlgValue.h"
#include"ProcessDlg.h"
// CMonitor_ComputerDlg �Ի���
class CMonitor_ComputerDlg : public CDialogEx
{
// ����
public:
	CMonitor_ComputerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITOR_COMPUTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabe;
	CDlgCpu m_Dlgcpu;
	CDlgValue m_Dlgvalue;
	CProcessDlg m_Dlgprocess;
	afx_msg void OnTcnSelchangeTabMytable(NMHDR *pNMHDR, LRESULT *pResult);
};
