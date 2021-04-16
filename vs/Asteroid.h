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
	void setPosition(Vector v);
	Vector& getVelocity();
	void setVelocity(Vector v);
	void update(float dt, float a_width, float a_height);
	void drawAsteroid();
	bool isInArena();

	void bounceInX(float dt);
	void bounceInY(float dt);

	void decrementHealthBy(int num);

	bool markedForDeletion();

	float getSize();

private:
	bool checkIfInArena(float ax, float ay);
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