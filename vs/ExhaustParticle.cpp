#include "ExhaustParticle.h"
#include "ExhaustConstants.h"
#include "GlutHeaders.h"


ExhaustParticle::ExhaustParticle(Vector position)
	: position_(position),
	  size_(EXHAUST_STARTING_SIZE),
	  decay_(EXHAUST_STARTING_SIZE / EXHAUST_DURATION) {}

void ExhaustParticle::update(float dt) {
	size_ -= decay_ * dt; // enforces time to "decay"

	// Prevent glPointSize being given a negative number
	if (size_ < 0) {
		size_ = 0;
	}
}

// Note to self: Changing this from int to float will kill program since
//  this is used for glPointSize() which only likes integers
int ExhaustParticle::size() {
	return size_;
}

// 5 step sizes (> 4/5, 3/5, 2/5, 1/5, 0) of starting size
void ExhaustParticle::draw() const {
	glPointSize(size_);
	glBegin(GL_POINTS);
	if (size_ > 0.8 * EXHAUST_STARTING_SIZE) {
		glColor3f(1.0, 1.0, 1.0);
	} else if (size_ > 0.6 * EXHAUST_STARTING_SIZE) {
		glColor3f(1.0, 1.0, 0.5);
	} else if (size_ > 0.4 * EXHAUST_STARTING_SIZE) {
		glColor3f(1.0, 1.0, 0);
	} else if (size_ > 0.2 * EXHAUST_STARTING_SIZE) {
		glColor3f(1.0, 0.5, 0.0);
	} else {
		glColor3f(1.0, 0.0, 0.0);
	}
	glVertex2d(position_.x, position_.y);
	glEnd();
}
