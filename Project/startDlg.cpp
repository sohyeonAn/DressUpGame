// startDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "clothing.h"
#include "startDlg.h"
#include "afxdialogex.h"
#include "ClothingDlg.h"



// startDlg ��ȭ �����Դϴ�.

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


// startDlg �޽��� ó�����Դϴ�.


void startDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ClothingDlg dlg;
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	dlg.DoModal();//â ����

}
