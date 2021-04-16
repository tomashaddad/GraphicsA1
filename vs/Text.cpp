#include "Text.h"
#include "GlutHeaders.h"

#include <string>

void Text::renderText(std::string text, double xpos, double ypos, double win_width, double win_height) {

	const double width = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,
		(const unsigned char*)text.c_str());

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, win_width, 0, win_height);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(xpos - width / 2.0f, ypos);

	for (char& c : text) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
