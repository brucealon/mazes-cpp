
#include <iostream>
#include <random>
#include "binary_tree.h"

BTMaze::BTMaze() {
    initialize();
}

BTMaze::BTMaze(int w, int h) {
    mWidth = w;
    mHeight = h;
    mMaze = nullptr;
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
