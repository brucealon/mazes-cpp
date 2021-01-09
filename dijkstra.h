
#pragma once

#include "maze.h"

struct CellDistance {
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int distance;
};

struct CellLocation {
    int x;
    int y;
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
    void reset();
    void calculate(int x, int y);
    void calculate_r(int x, int y, int value);
    int distance(int x, int y);
    CellLocation origin();
    CellDistance farthest();
    void longest_path();
};

std::ostream& operator<<(std::ostream& os, DijkstraMaze& dMaze);
