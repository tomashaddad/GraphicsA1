#include "Wall.h"

Wall::Wall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
	: x1(x1),
	  x2(x2),
	  y1(y1),
	  y2(y2) { }

void Wall::drawArena() {
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		glVertex2f(-MAX_ARENA_X, -MAX_ARENA_Y);
		glVertex2f(-MAX_ARENA_X, MAX_ARENA_Y);
		glVertex2f(MAX_ARENA_X, MAX_ARENA_Y);
		glVertex2f(MAX_ARENA_X, -MAX_ARENA_Y);
	glEnd();
}

void Wall::drawWall() {
	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}