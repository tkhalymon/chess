#include "pawn.hpp"

int Pawn::passCell;
Pawn* Pawn::passPawn = NULL;

Pawn::Pawn(Cell* pos, Color color) : Piece(pos, color)
{
	pType = PPawn;
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

void Pawn::move(Cell* cell)
{
	if (cell->empty() && this->cell->x() != cell->x() && passPawn != NULL)
	{
		passPawn->take();
	}
	if (abs(this->cell->y() - cell->y()) == 2)
	{
		passCell = this->cell->x();
		passPawn = this;
	}
	else
	{
		passPawn = NULL;
	}
	this->cell->setPiece(NULL);
	this->cell = cell;
	this->cell->setPiece(this);
}

bool Pawn::movePossible(Cell* cell)
{
// moving direction
	int moveDir;
// starting cell
	int stCell;
	if (_color == Black)
	{
		moveDir = 1;
		stCell = 1;
	}
	else
	{
		moveDir = -1;
		stCell = 6;
	}
	if (this->cell->x() == cell->x() && this->cell->y() == stCell && cell->y() == stCell + 2 * moveDir
			&& cellEmpty(cell->x(), stCell + moveDir) && cellEmpty(cell->x(), stCell + 2 * moveDir))
	{
		return true;
	}
	if (this->cell->x() == cell->x() && cell->y() == this->cell->y() + moveDir
			&& cellEmpty(cell->x(), this->cell->y() + moveDir))
	{
		return true;
	}
	if (cell->x() == this->cell->x() - 1 && cell->y() == this->cell->y() + moveDir
			&& !cellEmpty(this->cell->x() - 1, this->cell->y() + moveDir))
	{
		return true;
	}
	if (cell->x() == this->cell->x() + 1 && cell->y() == this->cell->y() + moveDir
			&& !cellEmpty(this->cell->x() + 1, this->cell->y() + moveDir))
	{
		return true;
	}
	
// check passant
	if (passPawn != NULL && this->cell->y() == stCell + 3 * moveDir)
	{
		if (cell->y() == stCell + 4 * moveDir && abs(this->cell->x() - cell->x()) == 1
				&& cell->x() == passCell)
		{
			return true;
		}
	}
	
	return false;
}

void Pawn::noPassant()
{
	passPawn = NULL;
}