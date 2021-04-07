#include "BulletStream.h"
#include <cmath>
#include "Defines.h"
#include <iostream>

void BulletStream::addBullet(Vector ship_position, float angle) {
	// unit vector in direction of current ship angle
	Vector bullet_velocity(angle);

	// Multiplying the unit vector by half the ship's width gives tip of ship
	Vector copy = bullet_velocity;
	copy = copy * SHIP_WIDTH * 0.5;

	bullet_velocity = bullet_velocity * BULLET_SPEED;

	Vector position{ ship_position.x + copy.x, ship_position.y + copy.y };
	bullets_.emplace_back(position, bullet_velocity);
}

void BulletStream::updateBullets(float dt) {
	for (auto i = 0; i < bullets_.size(); ++i) {
		bullets_[i].update(dt);

		if (bullets_[i].markedForDeletion()) {
			using std::swap;
			swap(bullets_[i], bullets_.back());
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
