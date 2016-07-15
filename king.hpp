#ifndef __KING_HPP__
#define __KING_HPP__

#include "piece.hpp"
#include "rook.hpp"

class King : public Piece
{
public:
	King(Cell* pos, Color color, Rook* left, Rook* right);
	~King();
	void move(Cell* cell);
	bool movePossible(Cell* cell);
	void check(bool underCheck);
	bool underCheck();
private:
	// check if castling is possible
	bool checkCastling(Cell* cell);

	// references to rooks  (for castling)
	Rook* leftRook;
	Rook* rightRook;

	bool checked;
};

#endif