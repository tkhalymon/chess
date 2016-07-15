#ifndef __BOARD_HPP__
#define __BOARD_HPP__

// board cells
#include "cell.hpp"
// library to work with .png textures, uses lodepng library
#include "pngtex.hpp"
// decart coordinates system
#include "position.hpp"
// piece types
#include "pawn.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "rook.hpp"
// side panel, shows notations
#include "panel.hpp"
// uses for notations and moves operations (undo)
#include "move.hpp"

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
private:

	// replaces piece
	bool move(Cell* from, Cell* to);

	bool check(Cell* from, Cell* to);

	// write move notation
	void writeNotation(Cell* from, Cell* to);

	// utility render functions
	void renderFrame();
	void renderCells();

	// checks if cell is empty
	static bool cellEmpty(int x, int y);

	// board cells
	static Cell** cell;

	// players
	std::vector<Piece*> pieces[2];
	
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
	
	// current player color
	Color currentPlayer;
	
	// game notations
	std::vector<Move> notation;

	// coordinates to render frame
	Position frameCoords[8];
};

#endif