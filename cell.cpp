
#include "cell.h"

Cell::Cell() :
    mRow{ -1 },
    mColumn{ -1 },
    mNorth{ nullptr },
    mEast{ nullptr },
    mSouth{ nullptr },
    mWest{ nullptr }
{}

Cell::Cell(int row, int column) :
    mRow{ row },
    mColumn{ column },
    mNorth{ nullptr },
    mEast{ nullptr },
    mSouth{ nullptr },
    mWest{ nullptr }
{}

int Cell::row() {
    return mRow;
}

int Cell::column() {
    return mColumn;
}

Cell *Cell::north() {
    return mNorth;
}

Cell *Cell::east() {
    return mEast;
}

Cell *Cell::south() {
    return mSouth;
}

Cell *Cell::west() {
    return mWest;
}

void Cell::set_north(Cell *cell) {
    mNorth = cell;
}

void Cell::set_east(Cell *cell) {
    mEast = cell;
}

void Cell::set_south(Cell *cell) {
    mSouth = cell;
}

void Cell::set_west(Cell *cell) {
    mWest = cell;
}

std::vector<Cell*> Cell::neighbors() {
    std::vector<Cell*> neighbors;
    if (mNorth != nullptr) {
        neighbors.push_back(mNorth);
    }
    if (mEast != nullptr) {
        neighbors.push_back(mEast);
    }
    if (mSouth != nullptr) {
        neighbors.push_back(mSouth);
    }
    if (mWest != nullptr) {
        neighbors.push_back(mWest);
    }

    return neighbors;
}

void Cell::link(Cell *cell, bool bidirectional) {
    if (cell != nullptr) {
        links[cell] = true;
        if (bidirectional) {
            cell->link(this, false);
        }
    }
}

void Cell::unlink(Cell *cell, bool bidirectional) {
    if (cell != nullptr) {
        links[cell] = false;
        if (bidirectional) {
            cell->unlink(this, false);
        }
    }
}

bool Cell::is_linked(Cell *cell) {
    if (cell == nullptr) {
        return false;
    }

    return links[cell];
}

std::vector<Cell*> Cell::linked_cells() {
    std::vector<Cell*> linked;

    for (auto pair : links) {
        linked.push_back(pair.first);
    }

    return linked;
}
