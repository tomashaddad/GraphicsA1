#include "GlutHeaders.h"
#include "Explosion.h"
#include "ExplosionParticle.h"
#include "ExplosionConstants.h"
#include "Utility.h"

#include <vector>

Explosion::Explosion()
	: num_particles_(EXP_MAX_EXPLOSIONS),
	  explosion_timer_(),
	  explosion_rate_() {}

void Explosion::populate(Vector position) {
	for (int i = 0; i < num_particles_; ++i)
	{
		const double angle = Utility::getRandomDoubleBetween(0, 360);
		auto velocity = Vector(angle);

		const double speed =
			Utility::getRandomDoubleBetween(EXP_MIN_SPEED, EXP_MAX_SPEED);

		velocity = velocity * speed;

		explosions_.emplace_back(position, velocity);
	}
}

void Explosion::update(double dt) {
	for (auto i = 0; i < explosions_.size(); ++i) {
		explosions_[i].update(dt);
		if (explosions_[i].size() == 0) {
			std::swap(explosions_[i], explosions_.back());
			explosions_.pop_back();
		}
	}
}

void Explosion::drawAll() {
	for (ExplosionParticle& particle : explosions_) {
		particle.draw();
	}
}


std::vector<ExplosionParticle>& Explosion::getExplosions() {
	return explosions_;
}

bool Explosion::isEmpty() const {
	return explosions_.empty();
}

void Explosion::clear() {
	explosions_.clear();
}