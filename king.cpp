#include "king.hpp"

King::King(Cell* pos, Color color) : Piece(pos, color)
{
	lCastling = true;
	rCastling = true;
	type = PKing;
	if (color == White)
	{
		tex.load("res/wking.png");
	}
	else
	{
		tex.load("res/bking.png");
	}
}

King::~King()
{

}

void King::move(Cell* cell)
{
	lCastling = false;
	rCastling = false;
	this->cell->setFigure(NULL);
	this->cell = cell;
	this->cell->setFigure(this);
}

bool King::movePossible(Cell* cell)
{
	if (abs(this->cell->x() - cell->x()) <= 1 && abs(this->cell->y() - cell->y()) <= 1)
		return true;
	if (lCastling)
	{
		
	}
	return false;
}