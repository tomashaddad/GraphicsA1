#ifndef I3D_STATE_H
#define I3D_STATE_H

enum class Movement {
	move_forward,
	move_backward,
	rotate_left,
	rotate_right
};

enum class Colour {
	red,
	white
};

enum class WallSide {
	top,
	bottom,
	left,
	right
};

#endif  // I3D_STATE_H