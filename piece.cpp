#include <GL/glut.h>
#include "pngtex.hpp"

#include "piece.hpp"

int Piece::cellSize;

bool (*Piece::cellEmpty)(int x, int y);

Piece::Piece(Cell* _cell, Color c) : cell (_cell), _color(c), _dead(false)
{
	_dead = false;
	cell->setFigure(this);
}

Piece::~Piece()
{}

Color Piece::color()
{
	return _color;
}

void Piece::kill()
{
	_dead = true;
}

bool Piece::dead()
{
	return _dead;
}

PieceType Piece::fType()
{
	return type;
}

void Piece::bindTex()
{
	tex.use();
}

void Piece::move(Cell* cell)
{
	this->cell->setFigure(NULL);
	this->cell = cell;
	this->cell->setFigure(this);
}

bool Piece::movePossible(Cell* cell)
{
	return false;
}

void Piece::setCellSize(int size)
{
	cellSize = size;
}