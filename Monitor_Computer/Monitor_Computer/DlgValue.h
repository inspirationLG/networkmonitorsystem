#pragma once


// CDlgValue 对话框

class CDlgValue : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgValue)

public:
	CDlgValue(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgValue();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VALUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
