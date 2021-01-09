
#include <random>
#include "sidewinder.h"

void build_sidewinder_maze(Maze *maze) {
    std::random_device rnd{};

    for (int y = maze->height() - 1; y >= 0; y--) {
        int run = 1;
        for (int x = 0; x < maze->width(); x++) {
            if (y == 0) {
                maze->add_path_east(x, y);
            } else if (x == maze->width() - 1) {
                maze->add_path_north(x - (rnd() % run), y);
                run = 1;
            } else if ((int)(rnd() % 2)) {
                maze->add_path_north(x - (rnd() % run), y);
                run = 1;
            } else {
                maze->add_path_east(x, y);
                run++;
            }
        }
    }
}
