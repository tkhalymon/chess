#ifndef __QUEEN_HPP__
#define __QUEEN_HPP__

#include "piece.hpp"

class Queen : public Piece
{
public:
	Queen(Cell* pos, Color color);
	~Queen();

	bool movePossible(Cell* cell);
};

#endif