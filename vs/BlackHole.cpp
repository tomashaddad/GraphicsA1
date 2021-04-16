#include "BlackHole.h"
#include "BlackHoleDefines.h"
#include "GlutHeaders.h"

#include <corecrt_math_defines.h>
#include <cmath>

BlackHole::BlackHole()
	: timer_(0),
	  pulse_rate_(BH_PULSE_RATE),
	  radius_(BH_RADIUS) {}

void BlackHole::draw() const {
	double x, y, theta;
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	for (double i = 0; i < 30; ++i) {
		theta = i / 30.0 * 2.0 * M_PI;
		x = radius_ * cos(theta) + position_.x;
		y = radius_ * sin(theta) + position_.y;
		glVertex2d(x, y);
	}
	glEnd();
}

void BlackHole::update(double dt) {
	radius_ -= pulse_rate_ * dt;

	if (radius_ <= 0 || timer_ >= BH_PULSE_RATE) {
		radius_ = BH_RADIUS;
		timer_ = 0;
	}
	
	if (timer_ < BH_PULSE_RATE) {
		timer_ += dt;
	}
}

Vector BlackHole::getPosition() const {
	return position_;
}

void BlackHole::reset() {
	radius_ = BH_RADIUS;
	timer_ = 0;
}

Vector BlackHole::pull(const Vector other_position, const double other_mass) const {
	Vector pull = position_ - other_position;
	pull.normalise();
	const double magnitude_sq = pull.getMagnitude() * pull.getMagnitude();
	const double root_magnitude = 
		(BH_PULL_STRENGTH * radius_ * other_mass) / magnitude_sq;
	pull = pull * root_magnitude * 20;
	
	return pull;
}