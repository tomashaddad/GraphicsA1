#ifndef I3D_ARENA_H
#define I3D_ARENA_H

#include "Wall.h"
#include "Window.h"
#include <array>

class Arena {
public:
	Arena(Window& window);

	void drawArena();
	void update(double dt);
	std::array<Wall, 4>& getWalls();

	void increasePointsBy(int points);
	void reset();

private:
	Window& window_;
	std::array<Wall, 4> walls_;
	int points_;
	double elapsed_time_;
};

#endif // I3D_ARENA_H