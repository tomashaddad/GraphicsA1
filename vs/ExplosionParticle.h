#ifndef I3D_EXPLOSIONPARTICLE_H
#define I3D_EXPLOSIONPARTICLE_H

#include "Vector.h"

class ExplosionParticle {
public:
	ExplosionParticle(Vector position, Vector velocity);
	void draw() const;
	void update(double dt);
	int size() const;
private:
	Vector position_;
	Vector velocity_;
	double size_;
	double decay_;
};

#endif // I3D_EXPLOSIONPARTICLE_H