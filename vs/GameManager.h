#ifndef I3D_GAMEMANAGER_H
#define I3D_GAMEMANAGER_H

#include "Ship.h"
#include "Arena.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"
#include "AsteroidField.h"
#include "BlackHole.h"
#include "Explosion.h"

class GameManager {
public:
	GameManager();
	static void startGameLoop();
	void onReshape(int w, int h);

	// Sets the keystate in the Keyboard object to True for the pressed key
	void onKeyDown(unsigned char key, int x, int y);

	// Sets the keystate in the Keyboard object to False for the pressed key
	void onKeyUp(unsigned char key, int x, int y);

	void onMouseClick(int button, int state, int x, int y);
	void onMouseClickDrag(int x, int y);
	void onDisplay();

	// Calculates time difference between frames
	void calculateTimeDelta();

	// Executes functions based on keys set to True in the Keyboard object
	void handleKeyboardInput();
	void handleMouseInput();

	// Handles ship->wall collisions
	void checkWallCollisions();
	
	// Handles ship->asteroid collisions
	void checkAsteroidCollisions();

	// Updates asteroid state
	void updateAsteroids();

	// On reshape, update the radius of the asteroid field
	void updateAsteroidFieldRadius();

	// Handles bullet->asteroid and bullet->wall collisions
	void checkBulletCollisions();

	void checkBlackHoleCollisions();
	
	// Clears all asteroids, resets the ship position
	void resetGame();

private:
	Window win_;
	Keyboard keyboard_;
	Mouse mouse_;

	BlackHole black_hole_;
	Ship ship_;
	Arena arena_;
	AsteroidField asteroid_field_;
	Explosion explosions_;
	
	double dt_;
	double last_time_;
	
	bool playing_;
	bool game_over_;
};

#endif // I3D_GAMEMANAGER_H