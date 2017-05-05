
// Monitor_ComputerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include"DlgCpu.h"
#include"DlgValue.h"
#include"ProcessDlg.h"
// CMonitor_ComputerDlg 对话框
class CMonitor_ComputerDlg : public CDialogEx
{
// 构造
public:
	CMonitor_ComputerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITOR_COMPUTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
