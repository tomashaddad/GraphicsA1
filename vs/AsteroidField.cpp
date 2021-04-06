#define _USE_MATH_DEFINES
#include <cmath>

#include "AsteroidField.h"
#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Defines.h"
#include "Utility.h"

#include <vector>
#include <random>
#include <iostream>

AsteroidField::AsteroidField()
	: asteroid_count_(1),
	  radius_(0) {}

AsteroidField::AsteroidField(float window_width, float window_height) {
	updateRadius(window_width, window_height);
}

void AsteroidField::updateRadius(float window_width, float window_height) {
	radius_ = 0.5 * hypotf(window_width, window_height);
}

void AsteroidField::launchAsteroidAtShip(Vector ship_position) {
	using namespace Utility;

	float theta = getRandomFloatBetween(0, 360) * (float)M_PI / 180.0f;

	Vector position{ radius_ * cosf(theta), radius_ * sinf(theta) };

	Vector velocity = ship_position - position;
	velocity.normalise();
	float scalar = getRandomFloatBetween(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
	velocity = velocity * scalar;

	asteroids_.emplace_back(position, velocity, ASTEROID_BASE_SIZE,
		ASTEROID_DEVIATION, 30);
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

int AsteroidField::asteroidCount() {
	return asteroid_count_;
}

bool AsteroidField::isEmpty() {
	return asteroids_.size() == 0;
}

void AsteroidField::updateAsteroids(float dt) {
	for (auto i = 0; i < asteroids_.size(); ++i) {
		asteroids_[i].update(dt);

		Vector a_pos = asteroids_[i].getPosition();
		float dist_from_center = sqrtf(a_pos.x * a_pos.x + a_pos.y * a_pos.y);

		if (dist_from_center > radius_) {
			using std::swap;
			swap(asteroids_[i], asteroids_.back());
			asteroids_.pop_back();
		}
	}
}