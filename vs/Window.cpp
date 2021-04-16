#include "Window.h"
#include "WorldDefines.h"

Window::Window()
	: plane_lim_(PLANE_LIM),
	  win_width_(0),
	  win_height_(0),
	  arena_width_(MAX_ARENA_X),
	  arena_height_(MAX_ARENA_Y),
	  xmin_(0),
	  xmax_(0),
	  ymin_(0),
	  ymax_(0) {}