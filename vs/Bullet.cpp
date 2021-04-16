#include "Bullet.h"
#include "Vector.h"
#include "GlutHeaders.h"

Bullet::Bullet(Vector position, Vector velocity)
	: position_(position),
	  velocity_(velocity),
	  to_delete_(false) {}

void Bullet::update(double dt) {
	position_ = position_ + velocity_ * dt;
}

void Bullet::draw() const {
	glPointSize(5);
	glBegin(GL_POINTS);
		glColor3f(1, 1, 1);
		glVertex2d(position_.x, position_.y);
	glEnd();
}

Vector Bullet::getPosition() const {
	return position_;
}

void Bullet::markForDeletion() {
	to_delete_ = true;
}

bool Bullet::markedForDeletion() const {
	return to_delete_;
}