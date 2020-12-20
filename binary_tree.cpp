
#include <iostream>
#include <random>
#include "binary_tree.h"

const unsigned short N = 1;
const unsigned short S = 2;
const unsigned short E = 4;
const unsigned short W = 8;

BTMaze::BTMaze() {
    initialize();
}

BTMaze::BTMaze(unsigned int w, unsigned int h) :
    mWidth(w),
    mHeight(w),
    maze(nullptr)
{
    initialize();
}

BTMaze::~BTMaze() {
    free(maze);
}

void BTMaze::build() {
    std::random_device rnd{};

    for (unsigned int y = 0; y < mHeight; y++) {
        for (unsigned int x = 0; x < mWidth; x++) {
            unsigned short value = get(x, y);
            if (y == 0) {
                if (x < (mWidth - 1)) {
                    set(x, y, value ^ E);
                    set(x + 1, y, get(x + 1, y) ^ W);
                }
            } else if (x == mWidth - 1) {
                if (y > 0) {
                    set(x, y, value ^ N);
                    set(x, y - 1, get(x, y - 1) ^ S);
                }
            } else if ((int)(rnd() % 2)) {
                set(x, y, value ^ N);
                set(x, y - 1, get(x, y - 1) ^ S);
            } else {
                set(x, y, value ^ E);
                set(x + 1, y, get(x + 1, y) ^ W);
            }
        }
    }
}

void BTMaze::initialize() {
    maze = (unsigned short *)calloc(mWidth * mHeight, sizeof(unsigned short *));
    reset();
}

void BTMaze::reset() {
    unsigned short all = N | S | E | W;

    for (unsigned int x = 0; x < mWidth; x++) {
        for (unsigned int y = 0; y < mHeight; y++) {
            set(x, y, all);
        }
    }
}

unsigned int BTMaze::width() {
    return mWidth;
}

unsigned int BTMaze::height() {
    return mHeight;
}

unsigned short BTMaze::get(unsigned int x, unsigned int y) {
    return maze[(x * mWidth) + y];
}

void BTMaze::set(unsigned int x, unsigned int y, unsigned short value) {
    maze[(x * mWidth) + y] = value;
}

bool BTMaze::has_north(unsigned int x, unsigned int y) {
    return get(x, y) & N;
}

bool BTMaze::has_south(unsigned int x, unsigned int y) {
    return get(x, y) & S;
}

bool BTMaze::has_east(unsigned int x, unsigned int y) {
    return get(x, y) & E;
}

bool BTMaze::has_west(unsigned int x, unsigned int y) {
    return get(x, y) & W;
}
