#include "GlutHeaders.h"
#include "Ship.h"
#include "Defines.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Ship::Ship(GLfloat width, GLfloat height, GLfloat radius, GLfloat warning_radius,
	GLfloat velocity, GLfloat acceleration)
	: width_(width),
	  height_(height),
	  radius_(radius),
	  warning_radius_(warning_radius),
	  velocity_(velocity),
	  acceleration_(acceleration)
{
	setStartingPosition(2 * MAX_ARENA_X, 2 * MAX_ARENA_Y);
}

void Ship::setStartingPosition(float arena_width, float arena_height) {
	float slope = arena_height / arena_width;
	float angle = 180.0 * (atanf(slope) / M_PI);
	float margin = 0.1; // arbitrary

	position_.x = -MAX_ARENA_X + arena_width * margin;
	position_.y = slope * position_.x; // y = mx + c

	std::cout << angle << std::endl;

	direction_ = Vector(0);

	starting_position_ = position_;
	starting_dir_ = direction_;
}

void Ship::drawSpaceShip() {
	GLfloat half_width = width_ / (GLfloat)2.0;
	GLfloat half_height = height_ / (GLfloat)2.0;
	GLfloat tail = position_.x - (GLfloat)1/3 * width_;

	// Isolate ship
	glPushMatrix();
		// Handle rotations
		glTranslatef(position_.x, position_.y, 0);
		glRotatef(direction_.getAngle(), 0, 0, 1);
		glTranslatef(-position_.x, -position_.y, 0);

		// Draw outline
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);
		glColor3f(SHIP_LINE_RGB);
		traceVertices(half_width, half_height, tail);

		// Fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(SHIP_FILL_RGB);
		traceVertices(half_width, half_height, tail);
	glPopMatrix();

	//float x, y, theta;
	//glBegin(GL_LINE_LOOP);
	//glColor3f(1, 1, 1);
	//for (int i = 0; i < 30; ++i) {
	//	theta = i / (float)30 * 2 * M_PI;
	//	x = radius_ * cosf(theta) + position_.x;
	//	y = radius_ * sinf(theta) + position_.y;
	//	glVertex2f(x, y);
	//}
	//glEnd();

	//glBegin(GL_LINE_LOOP);
	//glColor3f(1, 1, 1);
	//for (int i = 0; i < 30; ++i) {
	//	theta = i / (float)30 * 2 * M_PI;
	//	x = warning_radius_ * cosf(theta) + position_.x;
	//	y = warning_radius_ * sinf(theta) + position_.y;
	//	glVertex2f(x, y);
	//}
	//glEnd();
}

void Ship::traceVertices(GLfloat width, GLfloat height, GLfloat tail) {
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(position_.x - width, position_.y + height);
		glVertex2f(tail, position_.y);
		glVertex2f(position_.x + width, position_.y);
		glVertex2f(position_.x - width, position_.y - height);
	glEnd();
}

// TODO: ASK IF THIS IS CORRECT LOGIC?

void Ship::move(Movement movement, float dt) {
	if (movement == Movement::MOVE_FORWARD) {
		velocity_ = velocity_ + direction_ * acceleration_ * dt;
	}
	else if (movement == Movement::MOVE_BACKWARD) {
		velocity_ = velocity_ - direction_ * acceleration_ * dt;
	}
	position_ = position_ + velocity_ * dt;

	exhaust_.addParticle(position_, -direction_, velocity_);
	exhaust_.updateParticles(dt);
}

void Ship::drawExhaust() {
	exhaust_.drawAll();
}

void Ship::rotate(Movement movement) {
	if (movement == Movement::ROTATE_RIGHT) {
		direction_.rotate(-2);
	}
	else if (movement == Movement::ROTATE_LEFT) {
		direction_.rotate(2);
	}
}

void Ship::deaccelerate(float dt) {
	velocity_ = velocity_ * 0.99;
	position_ = position_ + velocity_ * dt;

	exhaust_.updateParticles(dt);
}

void Ship::setPosition(Point point) {
	position_.x = point.x;
	position_.y = point.y;
}

Vector Ship::getPosition() {
	return position_;
}

Vector Ship::getDirection() {
	return direction_;
}

float Ship::getCollisionRadius() {
	return radius_;
}

float Ship::getWarningRadius() {
	return warning_radius_;
}

void Ship::reset() {
	velocity_ = 0;
	position_ = starting_position_;
	direction_ = starting_dir_;
}