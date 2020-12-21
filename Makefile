
CC = g++
CFLAGS = -std=c++11 -g -Wall

.cpp.o:
	${CC} ${CFLAGS} -c -o $@ $<

maze: maze.cpp binary_tree.o sidewinder.o
	${CC} ${CFLAGS} -o maze -l SDL2 maze.cpp binary_tree.o sidewinder.o

clean:
	rm -f maze
	rm -f *.o
	rm -f vgcore.*

run: maze
	./maze

valgrind: maze
	valgrind --track-origins=yes --leak-check=full -s ./maze
