
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include "maze.h"
#include "aldous_broder.h"
#include "binary_tree.h"
#include "dijkstra.h"
#include "hunt_and_kill.h"
#include "sidewinder.h"
#include "traverse.h"
#include "wilson.h"

std::map<std::string, void (*)(Maze*)> algorithms =
    {
     {"Aldous-Broder", build_aldousbroder_maze},
     {"Binary tree",   build_bt_maze},
     {"Hunt and Kill", build_huntkill_maze},
     {"Sidewinder",    build_sidewinder_maze},
     {"Wilson",        build_wilson_maze}
    };

int run_test(std::string name, void (*builder)(Maze *)) {
    int failed = 0;

    Maze maze{30, 30};
    builder(&maze);
    Traversal traversal{&maze};

    traversal.traverse();
    if (!traversal.is_valid()) {
        std::cout << name << " maze is NOT valid.\n" << traversal;
        failed++;
    }
    maze.block_cell(5, 5);
    traversal.reset();
    traversal.traverse();
    if (traversal.is_valid()) {
        std::cout << name << " maze should not be valid but is.\n" << traversal << "\n";
        failed++;
    }

    return failed;
}

void run_tests() {
    int failed = 0;
    int count = 100;
    std::cout << "Testing " << count << " iterations of each builder.\n";

    for (int x = 0; x < count; x++) {
        for (auto elem : algorithms) {
            failed += run_test(elem.first, elem.second);
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

void average_deadends(int iterations) {
    int w{30};
    int h{30};

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

void show_mazes() {
    Maze maze{30, 30};
    build_huntkill_maze(&maze);
    Traversal traversal{&maze};
    traversal.traverse();
    std::cout << maze << "\n" << "Maze is" << (traversal.is_valid() ? "" : " not") << " valid.\n";
    DijkstraMaze dMaze{&maze};
    dMaze.calculate_longest_path();
    std::cout << "Distance to 0, 0 = " << dMaze.distance_to(0, 0) << "\n";
    auto frow = dMaze.farthest_row();
    auto fcol = dMaze.farthest_column();
    std::printf("Farthest cell is %d, %d at a distance of %d\n", frow, fcol, dMaze.distance_to(frow, fcol));
}

int main(int argc, char **argv) {
    if (std::getenv("TEST")) {
        run_tests();
    } else if (std::getenv("COUNT")) {
        average_deadends(100);
    } else {
        show_mazes();
    }

    return 0;
}

