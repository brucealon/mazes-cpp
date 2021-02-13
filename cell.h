
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

    std::map<Cell*,bool> links;

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

    void link(Cell *cell, bool bidirectional = true);
    void unlink(Cell *cell, bool bidirectional = true);
    bool is_linked(Cell *cell);
    std::vector<Cell*> linked_cells();
};
