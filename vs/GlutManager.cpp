#include "GlutManager.h"
#include "Defines.h"
#include <iostream>

GameManager::GameManager() : planeLim(PLANE_LIM), maxArenaX(MAX_ARENA_X), maxArenaY(MAX_ARENA_Y), maxArenaZ(MAX_ARENA_Z) {}

void GameManager::startGameLoop()
{
	glutMainLoop();
}

void GameManager::onReshape(int w, int h)
{
	GLdouble aspect = (GLdouble)h / (GLdouble)w;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h >= w) {
		glOrtho(-planeLim, planeLim, -planeLim * aspect, planeLim * aspect, -planeLim, 1);
	}
	else {
		glOrtho(-planeLim / aspect, planeLim / aspect, -planeLim, 1, -1, 1);
	}
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);
}

void GameManager::onKeyboardPress(unsigned char key, int x, int y)
{
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

void GameManager::onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		glVertex3f(-maxArenaX, -maxArenaY, 0.0);
		glVertex3f(-maxArenaX, maxArenaY, 0.0);
		glVertex3f(maxArenaX, maxArenaY, 0.0);
		glVertex3f(maxArenaX, -maxArenaY, 0.0);
	glEnd();

	ship.drawSpaceShip();

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void GameManager::onIdle()
{
	glutPostRedisplay();
}
