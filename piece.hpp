#ifndef __PIECE_HPP__
#define __PIECE_HPP__

class Piece;
enum Color {Black = 0, White = 1};

#include <vector>
#include "cell.hpp"
#include "pngtex.hpp"

enum PieceType { PPawn, PKing, PQueen, PBishop, PKnight, PRook };

class Piece
{
public:
	Piece(Cell* place, Color color);
	virtual ~Piece();

	Color color();
	std::vector<Cell> possibleMoves();
	void kill();
	bool dead();
	PieceType type();
	virtual void move(Cell* cell);
	virtual bool movePossible(Cell* cell);
	void bindTex();
	static void setCellSize(int size);
	static bool (*cellEmpty)(int x, int y);
protected:

	static int cellSize;
	Texture tex;
	Cell* cell;
	Color _color;
	bool _dead;
	PieceType pType;
};

#endif