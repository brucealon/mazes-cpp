
#pragma once

#include <iostream>
#include <vector>

#include "cell.h"

class Maze {
private:
    int mRows;
    int mColumns;
    std::vector<std::vector<Cell>> mMaze;

    void initialize();

public:
    Maze(int rows, int columns);
    ~Maze();

    int rows();
    int columns();

    Cell *get(int row, int column);
    void block_cell(int row, int column);

    void reset();

    std::vector<std::vector<Cell>>::iterator begin();
    std::vector<std::vector<Cell>>::iterator end();

    int deadends();
};

std::ostream& operator<<(std::ostream& os, Maze& maze);
