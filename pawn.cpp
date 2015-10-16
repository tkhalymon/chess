#include "pawn.hpp"

Pawn::Pawn(Cell* pos, Color color) : Figure(pos, color)
{
	firstMove = true;
	type = FPawn;
	if (color == White)
	{
		tex.load("res/wpawn.png");
	}
	else
	{
		tex.load("res/bpawn.png");
	}
}

Pawn::~Pawn()
{

}



bool Pawn::movePossible(Cell* cell)
{
	if (_color == Black)
	{
		if (firstMove && cell->y() == 3 && this->cell->x() == cell->x()
			&& cellEmpty(cell->x(), 2) && cellEmpty(cell->x(), 3))
		{
			return true;
		}
		if (cell->x() == this->cell->x() && cell->y() == this->cell->y() + 1
			&& (cellEmpty(cell->x(), cell->y())))
		{
			return true;
		}
		if (cell->x() == this->cell->x() + 1 && cell->y() == this->cell->y() + 1
			&& !cellEmpty(cell->x(), cell->y()) && cell->figure()->color() == White)
		{
			return true;
		}
		if (cell->x() == this->cell->x() - 1 && cell->y() == this->cell->y() + 1
			&& !cellEmpty(cell->x(), cell->y()) && cell->figure()->color() == White)
		{
			return true;
		}
	}
	else
	{
		if (firstMove && cell->y() == 4 && this->cell->x() == cell->x()
			&& cellEmpty(cell->x(), 4) && cellEmpty(cell->x(), 5))
		{
			return true;
		}
		if (cell->x() == this->cell->x() && cell->y() == this->cell->y() - 1
			&& (cellEmpty(cell->x(), cell->y())))
		{
			return true;
		}
		if (cell->x() == this->cell->x() + 1 && cell->y() == this->cell->y() - 1
			&& !cellEmpty(cell->x(), cell->y()) && cell->figure()->color() == Black)
		{
			return true;
		}
		if (cell->x() == this->cell->x() - 1 && cell->y() == this->cell->y() - 1
			&& !cellEmpty(cell->x(), cell->y()) && cell->figure()->color() == Black)
		{
			return true;
		}
	}
	return false;
}