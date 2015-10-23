#include "board.hpp"

Cell** Board::cell;

Board::Board()
{
	currentPlayer = White;
	pieceMoves = false;
	cell = new Cell*[8];
	for (int i = 0; i < 8; ++i)
		cell[i] = new Cell[8];
	for (int i = 0; i < 8; ++i)
	{
		pieces[White].push_back(new Pawn(&cell[i][6], White));
	}
	pieces[White].push_back(new Rook(&cell[0][7], White, &cell[3][7]));
	pieces[White].push_back(new Rook(&cell[7][7], White, &cell[5][7]));
	pieces[White].push_back(new Knight(&cell[1][7], White));
	pieces[White].push_back(new Knight(&cell[6][7], White));
	pieces[White].push_back(new Bishop(&cell[2][7], White));
	pieces[White].push_back(new Bishop(&cell[5][7], White));
	pieces[White].push_back(new Queen(&cell[3][7], White));
	pieces[White].push_back(new King(&cell[4][7], White, (Rook*)pieces[White][8], (Rook*)pieces[White][9]));

	for (int i = 0; i < 8; ++i)
	{
		pieces[Black].push_back(new Pawn(&cell[i][1], Black));
	}
	pieces[Black].push_back(new Rook(&cell[0][0], Black, &cell[3][0]));
	pieces[Black].push_back(new Rook(&cell[7][0], Black, &cell[5][0]));
	pieces[Black].push_back(new Knight(&cell[1][0], Black));
	pieces[Black].push_back(new Knight(&cell[6][0], Black));
	pieces[Black].push_back(new Bishop(&cell[2][0], Black));
	pieces[Black].push_back(new Bishop(&cell[5][0], Black));
	pieces[Black].push_back(new Queen(&cell[3][0], Black));
	pieces[Black].push_back(new King(&cell[4][0], Black, (Rook*)pieces[Black][8], (Rook*)pieces[Black][9]));

	Piece::cellEmpty = cellEmpty;

	selected = NULL;
}

Board::~Board()
{
	for (std::vector<Piece*>::iterator i = pieces[White].begin(); i != pieces[White].end(); ++i)
	{
		delete (*i);
	}
	for (std::vector<Piece*>::iterator i = pieces[Black].begin(); i != pieces[Black].end(); ++i)
	{
		delete (*i);
	}
}

void Board::render()
{
	if (glutGet(GLUT_WINDOW_HEIGHT) >= 300 && glutGet(GLUT_WINDOW_WIDTH) >= 300)
	{
		renderFrame();
		renderCells();
		if (panel.enabled())
		{
			panel.render();
		}
	}
}

void Board::reshape(int width, int height)
{
	if (height < 300)
	{
		glutReshapeWindow(300, 300);
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
	glMatrixMode(GL_MODELVIEW);
	frameCoords[0] = Position (0.05 * height, 0.05 * height);
	frameCoords[1] = Position (0.95 * height, 0.05 * height);
	frameCoords[2] = Position (0.95 * height, 0.95 * height);
	frameCoords[3] = Position (0.05 * height, 0.95 * height);
	frameCoords[4] = Position (0.1 * height, 0.1 * height);
	frameCoords[5] = Position (0.9 * height, 0.1 * height);
	frameCoords[6] = Position (0.9 * height, 0.9 * height);
	frameCoords[7] = Position (0.1 * height, 0.9 * height);
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
				found = true;
			}
		}
	}
	if (!found)
	{
		pointed = NULL;
	}
}

void Board::keypressed (unsigned char key)
{
	if (pointed == NULL)
	{
		pointed = lastPointed;
	}
	if (pointed == NULL)
	{
		pointed = &cell[0][0];
	}
	switch (key)
	{
	case 'w':
		if (pointed->y() > 0) pointed = &cell[pointed->x()][pointed->y() - 1];
		break;
	case 's':
		if (pointed->y() < 7) pointed = &cell[pointed->x()][pointed->y() + 1];
		break;
	case 'a':
		if (pointed->x() > 0) pointed = &cell[pointed->x() - 1][pointed->y()];
		break;
	case 'd':
		if (pointed->x() < 7) pointed = &cell[pointed->x() + 1][pointed->y()];
		break;
	case ' ':
		point (pointed);
		break;
	case 'p':
		if (panel.enabled()) panel.disable();
		else panel.enable();
		break;
	}
}
bool Board::move(Cell* from, Cell* to, bool write)
{
	if (from->piece()->type() != PPawn)
	{
		Pawn::noPassant();
	}
 	if (from->piece()->movePossible(to))
 	{
 		writeNotation(from, to);
 		if (!to->empty())
 		{
			to->piece()->take();
			to->setPiece(NULL);
 		}
 		from->piece()->move(to);
 		return true;
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
	// notation.push_back(new char[strlen(buffer)]);
	// strcpy(notation.back(), buffer);
}

void Board::renderFrame()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; ++i)
	{
		glColor3d(0, 0, 0);
		glVertex2dv(frameCoords[0 + i].v());
		glVertex2dv(frameCoords[(1 + i) % 4].v());
		glColor3d(0.3, 0.3, 0.3);
		glVertex2dv(frameCoords[4 + (1 + i) % 4].v());
		glVertex2dv(frameCoords[4 + i].v());
	}
	glEnd();
}

void Board::renderCells()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (&cell[i][j] != selected && &cell[i][j] != pointed)
			{
				cell[i][j].renderCell();
				if (!cell[i][j].empty())
				{
					cell[i][j].renderPiece();
				}
			}
		}
	}
	if (pointed != NULL) pointed->renderPointed();
	if (selected != NULL) selected->renderSelected();
}

bool Board::cellEmpty(int x, int y)
{
	return cell[x][y].empty();
}