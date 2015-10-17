#include <GL/glut.h>
#include "pngtex.hpp"

#include "piece.hpp"

bool (*Piece::cellEmpty)(int x, int y);

Piece::Piece(Cell* _cell, Color c) : cell (_cell), _color(c), _dead(false)
{
	_dead = false;
	cell->setPiece(this);
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

PieceType Piece::type()
{
	return pType;
}

void Piece::bindTex()
{
	tex.use();
}

void Piece::move(Cell* cell)
{
	this->cell->setPiece(NULL);
	this->cell = cell;
	this->cell->setPiece(this);
}

bool Piece::movePossible(Cell* cell)
{
	return false;
}