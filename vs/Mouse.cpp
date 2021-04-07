#include "Mouse.h"

Mouse::Mouse()
	: mouse_coords_{ 0, 0 },
	  left_clicking_(false),
	  right_clicking_(false){}

Point Mouse::getMouseCoords() {
	return mouse_coords_;
}

void Mouse::setMouseCoords(double x, double y) {
	mouse_coords_.x = x;
	mouse_coords_.y = y;
}

bool Mouse::isHoldingLeftClick() {
	return left_clicking_;
}

void Mouse::setHoldingLeftClick(bool state) {
	left_clicking_ = state;
}

bool Mouse::isHoldingRightClick() {
	return right_clicking_;
}

void Mouse::setHoldingRightClick(bool state) {
	right_clicking_ = state;
}