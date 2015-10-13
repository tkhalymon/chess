#include "bishop.hpp"

Bishop::Bishop(Cell* pos, Color color) : Figure(pos, color)
{
	if (color == White)
	{
		tex.load("res/wbishop.png");
	}
	else
	{
		tex.load("res/bbishop.png");
	}
}

Bishop::~Bishop()
{

}

bool Bishop::movePossible(Cell* cell)
{
	// vertical direction
	if (abs(this->cell->x() - cell->x()) == abs(this->cell->y() - cell->y()))
	{
		int vdir;
		if (cell->y() > this->cell->y()) vdir = 1;
		else vdir = -1;
		// horizontal direction
		int hdir;
		if (cell->x() > this->cell->x()) hdir = 1;
		else hdir = -1;
		// distance
		int dist = abs(this->cell->x() - cell->x());
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