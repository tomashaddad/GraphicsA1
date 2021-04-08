#ifndef I3D_STATE_H
#define I3D_STATE_H

enum class Movement {
	MOVE_FORWARD,
	MOVE_BACKWARD,
	ROTATE_LEFT,
	ROTATE_RIGHT
};

enum class Colour {
	RED,
	WHITE
};

enum class WallSide {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

#endif  // I3D_STATE_H