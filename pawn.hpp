#ifndef __PAWN_HPP__
#define __PAWN_HPP__

class Figure;

#include "figure.hpp"

class Pawn : public Figure
{
public:
	Pawn(Cell* pos, Color color);
	~Pawn();

	bool movePossible(Cell* cell);
private:

	bool firstMove;
};

#endif