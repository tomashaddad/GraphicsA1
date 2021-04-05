#define _USE_MATH_DEFINES
#include <cmath>
#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Point.h"

#include <random>

Asteroid::Asteroid(Vector position, Vector direction, float base_size,
	float deviation, int segments, float velocity)
	: position_(position),
	  direction_(direction),
	  average_radius_(base_size),
	  radius_deviation_(deviation),
	  segments_(segments),
	  velocity_(velocity)
{
	float x, y, theta;
	float radius;
	std::random_device engine;
	std::uniform_real_distribution<float> uniform_dist;
	for (int i = 0; i < segments_; ++i) {
		uniform_dist = std::uniform_real_distribution<float>
			{ average_radius_ - radius_deviation_, average_radius_ + radius_deviation_};
		radius = uniform_dist(engine);

		theta = i / (float)segments_ * 2 * M_PI;
		x = radius * cosf(theta);
		y = radius * sinf(theta);

		points_.push_back(Point{ x, y });
	}
}

void Asteroid::update(float dt) {
	position_ += direction_ * velocity_ * dt;
}

void Asteroid::drawAsteroid() {
	glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		for (Point& point : points_) {
			glVertex2f(position_.x + point.x, position_.y + point.y);
		}
	glEnd();
}

float Asteroid::getCollisionRadius() {
	return average_radius_;
}

Vector Asteroid::getPosition() {
	return position_;
}