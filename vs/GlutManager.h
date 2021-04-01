#ifndef I3D_GLUTMANAGER_H
#define I3D_GLUTMANAGER_H

#include "GlutHeaders.h"
#include "Ship.h"

void onReshape(int w, int h);
void onKeyboardPress(unsigned char key, int x, int y);
void onDisplay();
void onIdle();

class GameManager {
public:
	GameManager();
	void startGameLoop();

	void onReshape(int w, int h);
	void onKeyboardPress(unsigned char key, int x, int y);
	void onDisplay();
	void onIdle();

private:
	// Viewport dimensions
	GLfloat planeLim, maxArenaX, maxArenaY, maxArenaZ;
	Ship ship;
};

#endif // I3D_GLUTMANAGER_H