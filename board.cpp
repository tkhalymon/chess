#include "board.hpp"

Cell Board::cell[8][8];

Board::Board()
{
	sidePanel.init(&notation);
	currentPlayer = White;
	pieceMoves = false;
	for (int i = 0; i < 8; ++i)
	{
		whitePiece.push_back(new Pawn(&cell[i][6], White));
	}
	whitePiece.push_back(new Rook(&cell[0][7], White));
	whitePiece.push_back(new Rook(&cell[7][7], White));
	whitePiece.push_back(new Knight(&cell[1][7], White));
	whitePiece.push_back(new Knight(&cell[6][7], White));
	whitePiece.push_back(new Bishop(&cell[2][7], White));
	whitePiece.push_back(new Bishop(&cell[5][7], White));
	whitePiece.push_back(new Queen(&cell[3][7], White));
	whitePiece.push_back(new King(&cell[4][7], White));
	
	for (int i = 0; i < 8; ++i)
	{
		blackPiece.push_back(new Pawn(&cell[i][1], Black));
	}
	blackPiece.push_back(new Rook(&cell[0][0], Black));
	blackPiece.push_back(new Rook(&cell[7][0], Black));
	blackPiece.push_back(new Knight(&cell[1][0], Black));
	blackPiece.push_back(new Knight(&cell[6][0], Black));
	blackPiece.push_back(new Bishop(&cell[2][0], Black));
	blackPiece.push_back(new Bishop(&cell[5][0], Black));
	blackPiece.push_back(new Queen(&cell[3][0], Black));
	blackPiece.push_back(new King(&cell[4][0], Black));

	Piece::cellEmpty = cellEmpty;
	selected = NULL;
}

Board::~Board()
{
	for (std::vector<Piece*>::iterator i = whitePiece.begin(); i != whitePiece.end(); ++i)
	{
		delete (*i);
	}
	for (std::vector<Piece*>::iterator i = blackPiece.begin(); i != blackPiece.end(); ++i)
	{
		delete (*i);
	}
}

void Board::render()
{
	renderFrame();
	renderCells();
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
			if (cell[i][j].inside(x, y))
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
		if (!cell->empty() && cell->piece()->color() == currentPlayer)
		{
			selected = cell;
		}
	}
	else
	{
		if (!cell->empty() && cell->piece()->color() == selected->piece()->color())
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
			if (cell[i][j].inside(x, y))
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
	char ftype[2] = "P";
	switch (from->piece()->fType())
	{
	case PPawn: ftype[0] = '\0'; break;
	case PKing: ftype[0] = 'K'; break;
	case PQueen: ftype[0] = 'Q'; break;
	case PBishop: ftype[0] = 'B'; break;
	case PKnight: ftype[0] = 'N'; break;
	case PRook: ftype[0] = 'R'; break;
	}
	char action;
	if (!to->empty()) action = 'x';
	else action = '-';
	sprintf(buffer, "%s%c%d%c%c%d\n", ftype, 'a' + from->x(), 8 - from->y(), action, 'a' + to->x(), 8 - to->y());
 	notation.push_back(new char[20]);
 	strcpy(notation.back(), buffer);
}

bool Board::move(Cell* from, Cell* to)
{
	if (from->piece()->movePossible(to))
 	{
 		writeNotation(from, to);
 		if (!to->empty())
 		{
			to->piece()->kill();
			to->setFigure(NULL);
 		}
 		from->piece()->move(to);
 		return true;
 	}
 	return false;
}

bool Board::cellEmpty(int x, int y)
{
	return cell[x][y].empty();
}

void Board::reshape(int width, int height)
{
	frameCoords[0] = Position (0.05 * height, 0.05 * height);
	frameCoords[1] = Position (0.95 * height, 0.05 * height);
	frameCoords[2] = Position (0.95 * height, 0.95 * height);
	frameCoords[3] = Position (0.05 * height, 0.95 * height);
	frameCoords[4] = Position (0.09875 * height, 0.09875 * height);
	frameCoords[5] = Position (0.90125 * height, 0.09875 * height);
	frameCoords[6] = Position (0.90125 * height, 0.90125 * height);
	frameCoords[7] = Position (0.09875 * height, 0.90125 * height);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cell[i][j].setPos(i, j, (i + j) % 2 ? Black : White);
		}
	}
	sidePanel.reshape();
}

void Board::renderFrame()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; ++i)
	{
		glColor3d(0, 0, 0);
		glVertex2dv(frameCoords[0 + i].v());
		glVertex2dv(frameCoords[(1 + i) % 4].v());
		glColor3d(0.7, 0.7, 0.7);
		glVertex2dv(frameCoords[4 + (1 + i) % 4].v());
		glVertex2dv(frameCoords[4 + i].v());
	}
	glEnd();
}

void Board::renderCells()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cell[i][j].render();
		}
	}
	if (pointed != NULL) pointed->renderPointed();
	if (selected != NULL) selected->renderSelected();
	glEnd();
	// glEnable(GL_BLEND);
	// glBegin(GL_QUADS);
	// for (int i = 0; i < 8; ++i)
	// {
	// 	for (int j = 0; j < 8; ++j)
	// 	{
	// 		if ((i + j) % 2 == 0) glColor3d(0.3, 0.3, 0.3);
	// 		else glColor3d(0.7, 0.7, 0.7);
	// 		glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
	// 		glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
	// 		glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
	// 		glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));
	// 		if (selected == &cell[i][j] || pointed == &cell[i][j])
	// 		{
	// 			if (selected == &cell[i][j])
	// 				glColor3d(0, 1, 0);
	// 			else
	// 				glColor4d(0, 1, 0, 0.5);

	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.900), boardPos.y() + cellSize * (j + 0.100));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.100), boardPos.y() + cellSize * (j + 0.100));
				
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.900), boardPos.y() + cellSize * (j + 0.100));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.025));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.900), boardPos.y() + cellSize * (j + 0.900));

	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.100), boardPos.y() + cellSize * (j + 0.900));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.900), boardPos.y() + cellSize * (j + 0.900));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.975), boardPos.y() + cellSize * (j + 0.975));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));

	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.025));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.100), boardPos.y() + cellSize * (j + 0.100));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.100), boardPos.y() + cellSize * (j + 0.900));
	// 			glVertex2d(boardPos.x() + cellSize * (i + 0.025), boardPos.y() + cellSize * (j + 0.975));
	// 		}
	// 	}
	// }
	// glEnd();
	// glDisable(GL_BLEND);
}