
#include <cstdio>

#include "traverser.h"

const unsigned short N = 1;
const unsigned short S = 2;
const unsigned short E = 4;
const unsigned short W = 8;

struct cell {
    int x;
    int y;
    unsigned short facing;
};

cell turn_right(cell loc) {
    if (loc.facing == N) {
        loc.facing = E;
    } else if (loc.facing == E) {
        loc.facing = S;
    } else if (loc.facing == S) {
        loc.facing = W;
    } else {
        loc.facing = N;
    }

    return loc;
}

bool can_move(Maze *maze, cell loc) {
    if (loc.facing == E && maze->has_east_door(loc.x, loc.y) && !maze->visited(loc.x + 1, loc.y)) {
        return true;
    } else if (loc.facing == W && maze->has_west_door(loc.x, loc.y) && !maze->visited(loc.x - 1, loc.y)) {
        return true;
    } else if (loc.facing == S && maze->has_south_door(loc.x, loc.y) && !maze->visited(loc.x, loc.y + 1)) {
        return true;
    } else if (loc.facing == N && maze->has_north_door(loc.x, loc.y) && !maze->visited(loc.x, loc.y - 1)) {
        return true;
    }

    return false;
}

cell move(cell loc) {
    if (loc.facing == E) {
        loc.x++;
    } else if (loc.facing == W) {
        loc.x--;
    } else if (loc.facing == N) {
        loc.y--;
    } else if (loc.facing == S) {
        loc.y++;
    }

    return loc;
}

void traverse_r(Maze *maze, cell loc) {
    maze->visit(loc.x, loc.y);

    cell r_loc = turn_right(loc);
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

void traverse_maze(Maze *maze) {
    traverse_r(maze, cell{0, 0, E});
}

