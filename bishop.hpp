#ifndef __BISHOP_HPP__
#define __BISHOP_HPP__

#include "figure.hpp"

class Bishop : public Figure
{
public:
	Bishop(Cell* pos, Color color);
	~Bishop();

	bool movePossible(Cell* cell);
};

#endif