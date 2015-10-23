#include "king.hpp"

King::King(Cell* pos, Color color, Rook* left, Rook* right) : Piece(pos, color), leftRook(left), rightRook(right)
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

void King::move(Cell* cell)
{
	if (cell->x() == this->cell->x() + 2)
	{
		rightRook->castling();
	}
	if (cell->x() == this->cell->x() - 2)
	{
		leftRook->castling();
	}
	leftRook->noCastl();
	rightRook->noCastl();
	this->cell->setPiece(NULL);
	this->cell = cell;
	this->cell->setPiece(this);
}

bool King::movePossible(Cell* cell)
{
	// check regular moves
	if (abs(this->cell->x() - cell->x()) <= 1 && abs(this->cell->y() - cell->y()) <= 1)
		return true;
	// check castling
	return checkCastling(cell);
}

bool King::checkCastling(Cell* cell)
{
	// check if any castling is possible (it's kings first move)
	if (leftRook->castl() || rightRook->castl())
	{
		// short right castling
		if (cell->x() == this->cell->x() + 2 && rightRook->castl() && rightRook->movePossible(this->cell))
		{
			return true;
		}
		// long left castling
		if (cell->x() == this->cell->x() - 2 && leftRook->castl() && leftRook->movePossible(this->cell))
		{
			return true;
		}
	}
	return false;
}