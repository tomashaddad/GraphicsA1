#ifndef I3D_STATE_H
#define I3D_STATE_H

// Apparently convention is to have lowercase enums to not get confused with
// hash defines!

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