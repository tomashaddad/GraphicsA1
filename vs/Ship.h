#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Vector.h"
#include "Enums.h"
#include "Point.h"
#include "Window.h"
#include "Exhaust.h"

#include <queue>

class Ship {
public:
	Ship(GLfloat width, GLfloat height, GLfloat radius, GLfloat warning_radius);

	void drawSpaceShip();

	void setStartingPosition(float arena_width, float arena_height);

	void move(Movement movement, float dt);
	void rotate(Movement movement, float dt);
	void setPosition(Point point);
	void update(float dt);
	void reset();

	void drawExhaust();

	Vector getPosition();
	Vector getDirection();

	float getCollisionRadius();
	float getWarningRadius();

	void setAcceleration(Vector vec);

private:
	void traceVertices(GLfloat width, GLfloat height, GLfloat tail);

	GLfloat width_;
	GLfloat height_;

	Vector starting_position_;
	Vector starting_dir_;

	Vector position_;
	Vector direction_;
	Vector velocity_;
	
	Vector acceleration_;

	float rotation_degree_;

	float radius_;
	float warning_radius_;

	Exhaust exhaust_;
};

#endif // I3D_SHIP_H