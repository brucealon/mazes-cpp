
#include <iomanip>

#include "dijkstra.h"

DijkstraMaze::DijkstraMaze(Maze *maze) {
    mMaze = maze;
    mWidth = mMaze->width();
    mHeight = mMaze->height();
    mDistances = new int[mWidth * mHeight];

    for (int i = 0; i < (mWidth * mHeight); i++) {
        mDistances[i] = -1;
    }
}

DijkstraMaze::~DijkstraMaze() {
    delete[] mDistances;
    mMaze = nullptr;
}

Maze *DijkstraMaze::maze() {
    return mMaze;
}

int DijkstraMaze::get(int x, int y) {
    return mDistances[(x * mWidth) + y];
}

void DijkstraMaze::set(int x, int y, int value) {
    mDistances[(x * mWidth) + y] = value;
}

void DijkstraMaze::calculate_r(int x, int y, int distance) {
    set(x, y, distance);
    if (mMaze->can_go_north(x, y) && get(x, y - 1) < 0) {
        calculate_r(x, y - 1, distance + 1);
    }
    if (mMaze->can_go_east(x, y) && get(x + 1, y) < 0) {
        calculate_r(x + 1, y, distance + 1);
    }
    if (mMaze->can_go_south(x, y) && get(x, y + 1) < 0) {
        calculate_r(x, y + 1, distance + 1);
    }
    if (mMaze->can_go_west(x, y) && get(x - 1, y) < 0) {
        calculate_r(x - 1, y, distance + 1);
    }
}

void DijkstraMaze::calculate(int x, int y) {
    calculate_r(x, y, 0);
}

int DijkstraMaze::distance(int x, int y) {
    return get(x, y);
}

CellDistance DijkstraMaze::farthest() {
    CellDistance retval;

    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            int distance = get(x, y);
            if (distance > retval.distance) {
                retval.x = x;
                retval.y = y;
                retval.distance = distance;
            }
        }
    }

    return retval;
}

std::ostream& operator<<(std::ostream& os, DijkstraMaze& dMaze) {
    Maze *maze = dMaze.maze();
    os << "\u250C";
    for (int x = 0; x < maze->width(); x++) {
        os << "\u2500\u2500\u2500\u2500";
        os << (x == (maze->width() - 1) ? "\u2510" : "\u252C");
    }
    os << "\n";

    for (int y = 0; y < maze->height(); y++) {
        os << "\u2502";
        for (int x = 0; x < maze->width(); x++) {
            os << " " << std::setw(2) << dMaze.distance(x, y) << " ";
            os << (maze->can_go_east(x, y) ? " " : "\u2502");
        }
        os << "\n";
        os << (y == (maze->height() - 1) ? "\u2514" : "\u251C");
        for (int x = 0; x < maze->width(); x++) {
            os << (maze->can_go_south(x, y) ? "    " : "\u2500\u2500\u2500\u2500");
            if (y == (maze->height() - 1)) {
                os << (x == (maze->width() - 1) ? "\u2518" : "\u2534");
            } else {
                os << (x == (maze->width() - 1) ? "\u2524" : "\u253C");
            }
        }
        os << "\n";
    }

    return os;
}
