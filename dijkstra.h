
#pragma once

#include <map>

#include "maze.h"

class DijkstraMaze {
private:
    Maze *mMaze;
    std::map<Cell*,int> mDistances;
    Cell *mOrigin;
    Cell *mFarthest;

    void calculate_r(Cell *cell, int value);
    void reset();
    Cell *find_farthest_cell();
public:
    DijkstraMaze(Maze *maze);
    ~DijkstraMaze();
    Maze *maze();
    void calculate(Cell *cell);
    void calculate(int row, int column);
    int distance_to(Cell *cell);
    int distance_to(int row, int column);
    int longest_path();
    void calculate_longest_path();
    Cell *origin_cell();
    Cell *farthest_cell();
};

std::ostream& operator<<(std::ostream& os, DijkstraMaze& dMaze);
