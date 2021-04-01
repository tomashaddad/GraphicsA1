#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

#include "GlutManager.h"

#include <iostream>
#include <memory>

void onReshape(int w, int h);
void onKeyboardPress(unsigned char key, int x, int y);
void onDisplay();
void onIdle();

std::unique_ptr<GameManager> game = std::make_unique<GameManager>();

void onReshape(int w, int h) {
	game->onReshape(w, h);
}

void onKeyboardPress(unsigned char key, int x, int y) {
	game->onKeyboardPress(key, x, y);
}

void onDisplay() {
	game->onDisplay();
}

void onIdle() {
	game->onIdle();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Asteroid Arena");

	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKeyboardPress);
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onIdle);

	game->startGameLoop();

	return EXIT_SUCCESS;
}