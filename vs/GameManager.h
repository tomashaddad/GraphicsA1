#ifndef I3D_GLUTMANAGER_H
#define I3D_GLUTMANAGER_H

#include "GlutHeaders.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Arena.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"
#include "AsteroidField.h"
#include <memory>
#include <array>

class GameManager {
public:
	GameManager();
	void startGameLoop();

	void onReshape(int w, int h);
	void onKeyDown(unsigned char key, int x, int y);
	void onKeyUp(unsigned char key, int x, int y);
	void onMouseClick(int button, int state, int x, int y);
	void onMouseClickDrag(int x, int y);
	void onDisplay();
	void calculateTimeDelta();
	void handleKeyboardInput();
	void handleMouseInput();
	void checkWallCollisions();
	void updateAsteroids();
	void checkAsteroidCollisions();

	void resetGame();

private:
	Window win_;
	Keyboard keyboard_;
	Mouse mouse_;
	Ship ship_;
	Arena arena_;
	AsteroidField asteroid_field_;
	float last_time_;
	float dt_;
};

#endif // I3D_GLUTMANAGER_H