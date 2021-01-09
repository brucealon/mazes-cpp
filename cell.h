
#pragma once

class Cell {
private:
    Cell *mNorth;
    Cell *mEast;
    Cell *mSouth;
    Cell *mWest;

public:
    Cell();

    Cell *north();
    Cell *east();
    Cell *south();
    Cell *west();

    bool can_go_north();
    bool can_go_east();
    bool can_go_south();
    bool can_go_west();

    void connect_north(Cell *cell);
    void connect_east(Cell *cell);
    void connect_south(Cell *cell);
    void connect_west(Cell *cell);

    void disconnect_north();
    void disconnect_east();
    void disconnect_south();
    void disconnect_west();
};
