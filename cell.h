
#pragma once

#include <map>
#include <vector>

class Cell {
private:
    int   mRow;
    int   mColumn;

    Cell *mNorth;
    Cell *mEast;
    Cell *mSouth;
    Cell *mWest;

    std::map<Cell*,bool> mLinks;

public:
    Cell();
    Cell(int row, int column);

    int row();
    int column();

    Cell *north();
    Cell *east();
    Cell *south();
    Cell *west();

    void set_north(Cell *cell);
    void set_east(Cell *cell);
    void set_south(Cell *cell);
    void set_west(Cell *cell);

    std::vector<Cell*> neighbors();
    std::vector<Cell*> unvisited_neighbors();
    std::vector<Cell*> visited_neighbors();
    bool has_visited_neighbors();

    bool visited();
    bool unvisited();

    void link(Cell *cell, bool bidirectional = true);
    void unlink(Cell *cell, bool bidirectional = true);
    bool is_linked(Cell *cell);
    bool has_links();
    int links();
    std::vector<Cell*> linked_cells();
};
