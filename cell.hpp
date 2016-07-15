#ifndef __CELL_HPP__
#define __CELL_HPP__

class Cell;

#include <vector>
#include "piece.hpp"
#include "position.hpp"

class Cell
{
public:
	Cell();
	~Cell();

	// initialize cell coordinates and color
	void setPos(int x, int y, Color c);

	// returns pointer to piece on this cell, or NULL if it's empty
	Piece* piece();

	// sets cells piece
	void setPiece(Piece*);

	// check if point (x; y) lying inside this cell (used for mouse click)
	bool inside(int x, int y);

	// x coordinate of cell
	int x();

	// y coordinate of cell
	int y();

	// returns true if cell is empty
	bool empty();

	// drawing functions
	void renderCheck();
	void renderCell();
	void renderPiece(bool check = false);
	void renderPointed(bool check = false);
	void renderSelected(bool check = false);
private:

	// all vertices (used for render)
	Position coords[8];

	// cell color
	Color color;

	// pointer to piece in this cell
	Piece* _piece;

	// coordinates
	int _x;
	int _y;
};

#endif