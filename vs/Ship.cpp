#include "GlutHeaders.h"
#include "Ship.h"
#include "ShipConstants.h"


Ship::Ship(BlackHole& black_hole)
	: width_(SHIP_WIDTH),
	  height_(SHIP_HEIGHT),
	  cur_angle_(0),
	  init_angle_(0),
	  radius_(SHIP_COLLISION_RADIUS),
	  warning_radius_(SHIP_WARNING_RADIUS),
	  bullet_timer_(0),
	  fire_rate_(FIRE_RATE),
	  black_hole_(black_hole),
	  bullet_stream_(black_hole) {}

void Ship::setStartingPosition(double x, double y) {
	position_.x = x;
	position_.y = y;
	starting_position_ = position_;
	init_angle_ = cur_angle_;
}

void Ship::drawShip() {
	double half_width = width_ / 2.0;
	double half_height = height_ / 2.0;
	double tail = position_.x - 0.25 * width_;

	// Isolate ship
	glPushMatrix();
		// Handle rotations
		glTranslated(position_.x, position_.y, 0);
		glRotatef(cur_angle_, 0, 0, 1);
		glTranslated(-position_.x, -position_.y, 0);

		// Draw outline
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);
		glColor3f(SHIP_LINE_RGB);
		traceVertices(half_width, half_height, tail);

		// Fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(SHIP_FILL_RGB);
		traceVertices(half_width, half_height, tail);
	glPopMatrix();
}

void Ship::traceVertices(const double width, const double height,
	double tail) const {
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2d(position_.x - width, position_.y + height);
		glVertex2d(tail, position_.y);
		glVertex2d(position_.x + width, position_.y);
		glVertex2d(position_.x - width, position_.y - height);
	glEnd();
}

void Ship::move(const Movement movement, double dt) {
	if (movement == Movement::move_forward) {
		acceleration_ = Vector(cur_angle_) * SHIP_ACCELERATION;
	}
	else if (movement == Movement::move_backward) {
		acceleration_ = -Vector(cur_angle_) * SHIP_ACCELERATION;
	}

	exhaust_.addParticle(position_, acceleration_);
}

void Ship::drawExhaust() {
	exhaust_.drawAll();
}

void Ship::rotate(const Movement movement, const double dt) {
	if (movement == Movement::rotate_right) {
		cur_angle_ -= SHIP_TURN_RATE * dt;
	}
	else if (movement == Movement::rotate_left) {
		cur_angle_ += SHIP_TURN_RATE * dt;
	}
}

void Ship::setAcceleration(const Vector vec) {
	acceleration_ = vec;
}

void Ship::update(const double dt) {
	const Vector drag = -velocity_ * 0.5;
	const Vector pull = black_hole_.pull(position_, dt);
	velocity_ = velocity_ + (acceleration_ + drag) * dt;
	velocity_ = velocity_ + pull * SHIP_BH_MULT;
	position_ = position_ + velocity_ * dt;

	if (bullet_timer_ < fire_rate_) {
		bullet_timer_ += dt;
	}

	exhaust_.update(dt);
}

void Ship::setPosition(const Point point) {
	position_.x = point.x;
	position_.y = point.y;
}

Vector Ship::getPosition() const {
	return position_;
}

double Ship::getCollisionRadius() const  {
	return radius_;
}

double Ship::getWarningRadius() const {
	return warning_radius_;
}

void Ship::reset() {
	acceleration_ = { 0,0 };
	velocity_ = { 0,0 };
	position_ = starting_position_;
	cur_angle_ = init_angle_;
	exhaust_.clear();
	bullet_stream_.clear();
	bullet_timer_ = 0;
}

void Ship::setRotation(const double rotation) {
	cur_angle_ = rotation;
}

BulletStream& Ship::getBulletStream() {
	return bullet_stream_;
}

void Ship::drawBullets(const double dt) {
	bullet_stream_.updateBullets(dt);
	bullet_stream_.drawAll();
}

void Ship::shootBullet(const double dt) {
	// only shoot a bullet if we have elapsed the fire rate, then reset timer
	if (bullet_timer_ >= fire_rate_) {
		bullet_stream_.addBullet(position_, cur_angle_, SHIP_WIDTH);
		bullet_timer_ = 0;
	}
}