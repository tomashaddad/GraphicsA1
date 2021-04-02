#ifndef I3D_VECTOR_H
#define I3D_VECTOR_H

#define _USE_MATH_DEFINES
#include <math.h>

class Vector {
	Vector(float angle_degrees);
	Vector(float x, float y);

	float x, y;

	void rotate(float angle_degrees);
	float getAngle();

	//vec2d operator*(const float& scalar);
	Vector operator+(const Vector& vector);
	Vector operator-(const Vector& vector);
};

#endif // I3D_STRUCTS_H