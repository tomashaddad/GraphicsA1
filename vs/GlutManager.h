#ifndef I3D_GLUTMANAGER_H
#define I3D_GLUTMANAGER_H

#include "GlutHeaders.h"
#include "Ship.h"
#include <memory>

void reshape_callback(int w, int h);
void keyboard_callback(unsigned char key, int x, int y);
void display_callback();
void idle_callback();

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
	GLfloat plane_lim_, max_x_, max_y_, max_z_;
	std::unique_ptr<Ship> ship;
	float last_time;
	float dt;
};

#endif // I3D_GLUTMANAGER_H