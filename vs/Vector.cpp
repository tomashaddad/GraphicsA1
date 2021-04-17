#include "Vector.h"
#include <corecrt_math_defines.h>
#include <cmath>


Vector::Vector() : x(0), y(0) {}

Vector::Vector(double x, double y) : x(x), y(y) { }

Vector::Vector(double angle_degrees) {
	const double angle_radians = angle_degrees * M_PI / 180;
	this->x = cos(angle_radians);
	this->y = sin(angle_radians);
}

double Vector::getAngle() const {
	return atan2(y, x) * 180.0 / M_PI;
}

Vector& Vector::operator=(const Vector& rhs) {
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vector Vector::operator*(double scalar) const {
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
	return sqrt(x * x + y * y);
}

bool Vector::operator>(const Vector& rhs) const {
	return this->getMagnitude() > rhs.getMagnitude();
}

bool Vector::operator!=(const Vector& rhs) const
{
	return x != rhs.x && y != rhs.y;
}

Vector Vector::normalise() {
	const double magnitude = sqrt(x*x + y*y);
	return Vector(x /= magnitude, y /= magnitude);
}

double Vector::getDistanceFrom(Vector v) const {
	return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}
