#ifndef __KING_HPP__
#define __KING_HPP__

#include "figure.hpp"

class King : public Figure
{
public:
	King(Cell* pos, Color color);
	~King();
	void move(Cell*);
	bool movePossible(Cell* cell);
private:
	bool firstMove;
};

#endif