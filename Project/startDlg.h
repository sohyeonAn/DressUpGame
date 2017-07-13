#pragma once


// startDlg 대화 상자입니다.

class startDlg : public CDialogEx
{
	DECLARE_DYNAMIC(startDlg)

public:
	startDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~startDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
