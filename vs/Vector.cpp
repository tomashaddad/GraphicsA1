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
	float angle_radians = angle_degrees * M_PI / 180.0;
	float old_x = x;
	float old_y = y;

	x = old_x * cosf(angle_radians) - old_y * sinf(angle_radians);
	y = old_x * sinf(angle_radians) + old_y * cosf(angle_radians);

	// turn back into a unit vector due to math error
	float magnitude = sqrtf(powf(x, 2) + powf(y, 2));
	x = x / magnitude;
	y = y / magnitude;
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

Vector Vector::operator*(float x) {
	return Vector(this->x * x, this->y * x);
}
