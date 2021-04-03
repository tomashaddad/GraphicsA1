#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Vector.h"
#include "State.h"
#include "Point.h"
#include "Window.h"

class Ship {
public:
	Ship(Window window);
	void drawSpaceShip();

	void translate(Movement movement, float dt);
	void rotate(Movement movement);
	void setPos(Point point);
	void deaccelerate(float dt);

	Vector getPosition();

private:
	GLfloat width_;
	GLfloat height_;

	Vector pos_;
	Vector dir_;
	GLfloat velocity_;
	GLfloat acceleration_;
};

#endif // I3D_SHIP_H