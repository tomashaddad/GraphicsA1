#include <corecrt_math_defines.h>
#include <cmath>

#include "AsteroidField.h"
#include "Asteroid.h"
#include "AsteroidDefines.h"
#include "Utility.h"

#include <vector>

AsteroidField::AsteroidField(BlackHole& black_hole)
	: asteroid_count_(1),
	  radius_(0),
	  timer_(0),
	  time_between_levels_(TIME_BETWEEN_WAVES),
	  levelling_up_(false),
	  black_hole_(black_hole) {}

void AsteroidField::updateRadius(const double window_width,
	const double window_height) {
	radius_ = 0.5 * hypot(window_width, window_height);
}

void AsteroidField::launchAsteroidsAtShip(Vector ship_position) {
	for (int i = 0; i < asteroid_count_; ++i) {
		const double theta =
			Utility::getRandomDoubleBetween(0, 360) * M_PI / 180.0;

		Vector position{ radius_ * cos(theta), radius_ * sin(theta) };

		Vector velocity = ship_position - position;
		velocity.normalise();
		const double scalar =
			Utility::getRandomDoubleBetween(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
		velocity = velocity * scalar;

		asteroids_.emplace_back(position, velocity,
			ASTEROID_RADIUS_DEVIATION, ASTEROID_SEGMENTS, black_hole_);
	}
	levelling_up_ = false;
}

std::vector<Asteroid>& AsteroidField::getAsteroids() {
	return asteroids_;
}

void AsteroidField::reset() {
	asteroids_.clear();
	asteroid_count_ = 1;
	timer_ = 0;
}

void AsteroidField::increaseAsteroidCountBy(int counter) {
	asteroid_count_ += counter;
}

int AsteroidField::asteroidCount() const {
	return asteroid_count_;
}

bool AsteroidField::isEmpty() const {
	return asteroids_.empty();
}

bool AsteroidField::levellingUp() const {
	return levelling_up_;
}

void AsteroidField::update(double dt, double arena_xmax, double arena_ymax) {
	for (auto i = 0; i < asteroids_.size(); ++i) {
		asteroids_[i].update(dt, arena_xmax, arena_ymax, radius_);
		
		// swap an asteroid to be deleted with the last asteroid and pop
		if (asteroids_[i].markedForDeletion()) {
			std::swap(asteroids_[i], asteroids_.back());
			asteroids_.pop_back();
		}
	}

	if (timer_ < time_between_levels_) {
		timer_ += dt;
	}
	
	if (timer_ >= time_between_levels_) {
		levelling_up_ = true;
		timer_ = 0;
	}
}