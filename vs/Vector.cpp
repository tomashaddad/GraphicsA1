#include "Vector.h"
#include <iostream>

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

Vector Vector::operator+(const Vector& vector) {
	return Vector(x + vector.x, y + vector.y);
}

Vector Vector::operator-(const Vector& vector)
{
	return Vector(x - vector.x, y - vector.y);
}
