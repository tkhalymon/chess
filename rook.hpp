#ifndef __ROOK_HPP__
#define __ROOK_HPP__

#include "piece.hpp"

class Rook : public Piece
{
public:
	Rook(Cell* pos, Color color);
	~Rook();

	bool movePossible(Cell* cell);
};

#endif