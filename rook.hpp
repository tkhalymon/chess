#ifndef __ROOK_HPP__
#define __ROOK_HPP__

#include "figure.hpp"

class Rook : public Figure
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