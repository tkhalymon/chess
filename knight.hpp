#ifndef __KNIGHT_HPP__
#define __KNIGHT_HPP__

#include "piece.hpp"

class Knight : public Piece
{
public:
	Knight(Cell* pos, Color color);
	~Knight();

	bool movePossible(Cell* cell);
};

#endif