#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>


#define TRUE 1
#define FALSE 0


GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY; //���콺�� ��ǥ���� �����ϴ� ����
GLfloat R = 0.0, G = 0.0, B = 0.0;  //���� ���� ���� �� �̿�Ǵ� ����

GLboolean Line = TRUE; //TRUE�� ������ �ؼ� ó�� �����ϸ� ������ �׸���.

bool identify = TRUE; //���콺�� ������������ false, �ȴ����� true.  false�� �� ������� �׸���.
bool click = TRUE; // ȭ�� �ʱ�ȭ �ȵǰ� �����ִ� ����



void MyDisplay()
{

	if (click == TRUE)  // click�� True �� ���� ȭ���� �ʱ�ȭ���ش�.
	 //�׷��� Mousemove���� click = false�� �ϰ� true�� �ٲ��ִ°� �����Ƿ� �ʱ�ȭ �� ���� ����. //�������� �ٲٸ� click = TRUE�� ��
		glClear(GL_COLOR_BUFFER_BIT); // if���� �ȳ־��ָ� ��� �ݺ��ϸ鼭 ���� �ΰ��� �׷��ֹǷ� �̰� �ݵ�� �ʿ��ϴ�.
	glViewport(0, 0, 300, 300);

	glColor3f(1.0, 0.0, 0.0);   //RED color box
	glBegin(GL_POLYGON);
	glVertex3f(0.9, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 0.95, 0.0);
	glVertex3f(0.9, 0.95, 0.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);   //Green color box
	glBegin(GL_POLYGON);
	glVertex3f(0.9, 0.95, 0.0);
	glVertex3f(1.0, 0.95, 0.0);
	glVertex3f(1.0, 0.9, 0.0);
	glVertex3f(0.9, 0.9, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);   //Blue color box
	glBegin(GL_POLYGON);
	glVertex3f(0.9, 0.9, 0.0);
	glVertex3f(1.0, 0.9, 0.0);
	glVertex3f(1.0, 0.85, 0.0);
	glVertex3f(0.9, 0.85, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);   //Black color box
	glBegin(GL_POLYGON);
	glVertex3f(0.9, 0.85, 0.0);
	glVertex3f(1.0, 0.85, 0.0);
	glVertex3f(1.0, 0.8, 0.0);
	glVertex3f(0.9, 0.8, 0.0);
	glEnd();


	glColor3f(R, G, B); //���� ����.

	if (Line) //�����׸����� ���.
	{
		glBegin(GL_LINES);
		glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
		glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
		glEnd();
	}

	glFlush();
}

void MyMainMenu(int entryID)
{
	if (entryID == 1)
		Line = TRUE;  //�����׸���
	else if (entryID == 2)
		Line = FALSE;  //������׸���
	else
		exit(0);
	//glutPostRedisplay();
}


void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)
{
	GLfloat SelectX = X / 300.0;
	GLfloat SelectY = (300 - Y) / 300.0;
	if (SelectX >= 0.9 && SelectX <= 1.0 && SelectY >= 0.8 && SelectY <= 1.0)
	{

		/* RGB box�� ���콺�� Ŭ���ߴ��� Ȯ���ϴ� �κ�*/
		if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
		{

			if (SelectY >= 0.95 && SelectY <= 1.0)    //Red box
			{
				R = 1.0;
				G = 0.0;
				B = 0.0;
			}
			else if (SelectY >= 0.9 && SelectY <= 0.95)    //Green box
			{
				R = 0.0;
				G = 1.0;
				B = 0.0;
			}
			else if (SelectY >= 0.85 && SelectY <= 0.9)    //Blue box
			{
				R = 0.0;
				G = 0.0;
				B = 1.0;
			}
			else if (SelectY >= 0.8 && SelectY <= 0.85)    //Black box
			{
				R = 0.0;
				G = 0.0;
				B = 0.0;
			}
		}
	}
	if (Line)
		if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
		{
			TopLeftX = X;
			TopLeftY = Y;
		}

	if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP)     //���콺�� ���� �ٽ� �ٸ����� ������
	{                //���� ���� �Ƚ�Ű���� identify = TRUE�� �ٲ��ش�.
		identify = TRUE;
	}
}

void MyMouseMove(GLint X, GLint Y)
{
	if (Line)
	{
		click = TRUE; //ȭ�� �ʱ�ȭ
		BottomRightX = X;
		BottomRightY = Y;
		glutPostRedisplay();
	}
	else
	{
		BottomRightX = X;
		BottomRightY = Y;      //���콺�� �� ��ǥ�� bottom x, y�� ����
		if (identify == TRUE)
		{
			TopLeftX = BottomRightX;  //ó�� ���콺�� ������ �� top x, y�� �� ��ǥ�� ����.
			TopLeftY = BottomRightY;

			glutPostRedisplay(); // ���� ù��
		}


		identify = FALSE; //���콺�� ������ �ִ� ����
		click = FALSE;//click�� false�� ���� �������� ȭ���� �ʱ�ȭ���� �ʴ´�.
		//��, ���� �׸��� ��ǥ �ΰ��� �� �� �־��µ� ���� �������� �� �� �ִ°�.



		/*���콺Ŭ���Ͽ� ���� ��� �̵��ϴ� �������� top�� bottom�� ��� �����Ͽ� ������� �׸���*/

		glBegin(GL_LINES);
		glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
		glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
		glEnd();
		glFlush();
		glutPostRedisplay();  // R, G, B box�� �ݺ������� ǥ���ϰ� rgb�ڽ��� ������ ���� ���� �ٲٱ� ����.
			   // �׷��� �̰� MouseMove�� ��� ���� �������.(if(Line)�κ� ����)
		TopLeftX = BottomRightX; //���������� ���콺�� �ô� �κ��� ���� ������ǥ�� �ٲ۴�.
		TopLeftY = BottomRightY; //������ǥ�� �ٲٰ� ���� �׸���. �� ������ǥ�� �ٲ㼭 ���� �׸���. �̷��� �ݺ��ϸ鼭 ���� �׸�.
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("�ƹ� �̸��̳� �������.");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("������׸���", 2);
	glutAddMenuEntry("�����׸���", 1);
	glutAddMenuEntry("����", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutMainLoop();
	return 0;
}