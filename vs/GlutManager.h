#ifndef I3D_GLUTMANAGER_H
#define I3D_GLUTMANAGER_H

#include "GlutHeaders.h"
#include "Ship.h"
#include "Wall.h"
#include "Mouse.h"
#include "Window.h"
#include <memory>
#include <array>

class GameManager {
public:
	GameManager();
	void startGameLoop();

	void onReshape(int w, int h);
	void onKeyboardPress(unsigned char key, int x, int y);
	void onMouseClick(int button, int state, int x, int y);
	void onMouseClickDrag(int x, int y);
	void onDisplay();
	void onIdle();

private:
	Window win_;
	Mouse mouse_;
	Ship ship_;
	float last_time_;
	float dt_;
};

#endif // I3D_GLUTMANAGER_H