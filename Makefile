
CC = g++
CFLAGS = -std=c++11

.cpp.o:
	${CC} ${CFLAGS} -c -o $@ $<

maze: maze.cpp binary_tree.o
	${CC} ${CFLAGS} -o maze -l SDL2 maze.cpp binary_tree.o

clean:
	rm -f maze
	rm -f *.o
	rm -f vgcore.*

run: maze
	./maze

valgrind: maze
	valgrind --track-origins=yes --leak-check=full -s ./maze
