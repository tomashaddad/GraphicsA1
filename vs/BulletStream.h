#ifndef I3D_BULLETSTREAM_H
#define I3D_BULLETSTREAM_H

#include <vector>
#include "Bullet.h"

#include "BlackHole.h"

#include <memory>

class BulletStream {
public:
	BulletStream(BlackHole& blackhole);
	void addBullet(Vector ship_position, double angle, double ship_width);
	void updateBullets(double dt);
	void drawAll();
	std::vector<std::unique_ptr<Bullet>>& getBullets();
	void clear();
	void deleteBullet(int index);
private:
	std::vector<std::unique_ptr<Bullet>> bullets_;
	BlackHole& blackhole_;
};

#endif // I3D_BULLETSTREAM_H