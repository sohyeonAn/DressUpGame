// startDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "clothing.h"
#include "startDlg.h"
#include "afxdialogex.h"
#include "ClothingDlg.h"



// startDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(startDlg, CDialogEx)

startDlg::startDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

startDlg::~startDlg()
{
}

void startDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(startDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &startDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// startDlg 메시지 처리기입니다.


void startDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ClothingDlg dlg;
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	dlg.DoModal();//창 띄우기

}
