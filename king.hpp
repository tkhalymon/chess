#ifndef __KING_HPP__
#define __KING_HPP__

#include "piece.hpp"

class King : public Piece
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