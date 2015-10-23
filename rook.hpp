#ifndef __ROOK_HPP__
#define __ROOK_HPP__

#include "piece.hpp"

class Rook : public Piece
{
public:
	Rook(Cell* pos, Color color, Cell* castlePos);
	~Rook();

	bool movePossible(Cell* cell);

	void move(Cell* cell);

	// if castling possible
	bool castl();

	// sets castling impossible
	void noCastl();

	// make castling (move to it's position)
	void castling();

protected:
	// is castling possible
	bool castlPossible;

	// position for castling
	Cell* castlePos;
};

#endif