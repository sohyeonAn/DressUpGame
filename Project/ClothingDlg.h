#include <string>

using namespace std;
#pragma once


// ClothingDlg 대화 상자입니다.

class ClothingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ClothingDlg)

public:
	ClothingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ClothingDlg();
	HGLRC m_hRC;
	HDC m_hDC;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void GLResize(int, int);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void GLRenderScene();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	//변수 선언
	int mouseX;
	float rotate;
	int mouseState;
	float moveArm = 0, moveBody = 0, moveLeg = 0;
	bool isRight = false, isMove = false;
	int num[3];
	float rotateX, rotateY;

	//머리 색칠하기
	float headFront[5][81][3];
	float headLeft[5][81][3];
	float headRight[5][81][3];
	float headBack[5][81][3];
	float headTop[5][81][3];


	//몸통 색칠하기
	float bodyFront[5][108][3];
	float bodyLeft[5][60][3];
	float bodyRight[5][60][3];
	float bodyBack[5][108][3];

	//팔 색칠하기
	float armFront[5][36][3];
	float armLeft[5][60][3];
	float armRight[5][60][3];
	float armBack[5][36][3];

	//다리 색칠하기
	float legFront[5][36][3];
	float legLeft[5][60][3];
	float legRight[5][60][3];
	float legBack[5][36][3];
	float legBottom[5][15][3];


	void DrawHead(int i);
	void DrawBody(int i);
	void DrawLeftArm(int i);
	void DrawRightArm(int i);
	void DrawRightLeg(int i);
	void DrawLeftLeg(int i);
	double cube_size = 0.05;
	int pixel = 5;

	//CBitmap m_background;

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	void LoadColor();
	afx_msg void OnReset();
	afx_msg void OnDance();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStop();
	int pose;
	float pose_value[4][4];
	int move;
	afx_msg void OnPose1();
	afx_msg void OnPose2();
	afx_msg void OnPoseReset();
};