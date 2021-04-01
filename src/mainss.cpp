#include <iostream>

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

void on_display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
		
	glBegin(GL_LINES);
	glVertex3f(-2.5, -2.5, 0.0);
	glVertex3f(2.5, 2.5, 0.0);
	glEnd();

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

/* You can ignore this for now, it just lets you exit when you press 'q' or ESC */
void keyboard(unsigned char key, int x, int y)
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

void on_idle()
{
	glutPostRedisplay();
}

void on_reshape(int w, int h)
{
	GLdouble aspect = (GLdouble)h / (GLdouble)w;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h >= w) {
		glOrtho(-5 , 5 , -5 * aspect, 5 * aspect, -5, 5);
	}
	else {
		glOrtho(-5 / aspect, 5 / aspect, -5 , 5 , -5, 5);
	}
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);
}

void init_app(int* argcp, char** argv)
{
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Asteroid Arena");
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(keyboard);

	glutDisplayFunc(on_display);
	glutIdleFunc(on_idle);
}

int mains(int argc, char** argv)
{
	init_app(&argc, argv);
	glutMainLoop();
	return EXIT_SUCCESS;
}
