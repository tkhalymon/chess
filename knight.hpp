#ifndef __KNIGHT_HPP__
#define __KNIGHT_HPP__

#include "figure.hpp"

class Knight : public Figure
{
public:
	Knight(Cell* pos, Color color);
	~Knight();

	bool movePossible(Cell* cell);
};

#endif