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

void reshape_callback(int w, int h);
void keyboard_callback(unsigned char key, int x, int y);
void display_callback();
void idle_callback();

std::unique_ptr<GameManager> game = std::make_unique<GameManager>();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Asteroid Arena");

	glutReshapeFunc(reshape_callback);
	glutKeyboardFunc(keyboard_callback);
	glutDisplayFunc(display_callback);
	glutIdleFunc(idle_callback);

	game->startGameLoop();

	return EXIT_SUCCESS;
}

void reshape_callback(int w, int h) {
	game->onReshape(w, h);
}

void keyboard_callback(unsigned char key, int x, int y) {
	game->onKeyboardPress(key, x, y);
}

void display_callback() {
	game->onDisplay();
}

void idle_callback() {
	game->onIdle();
}
