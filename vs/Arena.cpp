#include "Arena.h"
#include "WorldConstants.h"
#include "Text.h"

#include <string>
#include <sstream>

Arena::Arena(Window& window)
	: window_(window),
	  points_(0),
	  elapsed_time_(0)
{
	walls_[0] = Wall(-MAX_ARENA_X, MAX_ARENA_Y, MAX_ARENA_X, MAX_ARENA_Y);
	walls_[0].setSide(WallSide::top);

	walls_[1] = Wall(MAX_ARENA_X, -MAX_ARENA_Y, -MAX_ARENA_X, -MAX_ARENA_Y);
	walls_[1].setSide(WallSide::bottom);

	walls_[2] = Wall(-MAX_ARENA_X, -MAX_ARENA_Y, -MAX_ARENA_X, MAX_ARENA_Y);
	walls_[2].setSide(WallSide::left);

	walls_[3] = Wall(MAX_ARENA_X, MAX_ARENA_Y, MAX_ARENA_X, -MAX_ARENA_Y);
	walls_[3].setSide(WallSide::right);
}

void Arena::update(double dt) {
	elapsed_time_ += dt;
}

#include <iostream>

void Arena::drawArena() {
	for (Wall& wall : walls_) {
		wall.drawWall();
	}

	std::ostringstream stream;
	stream << "Current points: " << points_;
	const std::string points = stream.str();

	Text::renderText(points,
		window_.win_width_ / 4.0,
		window_.win_height_ - 50,
		window_.win_width_,
		window_.win_height_);

	stream.str("");
	
	stream << "Current time: " << static_cast<int>(elapsed_time_);
	const std::string elapsed_time_ = stream.str();
	
	Text::renderText(elapsed_time_,
		window_.win_width_ * 3.0 / 4.0,
		window_.win_height_ - 50,
		window_.win_width_,
		window_.win_height_);
}

std::array<Wall, 4>& Arena::getWalls() {
	return walls_;
}


void Arena::increasePointsBy(int points) {
	points_ += points;
}

void Arena::reset() {
	points_ = 0;
	elapsed_time_ = 0;
}