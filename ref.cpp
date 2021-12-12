#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>


#define TRUE 1
#define FALSE 0


GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY; //마우스의 좌표값을 저장하는 변수
GLfloat R = 0.0, G = 0.0, B = 0.0;  //선의 색상 정할 때 이용되는 변수

GLboolean Line = TRUE; //TRUE로 설정을 해서 처음 실행하면 직선을 그린다.

bool identify = TRUE; //마우스를 누르고있으면 false, 안누르면 true.  false일 때 자유곡선을 그린다.
bool click = TRUE; // 화면 초기화 안되게 막아주는 변수



void MyDisplay()
{

	if (click == TRUE)  // click이 True 일 때에 화면을 초기화해준다.
	 //그러나 Mousemove에서 click = false로 하고 true로 바꿔주는게 없으므로 초기화 될 일이 없다. //직선으로 바꾸면 click = TRUE가 됨
		glClear(GL_COLOR_BUFFER_BIT); // if문을 안넣어주면 계속 반복하면서 선을 두개만 그려주므로 이건 반드시 필요하다.
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


	glColor3f(R, G, B); //선의 색상.

	if (Line) //직선그리기일 경우.
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
		Line = TRUE;  //직선그리기
	else if (entryID == 2)
		Line = FALSE;  //자유곡선그리기
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

		/* RGB box에 마우스를 클릭했는지 확인하는 부분*/
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

	if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP)     //마우스를 떼고 다시 다른곳에 누를때
	{                //선을 연결 안시키려고 identify = TRUE로 바꿔준다.
		identify = TRUE;
	}
}

void MyMouseMove(GLint X, GLint Y)
{
	if (Line)
	{
		click = TRUE; //화면 초기화
		BottomRightX = X;
		BottomRightY = Y;
		glutPostRedisplay();
	}
	else
	{
		BottomRightX = X;
		BottomRightY = Y;      //마우스의 현 좌표를 bottom x, y에 저장
		if (identify == TRUE)
		{
			TopLeftX = BottomRightX;  //처음 마우스를 눌렀을 때 top x, y에 현 좌표를 저장.
			TopLeftY = BottomRightY;

			glutPostRedisplay(); // 여기 첫선
		}


		identify = FALSE; //마우스를 누르고 있는 시점
		click = FALSE;//click이 false로 변한 시점부터 화면이 초기화되지 않는다.
		//즉, 선을 그릴때 좌표 두개만 쓸 수 있었는데 이제 무한으로 쓸 수 있는것.



		/*마우스클릭하여 점을 찍고 이동하는 순간부터 top과 bottom을 계속 연결하여 자유곡선을 그린다*/

		glBegin(GL_LINES);
		glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
		glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
		glEnd();
		glFlush();
		glutPostRedisplay();  // R, G, B box를 반복적으로 표시하고 rgb박스를 누를시 선의 색을 바꾸기 위함.
			   // 그래서 이게 MouseMove의 어디에 들어가든 상관없다.(if(Line)부분 빼고)
		TopLeftX = BottomRightX; //마지막으로 마우스를 뗐던 부분을 선의 시작좌표로 바꾼다.
		TopLeftY = BottomRightY; //시작좌표로 바꾸고 선을 그리고. 또 시작좌표로 바꿔서 선을 그리고. 이렇게 반복하면서 선을 그림.
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("아무 이름이나 지어보세요.");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("자유곡선그리기", 2);
	glutAddMenuEntry("직선그리기", 1);
	glutAddMenuEntry("종료", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutMainLoop();
	return 0;
}