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

void AsteroidField::launchAsteroidAtShip(Vector ship_position) {
	double theta = Utility::getRandomDoubleBetween(0, 360) * M_PI / 180.0;

	Vector position{ radius_ * cos(theta), radius_ * sin(theta) };

	Vector velocity = ship_position - position;
	velocity.normalise();
	double scalar = Utility::getRandomDoubleBetween(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
	velocity = velocity * scalar;

	asteroids_.emplace_back(position, velocity, ASTEROID_RADIUS_DEVIATION, 30);
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

void AsteroidField::updateAsteroids(double dt, double a_width, double a_height) {
	for (auto i = 0; i < asteroids_.size(); ++i) {
		asteroids_[i].update(dt, a_width, a_height);

		Vector a_pos = asteroids_[i].getPosition();
		double dist_from_center = sqrt(a_pos.x * a_pos.x + a_pos.y * a_pos.y);

		if (dist_from_center > radius_ + 5 || asteroids_[i].markedForDeletion()) {
			std::swap(asteroids_[i], asteroids_.back());
			asteroids_.pop_back();
		}
	}
}