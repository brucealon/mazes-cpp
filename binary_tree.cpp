
#include <iostream>
#include <random>
#include "binary_tree.h"

void build_bt_maze(Maze *maze) {
    std::random_device rnd{};

    for (int y = 0; y < maze->height(); y++) {
        for (int x = 0; x < maze->width(); x++) {
            if (y == 0) {
                maze->add_path_east(x, y);
            } else if (x == maze->width() - 1) {
                maze->add_path_north(x, y);
            } else if ((int)(rnd() % 2)) {
                maze->add_path_north(x, y);
            } else {
                maze->add_path_east(x, y);
            }
        }
    }
}
