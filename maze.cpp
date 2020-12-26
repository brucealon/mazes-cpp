
#include "maze.h"
#include "traverser.h"

Maze::Maze() {
    initialize();
}

Maze::Maze(int w, int h) {
    mWidth = w;
    mHeight = h;
    mMaze = nullptr;
    initialize();
}

Maze::~Maze() {
    delete[] mMaze;
}

void Maze::initialize() {
    mMaze = new unsigned short[mWidth * mHeight];
    reset();
}

void Maze::clear_visited() {
    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            set(x, y, get(x, y) & ~Visited);
        }
    }
}

bool Maze::is_valid() {
    for (int y = 0; y < mHeight; y++) {
        if (!(get(0, y) & W)) return false;
        if (!(get(mWidth - 1, y) & E)) return false;
    }

    for (int x = 0; x < mWidth; x++) {
        if (!(get(x, 0) & N)) return false;
        if (!(get(x, mHeight - 1) & S)) return false;
    }

    clear_visited();
    traverse_maze(this);
    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            if (!visited(x, y)) {
                return false;
            }
        }
    }
    clear_visited();

    return true;
}

void Maze::reset() {
    unsigned short all = N | S | E | W;

    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            set(x, y, all);
        }
    }
}

int Maze::width() {
    return mWidth;
}

int Maze::height() {
    return mHeight;
}

unsigned short Maze::get(int x, int y) {
    return mMaze[(x * mWidth) + y];
}

void Maze::set(int x, int y, unsigned short value) {
    mMaze[(x * mWidth) + y] = value;
}

void Maze::add_path_north(int x, int y) {
    if (y > 0) {
        set(x, y, get(x, y) & ~N);
        set(x, y - 1, get(x, y - 1) & ~S);
    }
}

void Maze::add_path_south(int x, int y) {
    if (y < (mHeight - 1)) {
        set(x, y, get(x, y) & ~S);
        set(x, y + 1, get(x, y + 1) & ~N);
    }
}

void Maze::add_path_east(int x, int y) {
    if (x < (mWidth - 1)) {
        set(x, y, get(x, y) & ~E);
        set(x + 1, y, get(x + 1, y) & ~W);
    }
}

void Maze::add_path_west(int x, int y) {
    if (x > 0) {
        set(x, y, get(x, y) & ~W);
        set(x - 1, y, get(x - 1, y) & ~E);
    }
}

bool Maze::has_north_wall(int x, int y) {
    return get(x, y) & N;
}

bool Maze::has_south_wall(int x, int y) {
    return get(x, y) & S;
}

bool Maze::has_east_wall(int x, int y) {
    return get(x, y) & E;
}

bool Maze::has_west_wall(int x, int y) {
    return get(x, y) & W;
}

bool Maze::has_north_door(int x, int y) {
    return !has_north_wall(x, y);
}

bool Maze::has_south_door(int x, int y) {
    return !has_south_wall(x, y);
}

bool Maze::has_east_door(int x, int y) {
    return !has_east_wall(x, y);
}

bool Maze::has_west_door(int x, int y) {
    return !has_west_wall(x, y);
}

void Maze::visit(int x, int y) {
    set(x, y, get(x, y) | Visited);
}

bool Maze::visited(int x, int y) {
    return get(x, y) & Visited;
}
