#include "Wall.h"
#include "Enums.h"
#include "Vector.h"

Wall::Wall(float x1, float y1, float x2, float y2)
	: p1{ x1, y1 },
	  p2{ x2, y2 },
	  colour_(Colour::WHITE) { }

void Wall::setSide(WallSide side) {
	side_ = side;
}

void Wall::setCoordinates(float x1, float y1, float x2, float y2) {
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
}

void Wall::drawWall() {

	if (colour_ == Colour::RED) {
		glLineWidth(3.0);
		glColor3f(1, 0, 0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(1, 1, 1);
	}

		glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
	glEnd();
}

void Wall::setColour(Colour colour) {
	this->colour_ = colour;
}

bool Wall::checkCollision(Vector position, float radius) {
	bool collision = false;
	if (side_ == WallSide::TOP) {
		if (position.y + radius > MAX_ARENA_Y) {
			collision = true;
		}
	}
	else if (side_ == WallSide::BOTTOM) {
		if (position.y - radius < -MAX_ARENA_Y) {
			collision = true;
		}
	}
	else if (side_ == WallSide::LEFT) {
		if (position.x - radius < -MAX_ARENA_X) {
			collision = true;
		}
	}
	else if (side_ == WallSide::RIGHT) {
		if (position.x + radius > MAX_ARENA_X) {
			collision = true;
		}
	}

	return collision;
}

WallSide Wall::getSide() {
	return side_;
}