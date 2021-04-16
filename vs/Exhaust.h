#ifndef I3D_EXHAUST_H
#define I3D_EXHAUST_H

#include "ExhaustParticle.h"
#include "Vector.h"
#include <vector>

class Exhaust {
public:
	Exhaust();
	void addParticle(Vector position, Vector ship_acceleration);
	void update(double dt);
	void drawAll();
	void clear();

private:
	std::vector<ExhaustParticle> exhaust_;
	int max_size_; // enforces max size
	double exhaust_timer_;
	double drop_rate_;
};

#endif // I3D_EXHAUST_H