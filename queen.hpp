#ifndef __QUEEN_HPP__
#define __QUEEN_HPP__

#include "figure.hpp"

class Queen : public Figure
{
public:
	Queen(Cell* pos, Color color);
	~Queen();

	bool movePossible(Cell* cell);
};

#endif