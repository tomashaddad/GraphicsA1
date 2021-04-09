#include "GlutHeaders.h"
#include "Ship.h"
#include "Defines.h"
#define _USE_MATH_DEFINES
#include <math.h>

Ship::Ship(float width, float height, float radius, float warning_radius)
	: width_(width),
	  height_(height),
	  radius_(radius),
	  warning_radius_(warning_radius),
	  cur_angle_(0),
	  init_angle_(0),
	  bullet_timer_(0),
	  fire_rate_(FIRE_RATE) {}

void Ship::setStartingPosition(float x, float y) {
	position_.x = x;
	position_.y = y;
	starting_position_ = position_;
	init_angle_ = cur_angle_;
}

void Ship::drawSpaceShip() {
	float half_width = width_ / (GLfloat)2.0;
	float half_height = height_ / (GLfloat)2.0;
	float tail = position_.x - (GLfloat)1/3 * width_;

	// Isolate ship
	glPushMatrix();
		// Handle rotations
		glTranslatef(position_.x, position_.y, 0);
		glRotatef(cur_angle_, 0, 0, 1);
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

void Ship::traceVertices(float width, float height, float tail) {
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
		acceleration_ = Vector((float)cur_angle_) * (float)SHIP_ACCELERATION;
	}
	else if (movement == Movement::MOVE_BACKWARD) {
		acceleration_ = -Vector((float)cur_angle_) * (float)SHIP_ACCELERATION;
	}

	exhaust_.addParticle(position_, acceleration_);
	//exhaust_.update(dt); // TODO: Get rid of this?
}

void Ship::drawExhaust() {
	exhaust_.drawAll();
}

void Ship::rotate(Movement movement, float dt) {
	if (movement == Movement::ROTATE_RIGHT) {
		cur_angle_ -= SHIP_TURN_RATE * dt;
	}
	else if (movement == Movement::ROTATE_LEFT) {
		cur_angle_ += SHIP_TURN_RATE * dt;
	}
}

void Ship::setAcceleration(Vector vec) {
	acceleration_ = vec;
}

void Ship::update(float dt) {
	Vector drag = -velocity_ * 0.5;
	velocity_ = velocity_ + (acceleration_ + drag) * dt;
	position_ = position_ + velocity_ * dt;

	if (bullet_timer_ < fire_rate_) {
		bullet_timer_ += dt;
	}

	exhaust_.update(dt);
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

void Ship::reset() {
	acceleration_ = { 0,0 };
	velocity_ = { 0,0 };
	position_ = starting_position_;
	cur_angle_ = init_angle_;
	exhaust_.clear();
	bulletStream_.clear();
}

void Ship::setRotation(float rotation) {
	cur_angle_ = rotation;
}

BulletStream& Ship::getBulletStream() {
	return bulletStream_;
}

void Ship::drawBullets(float dt) {
	bulletStream_.updateBullets(dt);
	bulletStream_.drawAll();
}

void Ship::shootBullet(float dt) {
	// only shoot a bullet if we have elapsed the fire rate, then reset timer
	if (bullet_timer_ >= fire_rate_) {
		bulletStream_.addBullet(position_, cur_angle_);
		bullet_timer_ = 0;
	}
}