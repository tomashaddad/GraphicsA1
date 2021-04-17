#ifndef I3D_SHIPCONSTANTS_H
#define I3D_SHIPCONSTANTS_H

// Ship parameters
#define  SHIP_FILL_RGB 1, 0, 0
#define SHIP_LINE_RGB 1, 1, 1

constexpr double SHIP_SCALING = 0.4;
constexpr double SHIP_TURN_RATE = 540; // degrees per second
constexpr double SHIP_WIDTH = 8;
constexpr double SHIP_HEIGHT = 5;

constexpr double SHIP_STARTING_VELOCITY = 0.0;
constexpr double SHIP_STARTING_ACCELERATION = 0.0;
constexpr double SHIP_ACCELERATION = 100;
constexpr double SHIP_WARNING_RADIUS = 15;
constexpr double SHIP_COLLISION_RADIUS = 1;
constexpr double FIRE_RATE = 0.2; // seconds per bullet

constexpr double SHIP_BH_MULT = 1; // makes ship more susceptible to black hole

#endif // I3D_SHIPCONSTANTS_H