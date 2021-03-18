
#include <algorithm>
#include <random>
#include <vector>
#include "wilson.h"

static std::random_device rnd{};

Cell *random_cell(std::vector<Cell*> cells) {
    int idx = (int)(rnd() % cells.size());
    return cells[idx];
}

bool includes(std::vector<Cell*> cells, Cell *cell) {
    for (auto c = cells.begin(); c != cells.end(); c++) {
        if (*c == cell) {
            return true;
        }
    }

    return false;
}

void delete_to_end(std::vector<Cell*> &cells, Cell *start) {
    std::vector<Cell*>::iterator istart;
    for (auto iter = cells.begin(); iter != cells.end(); iter++) {
        if (*iter == start) {
            istart = ++iter;
            break;
        }
    }
    cells.erase(istart, cells.end());
}

void remove_item(std::vector<Cell*> &cells, Cell *item) {
    cells.erase(std::find(cells.begin(), cells.end(), item));
}

void build_wilson_maze(Maze *maze) {
    std::vector<Cell*> unvisited;

    for (auto row = maze->begin(); row != maze->end(); row++) {
        for (auto cell = row->begin(); cell != row->end(); cell++) {
            unvisited.push_back(&(*cell));
        }
    }

    Cell *cell = random_cell(unvisited);
    remove_item(unvisited, cell);
    while (!unvisited.empty()) {
        cell = random_cell(unvisited);
        std::vector<Cell*> path;
        path.push_back(cell);

        while (includes(unvisited, cell)) {
            cell = random_cell(cell->neighbors());
            if (includes(path, cell)) {
                delete_to_end(path, cell);
            } else {
                path.push_back(cell);
            }
        }

        for (auto it = path.begin(); it < path.end() - 1; it++) {
            (*it)->link(*(it + 1));
            remove_item(unvisited, *it);
        }
    }
}
