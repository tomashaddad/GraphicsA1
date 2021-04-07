#ifndef I3D_EXHAUST_H
#define I3D_EXHAUST_H

#include "ExhaustParticle.h"
#include "GlutHeaders.h"
#include "Vector.h"
#include <deque>

class Exhaust {
public:
	void addParticle(Vector position, Vector ship_acceleration);
	void updateParticles();
	void drawAll();
	void clear();

private:
	std::deque<ExhaustParticle> exhaust_;
};

#endif // I3D_EXHAUST_H