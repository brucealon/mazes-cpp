
#include <random>
#include <vector>
#include "sidewinder.h"

void build_sidewinder_maze(Maze *maze) {
    std::random_device rnd{};

    for (auto rowp = maze->begin(); rowp != maze->end(); rowp++) {
        std::vector<Cell*> run;

        for (auto cellp = rowp->begin(); cellp != rowp->end(); cellp++) {
            run.push_back(&(*cellp));

            if (cellp->north() == nullptr) {
                cellp->link(cellp->east());
            } else if (cellp->east() == nullptr) {
                Cell *member = run[(int)(rnd() % run.size())];
                member->link(member->north());
                run.clear();
            } else if ((int)(rnd() % 2)) {
                Cell *member = run[(int)(rnd() % run.size())];
                member->link(member->north());
                run.clear();
            } else {
                cellp->link(cellp->east());
            }
        }
    }
}
