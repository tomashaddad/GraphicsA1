#include "Utility.h"

#include <random>

double Utility::getRandomDoubleBetween(double a, double b) {
	std::random_device engine;
	std::uniform_real_distribution<double> real_dist =
		std::uniform_real_distribution<double>{ a, b };
	return real_dist(engine);
}

// If no radii are passed, it checks collision with points
// If one radius is passed, it checks the collision of a circle with a point
// If two radii are passed, it checks the collision of a circle with a circle 
bool Utility::checkCollision(const Vector p1, const Vector p2, const double r1, const double r2) {
	const double distance_between =
		abs(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return distance_between <= (r1 + r2) * (r1 + r2);
}