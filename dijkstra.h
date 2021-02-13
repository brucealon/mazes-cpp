
#pragma once

#include <map>

#include "maze.h"

class DijkstraMaze {
private:
    Maze *mMaze;
    std::map<Cell*,int> mDistances;
    int mRows;
    int mColumns;
    int mFarthestRow;
    int mFarthestColumn;

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
    void calculate_longest_path();
    int farthest_row();
    int farthest_column();
};

std::ostream& operator<<(std::ostream& os, DijkstraMaze& dMaze);
