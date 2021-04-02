#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Vector.h"
#include "State.h"

class Ship {
public:
	Ship(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle);
	void drawSpaceShip();

	void translate(Movement movement);
	void rotate(Movement movement);
	void setPos(float x, float y);

private:
	GLfloat width;
	GLfloat height;

	Vector pos;
	Vector dir;
	GLfloat velocity;
};

#endif // I3D_SHIP_H