
#include <cstdio>
#include <iostream>
#include <random>
#include "sidewinder.h"

SidewinderMaze::SidewinderMaze() {
    initialize();
}

SidewinderMaze::SidewinderMaze(int w, int h) {
    mWidth = w;
    mHeight = h;
    mMaze = nullptr;
    initialize();
}

SidewinderMaze::~SidewinderMaze() {
    delete[] mMaze;
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
