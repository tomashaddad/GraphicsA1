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
	Ship(GLfloat width, GLfloat height, GLfloat radius, GLfloat warning_radius,
		GLfloat velocity, GLfloat acceleration);

	void drawSpaceShip();

	void setStartingPosition(float arena_width, float arena_height);

	void move(Movement movement, float dt);
	void rotate(Movement movement);
	void setPosition(Point point);
	void deaccelerate(float dt);
	void reset();

	void drawExhaust();

	Vector getPosition();
	Vector getDirection();
	GLfloat getVelocity();

	float getCollisionRadius();
	float getWarningRadius();

private:
	void traceVertices(GLfloat width, GLfloat height, GLfloat tail);

	GLfloat width_;
	GLfloat height_;

	Vector starting_position_;
	Vector starting_dir_;

	Vector position_;
	Vector direction_;

	GLfloat velocity_;
	GLfloat acceleration_;

	float radius_;
	float warning_radius_;

	Exhaust exhaust_;
};

#endif // I3D_SHIP_H