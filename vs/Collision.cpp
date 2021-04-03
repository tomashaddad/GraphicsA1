#include "Collision.h"
#define _USING_MATH_DEFINES
#include <math.h>

bool Collision::lineWithPoint(double x1, double y1, double x2, double y2, double px, double py) {
	double line_length = distanceBetweenPoints(x1, y1, x2, y2);
	double d1 = distanceBetweenPoints(x1, y1, px, py);
	double d2 = distanceBetweenPoints(x2, y2, px, py);
	double buffer = 0.1;

	return d1 + d2 >= line_length - buffer && d1 + d2 <= line_length + buffer;
}

bool Collision::circleWithLine(double x1, double y1, double x2, double y2, double cx, double cy, double r) {
	double line_length = distanceBetweenPoints(x1, y1, x2, y2);
	double dot_product = (((cx - x1) * (x2 - x1)) + ((cy - y1) * (y2 - y1))) / pow(line_length, 2);
	double closest_x = x1 + (dot_product * (x2 - x1));
	double closest_y = y1 + (dot_product * (y2 - y1));

	bool on_line = lineWithPoint(x1, y1, x2, y2, closest_x, closest_y);
	if (!on_line) {
		return false;
	}

	float distance = distanceBetweenPoints(closest_x, closest_y, cx, cy);

	return distance <= r;
}

double Collision::distanceBetweenPoints(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}