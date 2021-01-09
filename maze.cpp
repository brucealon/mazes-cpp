
#include "maze.h"

const unsigned short FaceN       = 1;
const unsigned short FaceS       = 2;
const unsigned short FaceE       = 4;
const unsigned short FaceW       = 8;

struct tcell {
    int x;
    int y;
    unsigned short facing;
};

tcell turn_right(tcell loc) {
    if (loc.facing == FaceN) {
        loc.facing = FaceE;
    } else if (loc.facing == FaceE) {
        loc.facing = FaceS;
    } else if (loc.facing == FaceS) {
        loc.facing = FaceW;
    } else {
        loc.facing = FaceN;
    }

    return loc;
}

bool can_move(Maze *maze, tcell loc) {
    if (loc.facing == FaceE && maze->can_go_east(loc.x, loc.y) && !maze->visited(loc.x + 1, loc.y)) {
        return true;
    } else if (loc.facing == FaceW && maze->can_go_west(loc.x, loc.y) && !maze->visited(loc.x - 1, loc.y)) {
        return true;
    } else if (loc.facing == FaceS && maze->can_go_south(loc.x, loc.y) && !maze->visited(loc.x, loc.y + 1)) {
        return true;
    } else if (loc.facing == FaceN && maze->can_go_north(loc.x, loc.y) && !maze->visited(loc.x, loc.y - 1)) {
        return true;
    }

    return false;
}

tcell move(tcell loc) {
    if (loc.facing == FaceE) {
        loc.x++;
    } else if (loc.facing == FaceW) {
        loc.x--;
    } else if (loc.facing == FaceN) {
        loc.y--;
    } else if (loc.facing == FaceS) {
        loc.y++;
    }

    return loc;
}

void traverse_r(Maze *maze, tcell loc) {
    maze->visit(loc.x, loc.y);

    tcell r_loc = turn_right(loc);
    if (can_move(maze, r_loc)) {
        traverse_r(maze, move(r_loc));
    }
    r_loc = turn_right(r_loc);
    if (can_move(maze, r_loc)) {
        traverse_r(maze, move(r_loc));
    }
    r_loc = turn_right(r_loc);
    if (can_move(maze, r_loc)) {
        traverse_r(maze, move(r_loc));
    }

    if (can_move(maze, loc)) {
        traverse_r(maze, move(loc));
    }
}

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
    delete[] mVisited;
}

void Maze::initialize() {
    mMaze = new Cell[mWidth * mHeight];
    int cells = mWidth * mHeight;
    for (int i = 0; i < cells; i++) {
        mMaze[i] = Cell{};
    }
    reset();
    mVisited = new bool[mWidth * mHeight];
    for (int i = 0; i < cells; i++) {
        mVisited[i] = false;
    }
}

void Maze::reset() {
    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            block_cell(x, y);
        }
    }
}

void Maze::clear_visited() {
    for (int x = 0; x < mWidth; x++) {
        for (int y = 0; y < mHeight; y++) {
            unvisit(x, y);
        }
    }
}

void Maze::traverse() {
    traverse_r(this, tcell{0, 0, FaceE});
}

bool Maze::is_valid() {
    for (int y = 0; y < mHeight; y++) {
        if (get(0, y)->can_go_west()) return false;
        if (get(mWidth - 1, y)->can_go_east()) return false;
    }

    for (int x = 0; x < mWidth; x++) {
        if (get(x, 0)->can_go_north()) return false;
        if (get(x, mHeight -1)->can_go_south()) return false;
    }

    clear_visited();
    traverse();
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

int Maze::width() {
    return mWidth;
}

int Maze::height() {
    return mHeight;
}

Cell *Maze::get(int x, int y) {
    return &(mMaze[(x * mWidth) + y]);
}

void Maze::set(int x, int y, Cell cell) {
    mMaze[(x * mWidth) + y] = cell;
}

void Maze::block_cell(int x, int y) {
    block_cell(get(x, y));
}

void Maze::block_cell(Cell *cell) {
    cell->disconnect_north();
    cell->disconnect_south();
    cell->disconnect_east();
    cell->disconnect_west();
}

void Maze::add_path_north(int x, int y) {
    if (y > 0) {
        get(x, y)->connect_north(get(x, y - 1));
    }
}

void Maze::add_path_south(int x, int y) {
    if (y < (mHeight - 1)) {
        get(x, y)->connect_south(get(x, y + 1));
    }
}

void Maze::add_path_east(int x, int y) {
    if (x < (mWidth - 1)) {
        get(x, y)->connect_east(get(x + 1, y));
    }
}

void Maze::add_path_west(int x, int y) {
    if (x > 0) {
        get(x, y)->connect_west(get(x - 1, y));
    }
}

bool Maze::has_north_wall(int x, int y) {
    return !can_go_north(x, y);
}

bool Maze::has_south_wall(int x, int y) {
    return !can_go_south(x, y);
}

bool Maze::has_east_wall(int x, int y) {
    return !can_go_east(x, y);
}

bool Maze::has_west_wall(int x, int y) {
    return !can_go_west(x, y);
}

bool Maze::can_go_north(int x, int y) {
    return get(x, y)->can_go_north();
}

bool Maze::can_go_south(int x, int y) {
    return get(x, y)->can_go_south();
}

bool Maze::can_go_east(int x, int y) {
    return get(x, y)->can_go_east();
}

bool Maze::can_go_west(int x, int y) {
    return get(x, y)->can_go_west();
}

void Maze::visit(int x, int y) {
    mVisited[(x * mWidth) + y] = true;
}

void Maze::unvisit(int x, int y) {
    mVisited[(x * mWidth) + y] = false;
}

bool Maze::visited(int x, int y) {
    return mVisited[(x * mWidth) + y];
}

std::ostream& operator<<(std::ostream& os, Maze& maze) {
    os << "\u250C";
    for (int x = 0; x < maze.width(); x++) {
        os << "\u2500\u2500\u2500";
        os << (x == (maze.width() - 1) ? "\u2510" : "\u252C");
    }
    os << "\n";

    for (int y = 0; y < maze.height(); y++) {
        os << "\u2502";
        for (int x = 0; x < maze.width(); x++) {
            os << " " << (maze.visited(x, y) ? "\u22C6" : " ") << " ";
            os << (maze.can_go_east(x, y) ? " " : "\u2502");
        }
        os << "\n";
        os << (y == (maze.height() - 1) ? "\u2514" : "\u251C");
        for (int x = 0; x < maze.width(); x++) {
            os << (maze.can_go_south(x, y) ? "   " : "\u2500\u2500\u2500");
            if (y == (maze.height() - 1)) {
                os << (x == (maze.width() - 1) ? "\u2518" : "\u2534");
            } else {
                os << (x == (maze.width() - 1) ? "\u2524" : "\u253C");
            }
        }
        os << "\n";
    }

    return os;
}

