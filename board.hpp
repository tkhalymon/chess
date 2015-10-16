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
#include "panel.hpp"

class Board
{
public:
	Board();
	~Board();

	void reshape(int width, int height);

	void render();
	void advance();
	void click(int button, int state, int x, int y);
	void point (Cell* cell);
	void mouseMove(int x, int y);
	void keypressed (unsigned char key);
	void writeNotation(Cell* from, Cell* to);
	bool move(Cell* from, Cell* to);
private:

	void renderFrame();
	void renderCells();

	static bool cellEmpty(int x, int y);
	static Cell cell[8][8];

	Panel sidePanel;
	bool pieceMoves;
	std::vector<Piece>::iterator selectedPiece;
	Texture texture;
	std::vector<Piece*> whitePiece;
	std::vector<Piece*> blackPiece;
	Cell* selected;
	Cell* lastPointed;
	Cell* pointed;
	int pointedX;
	int pointedY;
	Position boardPos;
	int cellSize;
	Color currentPlayer;
	std::vector<char* > notation;

	// coordinates to render frame
	Position frameCoords[8];
};

#endif