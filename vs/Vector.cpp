#include "Vector.h"
#include <iostream>

Vector::Vector() : x(0), y(0) {}

Vector::Vector(float x, float y) : x(x), y(y) { }

Vector::Vector(float angle_degrees) {
	float angle_radians = angle_degrees * M_PI / 180;
	this->x = cosf(angle_radians);
	this->y = sinf(angle_radians);
}

// https://matthew-brett.github.io/teaching/rotation_2d.html
void Vector::rotate(float angle_degrees) {
	float angle_radians = angle_degrees * M_PI / 180;
	x = x * cosf(angle_radians) - y * sinf(angle_radians);
	y = x * sinf(angle_radians) + y * cosf(angle_radians);
}

float Vector::getAngle() {
	return (atan2f(y, x) * 180.0) / M_PI;
}

Vector& Vector::operator+=(const Vector& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}


Vector& Vector::operator-=(const Vector& rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}
