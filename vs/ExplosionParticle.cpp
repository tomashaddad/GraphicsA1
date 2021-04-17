#include "ExplosionParticle.h"
#include "ExplosionConstants.h"
#include "GlutHeaders.h"

ExplosionParticle::ExplosionParticle(Vector position, Vector velocity)
	: position_(position),
	  velocity_(velocity),
	  size_(EXP_STARTING_SIZE),
	  decay_(EXP_STARTING_SIZE / EXP_DURATION) {}

void ExplosionParticle::update(const double dt) {
	position_ = position_ + velocity_ * dt;
	size_ -= decay_ * dt; // enforces time to "decay" in size

	// prevent glPointSize being given a negative number, will mark for deletion
	if (size_ < 0) {
		size_ = 0;
	}
}

int ExplosionParticle::size() const {
	return size_;
}

void ExplosionParticle::draw() const {
	glPointSize(static_cast<float>(size_));
		glBegin(GL_POINTS);
		glColor3d(EXP_R, EXP_G, EXP_B);
		glVertex2d(position_.x, position_.y);
	glEnd();
}