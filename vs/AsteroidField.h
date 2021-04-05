#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include <vector>
#include "Asteroid.h"
#include "GlutHeaders.h"

class AsteroidField {
public:
	AsteroidField();
	AsteroidField(GLfloat window_width, GLfloat window_height);

	void launchAsteroidAtShip(Vector ship_pos);
	void updateRadius(GLfloat window_width, GLfloat window_height);

	void increaseAsteroidCountBy(int counter);
	int asteroidCount();
	bool isEmpty();

	void updateAsteroids(float dt);

	void reset();

	std::vector<Asteroid>& getAsteroids();

private:
	int asteroid_count_;
	GLfloat radius;
	std::vector<Asteroid> asteroids;
};

#endif // I3D_ASTEROIDFIELD_H