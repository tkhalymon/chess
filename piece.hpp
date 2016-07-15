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

	// piece color
	Color color();

	// returns vector of cells, which are possible to move from current position (not realized yet)
	std::vector<Cell> possibleMoves();

	// removes piece from board
	void take();

	// true, if piece still on board
	bool alive();

	// piece type
	PieceType type();

	// move to other cell
	virtual void move(Cell* cell);

	// check if move to cell is possible
	virtual bool movePossible(Cell* cell);

	// binds piece texture to buffer (for render)
	void bindTex();

	// check if cell is empty (static to make usable from pieces realizations)
	static bool (*cellEmpty)(int x, int y);
protected:

	// texture object
	Texture tex;

	// cell, where piece is placed
	Cell* cell;

	// piece color
	Color _color;

	// is piece still on board
	bool pieceAlive;

	// piece type
	PieceType pType;
};

#endif