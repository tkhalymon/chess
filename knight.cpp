#include "knight.hpp"

Knight::Knight(Cell* pos, Color color) : Figure(pos, color)
{
	type = FKnight;
	if (color == White)
	{
		tex.load("res/wknight.png");
	}
	else
	{
		tex.load("res/bknight.png");
	}
}

Knight::~Knight()
{

}

bool Knight::movePossible(Cell* cell)
{
	if ((abs(this->cell->x() - cell->x()) == 2 && abs(this->cell->y() - cell->y()) == 1)
		|| (abs(this->cell->x() - cell->x()) == 1 && abs(this->cell->y() - cell->y()) == 2))
	{
		return true;
	}
	return false;
}