#include "Bullet.h"
#include "Vector.h"
#include "GlutHeaders.h"
#include "BulletConstants.h"

Bullet::Bullet(Vector position, Vector velocity, BlackHole& blackhole)
	: position_(position),
	  velocity_(velocity),
	  to_delete_(false),
	  blackhole_(blackhole) {}

void Bullet::update(double dt) {
	const Vector bh_pull = blackhole_.pull(position_, dt);
	velocity_ = velocity_ + bh_pull * BULLET_BH_MULT;
	position_ = position_ + velocity_ * dt;
}

void Bullet::draw() const {
	glPointSize(BULLET_SIZE);
	glBegin(GL_POINTS);
		glColor3f(BULLET_R, BULLET_G, BULLET_B);
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