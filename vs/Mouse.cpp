#include "Mouse.h"

Mouse::Mouse()
	: mouse_coords_{ 0, 0 },
	  left_clicking_(false),
	  right_clicking_(false){}

Point Mouse::getMouseCoords() const {
	return mouse_coords_;
}

void Mouse::setMouseCoords(double x, double y) {
	mouse_coords_.x = x;
	mouse_coords_.y = y;
}

bool Mouse::isHoldingLeftClick() const {
	return left_clicking_;
}

void Mouse::setHoldingLeftClick(const bool state) {
	left_clicking_ = state;
}

bool Mouse::isHoldingRightClick() const {
	return right_clicking_;
}

void Mouse::setHoldingRightClick(const bool state) {
	right_clicking_ = state;
}