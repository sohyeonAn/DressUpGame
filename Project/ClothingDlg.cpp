#include "stdafx.h"
#include "clothing.h"
#include "ClothingDlg.h"
#include "afxdialogex.h"
#include <gl/glut.h>


// ClothingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ClothingDlg, CDialogEx)

ClothingDlg::ClothingDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_DIALOG1, pParent)
, mouseX(0)
, rotateY(0)
, rotateX(0)
, mouseState(0)
, cube_size(0.025)
, pixel(9)
, pose(0)
, move(0)
{

}

ClothingDlg::~ClothingDlg()
{
}

void ClothingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ClothingDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_RESET, &ClothingDlg::OnReset)
	ON_COMMAND(ID_DANCE, &ClothingDlg::OnDance)
	ON_WM_TIMER()
	ON_COMMAND(ID_STOP, &ClothingDlg::OnStop)	
	ON_COMMAND(ID_POSE1, &ClothingDlg::OnPose1)
	ON_COMMAND(ID_POSE2, &ClothingDlg::OnPose2)
	ON_COMMAND(ID_POSE_RESET, &ClothingDlg::OnPoseReset)
END_MESSAGE_MAP()


// ClothingDlg 메시지 처리기입니다.


int ClothingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	int nPixelFormat;
	m_hDC = ::GetDC(m_hWnd);

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0, 0,
		0, 0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);

	VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));

	m_hRC = wglCreateContext(m_hDC);

	VERIFY(wglMakeCurrent(m_hDC, m_hRC));

	wglMakeCurrent(NULL, NULL);

	LoadColor();
	num[0] = 0;
	num[1] = 0;
	num[2] = 0;

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			pose_value[i][j] = 0;
		}
	}
	return 0;
}


void ClothingDlg::GLResize(int cx, int cy)
{
	GLfloat fAspect;

	if (cy == 0)cy = 1;
	glViewport(0, 0, cx, cy);
	fAspect = (GLfloat)cx / (GLfloat)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void ClothingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	//GLResize(cx, cy);
	VERIFY(wglMakeCurrent(NULL, NULL));
}

void ClothingDlg::GLRenderScene(void)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glTranslatef((GLfloat)-0.62, (GLfloat) 0.775, (GLfloat) 0.0);
	glRotatef((GLfloat)rotateX, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)rotateY, 0.0, 1.0, 0.0);


	glTranslatef((GLfloat)-0.13, (GLfloat) 0.0, (GLfloat) 0.0);
	glPushMatrix();
	DrawHead(num[0]);
	glPopMatrix();

	glTranslatef((GLfloat)0.0, (GLfloat)-0.225, (GLfloat)0.05);
	glPushMatrix();
	if (move == 1)
		glTranslatef((GLfloat)moveBody, (GLfloat)0.0, (GLfloat)0.0);
	else if (pose == 2)
		glRotatef(pose_value[0][0], pose_value[0][1], pose_value[0][2], pose_value[0][3]);
	DrawBody(num[1]);
	glPopMatrix();

	glTranslatef((GLfloat)-0.075, (GLfloat) 0.0, (GLfloat) 0.0);
	glPushMatrix();
	if (move == 1)
		glRotatef((GLfloat)moveArm, 1.0, 0.0, 0.0);
	else if (pose == 1)
		glRotatef(pose_value[0][0], pose_value[0][1], pose_value[0][2], pose_value[0][3]);
	DrawLeftArm(num[1]);
	glPopMatrix();

	glTranslatef((GLfloat)0.3, (GLfloat) 0.0, (GLfloat) 0.0);
	glPushMatrix();
	if (move == 1)
		glRotatef((GLfloat)moveArm, 1.0, 0.0, 0.0);
	else if (pose == 1)
		glRotatef(pose_value[1][0], pose_value[1][1], pose_value[1][2], pose_value[1][3]);
	DrawRightArm(num[1]);
	glPopMatrix();

	glTranslatef((GLfloat)-0.1125, (GLfloat)-0.3, (GLfloat) 0.0);
	glPushMatrix();
	if (move == 1)
		glTranslatef((GLfloat)moveLeg, (GLfloat)0.0, (GLfloat)0.0);
	else if (pose == 1)
		glRotatef(pose_value[2][0], pose_value[2][1], pose_value[2][2], pose_value[2][3]);
	else if (pose == 2)
		glRotatef(pose_value[1][0], pose_value[1][1], pose_value[1][2], pose_value[1][3]);
	DrawRightLeg(num[2]);
	glPopMatrix();

	glTranslatef((GLfloat)-0.075, (GLfloat)0.0, (GLfloat) 0.0);
	glPushMatrix();
	if (move == 1)
		glTranslatef((GLfloat)moveLeg, (GLfloat)0.0, (GLfloat)0.0);
	else if (pose == 1)
		glRotatef(pose_value[3][0], pose_value[3][1], pose_value[3][2], pose_value[3][3]);
	else if (pose == 2)
		glRotatef(pose_value[1][0], pose_value[1][1], pose_value[1][2], pose_value[1][3]);
	DrawLeftLeg(num[2]);
	glPopMatrix();

	//머리1
	glLoadIdentity();
	glTranslatef((GLfloat)-0.25, 0.8, 0.0);
	glPushMatrix();
	DrawHead(1);
	glPopMatrix();

	//머리2
	glLoadIdentity();
	glTranslatef((GLfloat)0.05, 0.8, 0.0);
	glPushMatrix();
	DrawHead(2);
	glPopMatrix();

	//머리3
	glLoadIdentity();
	glTranslatef((GLfloat)0.35, 0.8, 0.0);
	glPushMatrix();
	DrawHead(3);
	glPopMatrix();

	//머리4
	glLoadIdentity();
	glTranslatef((GLfloat)0.65, 0.8, 0.0);
	glPushMatrix();
	DrawHead(4);
	glPopMatrix();

	//몸통1
	glLoadIdentity();
	glTranslatef((GLfloat)-0.25, 0.5, 0.0);
	glPushMatrix();
	DrawBody(1);
	glPopMatrix();

	//몸통2
	glLoadIdentity();
	glTranslatef((GLfloat)0.05, 0.5, 0.0);
	glPushMatrix();
	DrawBody(2);
	glPopMatrix();

	//몸통3
	glLoadIdentity();
	glTranslatef((GLfloat)0.35, 0.5, 0.0);
	glPushMatrix();
	DrawBody(3);
	glPopMatrix();

	//몸통4
	glLoadIdentity();
	glTranslatef((GLfloat)0.65, 0.5, 0.0);
	glPushMatrix();
	DrawBody(4);
	glPopMatrix();

	//왼팔1
	glLoadIdentity();
	glTranslatef((GLfloat)-0.3, 0.5, 0.0);
	glPushMatrix();
	DrawLeftArm(1);
	glPopMatrix();

	//오른팔1
	glLoadIdentity();
	glTranslatef((GLfloat)-0.05, 0.5, 0.0);
	glPushMatrix();
	DrawRightArm(1);
	glPopMatrix();

	//왼팔2
	glLoadIdentity();
	glTranslatef((GLfloat)0.0, 0.5, 0.0);
	glPushMatrix();
	DrawLeftArm(2);
	glPopMatrix();

	//오른팔2
	glLoadIdentity();
	glTranslatef((GLfloat)0.24, 0.5, 1.0);
	glPushMatrix();
	DrawRightArm(2);
	glPopMatrix();

	//왼팔3
	glLoadIdentity();
	glTranslatef((GLfloat)0.3, 0.5, 0.0);
	glPushMatrix();
	DrawLeftArm(3);
	glPopMatrix();

	//오른팔3
	glLoadIdentity();
	glTranslatef((GLfloat)0.54, 0.5, 0.0);
	glPushMatrix();
	DrawRightArm(3);
	glPopMatrix();

	//왼팔4
	glLoadIdentity();
	glTranslatef((GLfloat)0.6, 0.5, 0.0);
	glPushMatrix();
	DrawLeftArm(4);
	glPopMatrix();

	//오른팔4
	glLoadIdentity();
	glTranslatef((GLfloat)0.84, 0.5, 0.0);
	glPushMatrix();
	DrawRightArm(4);
	glPopMatrix();

	//왼다리1
	glLoadIdentity();
	glTranslatef((GLfloat)-0.22, 0.1, 0.0);
	glPushMatrix();
	DrawLeftLeg(1);
	glPopMatrix();

	//왼다리2
	glLoadIdentity();
	glTranslatef((GLfloat)0.07, 0.1, 0.0);
	glPushMatrix();
	DrawLeftLeg(2);
	glPopMatrix();

	//왼다리3
	glLoadIdentity();
	glTranslatef((GLfloat)0.37, 0.1, 0.0);
	glPushMatrix();
	DrawLeftLeg(3);
	glPopMatrix();

	//왼다리4
	glLoadIdentity();
	glTranslatef((GLfloat)0.67, 0.1, 0.0);
	glPushMatrix();
	DrawLeftLeg(4);
	glPopMatrix();


	//오른다리1
	glLoadIdentity();
	glTranslatef((GLfloat)-0.145, 0.1, 0.0);
	glPushMatrix();
	DrawRightLeg(1);
	glPopMatrix();

	//오른다리2
	glLoadIdentity();
	glTranslatef((GLfloat)0.14, 0.1, 0.0);
	glPushMatrix();
	DrawRightLeg(2);
	glPopMatrix();

	//오른다리3
	glLoadIdentity();
	glTranslatef((GLfloat)0.44, 0.1, 0.0);
	glPushMatrix();
	DrawRightLeg(3);
	glPopMatrix();

	//오른다리4
	glLoadIdentity();
	glTranslatef((GLfloat)0.74, 0.1, 0.0);
	glPushMatrix();
	DrawRightLeg(4);
	glPopMatrix();
}


void ClothingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		wglMakeCurrent(m_hDC, m_hRC);
		GLRenderScene();
		SwapBuffers(m_hDC);
		wglMakeCurrent(m_hDC, NULL);
	}               // TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

}


void ClothingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}


void ClothingDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((335 <= point.x&&point.x <= 430) && (56 <= point.y&&point.y <= 122)) {
		num[0] = 1;
		Invalidate(TRUE);
	}
	else if ((416 <= point.x&&point.x <= 561) && (56 <= point.y&&point.y <= 122)) {
		num[0] = 2;
		Invalidate(TRUE);
	}
	else if ((596 <= point.x&&point.x <= 693) && (56 <= point.y&&point.y <= 122)) {
		num[0] = 3;
		Invalidate(TRUE);
	}
	else if ((727 <= point.x&&point.x <= 824) && (56 <= point.y&&point.y <= 122)) {
		num[0] = 4;
		Invalidate(TRUE);
	}


	else if ((337 <= point.x&&point.x <= 425) && (148 <= point.y&&point.y <= 235)) {
		num[1] = 1;
		Invalidate(TRUE);
	}
	else if ((467 <= point.x&&point.x <= 560) && (148 <= point.y&&point.y <= 235)) {
		num[1] = 2;
		Invalidate(TRUE);
	}
	else if ((597 <= point.x&&point.x <= 696) && (148 <= point.y&&point.y <= 235)) {
		num[1] = 3;
		Invalidate(TRUE);
	}
	else if ((728 <= point.x&&point.x <= 824) && (148 <= point.y&&point.y <= 235)) {
		num[1] = 4;
		Invalidate(TRUE);
	}


	else if ((347 <= point.x&&point.x <= 409) && (267 <= point.y&&point.y <= 356)) {
		num[2] = 1;
		Invalidate(TRUE);

	}
	else if ((475 <= point.x&&point.x <= 535) && (267 <= point.y&&point.y <= 356)) {
		num[2] = 2;
		Invalidate(TRUE);

	}
	else if ((606 <= point.x&&point.x <= 666) && (267 <= point.y&&point.y <= 356)) {
		num[2] = 3;
		Invalidate(TRUE);

	}
	else if ((736 <= point.x&&point.x <= 798) && (267 <= point.y&&point.y <= 356)) {
		num[2] = 4;
		Invalidate(TRUE);

	}


	CDialogEx::OnLButtonUp(nFlags, point);
}


void ClothingDlg::DrawHead(int index)
{
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;
	int k = 0, i = 0, j = 0;
	//CString str;
	//str.Format(L"%d",index);
	//MessageBox(NULL,str, 0);
	/*얼굴*/
	for (k = 0; k < pixel; k++) {
		for (i = 0; i < pixel; i++) {
			for (j = 0; j < pixel; j++) {
				//if (k == 0) {
				//   if (i == 1 && j == 1)
				//      glColor3f(1.0, 1.0, 1.0);
				//   else if (i == 1 && j == 3)
				//      glColor3f(1.0, 1.0, 1.0);
				//   else if (i == 3 && j == 1)
				//      glColor3f(1.0, 1.0, 1.0);
				//   else if (i == 3 && j == 2)
				//      glColor3f(1.0, 1.0, 1.0);
				//   else if (i == 3 && j == 3)
				//      glColor3f(1.0, 1.0, 1.0);
				//   else
				//      glColor3f(1.0, 0.4, 0.4);
				//}


				if (k == 0) {
					glColor3f(headFront[index][count1][0], headFront[index][count1][1], headFront[index][count1][2]);
					count1++;

				}

				if (k == pixel - 1)
				{
					glColor3f(headBack[index][count4][0], headBack[index][count4][1], headBack[index][count4][2]);
					count4++;

				}

				if (j == 0) {
					glColor3f(headLeft[index][count2][0], headLeft[index][count2][1], headLeft[index][count2][2]);
					count2++;

				}

				if (j == pixel - 1)
				{
					glColor3f(headRight[index][count3][0], headRight[index][count3][1], headRight[index][count3][2]);
					count3++;

				}

				if (i == 0) {
					glColor3f(headTop[index][count5][0], headTop[index][count5][1], headTop[index][count5][2]);
					count5++;

				}

				glTranslatef((GLfloat)cube_size, (GLfloat)0.0, (GLfloat) 0.0);
				glutSolidCube(cube_size);
			}
			glTranslatef((GLfloat)-(cube_size*pixel), (GLfloat)-cube_size, (GLfloat) 0.0);

		}
		glTranslatef((GLfloat)0.0, (GLfloat)(cube_size*pixel), (GLfloat)cube_size);
	}
}


void ClothingDlg::DrawBody(int index)
{
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	/*몸통*/

	for (int k = 0; k < pixel - 4; k++) {//두께
		for (int i = 0; i < pixel + 3; i++) {
			for (int j = 0; j < pixel; j++) {


				if (k == 0) {
					glColor3f(bodyFront[index][count1][0], bodyFront[index][count1][1], bodyFront[index][count1][2]);
					count1++;

				}

				if (k == pixel - 5)
				{
					glColor3f(bodyBack[index][count4][0], bodyBack[index][count4][1], bodyBack[index][count4][2]);
					count4++;

				}

				if (j == 0) {
					glColor3f(bodyLeft[index][count2][0], bodyLeft[index][count2][1], bodyLeft[index][count2][2]);
					count2++;

				}

				if (j == pixel - 1)
				{
					glColor3f(bodyRight[index][count3][0], bodyRight[index][count3][1], bodyRight[index][count3][2]);
					count3++;

				}


				glTranslatef((GLfloat)cube_size, (GLfloat)0.0, (GLfloat) 0.0);
				glutSolidCube(cube_size);
			}
			glTranslatef((GLfloat)-(cube_size*pixel), (GLfloat)-cube_size, (GLfloat) 0.0);

		}
		glTranslatef((GLfloat)0.0, (GLfloat)cube_size*(pixel + 3), (GLfloat)cube_size);

	}
}


void ClothingDlg::DrawLeftArm(int index)
{
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

	/*왼팔*/

	for (int k = 0; k < pixel - 4; k++) {//두께
		for (int i = 0; i < pixel + 3; i++) {
			for (int j = 0; j < pixel - 6; j++) {

				if (k == 0) {
					glColor3f(armFront[index][count1][0], armFront[index][count1][1], armFront[index][count1][2]);
					count1++;

				}

				if (k == pixel - 5)
				{
					glColor3f(armBack[index][count4][0], armBack[index][count4][1], armBack[index][count4][2]);
					count4++;

				}

				if (j == 0) {
					glColor3f(armLeft[index][count2][0], armLeft[index][count2][1], armLeft[index][count2][2]);
					count2++;

				}

				if (j == pixel - 7)
				{
					glColor3f(armRight[index][count3][0], armRight[index][count3][1], armRight[index][count3][2]);
					count3++;

				}

				glTranslatef((GLfloat)cube_size, (GLfloat)0.0, (GLfloat) 0.0);
				glutSolidCube(cube_size);
			}
			glTranslatef((GLfloat)-(cube_size*(pixel - 6)), (GLfloat)-cube_size, (GLfloat) 0.0);

		}
		glTranslatef((GLfloat)0.0, (GLfloat)cube_size*(pixel + 3), (GLfloat)cube_size);

	}
}


void ClothingDlg::DrawRightArm(int index)
{
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

	/*오른팔*/

	for (int k = 0; k < pixel - 4; k++) {//두께
		for (int i = 0; i < pixel + 3; i++) {
			for (int j = 0; j < pixel - 6; j++) {

				if (k == 0) {
					glColor3f(armFront[index][count1][0], armFront[index][count1][1], armFront[index][count1][2]);
					count1++;

				}

				if (k == pixel - 5)
				{
					glColor3f(armBack[index][count4][0], armBack[index][count4][1], armBack[index][count4][2]);
					count4++;

				}

				if (j == 0) {
					glColor3f(armLeft[index][count2][0], armLeft[index][count2][1], armLeft[index][count2][2]);
					count2++;

				}

				if (j == pixel - 7)
				{
					glColor3f(armRight[index][count3][0], armRight[index][count3][1], armRight[index][count3][2]);
					count3++;

				}

				glTranslatef((GLfloat)cube_size, (GLfloat)0.0, (GLfloat) 0.0);
				glutSolidCube(cube_size);
			}
			glTranslatef((GLfloat)-(cube_size*(pixel - 6)), (GLfloat)-cube_size, (GLfloat) 0.0);

		}
		glTranslatef((GLfloat)0.0, (GLfloat)cube_size*(pixel + 3), (GLfloat)cube_size);

	}
}


void ClothingDlg::DrawRightLeg(int index)
{
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;

	/*오른다리*/

	for (int k = 0; k < pixel - 4; k++) {//두께
		for (int i = 0; i < pixel + 3; i++) {
			for (int j = 0; j < pixel - 6; j++) {


				if (k == 0) {
					glColor3f(legFront[index][count1][0], legFront[index][count1][1], legFront[index][count1][2]);
					count1++;

				}

				if (k == pixel - 5)
				{
					glColor3f(legBack[index][count4][0], legBack[index][count4][1], legBack[index][count4][2]);
					count4++;

				}

				if (j == 0) {
					glColor3f(legLeft[index][count2][0], legLeft[index][count2][1], legLeft[index][count2][2]);
					count2++;

				}

				if (j == pixel - 7)
				{
					glColor3f(legRight[index][count3][0], legRight[index][count3][1], legRight[index][count3][2]);
					count3++;
				}

				if (i == pixel + 2)
				{
					glColor3f(legBottom[index][count5][0], legBottom[index][count5][1], legBottom[index][count5][2]);
					count5++;
				}
				glTranslatef((GLfloat)cube_size, (GLfloat)0.0, (GLfloat) 0.0);
				glutSolidCube(cube_size);
			}
			glTranslatef((GLfloat)-(cube_size*(pixel - 6)), (GLfloat)-cube_size, (GLfloat) 0.0);

		}
		glTranslatef((GLfloat)0.0, (GLfloat)cube_size*(pixel + 3), (GLfloat)cube_size);

	}
}


void ClothingDlg::DrawLeftLeg(int index)
{
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;

	/*왼다리*/

	for (int k = 0; k < pixel - 4; k++) {//두께
		for (int i = 0; i < pixel + 3; i++) {
			for (int j = 0; j < pixel - 6; j++) {


				if (k == 0) {
					glColor3f(legFront[index][count1][0], legFront[index][count1][1], legFront[index][count1][2]);
					count1++;

				}

				if (k == pixel - 5)
				{
					glColor3f(legBack[index][count4][0], legBack[index][count4][1], legBack[index][count4][2]);
					count4++;

				}

				if (j == 0) {
					glColor3f(legLeft[index][count2][0], legLeft[index][count2][1], legLeft[index][count2][2]);
					count2++;

				}

				if (j == pixel - 7)
				{
					glColor3f(legRight[index][count3][0], legRight[index][count3][1], legRight[index][count3][2]);
					count3++;
				}

				if (i == pixel + 2)
				{
					glColor3f(legBottom[index][count5][0], legBottom[index][count5][1], legBottom[index][count5][2]);
					count5++;
				}
				glTranslatef((GLfloat)cube_size, (GLfloat)0.0, (GLfloat) 0.0);
				glutSolidCube(cube_size);
			}
			glTranslatef((GLfloat)-(cube_size*(pixel - 6)), (GLfloat)-cube_size, (GLfloat) 0.0);

		}
		glTranslatef((GLfloat)0.0, (GLfloat)cube_size*(pixel + 3), (GLfloat)cube_size);

	}
}



BOOL ClothingDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*깜빡임 현상 없애기*/
	//CDialogEx::OnIconEraseBkgnd(pDC);

	//if (!m_background.m_hObject)
	//   return true;

	//CRect rect;
	//GetClientRect(&rect);

	//CDC dc;
	//dc.CreateCompatibleDC(pDC);
	//CBitmap* pOldBitmap = dc.SelectObject(&m_background);

	//BITMAP bmap;
	//m_background.GetBitmap(&bmap);
	//pDC->StretchBlt(0, 0, rect.Width(), rect.Height, &dc,
	//   0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);

	//dc.SelectObject(pOldBitmap);
	return TRUE;
}


void ClothingDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nKey = nChar;
	if (nKey == 0x41) {//a
		rotateY += 5;

		Invalidate(TRUE);
	}

	else if (nKey == 0x44) {//d
		rotateY -= 5;
		Invalidate(TRUE);
	}

	else if (nKey == 0x57)//w
	{
		rotateX += 5;
		Invalidate(TRUE);

	}
	else if (nKey == 0x53)//s
	{
		rotateX -= 5;
		Invalidate(TRUE);
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void ClothingDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


//파일에서 컬러 불러와서
//어레이에 저장하기
void ClothingDlg::LoadColor()
{

	FILE *fpt = fopen("head1.txt", "r");
	char line[100];
	int r, g, b;
	int i = 0, j = 0, k = 0;

	if (!fpt)
	{
		printf("파일이 없습니다.\n");
	}


	for (i = 0; i < 5; i++) {
		for (j = 0; j < 81; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &headFront[i][j][0], &headFront[i][j][1], &headFront[i][j][2]);
		}
		for (j = 0; j < 81; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &headLeft[i][j][0], &headLeft[i][j][1], &headLeft[i][j][2]);
		}
		for (j = 0; j < 81; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &headRight[i][j][0], &headRight[i][j][1], &headRight[i][j][2]);
		}
		for (j = 0; j < 81; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &headBack[i][j][0], &headBack[i][j][1], &headBack[i][j][2]);
		}
		for (j = 0; j < 81; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &headTop[i][j][0], &headTop[i][j][1], &headTop[i][j][2]);
		}
	}

	fclose(fpt);//머리 끝

	fpt = fopen("body.txt", "r");
	if (!fpt)
	{
		printf("파일이 없습니다.\n");
	}
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 108; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &bodyFront[i][j][0], &bodyFront[i][j][1], &bodyFront[i][j][2]);
		}
		for (j = 0; j < 60; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &bodyLeft[i][j][0], &bodyLeft[i][j][1], &bodyLeft[i][j][2]);
		}
		for (j = 0; j < 60; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &bodyRight[i][j][0], &bodyRight[i][j][1], &bodyRight[i][j][2]);
		}
		for (j = 0; j < 108; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &bodyBack[i][j][0], &bodyBack[i][j][1], &bodyBack[i][j][2]);
		}
	}

	fclose(fpt);//몸통 끝


	fpt = fopen("arm.txt", "r");
	if (!fpt)
	{
		printf("파일이 없습니다.\n");
	}
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 36; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &armFront[i][j][0], &armFront[i][j][1], &armFront[i][j][2]);
		}
		for (j = 0; j < 60; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &armLeft[i][j][0], &armLeft[i][j][1], &armLeft[i][j][2]);
		}
		for (j = 0; j < 60; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &armRight[i][j][0], &armRight[i][j][1], &armRight[i][j][2]);
		}
		for (j = 0; j < 36; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &armBack[i][j][0], &armBack[i][j][1], &armBack[i][j][2]);
		}
	}

	fclose(fpt);//팔 끝


	fpt = fopen("leg.txt", "r");
	if (!fpt)
	{
		printf("파일이 없습니다.\n");
	}
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 36; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &legFront[i][j][0], &legFront[i][j][1], &legFront[i][j][2]);
		}
		for (j = 0; j < 60; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &legLeft[i][j][0], &legLeft[i][j][1], &legLeft[i][j][2]);
		}
		for (j = 0; j <60; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &legRight[i][j][0], &legRight[i][j][1], &legRight[i][j][2]);
		}
		for (j = 0; j < 36; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &legBack[i][j][0], &legBack[i][j][1], &legBack[i][j][2]);
		}
		for (j = 0; j < 15; j++)
		{
			fgets(line, 2048, fpt);
			sscanf(line, "%f %f %f", &legBottom[i][j][0], &legBottom[i][j][1], &legBottom[i][j][2]);
		}
	}

	fclose(fpt);//다리 끝


}

void ClothingDlg::OnReset()
{
	for (int i = 0; i < 3; i++) {
		num[i] = 0;
	}
	Invalidate(TRUE);
}

void ClothingDlg::OnDance()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	move = 1;
	moveArm = 180;

	SetTimer(0, 65, NULL);

}


BOOL ClothingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//m_background.LoadBitmapW(IDB_BITMAP1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void ClothingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent == 0) {
		if (!isMove) {
			isMove = true;
			isRight = true;
		}

		if (isRight) {
			moveBody += 0.01;
			moveLeg += 0.005;

			if (moveBody > 0.02)
				isRight = false;
		}
		else {
			moveBody -= 0.01;
			moveLeg -= 0.005;

			if (moveBody < -0.02)
				isRight = true;
		}

	}

	Invalidate();
}


void ClothingDlg::OnStop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	move = 0;
	KillTimer(0);
	moveArm = 0;
	moveBody = 0;
	moveLeg = 0;
	pose = 0;

	isMove = false;
	isRight = false;

	Invalidate();

}


void ClothingDlg::OnPose1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pose = 1;
	pose_value[0][0] = 90.0;
	pose_value[0][1] = 1.0;
	pose_value[0][2] = 0.0;
	pose_value[0][3] = 0.0;

	pose_value[1][0] = 90.0;
	pose_value[1][1] = 1.0;
	pose_value[1][2] = 0.0;
	pose_value[1][3] = 0.0;

	pose_value[2][0] = 90.0;
	pose_value[2][1] = 0.0;
	pose_value[2][2] = 0.0;
	pose_value[2][3] = 1.0;

	pose_value[3][0] = 0.0;
	pose_value[3][1] = 0.0;
	pose_value[3][2] = 0.0;
	pose_value[3][3] = 0.0;
	Invalidate(TRUE);
}


void ClothingDlg::OnPose2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pose = 2;
	pose_value[0][0] = -10.0;
	pose_value[0][1] = 1.0;
	pose_value[0][2] = 0.0;
	pose_value[0][3] = 0.0;

	pose_value[1][0] = 20.0;
	pose_value[1][1] = 1.0;
	pose_value[1][2] = 0.0;
	pose_value[1][3] = 0.0;

	pose_value[2][0] = 0.0;
	pose_value[2][1] = 0.0;
	pose_value[2][2] = 0.0;
	pose_value[2][3] = 0.0;

	pose_value[3][0] = 0.0;
	pose_value[3][1] = 0.0;
	pose_value[3][2] = 0.0;
	pose_value[3][3] = 0.0;
	Invalidate(TRUE);
}


void ClothingDlg::OnPoseReset()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pose = 0;
	Invalidate(TRUE);
}
