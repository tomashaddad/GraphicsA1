#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Structs.h"

class Ship {
public:
	Ship();
	void drawSpaceShip(double x, double y, double width, double height);

private:
	vec2d pos;
	vec2d dir;
};

#endif // I3D_SHIP_H