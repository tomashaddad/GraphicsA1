#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include <vector>
#include "Asteroid.h"

class AsteroidField {
public:
	AsteroidField();
	AsteroidField(double window_width, double window_height);

	void launchAsteroidAtShip(Vector ship_pos);
	void updateRadius(double window_width, double window_height);

	void increaseAsteroidCountBy(int counter);
	int asteroidCount() const;
	bool isEmpty() const;

	void updateAsteroids(double dt, double a_width, double a_height);

	void reset();

	std::vector<Asteroid>& getAsteroids();

private:
	int asteroid_count_;
	double radius_;
	std::vector<Asteroid> asteroids_;
};

#endif // I3D_ASTEROIDFIELD_H