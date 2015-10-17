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

	void setPos(int x, int y, Color c);
	Piece* piece();
	void setPiece(Piece*);
	bool inside(int x, int y);
	Position* pos();
	int x();
	int y();
	bool empty();
	void render();
	void renderPointed();
	void renderSelected();
private:

	Position coords[8];
	Color color;
	Piece* _piece;
	int _x;
	int _y;
};

#endif