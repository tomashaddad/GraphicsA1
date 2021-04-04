#include "GlutManager.h"
#include "Defines.h"
#include "Enums.h"
#include "Collision.h"
#include "Vector.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <utility>
#include <iostream>

GameManager::GameManager()
	: ship_(Ship(win_)),
	  dt_(0),
	  last_time_(0) { }

void GameManager::startGameLoop() {
	glutMainLoop();
}

//Asteroid asteroid(window_, ship_);
void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	arena_.drawArena();
	ship_.drawSpaceShip();
	//asteroid.drawAsteroid();

	float x, y, theta;
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	for (int i = 0; i < 30; ++i) {
		theta = i / (float)30 * 2 * M_PI;
		x = 10 * cosf(theta) + 50;
		y = 10 * sinf(theta) + 50;
		glVertex2f(x, y);
	}
	glEnd();

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
			mouse_.setDragging(true);
			glutPostRedisplay();
		}
		else {
			mouse_.setDragging(false);
		}
		break;
	}
}

void GameManager::onMouseClickDrag(int x, int y)
{
	double xmouse = win_.xmin_ + (double(x) / win_.win_width_) * (win_.xmax_ - win_.xmin_);
	double ymouse = win_.ymax_ + (double(y) / win_.win_height_) * (win_.ymin_ - win_.ymax_);
	
	mouse_.setMouseCoords(xmouse, ymouse);
}


void GameManager::calculateTimeDelta() {
	float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt_ = cur_time - last_time_;
	last_time_ = cur_time;

	glutPostRedisplay();
}

void GameManager::handleKeyboardInput() {
	// quit
	if (keyboard_.getKeyState('q')) {
		exit(EXIT_SUCCESS);
	}

	// forward/backward (+ acceleration case)
	if (keyboard_.getKeyState('w')) {
		ship_.translate(Movement::MOVE_FORWARD, dt_);
	}
	else if (keyboard_.getKeyState('s')) {
		ship_.translate(Movement::MOVE_BACKWARD, dt_);
	}
	else {
		ship_.deaccelerate(dt_);
	}

	// rotation
	if (keyboard_.getKeyState('a')) {
		ship_.rotate(Movement::ROTATE_LEFT);
	}
	else if (keyboard_.getKeyState('d')) {
		ship_.rotate(Movement::ROTATE_RIGHT);
	}

	glutPostRedisplay();
}

void GameManager::handleMouseInput() {
	// allows ship to be moved by click-drag
	if (mouse_.isDragging()) {
		ship_.setPosition(mouse_.getMouseCoords());
	}
}

void GameManager::checkWallCollisions() {
	for (Wall& wall : arena_.getWalls()) {
		Point p1 = wall.p1;
		Point p2 = wall.p2;
		Vector pos = ship_.getPosition();
		float r_warning = ship_.getWarningRadius();
		float r_collision = ship_.getCollisionRadius();

		if (Collision::circleWithLine(p1.x, p1.y, p2.x, p2.y, pos.x, pos.y, r_warning)) {
			wall.setColour(Colour::RED);
		}
		else {
			wall.setColour(Colour::WHITE);
		}

		if (Collision::circleWithLine(p1.x, p1.y, p2.x, p2.y, pos.x, pos.y, r_collision)) {
			ship_.resetPosition();
		}
	}
}