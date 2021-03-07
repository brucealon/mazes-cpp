
CC = g++
CFLAGS = -std=c++11 -g -Wall $(shell sdl2-config --libs)

.cpp.o:
	${CC} ${CFLAGS} -c -o $@ $<

maze_runner: maze_runner.cpp cell.o dijkstra.o maze.o binary_tree.o sidewinder.o aldous_broder.o traverse.o wilson.o
	${CC} ${CFLAGS} -o maze_runner maze_runner.cpp cell.o dijkstra.o maze.o binary_tree.o sidewinder.o aldous_broder.o traverse.o wilson.o

mazetest: mazetest.cpp cell.o maze.o binary_tree.o sidewinder.o aldous_broder.o traverse.o
	${CC} ${CFLAGS} -o mazetest mazetest.cpp cell.o maze.o binary_tree.o sidewinder.o aldous_broder.o traverse.o

clean:
	rm -f maze_runner
	rm -f *.o
	rm -f vgcore.*

run: maze_runner
	./maze_runner

test: maze_runner
	TEST=true ./maze_runner

valgrind: maze_runner
	valgrind --track-origins=yes --leak-check=full -s ./maze_runner
