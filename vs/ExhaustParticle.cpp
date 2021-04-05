#include "ExhaustParticle.h"
#include <iostream>
#include <random>


ExhaustParticle::ExhaustParticle(Vector position, Vector direction,
	Vector velocity)
	: size_(10),
	  position_(position),
	  direction_(direction),
	  velocity_(velocity) {}

void ExhaustParticle::update(float dt) {
	std::random_device engine;

	std::uniform_real_distribution<float> real_dist =
		std::uniform_real_distribution<float>{ -5, 5 };

	float rand_angle = real_dist(engine);

	direction_.rotate(rand_angle);

	velocity_ = velocity_ + direction_ * dt * 200;
	position_ = position_ + velocity_ * dt;
	size_ -= 0.1f;
}

// Note to self: Changing this from int to float will kill program since
//  this is used for glPointSize() which only likes integers
int ExhaustParticle::size() {
	return size_;
}

void ExhaustParticle::draw() {
	glPointSize(size_);
	glBegin(GL_POINTS);
	if (size_ > 9) {
		glColor3f(1.0, 1.0, 1.0);
	} else if (size_ > 7) {
		glColor3f(1.0, 1.0, 0.5);
	} else if (size_ > 5) {
		glColor3f(1.0, 1.0, 0);
	} else if (size_ > 3) {
		glColor3f(1.0, 0.5, 0.0);
	} else {
		glColor3f(1.0, 0.0, 0.0);
	}
		glVertex2f(position_.x, position_.y);
	glEnd();
}
