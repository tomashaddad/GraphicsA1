#ifndef I3D_ASTEROID_H
#define I3D_ASTEROID_H

#include <vector>
#include "Point.h"
#include "Vector.h"
#include "BlackHole.h"
#include "Explosion.h"

class Asteroid {
public:
	Asteroid(Vector position, Vector velocity, double deviation, int segments,
		BlackHole blackhole);
	
	void resolveCollisionWith(Asteroid& other);
	double getRadius() const;
	Vector& getPosition();
	void setPosition(Vector v);
	Vector& getVelocity();
	void setVelocity(Vector v);
	void update(double dt, double arena_xmax, double arena_ymax, double field_radius);
	void draw() const;
	bool isInArena() const;

	void bounceInX(double dt);
	void bounceInY(double dt);

	void decrementHealthBy(int num);

	void markForDeletion();
	bool markedForDeletion() const;

	double getSize() const;
	int health() const;

private:
	bool checkIfInArena(double ax, double ay) const;
	static double mapHealth(double radius, double min_size, double max_size);

	std::vector<Point> points_;

	Vector position_;
	Vector velocity_;
	Vector acceleration_;
	double angle_;
	double rotation_speed_;
	int rotation_dir_;

	double size_;
	double radius_;
	double radius_deviation_;
	int segments_;

	int health_;
	bool in_arena_;
	bool to_delete_;

	Explosion explosion_;
	BlackHole black_hole_;
};

#endif // I3D_ASTEROID_H