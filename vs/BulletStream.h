#ifndef I3D_BULLETSTREAM_H
#define I3D_BULLETSTREAM_H

#include <vector>
#include "Bullet.h"

// Thin wrapper around currently active bullets

class BulletStream {
public:
	void addBullet(Vector ship_position, float angle);
	void updateBullets(float dt);
	void drawAll();
	std::vector<Bullet>& getBullets();
	void clear();
	void deleteBullet(int index);
private:
	std::vector<Bullet> bullets_;
};

#endif // I3D_BULLETSTREAM_H