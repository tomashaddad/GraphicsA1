#include "GlutHeaders.h"
#include "Ship.h"

void Ship::drawSpaceShip() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1, 1, 1);
		glVertex2f(-0.25, -0.25);
		glVertex2f(0, 0.25);
		glVertex2f(0, -0.125);
		glVertex2f(0.25, -0.25);
	glEnd();
}