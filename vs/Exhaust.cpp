#include "Exhaust.h"
#include "Vector.h"
#include "Utility.h"
#include "ExhaustDefines.h"

Exhaust::Exhaust()
	: drop_rate_(EXHAUST_DROP_RATE),
	  max_size_(MAX_EXHAUST_PARTICLES) {}

void Exhaust::addParticle(Vector position, Vector ship_acceleration) {
	// Enforces max number of particles and time between dropping each
	if (exhaust_.size() < max_size_ && exhaust_timer_ >= drop_rate_) {
		ship_acceleration.normalise();

		ship_acceleration = -ship_acceleration;

		position.x = position.x + 5 * ship_acceleration.x;
		position.y = position.y + 5 * ship_acceleration.y;

		double spread = 1.87;

		position.x += Utility::getRandomDoubleBetween(-spread, spread);
		position.y += Utility::getRandomDoubleBetween(-spread, spread);
		exhaust_.emplace_back(position);
		exhaust_timer_ = 0;
	}
}

void Exhaust::update(double dt) {
	for (auto i = 0; i < exhaust_.size(); ++i) {
		exhaust_[i].update(dt);
		
		// Check for <1 so that glPointSize() is never given a negative number 
		if (exhaust_[i].size() < 1) {
			std::swap(exhaust_[i], exhaust_.back());
			exhaust_.pop_back();
		}
	}

	if (exhaust_timer_ < drop_rate_) {
		exhaust_timer_ += dt;
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