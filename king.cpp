#include "king.hpp"

King::King(Cell* pos, Color color) : Figure(pos, color)
{
	firstMove = true;
	type = FKing;
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
	firstMove = false;
	this->cell->setFigure(NULL);
	this->cell = cell;
	this->cell->setFigure(this);
}

bool King::movePossible(Cell* cell)
{
	if (abs(this->cell->x() - cell->x()) <= 1 && abs(this->cell->y() - cell->y()) <= 1)
	{
		return true;
	}
	return false;
}