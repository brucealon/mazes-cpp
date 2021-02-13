
#include <random>
#include "binary_tree.h"

void build_bt_maze(Maze *maze) {
    std::random_device rnd{};

    for (auto rowp = maze->begin(); rowp != maze->end(); rowp++) {
        for (auto cellp = rowp->begin(); cellp != rowp->end(); cellp++) {
            if (cellp->north() == nullptr) {
                cellp->link(cellp->east());
            } else if (cellp->east() == nullptr) {
                cellp->link(cellp->north());
            } else if ((int)(rnd() % 2)) {
                cellp->link(cellp->north());
            } else {
                cellp->link(cellp->east());
            }
        }
    }
}
