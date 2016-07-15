#ifndef __PAWN_HPP__
#define __PAWN_HPP__

class Piece;

#include "piece.hpp"

class Pawn : public Piece
{
public:
	Pawn(Cell* pos, Color color);
	~Pawn();

	void move(Cell* cell);
	
	bool movePossible(Cell* cell);

	// sets passant impossible
	static void noPassant();

private:
	// x coordinate of pawn possible to passant
	static int passCell;

	// figure to take by passant
	static Pawn* passPawn;
};

#endif