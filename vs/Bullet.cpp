#include "Bullet.h"
#include "Vector.h"
#include "GlutHeaders.h"

Bullet::Bullet(Vector position, Vector velocity)
	: position_(position),
	  velocity_(velocity),
	  to_delete_(false) {}

void Bullet::update(float dt) {
	position_ = position_ + velocity_ * dt;
}

void Bullet::draw() {
	glPointSize(5);
	glBegin(GL_POINTS);
		glColor3f(1, 1, 1);
		glVertex2f(position_.x, position_.y);
	glEnd();
}

Vector Bullet::getPosition()
{
	return position_;
}

void Bullet::markForDeletion() {
	to_delete_ = true;
}

bool Bullet::markedForDeletion() {
	return to_delete_;
}