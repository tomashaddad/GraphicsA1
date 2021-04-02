#include "GlutHeaders.h"
#include "Ship.h"

int angle = 0;

Ship::Ship() {}

void Ship::drawSpaceShip(double x, double y, double width, double height) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3.0);

	glPushMatrix();

	glTranslatef(x, y, 0);
	glRotatef(angle++, 0, 0, 1);
	glTranslatef(-x, -y, 0);

	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1, 1, 1);
		glVertex2f(x - width/2.0, y - height/2.0);
		glVertex2f(x, y + height/2.0);
		glVertex2f(x, y - (height/2.0 - 0.2*height));
		glVertex2f(x + width/2.0, y - height/2.0);
	glEnd();

	glPopMatrix();

	if (angle == 360) {
		angle = 0;
	}
}