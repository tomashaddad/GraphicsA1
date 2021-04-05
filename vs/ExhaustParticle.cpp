#include "ExhaustParticle.h"
#include <iostream>
#include <random>


ExhaustParticle::ExhaustParticle(Vector position, Vector direction,
	GLfloat velocity)
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

	position_ += direction_ * velocity_ * dt * 3;
	--size_;
}

int ExhaustParticle::size() {
	return size_;
}

void ExhaustParticle::draw() {
	glPointSize(size_);
	glBegin(GL_POINTS);
	if (size_ > 6) {
		glColor3f(1.0, 1.0, 0);
	}
	else if (size_ > 4) {
		glColor3f(1.0, 0.5, 0.0);
	}
	else {
		glColor3f(1.0, 0.0, 0.0);
	}
		glVertex2f(position_.x, position_.y);
	glEnd();
}
