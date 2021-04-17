#ifndef I3D_EXPLOSION_H
#define I3D_EXPLOSION_H

#include "Vector.h"
#include "ExplosionParticle.h"
#include <vector>

class Explosion {
public:
	Explosion();
	void populate(Vector position);
	void update(double dt);
	void drawAll();
	bool isEmpty() const;
	void clear();

	std::vector<ExplosionParticle>& getExplosions();

private:
	std::vector<ExplosionParticle> explosions_;
	int num_particles_;
	double explosion_timer_;
	double explosion_rate_;
};

#endif // I3D_EXPLOSION_H