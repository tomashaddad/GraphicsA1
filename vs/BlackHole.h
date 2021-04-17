#ifndef I3D_BLACKHOLE_H
#define I3D_BLACKHOLE_H

#include "Vector.h"

class BlackHole {
public:
	BlackHole();
	void draw() const;
	void update(double dt);
	
	Vector pull(Vector other_position, double dt) const;

	void reset();
	
	// Will never spawn a black hole in the lower left quadrant
	void randomisePosition(double arena_width, double arena_height);

	void setPosition(Vector position);
	Vector getPosition() const;
	double getRadius() const;

private:
	double timer_;
	double pulse_rate_;
	double radius_;
	Vector position_;
};

#endif // I3D_BLACKHOLE_H