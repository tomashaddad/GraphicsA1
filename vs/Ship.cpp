#include "GlutHeaders.h"
#include "Ship.h"
#include "Defines.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Ship::Ship(Window window)
	: width_(SHIP_WIDTH),
	  height_(SHIP_HEIGHT),
	  radius_(SHIP_RADIUS),
	  warning_radius_(SHIP_WARNING_RADIUS),
	  velocity_(0),
	  acceleration_(SHIP_ACCELERATION)
{
	double slope = window.arena_height_ / window.arena_width_;
	double angle = 180.0 * (atanf(slope) / M_PI);
	double margin = 0.1; // arbitrary

	position_.x = -MAX_ARENA_X + window.arena_width_ * margin;
	position_.y = slope * this->position_.x; // y = mx + c
	dir_ = Vector(angle);

	starting_position_ = position_;
	starting_dir_ = dir_;
}

void Ship::drawSpaceShip() {
	GLfloat half_height = height_ / (GLfloat)2.0;
	GLfloat half_width = width_ / (GLfloat)2.0;
	GLfloat one_sixth_height = position_.y - (GLfloat)(1.0/3.0) * height_;

	// Isolate ship
	glPushMatrix();
		// Handle rotations
		glTranslatef(position_.x, position_.y, 0);
		glRotatef(dir_.getAngle(), 0, 0, 1);
		glTranslatef(-position_.x, -position_.y, 0);

		// Draw outline
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);

		glBegin(GL_TRIANGLE_STRIP);
			glColor3f(SHIP_LINE_RGB);
			glVertex2f(position_.x - half_width, position_.y + half_height);
			glVertex2f(position_.x - (GLfloat)1 / 3 * width_, position_.y);
			glVertex2f(position_.x + half_width, position_.y);
			glVertex2f(position_.x - half_width, position_.y - half_height);
		glEnd();

		// Fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLE_STRIP);
			glColor3f(SHIP_FILL_RGB);
			glVertex2f(position_.x - half_width, position_.y + half_height);
			glVertex2f(position_.x - (GLfloat)1 / 3 * width_, position_.y);
			glVertex2f(position_.x + half_width, position_.y);
			glVertex2f(position_.x - half_width, position_.y - half_height);
		glEnd();
	glPopMatrix();

	float x, y, dx, dy, theta;
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	for (int i = 0; i < 30; ++i) {
		theta = i / (float)30 * 2 * M_PI;
		x = radius_ * cosf(theta) + position_.x;
		y = radius_ * sinf(theta) + position_.y;

		dx = warning_radius_ * cosf(theta) + position_.x;
		dy = warning_radius_ * sinf(theta) + position_.y;

		glVertex2f(x, y);
		glVertex2f(dx, dy);
	}
	glEnd();
}

void Ship::translate(Movement movement, float dt) {
	if (movement == Movement::MOVE_FORWARD) {
		velocity_ += acceleration_ * dt;
	}
	else if (movement == Movement::MOVE_BACKWARD) {
		velocity_ -= acceleration_ * dt;
	}
	position_ += dir_ * velocity_ * dt;
}

void Ship::rotate(Movement movement) {
	if (movement == Movement::ROTATE_RIGHT) {
		dir_.rotate(-2);
	}
	else if (movement == Movement::ROTATE_LEFT) {
		dir_.rotate(2);
	}
}

void Ship::deaccelerate(float dt) {
	if (velocity_ > 0) {
		velocity_ -= acceleration_ * dt;
	}
	else {
		velocity_ += acceleration_ * dt;
	}
	position_ += dir_ * velocity_ * dt;
}

void Ship::setPosition(Point point) {
	position_.x = point.x;
	position_.y = point.y;
}

Vector Ship::getPosition() {
	return position_;
}

float Ship::getCollisionRadius() {
	return radius_;
}

float Ship::getWarningRadius() {
	return warning_radius_;
}

void Ship::resetPosition() {
	position_ = starting_position_;
	dir_ = starting_dir_;
}