#include "Utility.h"

#include <random>

double Utility::getRandomDoubleBetween(double a, double b) {
	std::random_device engine;
	std::uniform_real_distribution<double> real_dist =
		std::uniform_real_distribution<double>{ a, b };
	return real_dist(engine);
}
