
#pragma once

#include "maze.h"

struct CellDistance {
    int x;
    int y;
    int distance;
};

class DijkstraMaze {
private:
    int *mDistances;
    int mWidth;
    int mHeight;
    Maze *mMaze;

    int get(int x, int y);
    void set(int x, int y, int value);
public:
    DijkstraMaze(Maze *maze);
    ~DijkstraMaze();
    Maze *maze();
    void calculate(int x, int y);
    void calculate_r(int x, int y, int value);
    int distance(int x, int y);
    CellDistance farthest();
};

std::ostream& operator<<(std::ostream& os, DijkstraMaze& dMaze);
