#include "GlutManager.h"
#include "Defines.h"
#include "State.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

GameManager::GameManager()
	: ship_(Ship(win_)),
	  dt_(0),
	  last_time_(0) { }

void GameManager::startGameLoop() {
	glutMainLoop();
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

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	ship_.drawSpaceShip();

	if (keyboard_.getKeyState('q')) {
		exit(EXIT_SUCCESS);
	}
	
	if (keyboard_.getKeyState('w')) {
		ship_.translate(Movement::MOVE_FORWARD, dt_);
	}
	else if (keyboard_.getKeyState('s')) {
		ship_.translate(Movement::MOVE_BACKWARD, dt_);
	}
	else {
		ship_.deaccelerate(dt_);
	}
	
	
	if (keyboard_.getKeyState('a')) {
		ship_.rotate(Movement::ROTATE_LEFT);
	}
	else if (keyboard_.getKeyState('d')) {
		ship_.rotate(Movement::ROTATE_RIGHT);
	}

	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		glVertex2f(-MAX_ARENA_X, -MAX_ARENA_Y);
		glVertex2f(-MAX_ARENA_X, MAX_ARENA_Y);
		glVertex2f(MAX_ARENA_X, MAX_ARENA_Y);
		glVertex2f(MAX_ARENA_X, -MAX_ARENA_Y);
	glEnd();

	Vector ship_position = ship_.getPosition();

	if (ship_position.x - (-MAX_ARENA_X) < 10) {
		glLineWidth(5.0);
		glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex2f(-MAX_ARENA_X, -MAX_ARENA_Y);
			glVertex2f(-MAX_ARENA_X, MAX_ARENA_Y);
		glEnd();
	}

	if (mouse_.isDragging()) {
		ship_.setPos(mouse_.getMouseCoords());
	}

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void GameManager::onIdle() {
	float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt_ = cur_time - last_time_;
	last_time_ = cur_time;
	glutPostRedisplay();
}
