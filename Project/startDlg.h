#pragma once


// startDlg ��ȭ �����Դϴ�.

class startDlg : public CDialogEx
{
	DECLARE_DYNAMIC(startDlg)

public:
	startDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~startDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
