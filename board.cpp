#include "board.hpp"

Cell Board::cell[8][8];

Board::Board()
{
	sidePanel.init(&notation);
	currentPlayer = White;
	figureMoves = false;
	cellSize = glutGet(GLUT_WINDOW_HEIGHT) / 10;
	Figure::setCellSize(cellSize);
	boardPos.y(cellSize);
	boardPos.x(cellSize);
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
	glColor3d(0, 0, 0);
	glVertex2d(boardPos.x() + cellSize * (-0.5), boardPos.y() + cellSize * (-0.5));
	glVertex2d(boardPos.x() + cellSize * (8.5), boardPos.y() + cellSize * (-0.5));
	glColor3d(0.7, 0.7, 0.7);
	glVertex2d(boardPos.x() + cellSize * (8.025), boardPos.y() + cellSize * (-0.025));
	glVertex2d(boardPos.x() + cellSize * (-0.025), boardPos.y() + cellSize * (-0.025));
	
	glColor3d(0, 0, 0);
	glVertex2d(boardPos.x() + cellSize * (8.5), boardPos.y() + cellSize * (-0.5));
	glVertex2d(boardPos.x() + cellSize * (8.5), boardPos.y() + cellSize * (8.5));
	glColor3d(0.7, 0.7, 0.7);
	glVertex2d(boardPos.x() + cellSize * (8.025), boardPos.y() + cellSize * (8.025));
	glVertex2d(boardPos.x() + cellSize * (8.025), boardPos.y() + cellSize * (-0.025));

	glColor3d(0, 0, 0);
	glVertex2d(boardPos.x() + cellSize * (-0.5), boardPos.y() + cellSize * (8.5));
	glVertex2d(boardPos.x() + cellSize * (8.5), boardPos.y() + cellSize * (8.5));
	glColor3d(0.7, 0.7, 0.7);
	glVertex2d(boardPos.x() + cellSize * (8.025), boardPos.y() + cellSize * (8.025));
	glVertex2d(boardPos.x() + cellSize * (-0.025), boardPos.y() + cellSize * (8.025));

	glColor3d(0, 0, 0);
	glVertex2d(boardPos.x() + cellSize * (-0.5), boardPos.y() + cellSize * (8.5));
	glVertex2d(boardPos.x() + cellSize * (-0.5), boardPos.y() + cellSize * (-0.5));
	glColor3d(0.7, 0.7, 0.7);
	glVertex2d(boardPos.x() + cellSize * (-0.025), boardPos.y() + cellSize * (-0.025));
	glVertex2d(boardPos.x() + cellSize * (-0.025), boardPos.y() + cellSize * (8.025));
	glEnd();
	glEnable(GL_BLEND);
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
			if (selected == &cell[i][j] || pointed == &cell[i][j])
			{
				if (selected == &cell[i][j])
					glColor3d(0, 1, 0);
				else
					glColor4d(0, 1, 0, 0.5);

				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.900), boardPos.y() + cellSize * (j + 0.100));
				glVertex2d(boardPos.x() + cellSize * (i + 0.100), boardPos.y() + cellSize * (j + 0.100));
				
				glVertex2d(boardPos.x() + cellSize * (i + 0.900), boardPos.y() + cellSize * (j + 0.100));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
				glVertex2d(boardPos.x() + cellSize * (i + 0.900), boardPos.y() + cellSize * (j + 0.900));

				glVertex2d(boardPos.x() + cellSize * (i + 0.100), boardPos.y() + cellSize * (j + 0.900));
				glVertex2d(boardPos.x() + cellSize * (i + 0.900), boardPos.y() + cellSize * (j + 0.900));
				glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));

				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
				glVertex2d(boardPos.x() + cellSize * (i + 0.100), boardPos.y() + cellSize * (j + 0.100));
				glVertex2d(boardPos.x() + cellSize * (i + 0.100), boardPos.y() + cellSize * (j + 0.900));
				glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));
			}
		}
	}
	glEnd();
	glDisable(GL_BLEND);
	for (std::vector<Figure*>::iterator i = whiteFigure.begin(); i < whiteFigure.end(); ++i)
	{
		if (!(*i)->dead()) (*i)->render();
	}
	for (std::vector<Figure*>::iterator i = blackFigure.begin(); i < blackFigure.end(); ++i)
	{
		if (!(*i)->dead()) (*i)->render();
	}
	sidePanel.render();
}

void Board::advance()
{

}

void Board::click(int button, int state, int x, int y)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (x > cell[i][j].pos().x() + cellSize * 0.025 && y > cell[i][j].pos().y() + cellSize * 0.025
				&& x < cell[i][j].pos().x() + cellSize * 0.975 && y < cell[i][j].pos().y() + cellSize * 0.975)
			{
				point(&cell[i][j]);
			}
		}
	}
}

void Board::point(Cell* cell)
{
	if (selected == NULL)
	{
		if (!cell->empty() && cell->figure()->color() == currentPlayer)
		{
			selected = cell;
		}
	}
	else
	{
		if (!cell->empty() && cell->figure()->color() == selected->figure()->color())
		{
			selected = cell;
		}
		else
		{
			if (move(selected, cell))
			{
				if (currentPlayer == Black)
					currentPlayer = White;
				else currentPlayer = Black;
			}
			selected = NULL;
		}
	}
}

void Board::mouseMove(int x, int y)
{
	bool found = false;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (x > cell[i][j].pos().x() + cellSize * 0.025 && y > cell[i][j].pos().y() + cellSize * 0.025
				&& x < cell[i][j].pos().x() + cellSize * 0.975 && y < cell[i][j].pos().y() + cellSize * 0.975)
			{
				pointed = &cell[i][j];
				lastPointed = pointed;
				pointedX = i;
				pointedY = j;
				found = true;
			}
		}
	}
	if (!found)
	{
		lastPointed = pointed;
		pointed = NULL;
	}
}

void Board::keypressed (unsigned char key)
{
	switch (key)
	{
	case 'w':
		if (pointedY > 0) pointedY--;
		break;
	case 's':
		if (pointedX < 7) pointedY++;
		break;
	case 'a':
		if (pointedX > 0) pointedX--;
		break;
	case 'd':
		if (pointedX < 7) pointedX++;
		break;
	case ' ':
		point (pointed);
		break;
	}
	pointed = &cell[pointedX][pointedY];
}

void Board::writeNotation(Cell* from, Cell* to)
{
	char buffer[20];
	char ftype;
	switch (from->figure()->fType())
	{
	case FPawn: ftype = 'P'; break;
	case FKing: ftype = 'K'; break;
	case FQueen: ftype = 'Q'; break;
	case FBishop: ftype = 'B'; break;
	case FKnight: ftype = 'N'; break;
	case FRook: ftype = 'R'; break;
	}
	if (ftype == 'P')
		sprintf(buffer, "%c%d-%c%d\n", 'a' + from->x(), 8 - from->y(), 'a' + to->x(), 8 - to->y());
	else
		sprintf(buffer, "%c%c%d-%c%d\n", ftype, 'a' + from->x(), 8 - from->y(), 'a' + to->x(), 8 - to->y());
 	notation.push_back(new char[20]);
 	strcpy(notation.back(), buffer);
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
 		writeNotation(from, to);
 		from->figure()->move(to);
 		return true;
 	}
 	return false;
}

bool Board::cellEmpty(int x, int y)
{
	return cell[x][y].empty();
}