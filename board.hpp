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

struct Player
{
	std::vector<Piece*> piece;
};

class Board
{
public:
	Board();
	~Board();

	// draws board, pieces and notation panel
	void render();

	// processes changing of window size (for render)
	void reshape(int width, int height);

	// simulates time for render
	void advance();

	// selects field if no piece selected, or moves selected piece
	void point (Cell* cell);

	// captures mouse click
	void click(int button, int state, int x, int y);

	// captures mouse moving
	void mouseMove(int x, int y);

	// captures keyboard actions
	void keypressed (unsigned char key);

	// replaces piece
	bool move(Cell* from, Cell* to);
private:

	// write move notation
	void writeNotation(Cell* from, Cell* to);
	void renderFrame();
	void renderCells();

	// checks if cell is empty
	static bool cellEmpty(int x, int y);

	// board cells
	static Cell cell[8][8];

	// players
	Player white;
	Player black;

	// side panel with notations
	Panel panel;
	
	// flag of moving figure in progress (for render)
	bool pieceMoves;

	// selected cell
	Cell* selected;

	// previous pointed cell
	Cell* lastPointed;

	// pointed cell
	Cell* pointed;
	
	// coordinates of pointed (not selected) cell on board
	int pointedX;
	int pointedY;

	// current player color
	Color currentPlayer;
	
	// game notations
	std::vector<char* > notation;

	// coordinates to render frame
	Position frameCoords[8];
};

#endif