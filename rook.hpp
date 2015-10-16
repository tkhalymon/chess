#ifndef __ROOK_HPP__
#define __ROOK_HPP__

#include "piece.hpp"

class Rook : public Piece
{
public:
	Rook(Cell* pos, Color color);
	~Rook();

	void move(Cell* cell);
	bool movePossible(Cell* cell);

private:
	bool firstMove;
};

#endif