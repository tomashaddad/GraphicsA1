#ifndef I3D_ASTEROIDDEFINES_H
#define I3D_ASTEROIDDEFINES_H

constexpr double TIME_BETWEEN_WAVES = 5; // seconds

constexpr double ASTEROID_MIN_SPEED = 20;
constexpr double ASTEROID_MAX_SPEED = 40;
constexpr double ASTEROID_MIN_ROTATION_SPEED = 1;
constexpr double ASTEROID_MAX_ROTATION_SPEED = 5;
constexpr double ASTEROID_MIN_SIZE = 2;
constexpr double ASTEROID_MAX_SIZE = 5;
constexpr double ASTEROID_SEGMENTS = 30; // how many vertices make up its border

// Ship does 1 point of damage per bullet
constexpr auto ASTEROID_MIN_HEALTH = 1;
constexpr auto ASTEROID_MAX_HEALTH = 5;
constexpr auto ASTEROID_RADIUS_DEVIATION = 0.2; // Make sure MIN_SIZE - DEVIATION > 0!

#endif // I3D_ASTEROIDDEFINES_H