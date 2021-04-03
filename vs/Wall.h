#ifndef I3D_WALL_H
#define I3D_WALL_H

#include "GlutHeaders.h"
#include "Defines.h"
#include "Point.h"
#include "Enums.h"
#include <utility>

class Wall {
public:
	Wall() = default;
	Wall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void drawWall();
	void setColour(Colour colour);

	Point p1;
	Point p2;

private:
	Colour colour;
};

#endif // I3D_WALL_H