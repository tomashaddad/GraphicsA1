#include "Mouse.h"

Mouse::Mouse()
	: mouse_coords_{ 0, 0 },
	  dragging_(false) {}

Point Mouse::getMouseCoords() {
	return mouse_coords_;
}

void Mouse::setMouseCoords(double x, double y) {
	mouse_coords_.x = x;
	mouse_coords_.y = y;
}

bool Mouse::isDragging() {
	return dragging_;
}

void Mouse::setDragging(bool state) {
	dragging_ = state;
}
