#include "Arena.h"
#include "GlutHeaders.h"
#include "WorldDefines.h"

Arena::Arena() {
	walls_[0] = Wall(-MAX_ARENA_X, MAX_ARENA_Y, MAX_ARENA_X, MAX_ARENA_Y);
	walls_[0].setSide(WallSide::TOP);

	walls_[1] = Wall(MAX_ARENA_X, -MAX_ARENA_Y, -MAX_ARENA_X, -MAX_ARENA_Y);
	walls_[1].setSide(WallSide::BOTTOM);

	walls_[2] = Wall(-MAX_ARENA_X, -MAX_ARENA_Y, -MAX_ARENA_X, MAX_ARENA_Y);
	walls_[2].setSide(WallSide::LEFT);

	walls_[3] = Wall(MAX_ARENA_X, MAX_ARENA_Y, MAX_ARENA_X, -MAX_ARENA_Y);
	walls_[3].setSide(WallSide::RIGHT);
}

void Arena::drawArena() {
	for (Wall& wall : walls_) {
		wall.drawWall();
	}
}

std::array<Wall, 4>& Arena::getWalls() {
	return walls_;
}