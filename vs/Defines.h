#ifndef I3D_DEFINES_H
#define I3D_DEFINES_H

#define PLANE_LIM 100

// Arena parameters
#define MAX_ARENA_X PLANE_LIM * 0.95
#define MAX_ARENA_Y PLANE_LIM * 0.85

// Ship parameters
#define SHIP_FILL_RGB 1, 0, 0
#define SHIP_LINE_RGB 1, 1, 1

// Only change ship scaling, do not touch SHIP_WIDTH or SHIP_HEIGHT
#define SHIP_SCALING 0.5
#define SHIP_WIDTH PLANE_LIM * SHIP_SCALING * 0.2
#define SHIP_HEIGHT PLANE_LIM * SHIP_SCALING * 0.15

#define SHIP_STARTING_ANGLE 45

#define SHIP_STARTING_VELOCITY 0.0
#define SHIP_STARTING_ACCEELERATION 0.0
#define SHIP_ACCELERATION 30
#define SHIP_WARNING_RADIUS 10.0 // Warning radius
#define SHIP_RADIUS 2.5 // Actual ship radius used for collision detection

#define ASTEROID_MIN_SPEED 30
#define ASTEROID_MAX_SPEED 50
#define ASTEROID_MIN_ROTATION_SPEED 1
#define ASTEROID_MAX_ROTATION_SPEED 5
#define ASTEROID_BASE_SIZE 10
#define ASTEROID_DEVIATION 2

#endif // I3D_DEFINES_H