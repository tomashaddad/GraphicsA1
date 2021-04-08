#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Vector.h"
#include "Enums.h"
#include "Point.h"
#include "Window.h"
#include "Exhaust.h"
#include "BulletStream.h"

#include <queue>

class Ship {
public:
	Ship(float width, float height, float radius, float warning_radius);

	void drawSpaceShip();

	void setStartingPosition(float x, float y);

	void move(Movement movement, float dt);
	void rotate(Movement movement, float dt);
	void setPosition(Point point);
	void update(float dt);
	void reset();

	void drawExhaust();

	Vector getPosition();
	void setRotation(float rotation);

	float getCollisionRadius();
	float getWarningRadius();

	void setAcceleration(Vector vec);

	void shootBullet(float dt);
	void drawBullets(float dt);
	BulletStream& getBulletStream();

private:
	void traceVertices(float width, float height, float tail);

	float width_;
	float height_;

	Vector starting_position_;
	Vector starting_dir_;

	Vector position_;
	Vector direction_;
	Vector velocity_;
	
	Vector acceleration_;

	float cur_angle_;
	float init_angle_;

	float radius_;
	float warning_radius_;

	float bullet_timer_;
	float fire_rate_;

	Exhaust exhaust_;
	BulletStream bulletStream_;
};

#endif // I3D_SHIP_H