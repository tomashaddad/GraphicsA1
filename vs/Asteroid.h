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
	Asteroid(Vector position, Vector direction, float base_size,
		float deviation, int segments, float velocity);
	
	float getCollisionRadius();
	Vector getPosition();
	void update(float dt);
	void drawAsteroid();

private:
	float average_radius_;
	float radius_deviation_;
	int segments_;
	std::vector<Point> points_;

	Vector position_;
	Vector direction_;
	float velocity_;
	float rotation_speed_;
	int rotation_direction_;
};

#endif // I3D_ASTEROID_H