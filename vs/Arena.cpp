#include "Arena.h"
#include "GlutHeaders.h"

Arena::Arena() {
	addWall(-MAX_ARENA_X, -MAX_ARENA_Y, -MAX_ARENA_X, MAX_ARENA_Y); // left wall
	addWall(-MAX_ARENA_X, MAX_ARENA_Y, MAX_ARENA_X, MAX_ARENA_Y); // top wall
	addWall(MAX_ARENA_X, MAX_ARENA_Y, MAX_ARENA_X, -MAX_ARENA_Y); // right wall
	addWall(MAX_ARENA_X, -MAX_ARENA_Y, -MAX_ARENA_X, -MAX_ARENA_Y); // bottom wall
}

void Arena::addWall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	walls.push_back(Wall(x1, y1, x2, y2));
}

void Arena::drawArena() {
	for (Wall& wall : walls) {
		wall.drawWall();
	}
}

std::vector<Wall>& Arena::getWalls() {
	return walls;
}