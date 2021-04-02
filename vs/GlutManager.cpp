#include "GlutManager.h"
#include "Defines.h"
#include <iostream>

GameManager::GameManager()
	: plane_lim_(PLANE_LIM),
	  max_x_(MAX_ARENA_X),
	  max_y_(MAX_ARENA_Y),
	  max_z_(MAX_ARENA_Z),
	  ship(std::make_unique<Ship>()),
	  dt(0),
	  last_time(glutGet(GLUT_ELAPSED_TIME) / 1000.0) {}

void GameManager::startGameLoop() {
	glutMainLoop();
}

void GameManager::onReshape(int w, int h) {
	GLdouble aspect = (GLdouble)w / (GLdouble)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h) {
		glOrtho(-plane_lim_ * aspect, plane_lim_ * aspect, -plane_lim_, plane_lim_, -plane_lim_, 1);
	}
	else {
		glOrtho(-plane_lim_, plane_lim_, -plane_lim_ / aspect, plane_lim_ / aspect, -1, 1);
	}
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
	default:
		break;
	}
}

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		glVertex3f(-max_x_, -max_y_, 0.0);
		glVertex3f(-max_x_, max_y_, 0.0);
		glVertex3f(max_x_, max_y_, 0.0);
		glVertex3f(max_x_, -max_y_, 0.0);
	glEnd();

	ship->drawSpaceShip(-max_x_ + 20, -max_y_ + 20, 7, 10);

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void GameManager::onIdle() {
	float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt = cur_time - last_time;
	last_time = cur_time;
	glutPostRedisplay();
}
