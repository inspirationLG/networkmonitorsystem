#pragma once


// CDlgCpu �Ի���

class CDlgCpu : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCpu)

public:
	CDlgCpu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCpu();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CPU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
