#ifndef I3D_EXHAUSTPARTICLE_H
#define I3D_EXHAUSTPARTICLE_H

#include "Vector.h"

class ExhaustParticle {
public:
	ExhaustParticle() = default;
	ExhaustParticle(Vector position);
	void update(float dt);
	void draw() const;
	int size();

private:
	Vector position_;
	double size_;
	double decay_;
};

#endif // I3D_EXHAUSTPARTICLE_H