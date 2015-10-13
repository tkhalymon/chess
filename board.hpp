#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "cell.hpp"
#include "pngtex.hpp"
#include "position.hpp"
#include "pawn.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "rook.hpp"

class Board
{
public:
	Board();
	~Board();

	void render();
	void advance();
	void click(int button, int state, int x, int y);
	bool move(Cell* from, Cell* to);
private:

	static bool cellEmpty(int x, int y);

	bool figureMoves;

	std::vector<Figure>::iterator selectedFigure;

	Texture texture;

	static Cell cell[8][8];
	std::vector<Figure*> whiteFigure;
	std::vector<Figure*> blackFigure;
	Cell* selected;
	Position boardPos;
	int cellSize;
	Color currentPlayer;
};

#endif