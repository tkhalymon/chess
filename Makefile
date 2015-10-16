all: chess
chess: main.o board.o panel.o cell.o piece.o pngtex.o lodepng.o position.o pawn.o king.o queen.o bishop.o knight.o rook.o
	g++ -std=c++11 main.o board.o panel.o cell.o piece.o pngtex.o lodepng.o position.o pawn.o king.o queen.o bishop.o knight.o rook.o -lGL -lglut -o chess

main.o: main.cpp
	g++ -std=c++11 -c main.cpp
board.o: board.cpp board.hpp
	g++ -std=c++11 -c board.cpp
panel.o: panel.cpp panel.hpp
	g++ -std=c++11 -c panel.cpp
cell.o: cell.cpp cell.hpp
	g++ -std=c++11 -c cell.cpp
piece.o: piece.cpp piece.hpp
	g++ -std=c++11 -c piece.cpp
pngtex.o: pngtex.cpp pngtex.hpp
	g++ -std=c++11 -c pngtex.cpp
lodepng.o: lodepng.cpp lodepng.h
	g++ -std=c++11 -c lodepng.cpp
position.o: position.cpp position.hpp
	g++ -std=c++11 -c position.cpp
pawn.o: pawn.cpp pawn.hpp
	g++ -std=c++11 -c pawn.cpp
king.o: king.cpp king.hpp
	g++ -std=c++11 -c king.cpp
queen.o: queen.cpp queen.hpp
	g++ -std=c++11 -c queen.cpp
bishop.o: bishop.cpp bishop.hpp
	g++ -std=c++11 -c bishop.cpp
knight.o: knight.cpp knight.hpp
	g++ -std=c++11 -c knight.cpp
rook.o: rook.cpp rook.hpp
	g++ -std=c++11 -c rook.cpp

run: chess
	./chess

clean:
	rm *.o chess