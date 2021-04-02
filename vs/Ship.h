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

	void translate(Movement movement);
	void rotate(Movement movement);
	void setPos(Point point);

private:
	GLfloat width;
	GLfloat height;

	Vector pos;
	Vector dir;
	GLfloat velocity;
};

#endif // I3D_SHIP_H