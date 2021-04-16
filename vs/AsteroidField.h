#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include <vector>
#include "Asteroid.h"
#include "GlutHeaders.h"

class AsteroidField {
public:
	AsteroidField();
	AsteroidField(float window_width, float window_height);

	void launchAsteroidAtShip(Vector ship_pos);
	void updateRadius(float window_width, float window_height);

	void increaseAsteroidCountBy(int counter);
	int asteroidCount();
	bool isEmpty();

	void updateAsteroids(float dt, float a_width, float a_height);

	void reset();

	std::vector<Asteroid>& getAsteroids();

private:
	int asteroid_count_;
	float radius_;
	std::vector<Asteroid> asteroids_;
};

#endif // I3D_ASTEROIDFIELD_H