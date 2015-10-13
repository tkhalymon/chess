#include "board.hpp"

Cell Board::cell[8][8];

Board::Board()
{
	currentPlayer = White;
	figureMoves = false;
	cellSize = glutGet(GLUT_WINDOW_HEIGHT) / 10;
	Figure::setCellSize(cellSize);
	boardPos.y(cellSize);
	boardPos.x(glutGet(GLUT_WINDOW_WIDTH) / 2 - cellSize * 4);
	for (int i = 0; i < 8; ++i)
	{
		whiteFigure.push_back(new Pawn(&cell[i][6], White));
	}
	whiteFigure.push_back(new Rook(&cell[0][7], White));
	whiteFigure.push_back(new Rook(&cell[7][7], White));
	whiteFigure.push_back(new Knight(&cell[1][7], White));
	whiteFigure.push_back(new Knight(&cell[6][7], White));
	whiteFigure.push_back(new Bishop(&cell[2][7], White));
	whiteFigure.push_back(new Bishop(&cell[5][7], White));
	whiteFigure.push_back(new King(&cell[3][7], White));
	whiteFigure.push_back(new Queen(&cell[4][7], White));
	
	for (int i = 0; i < 8; ++i)
	{
		whiteFigure.push_back(new Pawn(&cell[i][1], Black));
	}
	whiteFigure.push_back(new Rook(&cell[0][0], Black));
	whiteFigure.push_back(new Rook(&cell[7][0], Black));
	whiteFigure.push_back(new Knight(&cell[1][0], Black));
	whiteFigure.push_back(new Knight(&cell[6][0], Black));
	whiteFigure.push_back(new Bishop(&cell[2][0], Black));
	whiteFigure.push_back(new Bishop(&cell[5][0], Black));
	whiteFigure.push_back(new King(&cell[3][0], Black));
	whiteFigure.push_back(new Queen(&cell[4][0], Black));
	
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cell[i][j].setPos(Position(boardPos.x() + cellSize * i, boardPos.y() + cellSize * j), i, j);
			glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
			glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
			glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
			glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));
		}
	}
	selected = NULL;
	Figure::cellEmpty = cellEmpty;
}

Board::~Board()
{
	for (std::vector<Figure*>::iterator i = whiteFigure.begin(); i != whiteFigure.end(); ++i)
	{
		delete (*i);
	}
	for (std::vector<Figure*>::iterator i = blackFigure.begin(); i != blackFigure.end(); ++i)
	{
		delete (*i);
	}
}

void Board::render()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if ((i + j) % 2 == 0) glColor3d(0.3, 0.3, 0.3);
			else glColor3d(0.7, 0.7, 0.7);
			glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
			glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
			glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
			glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));
			if (selected == &cell[i][j])
			{
				glColor3d(0, 1, 0);
				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.075));
				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.075));
				
				glVertex2d(boardPos.x() + cellSize * (i + 0.925), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
				glVertex2d(boardPos.x() + cellSize * (i + 0.925), boardPos.y() + cellSize * (j + 0.975));

				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.925));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.925));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));

				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.075), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.075), boardPos.y() + cellSize * (j + 0.975));
				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));
			}
		}
	}
	glEnd();
	for (std::vector<Figure*>::iterator i = whiteFigure.begin(); i < whiteFigure.end(); ++i)
	{
		if (!(*i)->dead()) (*i)->render();
	}
	for (std::vector<Figure*>::iterator i = blackFigure.begin(); i < blackFigure.end(); ++i)
	{
		if (!(*i)->dead()) (*i)->render();
	}
}

void Board::advance()
{

}

void Board::click(int button, int state, int x, int y)
{
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (x > cell[i][j].pos().x() + cellSize * 0.025 && y > cell[i][j].pos().y() + cellSize * 0.025
				&& x < cell[i][j].pos().x() + cellSize * 0.975 && y < cell[i][j].pos().y() + cellSize * 0.975)
			{
				if (selected == NULL)
				{
					if (!cell[i][j].empty() && cell[i][j].figure()->color() == currentPlayer)
					{
						selected = &cell[i][j];
					}
				}
				else
				{
					if (!cell[i][j].empty() && cell[i][j].figure()->color() == selected->figure()->color())
					{
						selected = &cell[i][j];
					}
					else
					{
						if (move(selected, &cell[i][j]))
						{
							if (currentPlayer == Black)
								currentPlayer = White;
							else currentPlayer = Black;
						}
						selected = NULL;
					}
				}
			}
		}
	}
}

bool Board::move(Cell* from, Cell* to)
{
	if (from->figure()->movePossible(to))
 	{
 		if (!to->empty())
 		{
			if (from->figure()->color() == White)
			{
				to->figure()->kill();
				to->setFigure(NULL);
			}
			else
			{
				to->figure()->kill();
				to->setFigure(NULL);
			}
 		}
 		from->figure()->move(to);
 		return true;
 	}
 	return false;
}

bool Board::cellEmpty(int x, int y)
{
	return cell[x][y].empty();
}