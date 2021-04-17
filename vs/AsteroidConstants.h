#ifndef I3D_ASTEROIDCONSTANTS_H
#define I3D_ASTEROIDCONSTANTS_H

constexpr double TIME_BETWEEN_WAVES = 20; // seconds

// Speed when shot at ship
constexpr double ASTEROID_MIN_SPEED = 20;
constexpr double ASTEROID_MAX_SPEED = 40;

constexpr double ASTEROID_MIN_ROTATION_SPEED = 1;
constexpr double ASTEROID_MAX_ROTATION_SPEED = 5;

constexpr double ASTEROID_MIN_SIZE = 2;
constexpr double ASTEROID_MAX_SIZE = 8;

constexpr double ASTEROID_RADIUS_DEVIATION = 0.2; // Make sure MIN_SIZE - DEVIATION > 0!
constexpr double ASTEROID_SEGMENTS = 30; // how many vertices make up its border

// Ship does 1 point of damage per bullet
constexpr auto ASTEROID_MIN_HEALTH = 1;
constexpr auto ASTEROID_MAX_HEALTH = 3;

constexpr auto ASTEROID_BH_MULT = 1; // makes asteroids more susceptible to black hole


constexpr auto ASTEROID_R = 0.58;
constexpr auto ASTEROID_G = 0.29;
constexpr auto ASTEROID_B = 0;

#endif // I3D_ASTEROIDCONSTANTS_H