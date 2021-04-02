#include "Wall.h"

void Wall::drawWall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	glLineWidth(1.0);
	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}