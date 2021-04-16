#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include <vector>
#include "Asteroid.h"
#include "BlackHole.h"

class AsteroidField {
public:
	AsteroidField(BlackHole& blackHole);

	void launchAsteroidsAtShip(Vector ship_position);
	void updateRadius(double window_width, double window_height);

	void increaseAsteroidCountBy(int counter);
	int asteroidCount() const;
	bool isEmpty() const;
	bool levellingUp() const;

	void update(double dt, double arena_xmax, double arena_ymax);

	void reset();

	std::vector<Asteroid>& getAsteroids();

private:
	int asteroid_count_;
	double radius_;
	double timer_;
	double time_between_levels_;
	bool levelling_up_;
	BlackHole black_hole_;
	std::vector<Asteroid> asteroids_;
};

#endif // I3D_ASTEROIDFIELD_H