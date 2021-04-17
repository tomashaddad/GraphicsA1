#include "BlackHole.h"
#include "BlackHoleConstants.h"
#include "GlutHeaders.h"
#include "Utility.h"

#include <corecrt_math_defines.h>
#include <cmath>

#include "Asteroid.h"

BlackHole::BlackHole()
	: timer_(0),
	  pulse_rate_(BH_RADIUS / BH_RESET_TIME),
	  radius_(BH_RADIUS) {}

void BlackHole::draw() const {
	double x, y, theta;
	glBegin(GL_LINE_LOOP);
	glColor3d(BH_R, BH_G, BH_B);
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

	if (radius_ <= 0 || timer_ >= pulse_rate_) {
		radius_ = BH_RADIUS;
		timer_ = 0;
	}
	
	if (timer_ < pulse_rate_) {
		timer_ += dt;
	}
}

void BlackHole::randomisePosition(double arena_width, double arena_height) {
	double x, y;
	do {
		x = Utility::getRandomDoubleBetween(-arena_width, arena_width);
		y = Utility::getRandomDoubleBetween(-arena_height, arena_height);
	} while (x < 0 && y < 0);

	position_.x = x;
	position_.y = y;
}

void BlackHole::setPosition(Vector position) {
	position_ = position;
}


Vector BlackHole::getPosition() const {
	return position_;
}

double BlackHole::getRadius() const {
	return radius_;
}

void BlackHole::reset() {
	radius_ = BH_RADIUS;
	timer_ = 0;
}

Vector BlackHole::pull(const Vector other_position,	const double dt) const {
	const Vector pull = position_ - other_position;
	const double distance = pull.getMagnitude();

	const double square_distance = pull.getMagnitude() * pull.getMagnitude();
	const double strength = BH_PULL_STRENGTH / square_distance;
	
	return pull * strength;
}

