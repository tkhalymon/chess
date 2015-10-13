#include "queen.hpp"

Queen::Queen(Cell* pos, Color color) : Figure(pos, color)
{
	if (color == White)
	{
		tex.load("res/wqueen.png");
	}
	else
	{
		tex.load("res/bqueen.png");
	}
}

Queen::~Queen()
{

}

bool Queen::movePossible(Cell* cell)
{
	// vertical direction
	if (abs(this->cell->x() - cell->x()) == abs(this->cell->y() - cell->y())
		|| this->cell->x() == cell->x() || this->cell->y() == cell->y())
	{
		int vdir;
		if (this->cell->y() == cell->y()) vdir = 0;
		else if (cell->y() > this->cell->y()) vdir = 1;
		else vdir = -1;
		// horizontal direction
		int hdir;
		if (this->cell->x() == cell->x()) hdir = 0;
		else if (cell->x() > this->cell->x()) hdir = 1;
		else hdir = -1;
		// distance
		int dist;
		if (hdir == 0) dist = abs(this->cell->y() - cell->y());
		else dist = abs(this->cell->x() - cell->x());
		for (int i = 1; i < dist; ++i)
		{
			if (!cellEmpty(this->cell->x() + hdir * i, this->cell->y() + vdir * i))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}