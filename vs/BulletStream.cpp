#include "BulletStream.h"
#include "BulletDefines.h"

void BulletStream::addBullet(Vector ship_position, double angle, double ship_width) {
	// unit vector in direction of current ship angle
	Vector bullet_velocity(angle);

	// Multiplying the unit vector by half the ship's width gives tip of ship
	Vector copy = bullet_velocity;
	copy = copy * ship_width * 0.5;

	bullet_velocity = bullet_velocity * BULLET_SPEED;

	Vector position{ ship_position.x + copy.x, ship_position.y + copy.y };
	bullets_.emplace_back(position, bullet_velocity);
}

void BulletStream::updateBullets(double dt) {
	for (auto i = 0; i < bullets_.size(); ++i) {
		bullets_[i].update(dt);

		if (bullets_[i].markedForDeletion()) {
			std::swap(bullets_[i], bullets_.back());
			bullets_.pop_back();
		}
	}
}

void BulletStream::drawAll() {
	for (Bullet& bullet : bullets_) {
		bullet.draw();
	}
}

std::vector<Bullet>& BulletStream::getBullets() {
	return bullets_;
}

void BulletStream::clear() {
	bullets_.clear();
}

void BulletStream::deleteBullet(int index) {
	if (index == 0) {
		bullets_.pop_back();
	} else {
		using std::swap;
		swap(bullets_[index], bullets_.back());
		bullets_.pop_back();
	}
}
