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
	double cellSize = glutGet(GLUT_WINDOW_HEIGHT) / 10.;
	coords[0] = Position(cellSize * (x + 1), cellSize * (y + 1));
	coords[1] = Position(cellSize * (x + 2), cellSize * (y + 1));
	coords[2] = Position(cellSize * (x + 2), cellSize * (y + 2));
	coords[3] = Position(cellSize * (x + 1), cellSize * (y + 2));

	coords[4] = Position(cellSize * (x + 1.1), cellSize * (y + 1.1));
	coords[5] = Position(cellSize * (x + 1.9), cellSize * (y + 1.1));
	coords[6] = Position(cellSize * (x + 1.9), cellSize * (y + 1.9));
	coords[7] = Position(cellSize * (x + 1.1), cellSize * (y + 1.9));
}

Piece* Cell::piece()
{
	return _piece;
}

void Cell::setPiece(Piece* piece)
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

void Cell::renderCell()
{
	glBegin(GL_QUADS);
	if (color == White) glColor3d(0.8, 0.8, 0.8);
	else glColor3d(0.5, 0.5, 0.5);
	glVertex2dv(coords[0].v());
	glVertex2dv(coords[1].v());
	glVertex2dv(coords[2].v());
	glVertex2dv(coords[3].v());
	glEnd();
}

void Cell::renderCheck()
{
	glEnable(GL_ALPHA);
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glColor4d(1, 0, 0, 0.5);
	glVertex2dv(coords[0].v());
	glVertex2dv(coords[1].v());
	glVertex2dv(coords[2].v());
	glVertex2dv(coords[3].v());
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA);
}

void Cell::renderPiece(bool check)
{
	if (check) renderCheck();
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	_piece->bindTex();
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
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Cell::renderPointed(bool check)
{
	renderCell();
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; ++i)
	{
		if (color == White) glColor3d(0.5, 0.5, 0.5);
		else glColor3d(0.8, 0.8, 0.8);
		glVertex2dv(coords[0 + i].v());
		glVertex2dv(coords[(1 + i) % 4].v());
		if (color == White) glColor3d(0.8, 0.8, 0.8);
		else glColor3d(0.5, 0.5, 0.5);
		glVertex2dv(coords[4 + (1 + i) % 4].v());
		glVertex2dv(coords[4 + i].v());
	}
	glEnd();
	if (!empty())
	{
		renderPiece(check);
	}
}

void Cell::renderSelected(bool check)
{
	renderCell();
	glBegin(GL_QUADS);
	glColor3d(0.3, 0.3, 0.3);
	for (int i = 0; i < 4; ++i)
	{
		glVertex2dv(coords[0 + i].v());
		glVertex2dv(coords[(1 + i) % 4].v());
		glVertex2dv(coords[4 + (1 + i) % 4].v());
		glVertex2dv(coords[4 + i].v());
	}
	glEnd();
	renderPiece(check);
}