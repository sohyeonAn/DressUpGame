
// clothingView.cpp : CclothingView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "clothing.h"
#endif

#include "clothingDoc.h"
#include "clothingView.h"
#include "startDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CclothingView

IMPLEMENT_DYNCREATE(CclothingView, CView)

BEGIN_MESSAGE_MAP(CclothingView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_NCMOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CclothingView ����/�Ҹ�

CclothingView::CclothingView()

{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CclothingView::~CclothingView()
{
}

BOOL CclothingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CclothingView �׸���

void CclothingView::OnDraw(CDC* /*pDC*/)
{
	CclothingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	startDlg dlg;
	dlg.DoModal();

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CclothingView �μ�

BOOL CclothingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CclothingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CclothingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CclothingView ����

#ifdef _DEBUG
void CclothingView::AssertValid() const
{
	CView::AssertValid();
}

void CclothingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CclothingDoc* CclothingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CclothingDoc)));
	return (CclothingDoc*)m_pDocument;
}
#endif //_DEBUG


// CclothingView �޽��� ó����



