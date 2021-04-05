#include "Exhaust.h"
#include "Vector.h"
#include "GlutHeaders.h"
#include <iostream>

void Exhaust::addParticle(Vector position_, Vector direction_, GLfloat velocity) {
	exhaust_.emplace_back(position_, direction_, velocity);
	if (exhaust_.size() > 20) {
		exhaust_.pop_front();
	}
}

void Exhaust::updateParticles(float dt) {
	for (ExhaustParticle& particle : exhaust_) {
		particle.update(dt);
		//if (particle.size() == 0) {
		//	exhaust_.pop_front();
		//}
	}
}

void Exhaust::drawAll() {
	glPointSize(10);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (ExhaustParticle& particle : exhaust_) {
		std::cout << "Drawing at" << particle.getX() << " " << particle.getY() << std::endl;
		glVertex2f(particle.getX(), particle.getY());
	}
	glEnd();
}