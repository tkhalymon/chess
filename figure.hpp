#ifndef __FIGURE_HPP__
#define __FIGURE_HPP__

class Figure;
enum Color {Black, White};

#include <vector>
#include "cell.hpp"
#include "pngtex.hpp"


class Figure
{
public:
	Figure(Cell* place, Color color);
	virtual ~Figure();

	Color color();
	std::vector<Cell> possibleMoves();
	void kill();
	bool dead();
	virtual void move(Cell* cell);
	virtual bool movePossible(Cell* cell);
	virtual void render();
	static void setCellSize(int size);
	static bool (*cellEmpty)(int x, int y);
protected:

	Texture tex;
	Cell* cell;
	Color _color;
	static int cellSize;
	bool _dead;
};

#endif