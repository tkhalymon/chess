#ifndef __MOVE_HPP__
#define __MOVE_HPP__

class Piece;

#include "piece.hpp"

class Move
{
public:
	// add is rook for castling or pawn for passant
	Move(Piece* p, Cell* dest, Piece* other = NULL);
	~Move();

private:
	// piece whitch moves
	Piece* piece;
	// destination cell
	Cell* destination;
	// uses for pawn passant or castling
	Piece* otherPiece;
};

#endif