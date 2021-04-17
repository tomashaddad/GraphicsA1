#ifndef I3D_EXPLOSION_H
#define I3D_EXPLOSION_H

#include "Vector.h"
#include "ExplosionParticle.h"
#include <vector>

class Explosion {
public:
	Explosion();

	// Populates the explosion vector with new explosion particles at the
	// position the asteroid died
	void populate(Vector position);

	// Updates all explosion particles and deletes them if they have reduced
	// to a size of 0
	void update(double dt);

	// Draws all explosion particles
	void drawAll();
	
	bool isEmpty() const;
	void reset();

	std::vector<ExplosionParticle>& getExplosions();

private:
	std::vector<ExplosionParticle> explosions_;
	int num_particles_;
	double explosion_timer_;
	double explosion_rate_;
};

#endif // I3D_EXPLOSION_H