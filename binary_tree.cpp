
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

BTMaze::BTMaze(int w, int h) :
    mWidth(w),
    mHeight(w),
    mMaze(nullptr)
{
    initialize();
}

BTMaze::~BTMaze() {
    delete[] mMaze;
}

void BTMaze::build() {
    std::random_device rnd{};

    for (int y = 0; y < mHeight; y++) {
        for (int x = 0; x < mWidth; x++) {
            unsigned short value = get(x, y);
            if (y == 0) {
                if (x < (mWidth - 1)) {
                    set(x, y, value ^ E);
                    set(x + 1, y, get(x + 1, y) ^ W);
                }
            } else if (x == mWidth - 1) {
                set(x, y, value ^ N);
                set(x, y - 1, get(x, y - 1) ^ S);
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
    mMaze = (unsigned short *)calloc(mWidth * mHeight, sizeof(unsigned short *));
    mMaze = new unsigned short[mWidth * mHeight];
    reset();
}

void BTMaze::reset() {
    unsigned short all = N | S | E | W;

    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            set(x, y, all);
        }
    }
}

int BTMaze::width() {
    return mWidth;
}

int BTMaze::height() {
    return mHeight;
}

unsigned short BTMaze::get(int x, int y) {
    return mMaze[(x * mWidth) + y];
}

void BTMaze::set(int x, int y, unsigned short value) {
    mMaze[(x * mWidth) + y] = value;
}

bool BTMaze::has_north(int x, int y) {
    return get(x, y) & N;
}

bool BTMaze::has_south(int x, int y) {
    return get(x, y) & S;
}

bool BTMaze::has_east(int x, int y) {
    return get(x, y) & E;
}

bool BTMaze::has_west(int x, int y) {
    return get(x, y) & W;
}
