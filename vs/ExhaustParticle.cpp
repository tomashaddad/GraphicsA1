#include "ExhaustParticle.h"
#include <iostream>
#include "Utility.h"


ExhaustParticle::ExhaustParticle(Vector position)
	: size_(6),
	  position_(position) {}

void ExhaustParticle::update(float dt) {
	size_ -= 4 * dt; // TODO: This needs dt scaling?
}

// Note to self: Changing this from int to float will kill program since
//  this is used for glPointSize() which only likes integers
int ExhaustParticle::size() {
	return size_;
}

void ExhaustParticle::draw() {
	glPointSize(size_);
	glBegin(GL_POINTS);
		if (size_ > 5) {
			glColor3f(1.0, 1.0, 1.0);
		} else if (size_ > 4) {
			glColor3f(1.0, 1.0, 0.5);
		} else if (size_ > 3) {
			glColor3f(1.0, 1.0, 0);
		} else if (size_ > 2) {
			glColor3f(1.0, 0.5, 0.0);
		} else {
			glColor3f(1.0, 0.0, 0.0);
		}
			glVertex2f(position_.x, position_.y);
	glEnd();
}
