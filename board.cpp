#include "board.hpp"

Cell Board::cell[8][8];

Board::Board()
{
	panel.init(&notation);
	currentPlayer = White;
	pieceMoves = false;
	for (int i = 0; i < 8; ++i)
	{
		white.piece.push_back(new Pawn(&cell[i][6], White));
	}
	white.piece.push_back(new Rook(&cell[0][7], White));
	white.piece.push_back(new Rook(&cell[7][7], White));
	white.piece.push_back(new Knight(&cell[1][7], White));
	white.piece.push_back(new Knight(&cell[6][7], White));
	white.piece.push_back(new Bishop(&cell[2][7], White));
	white.piece.push_back(new Bishop(&cell[5][7], White));
	white.piece.push_back(new Queen(&cell[3][7], White));
	white.piece.push_back(new King(&cell[4][7], White));
	
	for (int i = 0; i < 8; ++i)
	{
		black.piece.push_back(new Pawn(&cell[i][1], Black));
	}
	black.piece.push_back(new Rook(&cell[0][0], Black));
	black.piece.push_back(new Rook(&cell[7][0], Black));
	black.piece.push_back(new Knight(&cell[1][0], Black));
	black.piece.push_back(new Knight(&cell[6][0], Black));
	black.piece.push_back(new Bishop(&cell[2][0], Black));
	black.piece.push_back(new Bishop(&cell[5][0], Black));
	black.piece.push_back(new Queen(&cell[3][0], Black));
	black.piece.push_back(new King(&cell[4][0], Black));

	Piece::cellEmpty = cellEmpty;
	selected = NULL;
}

Board::~Board()
{
	for (std::vector<Piece*>::iterator i = white.piece.begin(); i != white.piece.end(); ++i)
	{
		delete (*i);
	}
	for (std::vector<Piece*>::iterator i = black.piece.begin(); i != black.piece.end(); ++i)
	{
		delete (*i);
	}
}

void Board::render()
{
	renderFrame();
	renderCells();
	if (panel.enabled())
	{
		panel.render();
	}
}

void Board::reshape(int width, int height)
{
	if (height < 500)
	{
		glutReshapeWindow(500, 500);
	}
	if (panel.enabled())
	{
		if (width < height * 1.1 + panel.width())
		{
			glutReshapeWindow(height * 1.1 + panel.width(), height);
		}
	}
	else
	{
		if (width < height)
		{
			glutReshapeWindow(height, height);
		}
	}
	glViewport(0, 0, width, height);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -2, 2);
	
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
	panel.reshape();
}

void Board::advance()
{

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

bool Board::move(Cell* from, Cell* to, bool write)
{
	if (from->piece()->movePossible(to))
 	{
 		writeNotation(from, to);
 		if (!to->empty())
 		{
			to->piece()->kill();
			to->setPiece(NULL);
 		}
 		from->piece()->move(to);
 		return true;
 	}
	if (checkCastling(from, to))
	{
		if (currentPlayer == White)
		{
			white.lCastling = false;
			white.rCastling = false;
		}
		return true;
	}
	return false;
}

bool Board::checkCastling(Cell* from, Cell* to)
{
	if (white.lCastling && from == &cell[0][7]) white.lCastling = false;
	if (white.rCastling && from == &cell[7][7]) white.lCastling = false;
	if (black.lCastling && from == &cell[0][0]) white.lCastling = false;
	if (black.rCastling && from == &cell[7][0]) white.lCastling = false;
	if (selected->piece()->type() == PKing)
	{
		if (currentPlayer == White)
		{
			if (from->y() == to->y() && from->x() + 2 == to->x() && white.rCastling
				&& cell[5][7].empty() && cell[6][7].empty())
			{
 				writeNotation(from, to);
				from->piece()->move(to);
				cell[7][7].piece()->move(&cell[5][7]);
				return true;
			}
			if (from->y() == to->y() && from->x() - 2 == to->x() && white.lCastling
				&& cell[1][7].empty() && cell[2][7].empty() && cell[3][7].empty())
			{
 				writeNotation(from, to);
				from->piece()->move(to);
				cell[0][7].piece()->move(&cell[3][7]);
				return true;
			}
		}
		else
		{
			if (from->y() == to->y() && from->x() + 2 == to->x() && black.rCastling
				&& cell[5][0].empty() && cell[6][0].empty())
			{
 				writeNotation(from, to);
				from->piece()->move(to);
				cell[7][0].piece()->move(&cell[5][0]);
				return true;
			}
			if (from->y() == to->y() && from->x() - 2 == to->x() && black.lCastling
				&& cell[1][0].empty() && cell[2][0].empty() && cell[3][0].empty())
			{
 				writeNotation(from, to);
				from->piece()->move(to);
				cell[0][0].piece()->move(&cell[3][0]);
				return true;
			}
		}
	}
	if ((white.lCastling || white.rCastling) && from->x() == 4 && from->y() == 7)
	{
		white.lCastling = false;
		white.rCastling = false;
	}
	if ((black.lCastling || black.rCastling) && from->x() == 4 && from->y() == 0)
	{
		black.lCastling = false;
		black.rCastling = false;
	}
	return false;
}

void Board::writeNotation(Cell* from, Cell* to)
{
	char buffer[20];
	char ftype[2] = " ";
	if (from->piece()->type() == PKing && abs(from->x() - to->x()) > 1)
	{
		if (from->x() < to->x()) strcpy(buffer, "0-0");
		else strcpy(buffer, "0-0-0");
	}
	else
	{
		switch (from->piece()->type())
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
	}
 	notation.push_back(new char[strlen(buffer)]);
 	strcpy(notation.back(), buffer);
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
}

bool Board::cellEmpty(int x, int y)
{
	return cell[x][y].empty();
}