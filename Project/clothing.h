
// clothing.h : clothing ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CclothingApp:
// �� Ŭ������ ������ ���ؼ��� clothing.cpp�� �����Ͻʽÿ�.
//

class CclothingApp : public CWinAppEx
{
public:
	CclothingApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CclothingApp theApp;
