#ifndef I3D_WINDOW_H
#define I3D_WINDOW_H

#include "GlutHeaders.h"

class Window {
public:
	Window();

	GLfloat win_width_, win_height_;
	GLfloat arena_width_, arena_height_;
	GLfloat plane_lim_;
	GLfloat xmin_, ymin_, xmax_, ymax_;
};


#endif // I3D_WINDOW_H