#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector.h"


Vector::Vector() : x(0), y(0) {}

Vector::Vector(double x, double y) : x(x), y(y) { }

Vector::Vector(double angle_degrees) {
	const float angle_radians = angle_degrees * M_PI / 180;
	this->x = cosf(angle_radians);
	this->y = sinf(angle_radians);
}

double Vector::getAngle() const {
	return (atan2(y, x) * 180.0) / M_PI;
}

Vector& Vector::operator=(const Vector& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vector Vector::operator*(float scalar) const {
	return Vector(x * scalar, y * scalar);
}

Vector Vector::operator-() const {
	return Vector(-x, -y);
}

Vector Vector::operator-(const Vector& rhs) const {
	return Vector(x - rhs.x, y - rhs.y);
}

Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(x + rhs.x, y + rhs.y);
}

double Vector::operator*(const Vector& rhs) const {
	return x * rhs.x + y * rhs.y;
}

double Vector::getMagnitude() const {
	return sqrtf(x * x + y * y);
}

bool Vector::operator>(const Vector& rhs) const {
	return this->getMagnitude() > rhs.getMagnitude();
}

bool Vector::operator!=(const Vector& rhs) const
{
	return x != rhs.x && y != rhs.y;
}

void Vector::normalise() {
	const double magnitude = sqrt(x*x + y*y);
	x /= magnitude;
	y /= magnitude;
}

double Vector::getDistanceFrom(Vector v) const {
	return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}
