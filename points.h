#pragma once
#ifndef __POINTS__
#define __POINTS__

#include <GL/glut.h>
class Points
{
public:
	Points();
	Points(GLfloat x, GLfloat y);
	~Points();
	GLfloat getX() { return x; }
	GLfloat getY() { return y; }
	void setX(GLfloat x);
	void setY(GLfloat y);
	bool operator == (const Points c2) {
		return x == c2.x && y==c2.y;
	}
private:
	GLfloat x, y;
};

Points::Points() {
	this->x = 0;
	this->y = 0;
}

Points::Points(GLfloat x, GLfloat y)
{
	this->x = x;
	this->y = y;
}

Points::~Points()
{
}
inline void Points::setX(GLfloat x) {
	this->x = x;
}
inline void Points::setY(GLfloat y) {
	this->y = y;
}
#endif // !__POINTS__
