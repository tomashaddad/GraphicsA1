#include "GlutManager.h"
#include "Defines.h"
#include "State.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

GameManager::GameManager()
	: plane_lim_(PLANE_LIM),
	  dragging_(false),
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

	this->ship_ = std::make_unique<Ship>(ship_x, ship_y, SHIP_WIDTH, SHIP_HEIGHT, angle);
}

void GameManager::startGameLoop() {
	glutMainLoop();
}

void GameManager::onReshape(int w, int h) {
	win_width_ = w;
	win_height_ = h;

	if (w > h) {
		xmin_ = plane_lim_ * -(GLfloat)w / h;
		xmax_ = plane_lim_ * (GLfloat)w / h;
		ymin_ = -plane_lim_;
		ymax_ = plane_lim_;
	}
	else {
		xmin_ = -plane_lim_;
		xmax_ = plane_lim_;
		ymin_ = plane_lim_ * -(GLfloat)h / w;
		ymax_ = plane_lim_ * (GLfloat)h / w;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xmin_, xmax_, ymin_, ymax_, -1.0, 1.0);
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
		ship_->translate(Movement::MOVE_FORWARD);
		break;
	case 'a':
		ship_->rotate(Movement::ROTATE_LEFT);
		break;
	case 's':
		ship_->translate(Movement::MOVE_BACKWARD);
		break;
	case 'd':
		ship_->rotate(Movement::ROTATE_RIGHT);
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
			dragging_ = true;
			glutPostRedisplay();
		}
		else {
			dragging_ = false;
		}
		break;
	}
}

void GameManager::onMouseClickDrag(int x, int y)
{
	mouse_x_ = xmin_ + (double(x) / win_width_) * (xmax_ - xmin_);
	mouse_y_ = ymax_ + (double(y) / win_height_) * (ymin_ - ymax_);
}

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//walls_[0]->drawWall(-xmax_, -ymax_, -xmax_, ymax_);
	//walls_[1]->drawWall(-xmax_, ymax_, xmax_, ymax_);
	//walls_[2]->drawWall(xmax_, ymax_, xmax_, -ymax_);
	//walls_[3]->drawWall(xmax_, -ymax_, -xmax_, -ymax_);

	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex3f(-MAX_ARENA_X, -MAX_ARENA_Y, 0.0);
	glVertex3f(-MAX_ARENA_X, MAX_ARENA_Y, 0.0);
	glVertex3f(MAX_ARENA_X, MAX_ARENA_Y, 0.0);
	glVertex3f(MAX_ARENA_X, -MAX_ARENA_Y, 0.0);
	glEnd();

	ship_->drawSpaceShip();

	if (dragging_) {
		ship_->setPos(mouse_x_, mouse_y_);
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
