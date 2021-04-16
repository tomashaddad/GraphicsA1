#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Point.h"
#include "AsteroidDefines.h"
#include "Utility.h"
#include "BlackHole.h"

#include <random>
#include <corecrt_math_defines.h>
#include <cmath>

Asteroid::Asteroid(Vector position, Vector velocity, double deviation,
	int segments, BlackHole black_hole)
	: position_(position),
	  velocity_(velocity),
	  angle_(0),
	  rotation_dir_(1),
	  radius_(1),
	  radius_deviation_(deviation),
	  segments_(segments),
	  in_arena_(false),
	  to_delete_(false),
	  black_hole_(black_hole)
{
	// Creates jagged edges
	double x, y, theta;
	double radius;
	for (int i = 0; i < segments_; ++i)
	{
		radius =
			Utility::getRandomDoubleBetween(radius_ - radius_deviation_,
			                               radius_ + radius_deviation_);

		theta = static_cast<double>(i) / static_cast<double>(segments_) * 2.0 * M_PI;
		x = radius * cos(theta);
		y = radius * sin(theta);

		points_.push_back(Point{x, y});
	}

	// Selects random rotation speed from range given in Define.h
	rotation_speed_ =
		Utility::getRandomDoubleBetween(ASTEROID_MIN_ROTATION_SPEED,
		                               ASTEROID_MAX_ROTATION_SPEED);

	// The Asteroid starts as a "unit" asteroid and is enlarged by some scalar
	size_ = Utility::getRandomDoubleBetween(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);
	radius_ *= size_;

	// The health of an Asteroid is mapped to a number between 
	// ASTEROID_MIN_HEALTH and ASTEROID_MAX_HEALTH
	health_ = round(mapHealth(radius_, ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE));

	// Returns either 1 or -1 to determine asteroid rotation direction
	std::random_device engine;
	std::discrete_distribution<int> int_dist{1, 2};
	rotation_dir_ = int_dist(engine) % 2 == 0 ? 1 : -1;
}

void Asteroid::update(const double dt, const double arena_xmax,
	const double arena_ymax, const double field_radius) {
	const Vector bh_pull = black_hole_.pull(position_, radius_);
	velocity_ = velocity_ + (bh_pull) * dt;
	position_ = position_ + velocity_ * dt;
	angle_ += 180 * dt;

	if (!in_arena_) {
		in_arena_ = checkIfInArena(arena_xmax, arena_ymax);
	}

	if (health_ <= 0) {
		to_delete_ = true;
	}

	const double dist_from_center =
		sqrt(position_.x * position_.x + position_.y * position_.y);

	if (dist_from_center > field_radius + 5) {
		to_delete_ = true;
	}
}

void Asteroid::drawAsteroid() const
{
	glPushMatrix();
		glTranslated(position_.x, position_.y, 0);

		glRotated(angle_ * rotation_dir_, 0, 0, 1);
		glScaled(radius_, radius_, 0.0);
		glTranslated(-position_.x, -position_.y, 0);

		glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1);
			for (const Point& point : points_)
			{
				glVertex2d(position_.x + point.x, position_.y + point.y);
			}
		glEnd();
	glPopMatrix();
}

bool Asteroid::checkCollision(const Vector position, const double radius) const
{
	const double distance_between =
		abs(pow(position.x - position_.x, 2) + pow(position.y - position_.y, 2));
	return distance_between <= (radius + radius_) * (radius + radius_);
}

void Asteroid::resolveCollisionWith(Asteroid& other) {
	// unit normal vector
	Vector un = this->position_ - other.getPosition();
	un.normalise();
	
	// unit tangent vector
	const auto ut = Vector(-un.y, un.x);

	// resolve static collision (move away from each other slightly)
	double distance = this->position_.getDistanceFrom(other.getPosition());
	distance -= this->radius_ + other.getRadius();
	const Vector new_a1_position = this->position_ - un * 0.5 * distance;
	const Vector new_a2_position = other.getPosition() + un * 0.5 * distance;
	position_ = new_a1_position;
	other.setPosition(new_a2_position);

	// project velocities onto unit normal and unit tangent vectors
	const double v1n = un * this->velocity_;
	const double v1t = ut * this->velocity_;
	const double v2n = un * other.getVelocity();
	const double v2t = ut * other.getVelocity();

	// use the radius of the asteroids as their "mass"
	const double a1m = this->size_;
	const double a2m = other.getSize();

	// compute new scalar normal velocities
	const double new_v1n = (v1n * (a1m - a2m) + 2 * a2m * v2n) / (a1m + a2m);
	const double new_v2n = (v2n * (a2m - a1m) + 2 * a1m * v1n) / (a1m + a2m);

	// convert scalar normal velocities into vectors
	const Vector new_a1_v = un * new_v1n + ut * v1t;
	const Vector new_a2_v = un * new_v2n + ut * v2t;

	velocity_ = new_a1_v;
	other.setVelocity(new_a2_v);
}

double Asteroid::getRadius() const
{
	return radius_;
}

Vector& Asteroid::getPosition()
{
	return position_;
}

Vector& Asteroid::getVelocity()
{
	return velocity_;
}

bool Asteroid::isInArena() const
{
	return in_arena_;
}

bool Asteroid::checkIfInArena(double ax, double ay) const
{
	if (position_.x - radius_ > -ax
		&& position_.x + radius_ < ax
		&& position_.y - radius_ > -ay
		&& position_.y + radius_ < ay)
	{
		return true;
	}
	return false;
}

void Asteroid::bounceInX(double dt)
{
	// move the asteroid slightly away from the wall before changing
	// the velocity so they don't get stuck on the wall
	position_.x = position_.x < 0 ? position_.x + 0.01 : position_.x - 0.01;
	velocity_.x = -velocity_.x;
}

void Asteroid::bounceInY(double dt)
{
	// move the asteroid slightly away from the wall before changing
	// the velocity so they don't get stuck on the wall
	position_.y = position_.y > 0 ? position_.y - 0.01 : position_.y + 0.01;
	velocity_.y = -velocity_.y;
}

// Maps a range of Asteroid sizes to a health range of [1, 5]
double Asteroid::mapHealth(double radius, double min_size, double max_size)
{
	const double old_range = max_size - min_size;
	const double new_range = ASTEROID_MAX_HEALTH - ASTEROID_MIN_HEALTH;
	return (radius - min_size) * new_range / old_range + ASTEROID_MIN_HEALTH;
}

void Asteroid::decrementHealthBy(int num)
{
	health_ -= num;
}

bool Asteroid::markedForDeletion() const
{
	return to_delete_;
}

double Asteroid::getSize() const
{
	return size_;
}


void Asteroid::setVelocity(Vector v)
{
	velocity_ = v;
}

void Asteroid::setPosition(Vector v)
{
	position_ = v;
}
