#ifndef __BISHOP_HPP__
#define __BISHOP_HPP__

#include "piece.hpp"

class Bishop : public Piece
{
public:
	Bishop(Cell* pos, Color color);
	~Bishop();

	bool movePossible(Cell* cell);
};

#endif