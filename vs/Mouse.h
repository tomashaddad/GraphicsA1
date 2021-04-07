#ifndef I3D_MOUSE_H
#define I3D_MOUSE_H

#include "GlutHeaders.h"
#include "Point.h"

class Mouse {
public:
	Mouse();

	Point getMouseCoords();
	void setMouseCoords(double x, double y);

	bool isHoldingLeftClick();
	void setHoldingLeftClick(bool state);

	bool isHoldingRightClick();
	void setHoldingRightClick(bool state);

private:
	Point mouse_coords_;
	bool left_clicking_;
	bool right_clicking_;
};

#endif // I3D_MOUSE_H