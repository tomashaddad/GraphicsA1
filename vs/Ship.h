#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Structs.h"
#include "State.h"

class Ship {
public:
	Ship(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle);
	void drawSpaceShip();

	void translate(Movement movement);
	void rotate(Movement movement);

private:
	GLfloat width;
	GLfloat height;

	vec2d pos;
	vec2d dir;
	GLfloat velocity;
};

#endif // I3D_SHIP_H