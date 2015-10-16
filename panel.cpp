#include <GL/glut.h>
#include <string.h>
#include "panel.hpp"

Panel::Panel()
{
	width = 170;
	// int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	inside[0] = Position (h + h / 20, h / 10);
	inside[1] = Position (h + h / 20 + width, 9 * h / 10);
	outside[0] = Position (h, h / 20);
	outside[1] = Position (h + h / 10 + width, 19 * h / 20);
}

Panel::~Panel()
{

}

void Panel::init(std::vector<char *>* _notation)
{
	notation = _notation;
}

void renderString(char* str, int x, int y)
{
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen((char *)str);
	for (i = 0; i < len; i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

void Panel::render()
{
	int cellSize = 0;
	glBegin(GL_QUADS);
	glColor3d(0, 0, 0);
	glVertex2d(outside[0].x() + cellSize * (-0.5), outside[0].y() + cellSize * (-0.5));
	glVertex2d(outside[1].x() + cellSize * (8.5), outside[0].y() + cellSize * (-0.5));
	glColor3d(0.5, 0.5, 0.5);
	glVertex2d(inside[1].x() + cellSize * (8.025), inside[0].y() + cellSize * (-0.025));
	glVertex2d(inside[0].x() + cellSize * (-0.025), inside[0].y() + cellSize * (-0.025));
	
	glColor3d(0, 0, 0);
	glVertex2d(outside[1].x() + cellSize * (8.5), outside[0].y() + cellSize * (-0.5));
	glVertex2d(outside[1].x() + cellSize * (8.5), outside[1].y() + cellSize * (8.5));
	glColor3d(0.5, 0.5, 0.5);
	glVertex2d(inside[1].x() + cellSize * (8.025), inside[1].y() + cellSize * (8.025));
	glVertex2d(inside[1].x() + cellSize * (8.025), inside[0].y() + cellSize * (-0.025));

	glColor3d(0, 0, 0);
	glVertex2d(outside[0].x() + cellSize * (-0.5), outside[1].y() + cellSize * (8.5));
	glVertex2d(outside[1].x() + cellSize * (8.5), outside[1].y() + cellSize * (8.5));
	glColor3d(0.5, 0.5, 0.5);
	glVertex2d(inside[1].x() + cellSize * (8.025), inside[1].y() + cellSize * (8.025));
	glVertex2d(inside[0].x() + cellSize * (-0.025), inside[1].y() + cellSize * (8.025));

	glColor3d(0, 0, 0);
	glVertex2d(outside[0].x() + cellSize * (-0.5), outside[1].y() + cellSize * (8.5));
	glVertex2d(outside[0].x() + cellSize * (-0.5), outside[0].y() + cellSize * (-0.5));
	glColor3d(0.5, 0.5, 0.5);
	glVertex2d(inside[0].x() + cellSize * (-0.025), inside[0].y() + cellSize * (-0.025));
	glVertex2d(inside[0].x() + cellSize * (-0.025), inside[1].y() + cellSize * (8.025));

	glVertex2d(inside[0].x(), inside[0].y());
	glVertex2d(inside[1].x(), inside[0].y());
	glVertex2d(inside[1].x(), inside[1].y());
	glVertex2d(inside[0].x(), inside[1].y());
	glEnd();
	glColor3d(1, 1, 1);
	for (int i = 0; i < notation->size(); i++)
	{
		renderString((*notation)[i], inside[0].x() + 5 + (i % 2) * width / 2, inside[0].y() + 20 + i / 2 * 20);
	}
}

void Panel::reshape()
{
	
}