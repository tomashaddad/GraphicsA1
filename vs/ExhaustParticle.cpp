#include "ExhaustParticle.h"
#include <iostream>
ExhaustParticle::ExhaustParticle(Vector position, Vector direction,
	GLfloat velocity)
	: size_(10),
	  position_(position),
	  direction_(direction),
	  velocity_(velocity) {}

void ExhaustParticle::update(float dt) {
	position_ += direction_ * velocity_ * dt;
}

int ExhaustParticle::size() {
	return size_;
}

GLfloat ExhaustParticle::getX() {
	return position_.x;
}

GLfloat ExhaustParticle::getY() {
	return position_.y;
}