#pragma once


// CDlgCpu 对话框

class CDlgCpu : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCpu)

public:
	CDlgCpu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCpu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CPU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
