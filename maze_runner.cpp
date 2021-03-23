
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include "maze.h"
#include "aldous_broder.h"
#include "binary_tree.h"
#include "dijkstra.h"
#include "hunt_and_kill.h"
#include "recursive_backtrack.h"
#include "sidewinder.h"
#include "traverse.h"
#include "wilson.h"

std::map<std::string, void (*)(Maze*)> algorithms =
    {
     {"Aldous-Broder",         build_aldousbroder_maze},
     {"Binary tree",           build_bt_maze},
     {"Hunt and Kill",         build_huntkill_maze},
     {"Recursive Backtracker", build_rb_maze},
     {"Sidewinder",            build_sidewinder_maze},
     {"Wilson",                build_wilson_maze}
    };

int run_test(int rows, int columns, std::string name, void (*builder)(Maze *)) {
    int failed = 0;

    Maze maze{rows, columns};
    builder(&maze);
    Traversal traversal{&maze};

    traversal.traverse();
    if (!traversal.is_valid()) {
        std::cout << name << " maze is NOT valid.\n" << traversal;
        failed++;
    }
    maze.block_cell(5, 5);
    traversal.traverse();
    if (traversal.is_valid()) {
        std::cout << name << " maze should not be valid but is.\n" << traversal << "\n";
        failed++;
    }

    return failed;
}

void run_tests(int rows, int columns, int iterations) {
    int failed = 0;
    std::cout << "Testing " << iterations << " iterations of each builder.\n";

    for (int x = 0; x < iterations; x++) {
        for (auto elem : algorithms) {
            failed += run_test(rows, columns, elem.first, elem.second);
        }
        std::cout << "."; std::cout.flush();
    }
    std::cout << "\n";
    std::cout << "Testing complete.\n";
    std::cout << failed << " tests failed.\n";
}

int count_deadends(void (*builder)(Maze*), int w, int h) {
    Maze maze{w, h};
    builder(&maze);
    return maze.deadends();
}

void average_deadends(int rows, int columns, int iterations) {
    int w{rows};
    int h{columns};

    for (auto elem : algorithms) {
        int sum{0};
        for (int idx = 0; idx < iterations; idx++) {
            sum += count_deadends(elem.second, w, h);
        }
        int avg = sum/iterations;
        int pct = (int)(100 * ((float)avg / (float)(w * h)));
        std::cout << "Average dead ends for " << elem.first << " is " << avg << " (" << pct << "%).\n";
    }
}

void average_distances(int rows, int columns, int iterations) {
    for (auto elem : algorithms) {
        int sum{0};
        for (int idx = 0; idx < iterations; idx++) {
            Maze maze{rows, columns};
            elem.second(&maze);
            DijkstraMaze dMaze{&maze};
            dMaze.calculate_longest_path();
            sum += dMaze.longest_path();
        }
        int avg = sum/iterations;
        std::cout << "Average distance for " << elem.first << " is " << avg << ".\n";
    }
}

void show_mazes() {
    Maze maze{30, 30};
    build_rb_maze(&maze);
    Traversal traversal{&maze};
    traversal.traverse();
    std::cout << maze << "\n" << "Maze is" << (traversal.is_valid() ? "" : " not") << " valid.\n";
    DijkstraMaze dMaze{&maze};
    dMaze.calculate_longest_path();
    Cell *origin = dMaze.origin_cell();
    std::printf("Origin is now %d, %d\n", origin->row(), origin->column());
    std::cout << "Distance to 0, 0 = " << dMaze.distance_to(0, 0) << "\n";
    Cell *farthest = dMaze.farthest_cell();
    std::printf("Farthest cell is %d, %d at a distance of %d\n",
                farthest->row(),
                farthest->column(),
                dMaze.distance_to(farthest));
}

int main(int argc, char **argv) {
    int iterations = 100;
    int rows = 30;
    int columns = 30;

    if (std::getenv("TEST")) {
        run_tests(rows, columns, iterations);
    } else if (std::getenv("COUNT")) {
        average_deadends(rows, columns, iterations);
    } else if (std::getenv("DISTANCE")) {
        average_distances(rows, columns, iterations);
    } else {
        show_mazes();
    }

    return 0;
}

