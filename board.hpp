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
	void point (Cell* cell);
	void mouseMove(int x, int y);
	void keypressed (unsigned char key);
	bool move(Cell* from, Cell* to);
private:

	static bool cellEmpty(int x, int y);
	static Cell cell[8][8];

	bool figureMoves;
	std::vector<Figure>::iterator selectedFigure;
	Texture texture;
	std::vector<Figure*> whiteFigure;
	std::vector<Figure*> blackFigure;
	Cell* selected;
	Cell* lastPointed;
	Cell* pointed;
	int pointedX;
	int pointedY;
	Position boardPos;
	int cellSize;
	int winWidth;
	int winHeight ;
	Color currentPlayer;
};

#endif