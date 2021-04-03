#include "Wall.h"
#include "Enums.h"

Wall::Wall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
	: p1{ x1, y1 },
	  p2{ x2, y2 },
	  colour(Colour::WHITE) { }

void Wall::drawWall() {

	if (colour == Colour::RED) {
		glLineWidth(3.0);
		glColor3f(1, 0, 0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(1, 1, 1);
	}

		glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
	glEnd();
}

void Wall::setColour(Colour colour) {
	this->colour = colour;
}