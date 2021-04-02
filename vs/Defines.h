#ifndef I3D_DEFINES_H
#define I3D_DEFINES_H

// Plane limit of 50 from origin means arena is a 100x100 cube
#define PLANE_LIM 100

// Arena parameters
#define MAX_ARENA_X PLANE_LIM * 0.9
#define MAX_ARENA_Y PLANE_LIM * 0.7
#define MAX_ARENA_Z 0

// Ship parameters
#define SHIP_FILL_RGB 1, 0, 0
#define SHIP_LINE_RGB 1, 1, 1

// Only change ship scaling, do not touch SHIP_WIDTH or SHIP_HEIGHT
#define SHIP_SCALING 0.4
#define SHIP_WIDTH PLANE_LIM * SHIP_SCALING * 0.2
#define SHIP_HEIGHT PLANE_LIM * SHIP_SCALING * 0.15

#define SHIP_STARTING_ANGLE 0

#define FPS 30

#endif // I3D_DEFINES_H