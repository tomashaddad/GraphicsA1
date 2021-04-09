#define _USE_MATH_DEFINES
#include <cmath>
#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Point.h"
#include "Defines.h"
#include "Utility.h"

#include <random>

Asteroid::Asteroid(Vector position, Vector velocity, float deviation, int segments)
	: position_(position),
	  radius_(1),
	  radius_deviation_(deviation),
	  segments_(segments),
	  velocity_(velocity),
	  angle_(0),
	  rotation_dir_(1),
	  in_arena_(false)
{
	float x, y, theta;
	float radius;
	for (int i = 0; i < segments_; ++i) {
		radius = 
			Utility::getRandomFloatBetween(radius_ - radius_deviation_,
										   radius_ + radius_deviation_);

		theta = (float)i / (float)segments_ * 2.0 * M_PI;
		x = radius * cosf(theta);
		y = radius * sinf(theta);

		points_.push_back(Point{ x, y });
	}

	rotation_speed_ =
		Utility::getRandomFloatBetween(ASTEROID_MIN_ROTATION_SPEED,
									   ASTEROID_MAX_ROTATION_SPEED);

	size_scalar_ = Utility::getRandomFloatBetween(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);
	radius_ *= size_scalar_;

	std::random_device engine;
	std::discrete_distribution<int> int_dist{ 1, 2 };
	rotation_dir_ = int_dist(engine) % 2 == 0 ? 1 : -1;
}

void Asteroid::update(float dt) {
	position_ = position_ + velocity_ * dt;
	angle_ += 180 * dt;

	if (!in_arena_) {
		in_arena_ = checkIfInArena();
	}
}

void Asteroid::drawAsteroid() {
	glPushMatrix();
		glTranslatef(position_.x, position_.y, 0);

		glRotatef(angle_ * rotation_dir_, 0, 0, 1);
		glScalef(radius_, radius_, 0.0);
		glTranslatef(-position_.x, -position_.y, 0);

		glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1);
			for (Point& point : points_) {
				glVertex2f(position_.x + point.x, position_.y + point.y);
			}
		glEnd();
	glPopMatrix();
}

bool Asteroid::checkCollision(Vector position, float radius) {
	float distance_between =
		sqrtf(powf(position.x - position_.x, 2) + powf(position.y - position_.y, 2));
	return distance_between <= radius + radius_;
}

float Asteroid::getCollisionRadius() {
	return radius_;
}

Vector Asteroid::getPosition() {
	return position_;
}

bool Asteroid::isInArena() {
	return in_arena_;
}

bool Asteroid::checkIfInArena() {
	if (position_.x - radius_ > -MAX_ARENA_X
		&& position_.x + radius_ < MAX_ARENA_X
		&& position_.y - radius_ > -MAX_ARENA_Y
		&& position_.y + radius_ < MAX_ARENA_Y) {
		std::cout << "in arena!" << std::endl;
		return true;
	}
	return false;
}

void Asteroid::bounceInX() {
	velocity_.x = -velocity_.x;
}

void Asteroid::bounceInY() {
	velocity_.y = -velocity_.y;
}