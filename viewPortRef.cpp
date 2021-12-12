#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
float angle = 0;
// �Ʒ��� �������� ����Ʈ�� ���� ������ ������.
// �������, ���� ��ǥ�� �ƴ϶� ����Ʈ�� ���� ������ ���̴�.
float viewport1_x, viewport1_y;
float viewport2_x, viewport2_y;
// ������ �Լ�. ���⼭ �� ����Ʈ ������ Ŭ���� ���� ������ �̷������.
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////////////////////////////////////////////////////////////////
	// ù��° ����Ʈ ����. �Ϲ����� ������ ����.
	////////////////////////////////////////////////////////////////
	glViewport(0, 0, viewport1_x, viewport1_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-7, 7, -7, 7, -7, 7); // Ŭ���� ���� ����.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// ���� ��ǥ���� �׷��ش�. ���� �Ϲ����� �κ�.. -_-;;
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
	// �ι�° ����Ʈ�� ������ �Ѵ�.
	// ù��°�� ���� ����.
	////////////////////////////////////////
	glViewport(viewport1_x, 0, viewport2_x, viewport2_y);
	// ù��° ����Ʈ�� ���� ������ ���� ����Ʈ�� �����ϱ� ������
	// ó�� �ΰ��� ���ڴ� viewport1_x, 0 �� �ȴ�.
	// �� ��°�� �� ��°�� ���� ���� ���̸� �Է�.
	// �������� ����� �κ��̴�.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 100, 0, 500, -50, 50); //Ŭ���� ���� ����.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 2, 0);
	glBegin(GL_QUADS); // Ŭ���� ������ x-y ũ��� �����ϰ� �׷��־����Ƿ�
	glVertex2f(0, 0); // xy ��鿡 ������ �簢���� �׷��� ���̴�.
	glVertex2f(100, 0);
	glVertex2f(100, 500);
	glVertex2f(0, 500);
	glEnd();
	glutSwapBuffers(); // ���۸� ����ش�.
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
	viewport1_x = 0.8 * x; // ù ��° ����Ʈ�� ���� ���� ������ ���� 80%.
	viewport1_y = y; // ���̴� ������ ���̿� ����.
	viewport2_x = x - viewport1_x; //�� ��° ����Ʈ�� ���� ������ �κ��� �ȴ�.
	viewport2_y = y; // ���� ���̴� �����ϴ�.
	// �Ʒ��� �ּ� ó���� �κ��� ���� Reshape �Լ� �Ǵ� MFC�� OnSize ����
	// ó���ϴ� �κ��̴�. �׷��� ������ RenderScene ���� ���ֱ� ������
	// ���⼭�� ������ �������� �Ǵ� ��� �� ����Ʈ�� ���� ������ �°�
	// ���Ҵ� �ϴ� �ϸ� ���ָ� �ȴ�.
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