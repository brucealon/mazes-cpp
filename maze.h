
#pragma once

#include <iostream>
#include "cell.h"

class Maze {
private:
    int mWidth;
    int mHeight;
    Cell *mMaze;
    bool *mVisited;

    void initialize();
    void clear_visited();

    Cell *get(int x, int y);
    void set(int x, int y, Cell cell);

    void block_cell(Cell *cell);

public:
    Maze();
    Maze(int w, int h);
    ~Maze();

    void reset();
    void traverse();
    bool is_valid();

    int width();
    int height();

    void block_cell(int x, int y);

    void add_path_north(int x, int y);
    void add_path_south(int x, int y);
    void add_path_east(int x, int y);
    void add_path_west(int x, int y);

    bool has_north_wall(int x, int y);
    bool has_south_wall(int x, int y);
    bool has_east_wall(int x, int y);
    bool has_west_wall(int x, int y);

    bool can_go_north(int x, int y);
    bool can_go_south(int x, int y);
    bool can_go_east(int x, int y);
    bool can_go_west(int x, int y);

    void visit(int x, int y);
    void unvisit(int x, int y);
    bool visited(int x, int y);
};

std::ostream& operator<<(std::ostream& os, Maze& maze);
