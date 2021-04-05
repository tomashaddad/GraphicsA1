#include "Vector.h"
#include <cmath>

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
	normalise();
}

float Vector::getAngle() {
	return (atan2f(y, x) * 180.0) / M_PI;
}

Vector Vector::operator=(const Vector& rhs)
{
	return Vector(x = rhs.x, y = rhs.y);
}

Vector Vector::operator*(float scalar) {
	return Vector(x * scalar, y * scalar);
}

Vector Vector::operator-() {
	return Vector(-x, -y);
}

Vector Vector::operator-(const Vector& rhs) {
	return Vector(x - rhs.x, y - rhs.y);
}

Vector Vector::operator+(const Vector& rhs)
{
	return Vector(x + rhs.x, y + rhs.y);
}

float Vector::operator*(const Vector& rhs) {
	return x * rhs.x + y * rhs.x;
}

float Vector::getMagnitude() const {
	return sqrtf(x * x + y * y);
}

bool Vector::operator>(const Vector& rhs) {
	return this->getMagnitude() > rhs.getMagnitude();
}

void Vector::normalise() {
	float magnitude = sqrtf(powf(x, 2) + powf(y, 2));
	x /= magnitude;
	y /= magnitude;
}

std::ostream& operator<<(std::ostream& ostream, Vector& vector)
{
	ostream << "Magnitude: " << vector.getMagnitude() << ", Angle: " <<
		vector.getAngle() << ", (x, y) = (" << vector.x << ", " << vector.y << ")";

	return ostream;
}
