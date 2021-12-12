#pragma once
#ifndef __SHAPES__
#define __SHAPES
#include <GL/glut.h>
#include "points.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class myShape
{
public:
	myShape() {}
	myShape(Points* topLeft, Points* topRight, Points* bottomLeft, Points* bottomRight, GLfloat r, GLfloat g, GLfloat b, bool fill) {
		this->topLeft = *topLeft;
		this->topRight = *topRight;
		this->bottomLeft = *bottomLeft;
		this->bottomRight = *bottomRight;
		this->r = r;
		this->g = g;
		this->b = b;
		this->fill = fill;
	}

	myShape(Points* topLeft, Points* topRight, Points* bottomLeft, Points* bottomRight, GLfloat r, GLfloat g, GLfloat b) {
		this->topLeft = *topLeft;
		this->topRight = *topRight;
		this->bottomLeft = *bottomLeft;
		this->bottomRight = *bottomRight;
		this->r = r;
		this->g = g;
		this->b = b;
		this->fill = true;
	}
	~myShape() {

	}
	bool operator == (const myShape c2) {
		return this->topLeft == c2.topLeft && this->topRight == c2.topRight && this->bottomLeft == c2.bottomLeft && this->bottomRight == c2.bottomRight;
	}
	virtual void setPoints(GLfloat mouseX, GLfloat mouseY) {
		this->topRight.setX(mouseX);
		this->bottomLeft.setY(mouseY);
		this->bottomRight.setX(mouseX);
		this->bottomRight.setY(mouseY);
	}
	virtual bool isInObj(GLfloat x, GLfloat y) { return true; }
	virtual void draw() { return; }
	void printPoints() {
		cout << "topLeft" << this->topLeft.getX() << " " << this->topLeft.getY() << endl;
		cout << "topRight" << this->topRight.getX() << " " << this->topRight.getY() << endl;
		cout << "bottomLeft" << this->bottomLeft.getX() << " " << this->bottomLeft.getY() << endl;
		cout << "bottomRight" << this->bottomRight.getX() << " " << this->bottomRight.getY() << endl;
	}
	void toString() {
		cout << "shape" << endl;
	}
	int getType() { return type; }
	virtual void displayBorder(int listID);
private:

protected:
	Points topLeft, topRight, bottomLeft, bottomRight;
	GLfloat r, g, b;
	bool fill;
	int type = 1;
};

void myShape::displayBorder(int listID) {
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(topLeft.getX() - 5, topLeft.getY(), 0);
	glCallList(listID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topRight.getX(), topRight.getY(), 0);
	glCallList(listID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bottomLeft.getX() - 5, bottomLeft.getY() - 5, 0);
	glCallList(listID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bottomRight.getX(), bottomRight.getY() - 5, 0);
	glCallList(listID);
	glPopMatrix();
}

class myRectangle : public myShape {
public:
	myRectangle() :myShape() { this->type = 2; }
	myRectangle(Points* topLeft, Points* topRight, Points* bottomLeft, Points* bottomRight, GLfloat r, GLfloat g, GLfloat b, bool fill) : myShape(topLeft, topRight, bottomLeft, bottomRight, r, g, b, fill) { this->type = 2; }
	~myRectangle() {

	}
	void draw();
	void toString() {
		cout << "rectangle" << endl;
	}
	virtual bool isInObj(GLfloat x, GLfloat y);
private:

};

inline void myRectangle::draw() {
	glColor3f(this->r, this->g, this->b);
	if (this->fill) {
		glBegin(GL_POLYGON);
		glVertex2f(this->topLeft.getX(), this->topLeft.getY());
		glVertex2f(this->topRight.getX(), this->topRight.getY());
		glVertex2f(this->bottomRight.getX(), this->bottomRight.getY());
		glVertex2f(this->bottomLeft.getX(), this->bottomLeft.getY());
		glEnd();
	} else {
		glBegin(GL_LINE_LOOP);
		glVertex2f(this->topLeft.getX(), this->topLeft.getY());
		glVertex2f(this->topRight.getX(), this->topRight.getY());
		glVertex2f(this->bottomRight.getX(), this->bottomRight.getY());
		glVertex2f(this->bottomLeft.getX(), this->bottomLeft.getY());
		glEnd();
	}
}
inline bool myRectangle::isInObj(GLfloat x, GLfloat y) {
	if (x >= topLeft.getX() && x <= topRight.getX() && y <= topLeft.getY() && y >= bottomLeft.getY())
		return true;
	else return false;
}

class myTriangle : public myShape {
public:
	myTriangle() : myShape() { this->type = 3; }
	myTriangle(Points* topLeft, Points* topRight, Points* bottomLeft, Points* bottomRight, GLfloat r, GLfloat g, GLfloat b, bool fill) : myShape(topLeft, topRight, bottomLeft, bottomRight, r, g, b, fill) { this->type = 3; }
	~myTriangle() {

	}
	void draw();
	void toString() {
		cout << "triangle" << endl;
	}
	virtual bool isInObj(GLfloat x, GLfloat y);
	void setPoints(GLfloat mouseX, GLfloat mouseY) {
		this->topRight.setX(mouseX);
		this->bottomLeft.setY(mouseY);
		this->bottomRight.setX(mouseX);
		this->bottomRight.setY(mouseY);
		GLfloat middle_x = (this->topLeft.getX() + this->topRight.getX()) / 2;
		middlePoint.setX(middle_x);
		middlePoint.setY(topLeft.getY());
	}
private:
	Points middlePoint = *new Points();
};

inline void myTriangle::draw() {

	glColor3f(this->r, this->g, this->b);
	if (this->fill) {
		glBegin(GL_TRIANGLES);
		glVertex2f(this->middlePoint.getX(), this->middlePoint.getY());
		glVertex2f(this->topLeft.getX(), this->bottomRight.getY());
		glVertex2f(this->topRight.getX(), this->bottomRight.getY());
		glEnd();
	} else {
		glBegin(GL_LINE_LOOP);
		glVertex2f((this->topLeft.getX() + this->topRight.getX()) / 2, this->topLeft.getY());
		glVertex2f(this->topLeft.getX(), this->bottomRight.getY());
		glVertex2f(this->topRight.getX(), this->bottomRight.getY());
		glEnd();
	}

}

inline bool myTriangle::isInObj(GLfloat x, GLfloat y) {
	float alpha = ((bottomLeft.getY() - bottomRight.getY()) * (x - bottomRight.getX()) + (bottomRight.getX() - bottomLeft.getX()) * (y - bottomRight.getY())) /
		((bottomLeft.getY() - bottomRight.getY()) * (middlePoint.getX() - bottomRight.getX()) + (bottomRight.getX() - bottomLeft.getX()) * (middlePoint.getY() - bottomRight.getY()));
	float beta = ((bottomRight.getY() - middlePoint.getY()) * (x - bottomRight.getX()) + (middlePoint.getX() - bottomRight.getX()) * (y - bottomRight.getY())) /
		((bottomLeft.getY() - bottomRight.getY()) * (middlePoint.getX() - bottomRight.getX()) + (bottomRight.getX() - bottomLeft.getX()) * (middlePoint.getY() - bottomRight.getY()));
	float gamma = 1.0f - alpha - beta;

	return alpha > 0 && beta > 0 && gamma > 0;
}

class myCircle : public myShape {
public:
	myCircle() : myShape() { this->type = 4; }
	myCircle(Points* topLeft, Points* topRight, Points* bottomLeft, Points* bottomRight, GLfloat r, GLfloat g, GLfloat b, bool fill) : myShape(topLeft, topRight, bottomLeft, bottomRight, r, g, b, fill) { this->type = 4; }
	~myCircle() {

	}
	void draw();
	void setPoints(GLfloat mouseX, GLfloat mouseY) {
		this->bottomLeft.setY(mouseY);
		GLfloat x_coord = (this->topLeft.getX() - this->bottomLeft.getX()) * (this->topLeft.getX() - this->bottomLeft.getX());
		GLfloat y_coord = (this->topLeft.getY() - this->bottomLeft.getY()) * (this->topLeft.getY() - this->bottomLeft.getY());
		this->radius = sqrt(x_coord + y_coord) / 2;
		this->topRight.setX(topLeft.getX() + radius * 2);
		this->bottomRight.setX(topLeft.getX() + radius * 2);
		this->bottomRight.setY(mouseY);
	}
	void toString() {
		cout << "circle" << endl;
	}
	virtual bool isInObj(GLfloat x, GLfloat y);
	virtual void displayBorder(int listID);
private:
	GLfloat radius = 0;
};

inline void myCircle::draw() {
	glColor3f(this->r, this->g, this->b);
	glPushMatrix();
	glTranslatef(this->topLeft.getX() + radius, this->topLeft.getY() - radius, 0);
	if (this->fill) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			double x = radius * cos(i);
			double y = radius * sin(i);
			glVertex2f(x, y);
		}
		glEnd();
	} else {
		glBegin(GL_LINE_LOOP);

		for (int i = 0; i < 360; i++)
		{
			double x = radius * cos(i);
			double y = radius * sin(i);
			glVertex2f(x, y);
		}
		glEnd();
	}
	glPopMatrix();
}

inline bool myCircle::isInObj(GLfloat x, GLfloat y)
{
	if (x >= topLeft.getX() && x <= topRight.getX() && y <= topLeft.getY() && y >= bottomLeft.getY())
		return true;
	else return false;
}

inline void myCircle::displayBorder(int listID) {
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(topLeft.getX(), topLeft.getY(), 0);
	glCallList(listID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topRight.getX(), topRight.getY(), 0);
	glCallList(listID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bottomLeft.getX(), bottomLeft.getY(), 0);
	glCallList(listID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bottomRight.getX(), bottomRight.getY(), 0);
	glCallList(listID);
	glPopMatrix();
}

class myLines : public myShape {
public:
	myLines() : myShape() { this->type = 5; }
	myLines(Points* topLeft, Points* topRight, Points* bottomLeft, Points* bottomRight, GLfloat r, GLfloat g, GLfloat b, int size) : myShape(topLeft, topRight, bottomLeft, bottomRight, r, g, b) { this->type = 5; this->size = size; }
	~myLines() {

	}
	void draw();
	void toString() {
		cout << "line" << endl;
	}
	bool isInObj(GLfloat x, GLfloat y) { return false; }
	void addPoint(GLfloat x, GLfloat y);
	vector<GLfloat> getPoints() { return vertices; }
private:
	vector<GLfloat> vertices;
	int size;
};

inline void myLines::draw() {
	glColor3f(this->r, this->g, this->b);
	glPointSize(this->size);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, this->vertices.data());
	glDrawArrays(GL_POINTS, 0, vertices.size());
	glDisableClientState(GL_VERTEX_ARRAY);
}

inline void myLines::addPoint(GLfloat x, GLfloat y) {
	vertices.push_back(x);
	vertices.push_back(y);
}

class myTexts : public myShape {
public:
	myTexts() : myShape() { this->type = 6; }
	myTexts(Points* topLeft, Points* topRight, Points* bottomLeft, Points* bottomRight, GLfloat r, GLfloat g, GLfloat b) : myShape(topLeft, topRight, bottomLeft, bottomRight, r, g, b) { this->type = 6; }
	~myTexts() {

	}
	void draw();
	void toString() {
		cout << "line" << endl;
	}
	void setPoints(GLfloat x, GLfloat y) {
		this->topRight.setX(x);
		this->bottomLeft.setY(y);
		this->bottomRight.setX(x);
		this->bottomRight.setY(y);
	}
	void setPoints(Points* topLeft, Points* topRight, Points* bottomLeft, Points* bottomRight) {
		this->topLeft = *topLeft;
		this->topRight = *topRight;
		bottomLeft->setY(topLeft->getY() - 18);
		this->bottomLeft = *bottomLeft;
		bottomRight->setY(topLeft->getY() - 18);
		this->bottomRight = *bottomRight;
		this->size = (topRight->getX() - topLeft->getX()) / 12;
	}
	bool isInObj(GLfloat x, GLfloat y);
	void addChar(char c);
	void printBuffAddr() { cout << &chars << endl; };
private:
	vector<char> chars;
	int size;
};

void myTexts::draw() {
	glLineWidth(0.1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(this->topLeft.getX(), this->topLeft.getY());
	glVertex2f(this->topRight.getX(), this->topRight.getY());
	glVertex2f(this->bottomRight.getX(), this->bottomRight.getY());
	glVertex2f(this->bottomLeft.getX(), this->bottomLeft.getY());
	glEnd();

	int stride = 0;

	for (char c : chars) {
		glRasterPos2i(this->bottomLeft.getX() + stride + 2, this->bottomLeft.getY() + 6);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
		stride += 12;
	}
	return;
}

inline bool myTexts::isInObj(GLfloat x, GLfloat y) {
	if (x >= topLeft.getX() && x <= topRight.getX() && y <= topLeft.getY() && y >= bottomLeft.getY())
		return true;
	else return false;
}

inline void myTexts::addChar(char c) {
	if (size - 1 >= chars.size())
		chars.push_back(c);
}

#endif // !__SHAPES__

