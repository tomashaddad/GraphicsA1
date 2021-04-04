#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Vector.h"
#include "Enums.h"
#include "Point.h"
#include "Window.h"

class Ship {
public:
	Ship(Window window);
	void drawSpaceShip();

	void translate(Movement movement, float dt);
	void rotate(Movement movement);
	void setPosition(Point point);
	void deaccelerate(float dt);
	void resetPosition();

	Vector getPosition();
	Vector getDirection();
	float getCollisionRadius();
	float getWarningRadius();

private:
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
};

#endif // I3D_SHIP_H