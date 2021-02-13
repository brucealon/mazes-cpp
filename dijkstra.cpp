
#include <iomanip>

#include "dijkstra.h"

DijkstraMaze::DijkstraMaze(Maze *maze) :
    mMaze{ maze },
    mRows{ maze->rows() },
    mColumns{ maze->columns() },
    mFarthestRow{ -1 },
    mFarthestColumn{ -1 }
{
    reset();
}

DijkstraMaze::~DijkstraMaze() {
    mDistances.clear();
    mMaze = nullptr;
}

Maze *DijkstraMaze::maze() {
    return mMaze;
}

void DijkstraMaze::reset() {
    mDistances.clear();
    for (auto rowp = mMaze->begin(); rowp < mMaze->end(); rowp++) {
        for (auto cellp = rowp->begin(); cellp < rowp->end(); cellp++) {
            mDistances[&(*cellp)] = -1;
        }
    }
    mFarthestRow = -1;
    mFarthestColumn = -1;
}

Cell *DijkstraMaze::find_farthest_cell() {
    Cell *farthest = nullptr;

    for (auto rowp = mMaze->begin(); rowp < mMaze->end(); rowp++) {
        for (auto cellp = rowp->begin(); cellp < rowp->end(); cellp++) {
            Cell *cell = &(*cellp);
            if (mDistances[cell] > mDistances[farthest]) {
                farthest = cell;
            }
        }
    }

    return farthest;
}

void DijkstraMaze::calculate_r(Cell *cell, int distance) {
    mDistances[cell] = distance;

    if (cell->is_linked(cell->north()) && mDistances[cell->north()] < 0) {
        calculate_r(cell->north(), distance + 1);
    }
    if (cell->is_linked(cell->east()) && mDistances[cell->east()] < 0) {
        calculate_r(cell->east(), distance + 1);
    }
    if (cell->is_linked(cell->south()) && mDistances[cell->south()] < 0) {
        calculate_r(cell->south(), distance + 1);
    }
    if (cell->is_linked(cell->west()) && mDistances[cell->west()] < 0) {
        calculate_r(cell->west(), distance + 1);
    }
}

void DijkstraMaze::calculate(Cell *cell) {
    calculate_r(cell, 0);
}

void DijkstraMaze::calculate(int row, int column) {
    calculate_r(mMaze->get(row, column), 0);
}

int DijkstraMaze::distance_to(Cell *cell) {
    return mDistances[cell];
}

int DijkstraMaze::distance_to(int row, int column) {
    return distance_to(mMaze->get(row, column));
}

void DijkstraMaze::calculate_longest_path() {
    calculate(0, 0);
    Cell *farthest = find_farthest_cell();
    reset();
    calculate(farthest);
    farthest = find_farthest_cell();
    mFarthestRow = farthest->row();
    mFarthestColumn = farthest->column();
}

int DijkstraMaze::farthest_row() {
    return mFarthestRow;
}

int DijkstraMaze::farthest_column() {
    return mFarthestColumn;
}

std::ostream& operator<<(std::ostream& os, DijkstraMaze& dMaze) {
    Maze *maze = dMaze.maze();
    os << "\u250C";
    for (int column = 0; column < maze->columns(); column++) {
        os << "\u2500\u2500\u2500\u2500\u2500";
        os << (column == (maze->columns() - 1) ? "\u2510" : "\u252C");
    }
    os << "\n";

    for (int row = 0; row < maze->rows(); row++) {
        os << "\u2502";
        for (int column = 0; column < maze->columns(); column++) {
            Cell *cell = maze->get(row, column);
            os << " " << std::setw(3) << dMaze.distance_to(cell) << " ";
            os << (cell->is_linked(cell->east()) ? " " : "\u2502");
        }
        os << "\n";
        os << (row == (maze->rows() - 1) ? "\u2514" : "\u251C");
        for (int column = 0; column < maze->columns(); column++) {
            Cell *cell = maze->get(row, column);
            os << (cell->is_linked(cell->south()) ? "     " : "\u2500\u2500\u2500\u2500\u2500");
            if (row == (maze->rows() - 1)) {
                os << (row == (maze->columns() - 1) ? "\u2518" : "\u2534");
            } else {
                os << (row == (maze->columns() - 1) ? "\u2524" : "\u253C");
            }
        }
        os << "\n";
    }

    return os;
}
