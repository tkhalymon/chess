#include "king.hpp"

King::King(Cell* pos, Color color) : Piece(pos, color)
{
	pType = PKing;
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

bool King::movePossible(Cell* cell)
{
	if (abs(this->cell->x() - cell->x()) <= 1 && abs(this->cell->y() - cell->y()) <= 1)
		return true;
	return false;
}