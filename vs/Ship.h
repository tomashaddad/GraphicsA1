#ifndef I3D_SHIP_H
#define I3D_SHIP_H

#include "Vector.h"
#include "Enums.h"
#include "Point.h"
#include "Exhaust.h"
#include "BulletStream.h"

class Ship {
public:
	Ship();
	void drawSpaceShip();

	void setStartingPosition(double x, double y);

	void move(Movement movement, double dt);
	void rotate(Movement movement, double dt);
	void setPosition(Point point);
	void update(double dt);
	void reset();

	void drawExhaust();

	Vector getPosition() const;
	void setRotation(double rotation);

	double getCollisionRadius() const;
	double getWarningRadius() const;

	void setAcceleration(Vector vec);

	void shootBullet(float dt);
	void drawBullets(float dt);
	BulletStream& getBulletStream();

private:
	void traceVertices(double width, double height, double tail) const;

	double width_;
	double height_;

	Vector starting_position_;
	Vector starting_dir_;

	Vector position_;
	Vector direction_;
	Vector velocity_;
	
	Vector acceleration_;

	double cur_angle_;
	double init_angle_;

	double radius_;
	double warning_radius_;

	double bullet_timer_;
	double fire_rate_;

	Exhaust exhaust_;
	BulletStream bulletStream_;
};

#endif // I3D_SHIP_H