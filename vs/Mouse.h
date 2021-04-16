#ifndef I3D_MOUSE_H
#define I3D_MOUSE_H

#include "Point.h"

class Mouse {
public:
	Mouse();

	Point getMouseCoords() const;
	void setMouseCoords(double x, double y);

	bool isHoldingLeftClick() const;
	void setHoldingLeftClick(bool state);

	bool isHoldingRightClick() const;
	void setHoldingRightClick(bool state);

private:
	Point mouse_coords_;
	bool left_clicking_;
	bool right_clicking_;
};

#endif // I3D_MOUSE_H