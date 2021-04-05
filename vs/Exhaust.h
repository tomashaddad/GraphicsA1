#ifndef I3D_EXHAUST_H
#define I3D_EXHAUST_H

#include "ExhaustParticle.h"
#include "GlutHeaders.h"
#include "Vector.h"
#include <deque>

class Exhaust {
public:
	void addParticle(Vector position_, Vector direction_, Vector velocity);
	void updateParticles(float dt);

	void drawAll();

private:
	std::deque<ExhaustParticle> exhaust_;
};

#endif // I3D_EXHAUST_H