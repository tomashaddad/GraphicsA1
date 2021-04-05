#include "Exhaust.h"
#include "Vector.h"
#include "GlutHeaders.h"
#include <iostream>

void Exhaust::addParticle(Vector position_, Vector direction_, Vector velocity) {
	exhaust_.emplace_back(position_, direction_, velocity);
}

void Exhaust::updateParticles(float dt) {
	for (ExhaustParticle& particle : exhaust_) {
		particle.update(dt);
		if (particle.size() == 0) {
			exhaust_.pop_front();
		}
	}
}

void Exhaust::drawAll() {
	for (ExhaustParticle& particle : exhaust_) {
		particle.draw();
	}
}