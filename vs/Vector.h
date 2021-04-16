#ifndef I3D_VECTOR_H
#define I3D_VECTOR_H

class Vector {
public:
	Vector();
	explicit Vector(double angle_degrees);
	Vector(double x, double y);

	double x, y;

	double getAngle() const;
	double getMagnitude() const;

	double getDistanceFrom(Vector v) const;

	void normalise();

	Vector& operator=(const Vector& rhs);
	Vector operator*(float scalar) const;
	Vector operator-() const;
	Vector operator-(const Vector& rhs) const;
	Vector operator+(const Vector& rhs) const;
	double operator*(const Vector& rhs) const;
	bool operator>(const Vector& rhs) const;
	bool operator!=(const Vector& rhs) const;

};

#endif // I3D_STRUCTS_H