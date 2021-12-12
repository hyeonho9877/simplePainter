#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <iostream>
#include "init.h"
#include "points.h"
#include "shapes.h"
#include <vector>
using namespace std;

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

int width, height, mode = 1, eraserID, eraserWidth = 10, borderBoxID;
int mainMenu, objSubmenu, lineSubmenu, fillSubmenu;
GLfloat mouseInitX = -1, mouseInitY = -1, mouseX = -1, mouseY = -1, prevMouseX = -1, prevMouseY = -1;
GLfloat r = -1, g = -1, b = -1;
bool clear = true, inClick = false, clickedLeft = false, fillObj = true, extended = false, keyAccepting = false;
myRectangle* rectangle;
myTriangle* triangle;
myCircle* circle;
myLines* line;
myShape* deleteTarget;
myTexts* texts;
myTexts* targetText;
int stride = 0, pointSize = 3;
vector<myShape*> objects;
vector<myTexts*> textObjs;

void createBorderBoxList() {
	borderBoxID = glGenLists(1);
	glNewList(borderBoxID, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(5, 0);
	glVertex2f(5, 5);
	glVertex2f(0, 5);
	glEnd();
	glEndList();
}

void motion(int x, int y) {
	if (clickedLeft) {
		if (deleteTarget != 0)
			deleteTarget = 0;
		if (inClick) {
			inClick = false;
		} else if (mode == 1 && (prevMouseX != x || prevMouseY != height - y) && stride++ % 2 == 0) {
			line->addPoint(x, height - y);
			extended = true;
		} else if (mode == 2 && (prevMouseX != -1 && prevMouseY != -1)) {
			rectangle->setPoints(x, height - y);
			extended = true;
		} else if (mode == 3) {
			triangle->setPoints(x, height - y);
			extended = true;
		} else if (mode == 4) {
			circle->setPoints(x, height - y);
			extended = true;
		} else if (mode == 5) {
			extended = true;
		}

		if (prevMouseX == -1 && prevMouseY == -1) {
			prevMouseX = x;
			prevMouseY = height - y;
		} else {
			prevMouseX = mouseX;
			prevMouseY = mouseY;
		}

		mouseX = (GLfloat)x;
		mouseY = (GLfloat)(height - y);
		glutPostRedisplay();
	}
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseInitX = (GLfloat)x;
		mouseInitY = (GLfloat)(height - y);
		inClick = true;
		clear = false;
		clickedLeft = true;

		switch (mode) {
		case 1:
			line = new myLines(
				new Points(x, height - y),
				new Points(x, height - y),
				new Points(x, height - y),
				new Points(x, height - y),
				r, g, b, pointSize
			);
			line->addPoint(x, height - y);
			break;
		case 2:
			rectangle = new myRectangle(
				new Points(x, height - y),
				new Points(x, height - y),
				new Points(x, height - y),
				new Points(x, height - y),
				r, g, b,
				fillObj
			);
			break;
		case 3:
			triangle = new myTriangle(
				new Points(x, height - y),
				new Points(x, height - y),
				new Points(x, height - y),
				new Points(x, height - y),
				r, g, b,
				fillObj
			);
			break;
		case 4:
			circle = new myCircle(
				new Points(x, height - y),
				new Points(x, height - y),
				new Points(x, height - y),
				new Points(x, height - y),
				r, g, b,
				fillObj
			);
			break;
		case 5:
			texts = new myTexts();
			break;
		}
		
	} else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		clickedLeft = false;
		prevMouseX = -1;
		prevMouseY = -1;

		switch (mode) {
		case 1:
			if (extended) {
				objects.push_back(line);
				extended = false;
			}
			break;
		case 2:
			if (extended) {
				objects.push_back(rectangle);
				extended = false;
			}
			break;
		case 3:
			if (extended) {
				objects.push_back(triangle);
				extended = false;
			}
			break;
		case 4:
			if (extended) {
				objects.push_back(circle);
				extended = false;
			}
			break;
		case 5:
			if (extended) {
				texts->setPoints(
					new Points(mouseInitX, mouseInitY),
					new Points(x, mouseInitY),
					new Points(mouseInitX, height - y),
					new Points(x, height - y)
				);
				textObjs.push_back(texts);
				extended = false;
			} else {
				texts->~myTexts();
			}

			break;
		}
		bool found = false;
		for (auto o : objects) {
			if (o->isInObj(x, height - y)) {
				found = true;
				deleteTarget = o;
			}
		}
		for (auto t : textObjs) {
			if (t->isInObj(x, height - y)) {
				found = true;
				deleteTarget = t;
			}
		}
		if (!found) {
			if (keyAccepting)
				keyAccepting = false;
			deleteTarget = 0;
		}
		clear = true;
		glColor3f(r, g, b);
		glutPostRedisplay();
	}
}

void display() {
	glClearColor(0.9, 0.9, 0.9, 0.0);
	if (clear) {

		glClear(GL_COLOR_BUFFER_BIT);

		for (myShape* o : objects) {
			if (o == deleteTarget) {
				o->displayBorder(borderBoxID);
			}
			o->draw();
		}
		for (myTexts* t : textObjs) {
			if (t == deleteTarget) {
				t->displayBorder(borderBoxID);
			}
			t->draw();
		}
	}

	glColor3f(r, g, b);

	switch (mode) {
	case 1:
		if (mouseX != -1 && mouseY != -1 && clickedLeft && !inClick) {
			if (r == -1 && g == -1 && b == -1)
				glColor3f(0, 0, 0);
			line->draw();
		}
		break;
	case 2:
		if (mouseX != -1 && mouseY != -1 && clickedLeft && !inClick) {
			if (r == -1 && g == -1 && b == -1)
				glColor3f(0, 0, 0);
			rectangle->draw();
			clear = true;
		}
		break;
	case 3:
		if (mouseX != -1 && mouseY != -1 && clickedLeft && !inClick) {
			if (r == -1 && g == -1 && b == -1)
				glColor3f(0, 0, 0);
			triangle->draw();
			clear = true;
		}
		break;
	case 4:
		if (mouseX != -1 && mouseY != -1 && clickedLeft && !inClick) {
			if (r == -1 && g == -1 && b == -1)
				glColor3f(0, 0, 0);
			circle->draw();
			clear = true;
		}
	default:
		break;
	}

	glFlush();
}

void reshape(int w, int h) {
	width = w, height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	if (deleteTarget != 0) {
		if (key == 127) {
			for (vector<myShape*>::iterator it = objects.begin(); it != objects.end(); ++it) {
				if (*it == deleteTarget) {
					objects.erase(it);
					break;
				}
			}
		}
		if ((key == 13 && deleteTarget->getType() == 6) || keyAccepting) {
			for (myTexts* t : textObjs) {
				if (deleteTarget == t) {
					if (!keyAccepting) {
						keyAccepting = true;
					} else {
						t->addChar(key);
					}
					break;
				}
			}
		}
	}
	clear = true;
	glutPostRedisplay();
}

void init() {
	glPointSize(pointSize);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);

	mainMenu = glutCreateMenu(mainMenuHandler);
	objSubmenu = glutCreateMenu(objectSubmenuHandler);
	lineSubmenu = glutCreateMenu(lineSubmenuHandler);
	fillSubmenu = glutCreateMenu(fillSubmenuHandler);

	glutSetMenu(mainMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddSubMenu("Object", objSubmenu);
	glutAddSubMenu("Fill Object", fillSubmenu);
	glutAddSubMenu("Line Width", lineSubmenu);
	glutAddMenuEntry("Set Color", 6);
	glutAddMenuEntry("Exit", 7);

	glutSetMenu(objSubmenu);
	glutAddMenuEntry("Line", 1);
	glutAddMenuEntry("Rectangle", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Circle", 4);
	glutAddMenuEntry("Text", 5);

	glutSetMenu(fillSubmenu);
	glutAddMenuEntry("Yes", 1);
	glutAddMenuEntry("No", 0);

	glutSetMenu(lineSubmenu);
	glutAddMenuEntry("Thin", 1);
	glutAddMenuEntry("Regular", 3);
	glutAddMenuEntry("Bold", 5);
	glutAddMenuEntry("Extra Bold", 10);

	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	createBorderBoxList();
}

void getColorValue() {
	GLfloat userR, userG, userB;
	cout << "Enter R,G,B : ";
	cin >> userR >> userG >> userB;
	userR = userR > 255 ? 255 : userR;
	userG = userG > 255 ? 255 : userG;
	userB = userB > 255 ? 255 : userB;
	r = userR / 255, g = userG / 255, b = userB / 255;
	glColor3f(r, g, b);
}

void mainMenuHandler(int value) {
	switch (value) {
	case 5:
		mode = value;
		break;
	case 6:
		getColorValue();
		break;
	case 7:
		exit(0);
	default:
		break;
	}
}

void objectSubmenuHandler(int value) {
	glColor3f(r, g, b);
	mode = value;
}

void lineSubmenuHandler(int value) {
	pointSize = value;
	glPointSize(pointSize);
}

void fillSubmenuHandler(int value) {
	fillObj = value;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("±×¸²ÆÇ");

	init();
	glutMainLoop();
	return 0;
}