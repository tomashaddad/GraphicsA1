#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include <vector>
#include "Asteroid.h"
#include "GlutHeaders.h"

class AsteroidField {
public:
	AsteroidField() = default;
	AsteroidField(GLfloat window_width, GLfloat window_height);

	void launchAsteroidAtShip(Vector ship_pos);
	void updateRadius(GLfloat window_width, GLfloat window_height);

	void reset();

	std::vector<Asteroid>& getAsteroids();

private:
	GLfloat radius;
	std::vector<Asteroid> asteroids;
};

#endif // I3D_ASTEROIDFIELD_H