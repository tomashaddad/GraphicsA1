#ifndef I3D_WALL_H
#define I3D_WALL_H

#include "GlutHeaders.h"
#include "Point.h"
#include "Enums.h"
#include "Vector.h"
#include <utility>

class Wall {
public:
	Wall() = default;
	Wall(float x1, float y1, float x2, float y2);

	// Radius doesn't need to be checked for points (i.e. bullets)
	bool checkCollision(Vector position, float a_xmax, float a_ymax, float radius = 0);
	void setSide(WallSide side);
	void setCoordinates(float x1, float y1, float x2, float y2);
	void drawWall();
	void setColour(Colour colour);

	WallSide getSide();

	Point p1;
	Point p2;

private:
	Colour colour_;
	WallSide side_;
};

#endif // I3D_WALL_H