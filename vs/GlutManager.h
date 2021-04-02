#ifndef I3D_GLUTMANAGER_H
#define I3D_GLUTMANAGER_H

#include "GlutHeaders.h"
#include "Ship.h"
#include "Wall.h"
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
	// Viewport dimensions
	GLfloat plane_lim_, xmin_, ymin_, xmax_, ymax_, mouse_x_, mouse_y_;
	int win_width_, win_height_;
	bool dragging_;
	std::unique_ptr<Ship> ship_;
	std::array<std::unique_ptr<Wall>, 4> walls_;
	float last_time_;
	float dt_;
};

#endif // I3D_GLUTMANAGER_H