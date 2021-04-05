#ifndef I3D_COLLISION_H
#define I3D_COLLISION_H

namespace Collision {
	bool lineWithPoint(float x1, float y1, float x2, float y2, float px, float py);

	bool circleWithLine(float x1, float y1, float x2, float y2, float cx, float cy, float r);

	bool circleWithCircle(float cx1, float cy1, float cr1, float cx2, float cy2, float cr2);

	float distanceBetweenPoints(float x1, float y1, float x2, float y2);
};

#endif // I3D_COLLISION_H