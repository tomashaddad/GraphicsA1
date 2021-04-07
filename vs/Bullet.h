#ifndef I3D_BULLET_H
#define I3D_BULLET_H

#include "Vector.h"

// Thin wrapper around currently active bullets

class Bullet {
public:
	Bullet(Vector position, Vector velocity);

	void update(float dt);
	void draw();
	Vector getPosition();
	void markForDeletion();
	bool markedForDeletion();

private:
	Vector position_;
	Vector velocity_;
	bool to_delete_;
};

#endif // I3D_BULLET_H