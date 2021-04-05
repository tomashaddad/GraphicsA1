#include "Collision.h"
#define _USING_MATH_DEFINES
#include <cmath>

bool Collision::lineWithPoint(float x1, float y1, float x2, float y2, float px, float py) {
	float line_length = distanceBetweenPoints(x1, y1, x2, y2);
	float d1 = distanceBetweenPoints(x1, y1, px, py);
	float d2 = distanceBetweenPoints(x2, y2, px, py);
	float buffer = 0.1;

	return d1 + d2 >= line_length - buffer && d1 + d2 <= line_length + buffer;
}

bool Collision::circleWithCircle(float cx1, float cy1, float cr1, float cx2, float cy2, float cr2) {
	return distanceBetweenPoints(cx1, cy1, cx2, cy2) <= cr1 + cr2;
}

// https://math.stackexchange.com/questions/4087977/distance-from-circle-to-line-segment-what-is-the-intuition-or-geometry-behind-t/
bool Collision::circleWithLine(float x1, float y1, float x2, float y2, float cx, float cy, float r) {
	x1 -= cx;
	y1 -= cy;
	x2 -= cx;
	y2 -= cy;

	float r2 = r * r;
	float len2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

	float nx = y2 - y1;
	float ny = x1 - x2;

	float dist2 = nx * x1 + ny * y1;

	dist2 *= dist2;

	if (dist2 > len2 * r2) return false;

	float index = (x1 * (x1 - x2) + y1 * (y1 - y2));
	if (index < 0) return false;
	if (index > len2) return false;
	return true;
}

float Collision::distanceBetweenPoints(float x1, float y1, float x2, float y2) {
	return sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
}