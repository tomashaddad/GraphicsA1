#include "Exhaust.h"
#include "Vector.h"
#include "Utility.h"
#include "GlutHeaders.h"
#include <iostream>

#include <cmath>

void Exhaust::addParticle(Vector position, Vector ship_acceleration) {

	ship_acceleration.normalise();

	ship_acceleration = -ship_acceleration;

	position.x = position.x + 5 * ship_acceleration.x;
	position.y = position.y + 5 * ship_acceleration.y;

	float spread = 1.87;

	position.x += Utility::getRandomFloatBetween(-spread, spread);
	position.y += Utility::getRandomFloatBetween(-spread, spread);
	exhaust_.emplace_back(position);
}

void Exhaust::updateParticles() {
	for (ExhaustParticle& particle : exhaust_) {
		particle.update();
		if (particle.size() == 0) {
			exhaust_.pop_front();
		}
	}
}

void Exhaust::drawAll() {
	for (ExhaustParticle& particle : exhaust_) {
		particle.draw();
	}
}

void Exhaust::clear() {
	exhaust_.clear();
}