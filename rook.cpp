#include "rook.hpp"

Rook::Rook(Cell* pos, Color color, Cell* castlePos) : Piece(pos, color), castlePos(castlePos)
{
	pType = PRook;
	if (color == White)
	{
		tex.load("res/wrook.png");
	}
	else
	{
		tex.load("res/brook.png");
	}
	castlPossible = true;
}

Rook::~Rook()
{

}

void Rook::move(Cell* cell)
{
	castlPossible = false;
	this->cell->setPiece(NULL);
	this->cell = cell;
	this->cell->setPiece(this);
}

bool Rook::movePossible(Cell* cell)
{
	if (this->cell->x() == cell->x() || this->cell->y() == cell->y())
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

bool Rook::castl()
{
	return castlPossible;
}

void Rook::noCastl()
{
	castlPossible = false;
}

void Rook::castling()
{
	move(castlePos);
}