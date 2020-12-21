
#include <cstdio>
#include <iostream>
#include <random>
#include "sidewinder.h"

const unsigned short N = 1;
const unsigned short S = 2;
const unsigned short E = 4;
const unsigned short W = 8;

SidewinderMaze::SidewinderMaze() {
    initialize();
}

SidewinderMaze::SidewinderMaze(int w, int h) :
    mWidth(w),
    mHeight(w),
    mMaze(nullptr)
{
    initialize();
}

SidewinderMaze::~SidewinderMaze() {
    free(mMaze);
}

void SidewinderMaze::build() {
    std::random_device rnd{};

    for (int y = mHeight - 1; y >= 0; y--) {
        int run = 1;
        for (int x = 0; x < mWidth; x++) {
            if (y == 0) {
                if (x < (mWidth - 1)) {
                    set(x, y, get(x, y) & ~E);
                    set(x + 1, y, get(x + 1, y) & ~W);
                }
            } else if (x == mWidth - 1) {
                unsigned int cx = x - (rnd() % run);
                set(cx, y, get(cx, y) & ~N);
                set(cx, y - 1, get(cx, y - 1) & ~S);
                run = 1;
            } else if ((int)(rnd() % 2)) {
                unsigned int cx = x - (rnd() % run);
                set(cx, y, get(cx, y) & ~N);
                set(cx, y - 1, get(cx, y - 1) & ~S);
                run = 1;
            } else {
                set(x, y, get(x, y) & ~E);
                set(x + 1, y, get(x + 1, y) & ~W);
                run++;
            }
        }
    }
}

void SidewinderMaze::initialize() {
    mMaze = (unsigned short *)calloc(mWidth * mHeight, sizeof(unsigned short *));
    reset();
}

void SidewinderMaze::reset() {
    unsigned short all = N | S | E | W;

    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            set(x, y, all);
        }
    }
}

int SidewinderMaze::width() {
    return mWidth;
}

int SidewinderMaze::height() {
    return mHeight;
}

unsigned short SidewinderMaze::get(int x, int y) {
    return mMaze[(x * mWidth) + y];
}

void SidewinderMaze::set(int x, int y, unsigned short value) {
    mMaze[(x * mWidth) + y] = value;
}

bool SidewinderMaze::has_north(int x, int y) {
    return get(x, y) & N;
}

bool SidewinderMaze::has_south(int x, int y) {
    return get(x, y) & S;
}

bool SidewinderMaze::has_east(int x, int y) {
    return get(x, y) & E;
}

bool SidewinderMaze::has_west(int x, int y) {
    return get(x, y) & W;
}
