#ifndef I3D_WINDOW_H
#define I3D_WINDOW_H

class Window {
public:
	Window();

	double win_width_, win_height_;
	double arena_width_, arena_height_;
	double plane_lim_;
	double xmin_, ymin_, xmax_, ymax_;
};


#endif // I3D_WINDOW_H