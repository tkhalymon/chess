#include "cell.hpp"

Cell::Cell()
{}

Cell::~Cell()
{

}

void Cell::setPos(Position pos, int x, int y)
{
	position = pos;
	_x = x;
	_y = y;
}

Position Cell::pos()
{
	return position;
}

Figure* Cell::figure()
{
	return fig;
}

void Cell::setFigure(Figure* figure)
{
	this->fig = figure;
}

int Cell::x()
{
	return _x;
}

int Cell::y()
{
	return _y;
}

bool Cell::empty()
{
	return fig == NULL;
}