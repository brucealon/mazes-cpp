
#include "maze.h"

void Maze::initialize() {
    mMaze = new unsigned short[mWidth * mHeight];
    reset();
}

void Maze::reset() {
    unsigned short all = N | S | E | W;

    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            set(x, y, all);
        }
    }
}

int Maze::width() {
    return mWidth;
}

int Maze::height() {
    return mHeight;
}

unsigned short Maze::get(int x, int y) {
    return mMaze[(x * mWidth) + y];
}

void Maze::set(int x, int y, unsigned short value) {
    mMaze[(x * mWidth) + y] = value;
}

bool Maze::has_north(int x, int y) {
    return get(x, y) & N;
}

bool Maze::has_south(int x, int y) {
    return get(x, y) & S;
}

bool Maze::has_east(int x, int y) {
    return get(x, y) & E;
}

bool Maze::has_west(int x, int y) {
    return get(x, y) & W;
}
