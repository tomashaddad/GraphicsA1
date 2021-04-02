#include "GlutManager.h"
#include "Defines.h"
#include "State.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

GameManager::GameManager()
	: ship_(Ship(win_)),
	  dt_(0),
	  last_time_(glutGet(GLUT_ELAPSED_TIME) / 1000.0) 
{
	double arena_width = 2 * MAX_ARENA_X;
	double arena_height = 2 * MAX_ARENA_Y;

	double slope = arena_height / arena_width;
	double angle = 180.0 * ( atanf(slope) / M_PI );

	double margin = 0.1; // arbitrarily chosen to be a 10% margin
	double ship_x = -MAX_ARENA_X + arena_width * margin; 
	double ship_y = slope * ship_x; // y = mx + c, m = slope, c = 0
	Point starting_coords{ ship_x, ship_y };
}

void GameManager::startGameLoop() {
	glutMainLoop();
}

void GameManager::onReshape(int w, int h) {
	win_.win_width_ = w;
	win_.win_height_ = h;

	if (w > h) {
		win_.xmin_ = win_.plane_lim_ * -(GLfloat)w / h;
		win_.xmax_ = win_.plane_lim_ * (GLfloat)w / h;
		win_.ymin_ = -win_.plane_lim_;
		win_.ymax_ = win_.plane_lim_;
	}
	else {
		win_.xmin_ = -win_.plane_lim_;
		win_.xmax_ = win_.plane_lim_;
		win_.ymin_ = win_.plane_lim_ * -(GLfloat)h / w;
		win_.ymax_ = win_.plane_lim_ * (GLfloat)h / w;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(win_.xmin_, win_.xmax_, win_.ymin_, win_.ymax_, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);
}

void GameManager::onKeyboardPress(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	case 'w':
		ship_.translate(Movement::MOVE_FORWARD);
		break;
	case 'a':
		ship_.rotate(Movement::ROTATE_LEFT);
		break;
	case 's':
		ship_.translate(Movement::MOVE_BACKWARD);
		break;
	case 'd':
		ship_.rotate(Movement::ROTATE_RIGHT);
		break;
	default:
		break;
	}
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

	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex2f(-MAX_ARENA_X, -MAX_ARENA_Y);
	glVertex2f(-MAX_ARENA_X, MAX_ARENA_Y);
	glVertex2f(MAX_ARENA_X, MAX_ARENA_Y);
	glVertex2f(MAX_ARENA_X, -MAX_ARENA_Y);
	glEnd();

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
