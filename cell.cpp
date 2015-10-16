#include "cell.hpp"

Cell::Cell()
{}

Cell::~Cell()
{}

void Cell::setPos(int x, int y, Color c)
{
	color = c;
	_x = x;
	_y = y;
	double cellSize = glutGet(GLUT_WINDOW_HEIGHT) / 10;
	coords[0] = Position(cellSize * ((double)x + 1.025), cellSize * ((double)y + 1.025));
	coords[1] = Position(cellSize * ((double)x + 1.975), cellSize * ((double)y + 1.025));
	coords[2] = Position(cellSize * ((double)x + 1.975), cellSize * ((double)y + 1.975));
	coords[3] = Position(cellSize * ((double)x + 1.025), cellSize * ((double)y + 1.975));
	coords[4] = Position(cellSize * ((double)x + 1.12), cellSize * ((double)y + 1.12));
	coords[5] = Position(cellSize * ((double)x + 1.88), cellSize * ((double)y + 1.12));
	coords[6] = Position(cellSize * ((double)x + 1.88), cellSize * ((double)y + 1.88));
	coords[7] = Position(cellSize * ((double)x + 1.12), cellSize * ((double)y + 1.88));
}

Piece* Cell::piece()
{
	return _piece;
}

void Cell::setFigure(Piece* piece)
{
	this->_piece = piece;
}

bool Cell::inside(int x, int y)
{
	if (x > coords[0].x() && y > coords[0].y() && x < coords[2].x() && y < coords[2].y())
	{
		return true;
	}
	return false;
}

Position* Cell::pos()
{
	return coords;
}

int Cell::x()
{
	return _x;
}

int Cell::y()
{
	return _y;
}

bool Cell::empty()
{
	return _piece == NULL;
}

void Cell::render()
{
	if (color == White) glColor3d(0.7, 0.7, 0.7);
	else glColor3d(0.3, 0.3, 0.3);
	glVertex2dv(coords[0].v());
	glVertex2dv(coords[1].v());
	glVertex2dv(coords[2].v());
	glVertex2dv(coords[3].v());
	glEnd();
	if (!empty())
	{
		glEnable(GL_TEXTURE_2D);
		_piece->bindTex();
		glEnable(GL_BLEND);
		glEnable(GL_SMOOTH);
		glBegin(GL_QUADS);
		glColor3d(1, 1, 1);
		glTexCoord2d(0, 0);
		glVertex2dv(coords[0].v());
		glTexCoord2d(1, 0);
		glVertex2dv(coords[1].v());
		glTexCoord2d(1, 1);
		glVertex2dv(coords[2].v());
		glTexCoord2d(0, 1);
		glVertex2dv(coords[3].v());
		glEnd();
		glDisable(GL_SMOOTH);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
	glBegin(GL_QUADS);

}

void Cell::renderPointed()
{
	for (int i = 0; i < 4; ++i)
	{
		if (color == White) glColor3d(0.3, 0.3, 0.3);
		else glColor3d(0.7, 0.7, 0.7);
		glVertex2dv(coords[0 + i].v());
		glVertex2dv(coords[(1 + i) % 4].v());
		if (color == White) glColor3d(0.7, 0.7, 0.7);
		else glColor3d(0.3, 0.3, 0.3);
		
		glVertex2dv(coords[4 + (1 + i) % 4].v());
		glVertex2dv(coords[4 + i].v());
	}
}

void Cell::renderSelected()
{
	for (int i = 0; i < 4; ++i)
	{
		glColor3d(1, 1, 1);
		glVertex2dv(coords[0 + i].v());
		glVertex2dv(coords[(1 + i) % 4].v());
		glVertex2dv(coords[4 + (1 + i) % 4].v());
		glVertex2dv(coords[4 + i].v());
	}
}