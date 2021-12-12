#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
float angle = 0;
// 아래의 변수들은 뷰포트의 폭을 저장할 변수들.
// 명심하자, 점의 좌표가 아니라 뷰포트의 가로 세로의 폭이다.
float viewport1_x, viewport1_y;
float viewport2_x, viewport2_y;
// 렌더링 함수. 여기서 각 뷰포트 설정과 클리핑 볼륨 설정이 이루어진다.
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////////////////////////////////////////////////////////////////
	// 첫번째 뷰포트 설정. 일반적인 설정과 같다.
	////////////////////////////////////////////////////////////////
	glViewport(0, 0, viewport1_x, viewport1_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-7, 7, -7, 7, -7, 7); // 클리핑 볼륨 설정.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// 구와 좌표축을 그려준다. 역시 일반적인 부분.. -_-;;
	glRotatef(angle, 0, 1, 0);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 10);
	glVertex3f(0, 0, 0);
	glEnd();
	glColor3f(1, 0, 0);
	glutSolidSphere(4, 12, 12);
	///////////////////////////////////////
	// 두번째 뷰포트의 설정을 한다.
	// 첫번째와 거의 같다.
	////////////////////////////////////////
	glViewport(viewport1_x, 0, viewport2_x, viewport2_y);
	// 첫번째 뷰포트가 끝난 곳에서 다음 뷰포트가 시작하기 때문에
	// 처음 두개의 인자는 viewport1_x, 0 이 된다.
	// 세 번째와 네 번째는 역시 폭과 높이를 입력.
	// 나머지는 평범한 부분이다.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 100, 0, 500, -50, 50); //클리핑 볼륨 설정.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 2, 0);
	glBegin(GL_QUADS); // 클리핑 볼륨의 x-y 크기와 동일하게 그려주었으므로
	glVertex2f(0, 0); // xy 평면에 가득찬 사각형이 그려질 것이다.
	glVertex2f(100, 0);
	glVertex2f(100, 500);
	glVertex2f(0, 500);
	glEnd();
	glutSwapBuffers(); // 버퍼를 비워준다.
}
void idle()
{
	angle += 0.51;
	if (angle >= 360)
		angle = 0;
	RenderScene();
}
void SetLighting()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float specularLight[] = { 0.7,0.7,0.7 };
	float diffuseLight[] = { 0.7, 0.7, 0.7 };
	float ambientLight[] = { 0.7, 0.7, 0.7 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
	glMaterialf(GL_FRONT, GL_SHININESS, 128);
}
void Reshape(int x, int y)
{
	if (y == 0)
		y = 1;
	viewport1_x = 0.8 * x; // 첫 번째 뷰포트의 폭을 설정 윈도우 폭의 80%.
	viewport1_y = y; // 높이는 윈도우 높이와 같다.
	viewport2_x = x - viewport1_x; //두 번째 뷰포트의 폭은 나머지 부분이 된다.
	viewport2_y = y; // 역시 높이는 동일하다.
	// 아래의 주석 처리된 부분은 보통 Reshape 함수 또는 MFC의 OnSize 에서
	// 처리하는 부분이다. 그러나 지금은 RenderScene 에서 해주기 때문에
	// 여기서는 윈도가 리사이즈 되는 경우 각 뷰포트의 폭을 비율에 맞게
	// 재할당 하는 일만 해주면 된다.
	/* glViewport(0,0,x,y) ;
	glViewport(0,0,400,y) ;
	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	glOrtho(-7,7,-7,7,-7,7) ;
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;
	*/
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("LIGHTING TEST");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutIdleFunc(idle);
	SetLighting();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}