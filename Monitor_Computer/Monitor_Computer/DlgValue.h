#pragma once


// CDlgValue �Ի���

class CDlgValue : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgValue)

public:
	CDlgValue(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgValue();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VALUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
