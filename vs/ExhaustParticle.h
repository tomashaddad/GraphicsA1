#ifndef I3D_EXHAUSTPARTICLE_H
#define I3D_EXHAUSTPARTICLE_H

#include "GlutHeaders.h"
#include "Vector.h"

class ExhaustParticle {
public:
	ExhaustParticle(Vector position, Vector direction, GLfloat velocity);
	void update(float dt);
	void draw();

	int size();

private:
	Vector position_;
	Vector direction_;
	GLfloat velocity_;

	int size_;
};

#endif // I3D_EXHAUSTPARTICLE_H