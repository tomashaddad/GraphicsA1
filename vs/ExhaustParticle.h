#ifndef I3D_EXHAUSTPARTICLE_H
#define I3D_EXHAUSTPARTICLE_H

#include "GlutHeaders.h"
#include "Vector.h"

class ExhaustParticle {
public:
	ExhaustParticle(Vector position);
	void update(float dt);
	void draw();
	int size();

private:
	Vector position_;
	float size_;
};

#endif // I3D_EXHAUSTPARTICLE_H