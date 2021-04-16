#ifndef I3D_EXHAUST_H
#define I3D_EXHAUST_H

#include "ExhaustParticle.h"
#include "GlutHeaders.h"
#include "Vector.h"
#include "ExhaustDefines.h"
#include <vector>

class Exhaust {
public:
	Exhaust();
	void addParticle(Vector position, Vector ship_acceleration);
	void update(float dt);
	void drawAll();
	void clear();

private:
	std::vector<ExhaustParticle> exhaust_;
	int max_size_; // enforces max size
	float exhaust_timer_;
	float drop_rate_;
};

#endif // I3D_EXHAUST_H