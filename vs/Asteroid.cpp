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
	  in_arena_(false),
	  to_delete_(false)
{
	// Creates jagged edges
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

	// Selects random rotation speed from range given in Define.h
	rotation_speed_ =
		Utility::getRandomFloatBetween(ASTEROID_MIN_ROTATION_SPEED,
									   ASTEROID_MAX_ROTATION_SPEED);

	// The Asteroid starts as a "unit" asteroid and is enlarged by some scalar
	size_scalar_ = Utility::getRandomFloatBetween(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);
	radius_ *= size_scalar_;

	// The health of an Asteroid is mapped to a number between 
	// ASTEROID_MIN_HEALTH and ASTEROID_MAX_HEALTH
	health_ = round(mapHealth(radius_, ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE));

	// Returns either 1 or -1 to determine asteroid rotation direction
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

	if (health_ <= 0) {
		to_delete_ = true;
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
		fabs(powf(position.x - position_.x, 2) + powf(position.y - position_.y, 2));
	return distance_between <= (radius + radius_)*(radius + radius_);
}

float Asteroid::getCollisionRadius() {
	return radius_;
}

Vector& Asteroid::getPosition() {
	return position_;
}

Vector& Asteroid::getVelocity() {
	return velocity_;
}

bool Asteroid::isInArena() {
	return in_arena_;
}

bool Asteroid::checkIfInArena() {
	if (position_.x - radius_ > -MAX_ARENA_X
		&& position_.x + radius_ < MAX_ARENA_X
		&& position_.y - radius_ > -MAX_ARENA_Y
		&& position_.y + radius_ < MAX_ARENA_Y) {
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

// Maps a range of Asteroid sizes to a health range of [1, 5]
float Asteroid::mapHealth(float radius, float min_size, float max_size) {
	float old_range = max_size - min_size;
	float new_range = ASTEROID_MAX_HEALTH - ASTEROID_MIN_HEALTH;
	return (((radius - min_size) * new_range) / old_range) + ASTEROID_MIN_HEALTH;
}

void Asteroid::decrementHealthBy(int num) {
	health_ -= num;
}

bool Asteroid::markedForDeletion() {
	return to_delete_;
}

void Asteroid::handleAsteroidCollision(Vector other_position, Vector other_velocity) {
	std::cout << "BEFORE:" << std::endl;
	std::cout << velocity_ << std::endl;
	Vector position_difference = position_ - other_position;
	float magnitude = position_difference.getMagnitude();
	float squared_mag = magnitude * magnitude;

	float dot_product = (velocity_ - other_velocity) * (position_ - other_position);
	velocity_ = velocity_ - (position_difference * (dot_product / squared_mag));


	std::cout << "AFTER:" << std::endl;
	std::cout << velocity_ << std::endl;
}