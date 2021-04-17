#ifndef I3D_UTILITY_H
#define I3D_UTILITY_H

#include "Vector.h"

namespace Utility {
	double getRandomDoubleBetween(double a, double b);
	bool checkCollision(Vector p1, Vector p2, double r1 = 0, double r2 = 0);
}

#endif // I3D_UTILITY_H