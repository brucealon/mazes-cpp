
#include "traverse.h"

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

void maze_traverse(Maze *maze) {
    traverse_r(maze, tcell{0, 0, FaceE});
}
