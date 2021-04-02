#ifndef I3D_MOUSE_H
#define I3D_MOUSE_H

#include "GlutHeaders.h"
#include "Point.h"

class Mouse {
public:
	Mouse();

	Point getMouseCoords();
	void setMouseCoords(double x, double y);

	bool isDragging();
	void setDragging(bool state);

private:
	Point mouse_coords_;
	bool dragging_;
};

#endif // I3D_MOUSE_H