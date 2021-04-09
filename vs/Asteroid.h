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
	Asteroid(Vector position, Vector velocity, float deviation, int segments);
	
	bool checkCollision(Vector position, float radius = 0);
	float getCollisionRadius();
	Vector& getPosition();
	Vector& getVelocity();
	void update(float dt);
	void drawAsteroid();
	bool isInArena();

	void bounceInX();
	void bounceInY();

	void decrementHealthBy(int num);

	bool markedForDeletion();

	void handleAsteroidCollision(Vector other_position, Vector other_velocity);

private:
	bool checkIfInArena();
	float mapHealth(float radius, float min_size, float max_size);

	std::vector<Point> points_;

	Vector position_;
	Vector velocity_;
	float angle_;
	float rotation_speed_;
	int rotation_dir_;

	float size_scalar_;
	float radius_;
	float radius_deviation_;
	int segments_;

	int health_;
	bool in_arena_;
	bool to_delete_;
};

#endif // I3D_ASTEROID_H