#ifndef I3D_BLACKHOLE_H
#define I3D_BLACKHOLE_H

#include "Vector.h"

class BlackHole {
public:
	BlackHole();
	void draw() const;
	void update(double dt);
	
	Vector pull(Vector other_position, double other_mass) const;

	void reset();

	Vector getPosition() const;

private:
	double timer_;
	double pulse_rate_;
	double radius_;
	Vector position_;
};

#endif // I3D_BLACKHOLE_H