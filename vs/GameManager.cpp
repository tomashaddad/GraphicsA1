#include "GameManager.h"
#include "Defines.h"
#include "Enums.h"
#include "Collision.h"
#include "Vector.h"
#include "Text.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <utility>
#include <iostream>
#include <string>

GameManager::GameManager()
	: ship_(Ship(SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLLISION_RADIUS, SHIP_WARNING_RADIUS)),
	  dt_(0),
	  last_time_(0),
	  playing(false)
{
	// diagonal of arena
	float slope = win_.arena_height_ / win_.arena_width_;
	ship_.setRotation(180.0 * (atanf(slope) / M_PI));

	// 1/3 in from the bottom left
	ship_.setStartingPosition(-0.3 * win_.arena_width_, -0.3 * win_.arena_height_);
}

void GameManager::startGameLoop() {
	glutMainLoop();
}

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	arena_.drawArena();

	if (playing) {
		ship_.drawSpaceShip();
		ship_.drawExhaust();
		ship_.updateBulletTimer(dt_); // TODO: Ask if this is the best way to determine fire rate
		ship_.drawBullets(dt_);

		// Asteroids are only shot at the ship if there are no asteroids
		// currently in the arena
		if (asteroid_field_.isEmpty()) {
			for (int i = 0; i < asteroid_field_.asteroidCount(); ++i) {
				asteroid_field_.launchAsteroidAtShip(ship_.getPosition());
			}
			asteroid_field_.increaseAsteroidCountBy(1);
		}

		asteroid_field_.updateAsteroids(dt_);

		for (Asteroid& asteroid : asteroid_field_.getAsteroids()) {
			asteroid.drawAsteroid();
		}
	} else {
		Text::renderText("Press 'B' to begin!",
			win_.win_width_ / 2.0f, win_.win_height_ / 2.0f,
			win_.win_width_, win_.win_height_);
	}

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void GameManager::onReshape(int w, int h) {
	win_.win_width_ = w;
	win_.win_height_ = h;

	GLfloat aspect_ratio = (GLfloat)w / (GLfloat)h;

	if (w > h) {
		win_.xmin_ = win_.plane_lim_ * -aspect_ratio;
		win_.xmax_ = win_.plane_lim_ * aspect_ratio;
		win_.ymin_ = -win_.plane_lim_;
		win_.ymax_ = win_.plane_lim_;
	}
	else {
		win_.xmin_ = -win_.plane_lim_;
		win_.xmax_ = win_.plane_lim_;
		win_.ymin_ = win_.plane_lim_ / -aspect_ratio;
		win_.ymax_ = win_.plane_lim_ / aspect_ratio;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(win_.xmin_, win_.xmax_, win_.ymin_, win_.ymax_, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);
}

void GameManager::onKeyDown(unsigned char key, int x, int y) {
	keyboard_.setKeyState(key, true);
}

void GameManager::onKeyUp(unsigned char key, int x, int y) {
	keyboard_.setKeyState(key, false);
}

// "Click-and-Drag demo" by Glenn G. Chappell
void GameManager::onMouseClick(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse_.setHoldingLeftClick(true);
		} else {
			mouse_.setHoldingLeftClick(false);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse_.setHoldingRightClick(true);
		} else {
			mouse_.setHoldingRightClick(false);
		}
	}
	glutPostRedisplay();
}

void GameManager::onMouseClickDrag(int x, int y)
{
	float xmouse = win_.xmin_ + (float(x) / win_.win_width_) * (win_.xmax_ - win_.xmin_);
	float ymouse = win_.ymax_ + (float(y) / win_.win_height_) * (win_.ymin_ - win_.ymax_);
	
	mouse_.setMouseCoords(xmouse, ymouse);
}


void GameManager::calculateTimeDelta() {
	// gives delta time in seconds
	float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt_ = cur_time - last_time_;
	last_time_ = cur_time;
}

void GameManager::handleKeyboardInput() {
	// quit
	if (keyboard_.getKeyState('q')) {
		exit(EXIT_SUCCESS);
	}

	if (keyboard_.getKeyState('b') && !playing) {
		playing = true;
	}

	if (playing) {
		// forward/backward (+ acceleration case)
		if (keyboard_.getKeyState('w')) {
			ship_.move(Movement::MOVE_FORWARD, dt_);
		}
		else if (keyboard_.getKeyState('s')) {
			ship_.move(Movement::MOVE_BACKWARD, dt_);
		}
		else {
			ship_.setAcceleration(Vector{ 0,0 });
		}

		// rotation
		if (keyboard_.getKeyState('a')) {
			ship_.rotate(Movement::ROTATE_LEFT, dt_);
		}
		else if (keyboard_.getKeyState('d')) {
			ship_.rotate(Movement::ROTATE_RIGHT, dt_);
		}

		ship_.update(dt_);
	}

	glutPostRedisplay();
}

void GameManager::handleMouseInput() {
	// allows ship to be moved by click-drag
	if (mouse_.isHoldingLeftClick()) {
		ship_.setPosition(mouse_.getMouseCoords());
	}

	if (mouse_.isHoldingRightClick()) {
		// pass dt_ to determine if shooting a bullet is allowed
		ship_.shootBullet(dt_);
	}
}

void GameManager::checkWallCollisions() {
	Vector pos = ship_.getPosition();
	for (Wall& wall : arena_.getWalls()) {
		Point p1 = wall.p1;
		Point p2 = wall.p2;
		float r_warning = ship_.getWarningRadius();
		float r_collision = ship_.getCollisionRadius();

		if (Collision::circleWithLine(p1.x, p1.y, p2.x, p2.y, pos.x, pos.y, r_warning)) {
			wall.setColour(Colour::RED);
		}
		else {
			wall.setColour(Colour::WHITE);
		}

		if (Collision::circleWithLine(p1.x, p1.y, p2.x, p2.y, pos.x, pos.y, r_collision)) {
			resetGame();
		}
	}
}

void GameManager::updateAsteroidFieldRadius() {
	asteroid_field_.updateRadius(win_.xmax_ - win_.xmin_,
								 win_.ymax_ - win_.ymin_);
}



void GameManager::checkAsteroidCollisions() {
	Vector s_pos = ship_.getPosition();
	for (Asteroid& asteroid : asteroid_field_.getAsteroids()) {
		Vector a_pos = asteroid.getPosition();
		if (Collision::circleWithCircle(
							s_pos.x, s_pos.y,
							ship_.getCollisionRadius(),
							a_pos.x, a_pos.y,
							asteroid.getCollisionRadius())) {
			resetGame();
		}
	}
}

void GameManager::checkBulletCollisions() {
	int counter = 0;
	for (Bullet& bullet : ship_.getBulletStream().getBullets()) {
		for (Wall& wall : arena_.getWalls()) {
			Point p1 = wall.p1;
			Point p2 = wall.p2;
			Vector b_position = bullet.getPosition();
			if (Collision::lineWithPoint(p1.x, p1.y, p2.x, p2.y, b_position.x, b_position.y)) {
				bullet.markForDeletion();
			}
		}
		++counter;
	}
}

void GameManager::resetGame() {
	ship_.reset();
	asteroid_field_.reset();
	playing = false;
}