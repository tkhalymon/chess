#include <GL/glut.h>
#include "pngtex.hpp"

#include "figure.hpp"

int Figure::cellSize;

bool (*Figure::cellEmpty)(int x, int y);

Figure::Figure(Cell* _cell, Color c) : cell (_cell), _color(c), _dead(false)
{
	_dead = false;
	cell->setFigure(this);
}

Figure::~Figure()
{}

Color Figure::color()
{
	return _color;
}

void Figure::kill()
{
	_dead = true;
}

bool Figure::dead()
{
	return _dead;
}

void Figure::render()
{
	tex.use();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3d(1, 1, 1);
	glTexCoord2d(0, 0);
	glVertex2d(cell->pos().x() + cellSize * 0.025, cell->pos().y() + cellSize * 0.025);
	glTexCoord2d(1, 0);
	glVertex2d(cell->pos().x() + cellSize * 0.975, cell->pos().y() + cellSize * 0.025);
	glTexCoord2d(1, 1);
	glVertex2d(cell->pos().x() + cellSize * 0.975, cell->pos().y() + cellSize * 0.975);
	glTexCoord2d(0, 1);
	glVertex2d(cell->pos().x() + cellSize * 0.025, cell->pos().y() + cellSize * 0.975);
	glEnd();
	glDisable(GL_SMOOTH);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Figure::move(Cell* cell)
{
	this->cell->setFigure(NULL);
	this->cell = cell;
	this->cell->setFigure(this);
}

bool Figure::movePossible(Cell* cell)
{
	return false;
}

void Figure::setCellSize(int size)
{
	cellSize = size;
}