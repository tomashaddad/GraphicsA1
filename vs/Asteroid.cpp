#define _USE_MATH_DEFINES
#include <cmath>
#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Point.h"
#include "Defines.h"

#include <random>

#include <iostream>

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
	std::uniform_real_distribution<float> real_dist;
	for (int i = 0; i < segments_; ++i) {
		real_dist = std::uniform_real_distribution<float>
			{ average_radius_ - radius_deviation_,
			  average_radius_ + radius_deviation_};
		radius = real_dist(engine);

		theta = i / (float)segments_ * 2 * M_PI;
		x = radius * cosf(theta);
		y = radius * sinf(theta);

		points_.push_back(Point{ x, y });
	}

	real_dist =
		std::uniform_real_distribution<float>{ ASTEROID_MIN_ROTATION_SPEED,
											   ASTEROID_MAX_ROTATION_SPEED };
	rotation_speed_ = real_dist(engine);

	std::discrete_distribution<int> int_dist{ 1, 2 };
	rotation_direction_ = int_dist(engine) % 2 == 0 ? 1 : -1;
}

void Asteroid::update(float dt) {
	position_ = position_ + direction_ * velocity_ * dt;
	direction_.rotate(rotation_direction_ * rotation_speed_);
}

void Asteroid::drawAsteroid() {
	glPushMatrix();
		glTranslatef(position_.x, position_.y, 0);
		glRotatef(direction_.getAngle(), 0, 0, 1);
		glTranslatef(-position_.x, -position_.y, 0);

		glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1);
			for (Point& point : points_) {
				glVertex2f(position_.x + point.x, position_.y + point.y);
			}
		glEnd();
	glPopMatrix();
}

float Asteroid::getCollisionRadius() {
	return average_radius_;
}

Vector Asteroid::getPosition() {
	return position_;
}