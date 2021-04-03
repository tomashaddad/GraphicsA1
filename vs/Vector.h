#ifndef I3D_VECTOR_H
#define I3D_VECTOR_H

#define _USE_MATH_DEFINES
#include <math.h>

class Vector {
public:
	Vector() = default;
	Vector(float angle_degrees);
	Vector(float x, float y);

	float x, y;

	void rotate(float angle_degrees);
	float getAngle();

	Vector operator=(const Vector& rhs);
	Vector& operator+=(const Vector& rhs);
	Vector& operator-=(const Vector& rhs);
	Vector operator*(float x);
};

#endif // I3D_STRUCTS_H