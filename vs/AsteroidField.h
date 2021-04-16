#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include <vector>
#include "Asteroid.h"

class AsteroidField {
public:
	AsteroidField();
	AsteroidField(double window_width, double window_height);

	void launchAsteroidsAtShip(Vector ship_pos);
	void updateRadius(double window_width, double window_height);

	void increaseAsteroidCountBy(int counter);
	int asteroidCount() const;
	bool isEmpty() const;

	void update(double dt, double arena_xmax, double arena_ymax);

	void reset();

	std::vector<Asteroid>& getAsteroids();

private:
	int asteroid_count_;
	double radius_;
	std::vector<Asteroid> asteroids_;
};

#endif // I3D_ASTEROIDFIELD_H