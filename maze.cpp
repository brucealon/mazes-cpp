
#include <iostream>

#include "maze.h"

Maze::Maze(int rows, int columns) :
    mRows{ rows },
    mColumns{ columns }
{
    initialize();
}

Maze::~Maze() {
}

void Maze::initialize() {
    for (int row = 0; row < mRows; row++) {
        std::vector<Cell>cells;
        for (int column = 0; column < mColumns; column++) {
            cells.push_back(Cell{row, column});
        }
        mMaze.push_back(cells);
    }
    for (auto rowp = mMaze.begin(); rowp != mMaze.end(); rowp++) {
        for (auto cellp = rowp->begin(); cellp != rowp->end(); cellp++) {
            int row = cellp->row();
            int column = cellp->column();

            cellp->set_north(get(row - 1, column));
            cellp->set_east(get(row, column + 1));
            cellp->set_south(get(row + 1, column));
            cellp->set_west(get(row, column - 1));
        }
    }
}

Cell *Maze::get(int row, int column) {
    if (row > -1 && row < mRows && column > -1 && column < mColumns) {
        return &mMaze[row][column];
    }

    return nullptr;
}

void Maze::block_cell(int row, int column) {
    Cell *cell = get(row, column);
    auto cells = cell->linked_cells();
    for (auto cellp = cells.begin(); cellp < cells.end(); cellp++) {
        cell->unlink(*cellp);
    }
}

int Maze::rows() {
    return mRows;
}

int Maze::columns() {
    return mColumns;
}

void Maze::reset() {
    for (auto iter = mMaze.begin(); iter != mMaze.end(); iter++) {
        (*iter).erase((*iter).begin(), (*iter).end());
    }
    mMaze.erase(mMaze.begin(), mMaze.end());
    initialize();
}

std::vector<std::vector<Cell>>::iterator Maze::begin() {
    return mMaze.begin();
}

std::vector<std::vector<Cell>>::iterator Maze::end() {
    return mMaze.end();
}

std::ostream& operator<<(std::ostream& os, Maze& maze) {
    os << "\u250C";
    for (int column = 0; column < maze.columns(); column++) {
        os << "\u2500\u2500\u2500";
        os << (column == (maze.columns() - 1) ? "\u2510" : "\u252C");
    }
    os << "\n";

    for (int row = 0; row < maze.rows(); row++) {
        os << "\u2502";
        for (int column = 0; column < maze.columns(); column++) {
            Cell *cell = maze.get(row, column);
            os << "   ";
            os << (cell->is_linked(cell->east()) ? " " : "\u2502");
        }
        os << "\n";
        os << (row == (maze.rows() - 1) ? "\u2514" : "\u251C");
        for (int column = 0; column < maze.columns(); column++) {
            Cell *cell = maze.get(row, column);
            os << (cell->is_linked(cell->south()) ? "   " : "\u2500\u2500\u2500");
            if (row == (maze.rows() - 1)) {
                os << (row == (maze.columns() - 1) ? "\u2518" : "\u2534");
            } else {
                os << (row == (maze.columns() - 1) ? "\u2524" : "\u253C");
            }
        }
        os << "\n";
    }

    return os;
}

