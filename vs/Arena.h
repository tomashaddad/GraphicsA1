#ifndef I3D_ARENA_H
#define I3D_ARENA_H

#include "Wall.h"
#include <vector>

enum WallSide {
	TOP = 0,
	BOTTOM = 1,
	LEFT = 2,
	RIGHT = 3
};

class Arena {
public:
	Arena();

	void addWall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void drawArena();
	std::vector<Wall>& getWalls();

private:
	std::vector<Wall> walls;
};

#endif // I3D_ARENA_H