#include "Wall.h"
#include "Enums.h"
#include "Vector.h"
#include "GlutHeaders.h"

Wall::Wall(double x1, double y1, double x2, double y2)
	: p1{ x1, y1 },
	  p2{ x2, y2 },
	  colour_(Colour::white) { }

void Wall::setSide(WallSide side) {
	side_ = side;
}

void Wall::setCoordinates(double x1, double y1, double x2, double y2) {
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
}

void Wall::drawWall() const {
	if (colour_ == Colour::red) {
		glLineWidth(3.0);
		glColor3f(1, 0, 0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(1, 1, 1);
	}

	glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
	glEnd();
}

void Wall::setColour(Colour colour) {
	this->colour_ = colour;
}

bool Wall::checkCollision(const Vector position, const double a_xmax,
	const double a_ymax, const double radius) {
	bool collision = false;
	if (side_ == WallSide::top) {
		if (position.y + radius > a_ymax) {
			collision = true;
		}
	}
	else if (side_ == WallSide::bottom) {
		if (position.y - radius < -a_ymax) {
			collision = true;
		}
	}
	else if (side_ == WallSide::left) {
		if (position.x - radius < -a_xmax) {
			collision = true;
		}
	}
	else if (side_ == WallSide::right) {
		if (position.x + radius > a_xmax) {
			collision = true;
		}
	}

	return collision;
}

WallSide Wall::getSide() {
	return side_;
}