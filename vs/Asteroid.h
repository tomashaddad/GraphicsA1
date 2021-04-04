#ifndef I3D_ASTEROID_H
#define I3D_ASTEROID_H

#include <random>
#include <vector>
#include "Point.h"
#include "Vector.h"
#include "Window.h"
#include "Ship.h"

class Asteroid {
public:
	Asteroid();
	Asteroid(Window window, Ship ship);
	
	void drawAsteroid();

private:
	float launch_radius_;
	float base_size_;
	float deviation_;
	int segments_;
	std::vector<Point> points_;

	Vector position_;
	Vector direction_;
	float velocity_;
	float acceleration_;
};

#endif // I3D_ASTEROID_H