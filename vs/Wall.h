#ifndef I3D_WALL_H
#define I3D_WALL_H

#include "GlutHeaders.h"
#include "Defines.h"

class Wall {
public:
	Wall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void drawArena();
	void drawWall();

private:
	GLfloat x1, y1, x2, y2;
};

#endif // I3D_WALL_H