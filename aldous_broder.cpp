
#include <cstdio>
#include <random>
#include "aldous_broder.h"

void build_aldousbroder_maze(Maze *maze) {
    std::random_device rnd{};
    int width = maze->width();
    int height = maze->height();
    int x = (int)(rnd() % width);
    int y = (int)(rnd() % height);

    int unvisited = width * height;
    bool visited[unvisited];
    for (int i = 0; i < unvisited; i++) {
        visited[i] = 0;
    }

    while (unvisited > 0) {
        short direction = (short)(rnd() % 4);
        switch (direction) {
        case 0: // north
            if (y > 0) {
                y--;
                if (!visited[(x * width) + y]) {
                    visited[(x * width) + y] = true;
                    unvisited--;
                    maze->add_path_south(x, y);
                }
            }
            break;
        case 1: // south
            if (y < (height - 1)) {
                y++;
                if (!visited[(x * width) + y]) {
                    visited[(x * width) + y] = true;
                    unvisited--;
                    maze->add_path_north(x, y);
                }
            }
            break;
        case 2: // east
            if (x < (width - 1)) {
                x++;
                if (!visited[(x * width) + y]) {
                    visited[(x * width) + y] = true;
                    unvisited--;
                    maze->add_path_west(x, y);
                }
            }
            break;
        case 3: // west
            if (x > 0) {
                x--;
                if (!visited[(x * width) + y]) {
                    visited[(x * width) + y] = true;
                    unvisited--;
                    maze->add_path_east(x, y);
                }
            }
            break;
        }
    }
}
