#ifndef I3D_DEFINES_H
#define I3D_DEFINES_H

#define PLANE_LIM 100

// Arena parameters
#define MAX_ARENA_X PLANE_LIM * 0.95
#define MAX_ARENA_Y PLANE_LIM * 0.85

// Ship parameters
#define SHIP_FILL_RGB 1, 0, 0
#define SHIP_LINE_RGB 1, 1, 1
#define SHIP_SCALING 0.4
#define SHIP_WIDTH PLANE_LIM * SHIP_SCALING * 0.2
#define SHIP_HEIGHT PLANE_LIM * SHIP_SCALING * 0.15

// Exhaust parameters

// Bullet parameters
#define BULLET_SPEED 100
#define FIRE_RATE 0.2 // seconds per bullet

#define SHIP_STARTING_VELOCITY 0.0
#define SHIP_STARTING_ACCEELERATION 0.0
#define SHIP_ACCELERATION 50
#define SHIP_WARNING_RADIUS 10.0
#define SHIP_COLLISION_RADIUS 2.5

// Asteroid parameters
#define ASTEROID_MIN_SPEED 40
#define ASTEROID_MAX_SPEED 80
#define ASTEROID_MIN_ROTATION_SPEED 1
#define ASTEROID_MAX_ROTATION_SPEED 5
#define ASTEROID_BASE_SIZE 10
#define ASTEROID_RADIUS_DEVIATION 2

#endif // I3D_DEFINES_H