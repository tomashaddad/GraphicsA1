#ifndef I3D_ASTEROIDDEFINES_H
#define I3D_ASTEROIDDEFINES_H

constexpr double ASTEROID_MIN_SPEED = 40;
constexpr double ASTEROID_MAX_SPEED = 80;
constexpr double ASTEROID_MIN_ROTATION_SPEED = 1;
constexpr double ASTEROID_MAX_ROTATION_SPEED = 5;
constexpr double ASTEROID_BASE_SIZE = 1;
constexpr double ASTEROID_MIN_SIZE = 5;
constexpr double ASTEROID_MAX_SIZE = 10;

// Ship does 1 point of damage per bullet
constexpr auto ASTEROID_MIN_HEALTH = 1;
constexpr auto ASTEROID_MAX_HEALTH = 5;
constexpr auto ASTEROID_RADIUS_DEVIATION = 0.2; // Make sure MIN_SIZE - DEVIATION > 0!

#endif // I3D_ASTEROIDDEFINES_H