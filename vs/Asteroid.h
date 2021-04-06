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
	Asteroid(Vector position, Vector velocity, float base_size, float deviation,
		int segments);
	
	float getCollisionRadius();
	Vector getPosition();
	void update(float dt);
	void drawAsteroid();

private:
	std::vector<Point> points_;

	Vector position_;
	Vector velocity_;
	float angle_;
	float rotation_speed_;
	int rotation_dir_;

	float average_radius_;
	float radius_deviation_;
	int segments_;
};

#endif // I3D_ASTEROID_H