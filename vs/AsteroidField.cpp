#include <corecrt_math_defines.h>
#include <cmath>

#include "AsteroidField.h"
#include "Asteroid.h"
#include "AsteroidDefines.h"
#include "Utility.h"

#include <vector>

AsteroidField::AsteroidField()
	: asteroid_count_(1),
	  radius_(0) {}

AsteroidField::AsteroidField(double window_width, double window_height) {
	updateRadius(window_width, window_height);
}

void AsteroidField::updateRadius(double window_width, double window_height) {
	radius_ = 0.5 * hypot(window_width, window_height);
}

void AsteroidField::launchAsteroidsAtShip(Vector ship_position) {
	for (int i = 0; i < asteroid_count_; ++i) {
		double theta = Utility::getRandomDoubleBetween(0, 360) * M_PI / 180.0;

		Vector position{ radius_ * cos(theta), radius_ * sin(theta) };

		Vector velocity = ship_position - position;
		velocity.normalise();
		double scalar =
			Utility::getRandomDoubleBetween(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
		velocity = velocity * scalar;

		asteroids_.emplace_back(position, velocity,
			ASTEROID_RADIUS_DEVIATION, 30);
	}
}

std::vector<Asteroid>& AsteroidField::getAsteroids() {
	return asteroids_;
}

void AsteroidField::reset() {
	asteroids_.clear();
	asteroid_count_ = 1;
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

void AsteroidField::update(double dt, double arena_xmax, double arena_ymax) {
	for (auto i = 0; i < asteroids_.size(); ++i) {
		asteroids_[i].update(dt, arena_xmax, arena_ymax, radius_);
		
		// swap an asteroid to be deleted with the last asteroid and pop
		if (asteroids_[i].markedForDeletion()) {
			std::swap(asteroids_[i], asteroids_.back());
			asteroids_.pop_back();
		}
	}
}