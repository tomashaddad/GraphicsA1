#define _USE_MATH_DEFINES
#include <cmath>

#include "AsteroidField.h"
#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Defines.h"

#include <vector>
#include <random>
#include <iostream>

AsteroidField::AsteroidField()
	: asteroid_count_(1),
	  radius(0) {}

AsteroidField::AsteroidField(GLfloat window_width, GLfloat window_height) {
	updateRadius(window_width, window_height);
}

void AsteroidField::updateRadius(GLfloat window_width, GLfloat window_height) {
	radius = 0.5 * hypot(window_width, window_height);
}

void AsteroidField::launchAsteroidAtShip(Vector ship_position) {
	std::random_device engine;

	std::uniform_real_distribution<float> speed_dist =
		std::uniform_real_distribution<float>{ ASTEROID_MIN_SPEED,
											   ASTEROID_MAX_SPEED };

	float velocity = speed_dist(engine);

	std::uniform_real_distribution<float> angle_dist =
		std::uniform_real_distribution<float>{ 0, 360 };

	float xpos, ypos;

	float theta = angle_dist(engine); // degrees
	theta *= M_PI / 180.0;

	xpos = radius * cosf(theta);
	ypos = radius * sinf(theta);

	Vector asteroid_position{ xpos, ypos };

	Vector asteroid_direction = ship_position - asteroid_position;
	asteroid_direction.normalise();

	asteroids.push_back(
		Asteroid(
			asteroid_position,
			asteroid_direction,
			ASTEROID_BASE_SIZE,
			ASTEROID_DEVIATION,
			30,
			velocity
		)
	);
}

std::vector<Asteroid>& AsteroidField::getAsteroids() {
	return asteroids;
}

void AsteroidField::reset() {
	asteroids.clear();
	asteroid_count_ = 1;
}

void AsteroidField::increaseAsteroidCountBy(int counter) {
	asteroid_count_ += counter;
}

int AsteroidField::asteroidCount() {
	return asteroid_count_;
}

bool AsteroidField::isEmpty() {
	return asteroids.size() == 0;
}

void AsteroidField::updateAsteroids(float dt) {
	for (auto i = 0; i < asteroids.size(); ++i) {
		asteroids[i].update(dt);

		Vector a_pos = asteroids[i].getPosition();
		float dist_from_center = sqrtf(a_pos.x * a_pos.x + a_pos.y * a_pos.y);

		if (dist_from_center > radius) {
			using std::swap;
			swap(asteroids[i], asteroids.back());
			asteroids.pop_back();
		}
	}
}