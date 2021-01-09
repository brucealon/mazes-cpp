
#include "cell.h"

Cell::Cell() {
    mNorth = nullptr;
    mSouth = nullptr;
    mEast = nullptr;
    mWest = nullptr;
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

bool Cell::can_go_north() {
    return mNorth != nullptr;
}

bool Cell::can_go_east() {
    return mEast != nullptr;
}

bool Cell::can_go_south() {
    return mSouth != nullptr;
}

bool Cell::can_go_west() {
    return mWest != nullptr;
}

void Cell::connect_north(Cell *cell) {
    if (mNorth != cell) {
        mNorth = cell;
        cell->connect_south(this);
    }
}

void Cell::connect_east(Cell *cell) {
    if (mEast != cell) {
        mEast = cell;
        cell->connect_west(this);
    }
}

void Cell::connect_south(Cell *cell) {
    if (mSouth != cell) {
        mSouth = cell;
        cell->connect_north(this);
    }

}

void Cell::connect_west(Cell *cell) {
    if (mWest != cell) {
        mWest = cell;
        cell->connect_east(this);
    }
}

void Cell::disconnect_north() {
    if (mNorth != nullptr) {
        Cell *cell = mNorth;
        mNorth = nullptr;
        if (cell->can_go_south()) {
            cell->disconnect_south();
        }
    }
}

void Cell::disconnect_east() {
    if (mEast != nullptr) {
        Cell *cell = mEast;
        mEast = nullptr;
        if (cell->can_go_west()) {
            cell->disconnect_west();
        }
    }
}

void Cell::disconnect_south() {
    if (mSouth != nullptr) {
        Cell *cell = mSouth;
        mSouth = nullptr;
        if (cell->can_go_north()) {
            cell->disconnect_north();
        }
    }
}

void Cell::disconnect_west() {
    if (mWest != nullptr) {
        Cell *cell = mWest;
        mWest = nullptr;
        if (cell->can_go_east()) {
            cell->disconnect_east();
        }
    }
}
