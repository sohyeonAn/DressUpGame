
// clothingView.h : CclothingView Ŭ������ �������̽�
//

#pragma once


class CclothingView : public CView
{
protected: // serialization������ ��������ϴ�.
	CclothingView();
	DECLARE_DYNCREATE(CclothingView)

// Ư���Դϴ�.
public:
	CclothingDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CclothingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // clothingView.cpp�� ����� ����
inline CclothingDoc* CclothingView::GetDocument() const
   { return reinterpret_cast<CclothingDoc*>(m_pDocument); }
#endif

