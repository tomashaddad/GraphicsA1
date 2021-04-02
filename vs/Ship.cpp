#include "GlutHeaders.h"
#include "Ship.h"
#include "Defines.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Ship::Ship(Window window)
	: width(SHIP_WIDTH),
	  height(SHIP_HEIGHT)
{
	double slope = window.arena_height_ / window.arena_width_;
	double angle = 180.0 * (atanf(slope) / M_PI);
	double margin = 0.1; // arbitrary

	this->pos.x = -MAX_ARENA_X + window.arena_width_ * margin;
	this->pos.y = slope * this->pos.x; // y = mx + c
	this->dir = Vector(angle);
}

void Ship::drawSpaceShip() {
	GLfloat half_height = height / (GLfloat)2.0;
	GLfloat half_width = width / (GLfloat)2.0;
	GLfloat one_sixth_height = pos.y - (GLfloat)1 / 3 * height;

	// Isolate ship
	glPushMatrix();
		// Handle rotations
		glTranslatef(pos.x, pos.y, 0);
		glRotatef(dir.getAngle(), 0, 0, 1);
		glTranslatef(-pos.x, -pos.y, 0);

		// Draw outline
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);

		glBegin(GL_TRIANGLE_STRIP);
			glColor3f(SHIP_LINE_RGB);
			glVertex2f(pos.x - half_width, pos.y + half_height);
			glVertex2f(pos.x - (GLfloat)1 / 3 * width, pos.y);
			glVertex2f(pos.x + half_width, pos.y);
			glVertex2f(pos.x - half_width, pos.y - half_height);
		glEnd();

		// Fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLE_STRIP);
			glColor3f(SHIP_FILL_RGB);
			glVertex2f(pos.x - half_width, pos.y + half_height);
			glVertex2f(pos.x - (GLfloat)1 / 3 * width, pos.y);
			glVertex2f(pos.x + half_width, pos.y);
			glVertex2f(pos.x - half_width, pos.y - half_height);
		glEnd();

	glPopMatrix();

	//float x, y, theta;
	//glBegin(GL_LINE_LOOP);
	//glColor3f(1, 1, 1);
	//for (int i = 0; i < 30; ++i) {
	//	theta = i / (float)30 * 2 * M_PI;
	//	x = height * cosf(theta) + pos.x;
	//	y = height * sinf(theta) + pos.y;
	//	glVertex2f(x, y);
	//}
	//glEnd();
}

void Ship::translate(Movement movement) {
	movement == Movement::MOVE_FORWARD ? pos += dir : pos -= dir;
}

void Ship::rotate(Movement movement) {
	movement == Movement::ROTATE_RIGHT ? dir.rotate(-2) : dir.rotate(2);
}

void Ship::setPos(Point point) {
	pos.x = point.x;
	pos.y = point.y;
}