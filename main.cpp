#include <GL/glut.h>

void display();
void timer(int);
void reshape(int width, int height);
void mousePressed(int button, int state, int x, int y);
void mouseMove(int x, int y);
void mousePressedMove(int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);

#include "board.hpp"

Board* board;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	// int w = 640;
	// int h = 640;
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("Chess 1.0 beta");
	glClearColor(0.05, 0.05, 0.05, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -2, 2);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutReshapeFunc(reshape);
	glutMouseFunc(mousePressed);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mousePressedMove);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	board = new Board();
	// glutFullScreen();
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	board->advance();
	board->render();
	glutSwapBuffers();
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(2, timer, 0);
}

void reshape(int width, int height)
{
	board->reshape(width, height);
}

void mousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	board->click(button, state, x, y);
}

void mouseMove(int x, int y)
{
	board->mouseMove(x, y);
}

void mousePressedMove(int x, int y)
{

}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:
		delete(board);
		glutDestroyWindow(1);
		exit(0);
		break;
	default:
		board->keypressed(key);
		break;
	}
}

void specialKeyboard(int key, int x, int y)
{

}
