#include "Collision.h"
#define _USING_MATH_DEFINES
#include <cmath>

bool Collision::lineWithPoint(double x1, double y1, double x2, double y2, double px, double py) {
	double line_length = distanceBetweenPoints(x1, y1, x2, y2);
	double d1 = distanceBetweenPoints(x1, y1, px, py);
	double d2 = distanceBetweenPoints(x2, y2, px, py);
	double buffer = 0.1;

	return d1 + d2 >= line_length - buffer && d1 + d2 <= line_length + buffer;
}

// https://math.stackexchange.com/questions/4087977/distance-from-circle-to-line-segment-what-is-the-intuition-or-geometry-behind-t/
bool Collision::circleWithLine(double x1, double y1, double x2, double y2, double cx, double cy, double r) {
	x1 -= cx;
	y1 -= cy;
	x2 -= cx;
	y2 -= cy;

	double r2 = r * r;
	double len2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

	double nx = y2 - y1;
	double ny = x1 - x2;

	double dist2 = nx * x1 + ny * y1;

	dist2 *= dist2;

	if (dist2 > len2 * r2) return false;

	double index = (x1 * (x1 - x2) + y1 * (y1 - y2));
	if (index < 0) return false;
	if (index > len2) return false;
	return true;
}

double Collision::distanceBetweenPoints(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}