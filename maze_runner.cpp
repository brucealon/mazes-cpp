
#include <cstdio>
#include <iostream>
#include "maze.h"
#include "aldous_broder.h"
#include "binary_tree.h"
#include "sidewinder.h"
#include "dijkstra.h"
#include "traverse.h"
#include "wilson.h"

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
        failed += run_test("Binary tree",   build_bt_maze);
        failed += run_test("Sidewinder",    build_sidewinder_maze);
        failed += run_test("Aldous-Broder", build_aldousbroder_maze);
        failed += run_test("Wilson",        build_wilson_maze);
        std::cout << "."; std::cout.flush();
    }
    std::cout << "\n";
    std::cout << "Testing complete.\n";
    std::cout << failed << " tests failed.\n";
}

void show_mazes() {
    Maze maze{30, 30};
    build_wilson_maze(&maze);
    Traversal traversal{&maze};
    traversal.traverse();
    std::cout << maze << "\n" << "Maze is" << (traversal.is_valid() ? "" : " not") << " valid.\n";
    DijkstraMaze dMaze{&maze};
    dMaze.calculate_longest_path();
    std::cout << dMaze;
    std::cout << "Distance to 0, 0 = " << dMaze.distance_to(0, 0) << "\n";
    auto frow = dMaze.farthest_row();
    auto fcol = dMaze.farthest_column();
    std::printf("Farthest cell is %d, %d at a distance of %d\n", frow, fcol, dMaze.distance_to(frow, fcol));
}

int main(int argc, char **argv) {
    show_mazes();
    std::cout << "\n\n";
    run_tests();

    return 0;
}

