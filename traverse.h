
#pragma once

#include <map>

#include "maze.h"

class Traversal {
private:
    Maze *mMaze;
    std::map<Cell*,bool> visited;

    void traverse_r(Cell *cell);

public:
    Traversal(Maze *maze);

    void reset();
    void traverse(int row = 0, int column = 0);
    Maze *maze();
    bool is_visited(Cell *cell);
    bool is_valid();
};

std::ostream& operator<<(std::ostream& os, Traversal& traversal);
