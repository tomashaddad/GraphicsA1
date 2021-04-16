#ifndef I3D_ARENA_H
#define I3D_ARENA_H

#include "Wall.h"
#include <array>

class Arena {
public:
	Arena();

	void drawArena();
	std::array<Wall, 4>& getWalls();

private:
	std::array<Wall, 4> walls_;
};

#endif // I3D_ARENA_H