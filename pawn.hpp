#ifndef __PAWN_HPP__
#define __PAWN_HPP__

class Piece;

#include "piece.hpp"

class Pawn : public Piece
{
public:
	Pawn(Cell* pos, Color color);
	~Pawn();

	bool movePossible(Cell* cell);
private:

	bool firstMove;
};

#endif