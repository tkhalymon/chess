#ifndef __CELL_HPP__
#define __CELL_HPP__

class Cell;

#include <vector>
#include "figure.hpp"
#include "position.hpp"

class Cell
{
public:
	Cell();
	~Cell();

	void setPos(Position pos, int x, int y);

	Position pos();

	Figure* figure();

	void setFigure(Figure*);

	int x();

	int y();

	bool empty();

private:

	Position position;

	bool busy;
	
	Figure* fig;

	int _x;

	int _y;
};

#endif