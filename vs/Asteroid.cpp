#define _USE_MATH_DEFINES
#include <cmath>
#include "Asteroid.h"
#include "GlutHeaders.h"
#include "Point.h"

#include <random>

Asteroid::Asteroid() : base_size_(10.0), deviation_(2.0), segments_(30)
{
	float x, y, theta;
	float radius;
	std::random_device engine;
	std::uniform_real_distribution<float> uniform_dist;
	for (int i = 0; i < segments_; ++i) {
		uniform_dist = std::uniform_real_distribution<float>{ base_size_ - deviation_, base_size_ + deviation_};
		radius = uniform_dist(engine);

		theta = i / (float)segments_ * 2 * M_PI;
		x = radius * cosf(theta);
		y = radius * sinf(theta);

		points_.push_back(Point{ x, y });
	}
}

Asteroid::Asteroid(Window window, Ship ship) : Asteroid() {
	launch_radius_ = (sqrtf((window.win_height_ * window.win_height_) + (window.win_width_ * window.win_width_)))/2.0;
	direction_ = -ship.getDirection();
}

void Asteroid::drawAsteroid() {
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		for (Point& point : points_) {
			glVertex2f(position_.x + point.x, position_.y + point.y);
		}
	glEnd();
	glPopMatrix();

	position_ += direction_ * velocity_;
}