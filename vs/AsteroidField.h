#ifndef I3D_ASTEROIDFIELD_H
#define I3D_ASTEROIDFIELD_H

#include <vector>
#include "Asteroid.h"
#include "BlackHole.h"

class AsteroidField {
public:
	AsteroidField(BlackHole& blackHole);

	// Launches a number of asteroids at the ship based on the wave number
	void launchAsteroidsAtShip(Vector ship_position);
	
	void updateRadius(double window_width, double window_height);
	void update(double dt, double arena_xmax, double arena_ymax);
	void increaseAsteroidCountBy(int counter);
	void resetTimer();
	void reset();

	// Getters and setters
	int asteroidCount() const;
	bool isEmpty() const;
	bool levellingUp() const;
	std::vector<Asteroid>& getAsteroids();

private:
	int asteroid_count_;
	double radius_;
	double timer_;
	double time_between_levels_;
	bool levelling_up_;
	BlackHole& blackhole_;
	std::vector<Asteroid> asteroids_;
};

#endif // I3D_ASTEROIDFIELD_H