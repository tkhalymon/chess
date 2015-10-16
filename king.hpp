#ifndef __KING_HPP__
#define __KING_HPP__

#include "piece.hpp"
#include "rook.hpp"

class King : public Piece
{
public:
	King(Cell* pos, Color color);
	~King();
	bool movePossible(Cell* cell);
};

#endif