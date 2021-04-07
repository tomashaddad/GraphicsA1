#ifndef I3D_VECTOR_H
#define I3D_VECTOR_H

#define _USE_MATH_DEFINES

#include <iostream>
#include "Point.h"

class Vector {
public:
	Vector();
	Vector(float angle_degrees);
	Vector(float x, float y);

	float x, y;

	void rotate(float angle_degrees);
	float getAngle();
	float getMagnitude() const;

	void normalise();

	Vector operator=(const Vector& rhs);
	Vector operator*(float scalar);
	Vector operator-();
	Vector operator-(const Vector& rhs);
	Vector operator+(const Vector& rhs);
	float operator*(const Vector& rhs);
	bool operator>(const Vector& rhs);

	friend std::ostream& operator<<(std::ostream& ostream, Vector& vector);

};

std::ostream& operator<<(std::ostream& ostream, Vector& vector);

#endif // I3D_STRUCTS_H