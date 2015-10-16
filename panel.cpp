#include <GL/glut.h>
#include <string.h>
#include "panel.hpp"

Panel::Panel()
{
	
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
	glPushMatrix();
	// glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen((char *)str);
	glLineWidth(2);
	glTranslated(x, y, 0);
	glScaled(0.15, -0.15, 1);
	for (i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
}

void Panel::render()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; ++i)
	{
		glColor3d(0, 0, 0);
		glVertex2dv(coords[0 + i].v());
		glVertex2dv(coords[(1 + i) % 4].v());
		glColor3d(0.7, 0.7, 0.7);
		glVertex2dv(coords[4 + (1 + i) % 4].v());
		glVertex2dv(coords[4 + i].v());
	}
	glVertex2dv(coords[4].v());
	glVertex2dv(coords[5].v());
	glVertex2dv(coords[6].v());
	glVertex2dv(coords[7].v());
	glEnd();
	glColor3d(0, 0, 0);
	for (int i = 0; i < notation->size(); i++)
	{
		renderString((*notation)[i], coords[4].x() + 5 + (i % 2) * width / 2, coords[4].y() + 20 + i / 2 * 25);
	}
}

void Panel::reshape()
{
	width = 170;
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	coords[0] = Position (h - 0.05 * h, 0.05 * h);
	coords[1] = Position (h + width + 0.05 * h, 0.05 * h);
	coords[2] = Position (h + width + 0.05 * h, 0.95 * h);
	coords[3] = Position (h - 0.05 * h, 0.95 * h);
	coords[4] = Position (h - 0.0025 * h, 0.0975 * h);
	coords[5] = Position (h + width + 0.0025 * h, 0.0975 * h);
	coords[6] = Position (h + width + 0.0025 * h, 0.9025 * h);
	coords[7] = Position (h - 0.0025 * h, 0.9025 * h);
}