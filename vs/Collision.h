#ifndef I3D_COLLISION_H
#define I3D_COLLISION_H

// Collision algorithms sourced online:
// J. Thompson, "Collision Detection", Collision Detection, 2021. [Online]. Available: https://www.jeffreythompson.org/collision-detection/.

namespace Collision {
	// Description
	bool lineWithPoint(double x1, double y1, double x2, double y2, double px, double py);

	// Description
	bool circleWithLine(double x1, double y1, double x2, double y2, double cx, double cy, double r);

	double distanceBetweenPoints(double x1, double y1, double x2, double y2);
};

#endif // I3D_COLLISION_H