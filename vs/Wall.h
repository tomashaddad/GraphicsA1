#ifndef I3D_WALL_H
#define I3D_WALL_H

#include "Point.h"
#include "Enums.h"
#include "Vector.h"

class Wall {
public:
	Wall() = default;
	Wall(double x1, double y1, double x2, double y2);

	// Radius doesn't need to be checked for points (i.e. bullets)
	bool checkCollision(Vector position, double a_xmax, double a_ymax, double radius = 0);
	void setSide(WallSide side);
	void setCoordinates(double x1, double y1, double x2, double y2);
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