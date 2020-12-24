
#pragma once

#include "maze.h"

class SidewinderMaze : public Maze {
public:
    SidewinderMaze();
    SidewinderMaze(int x, int y);
    ~SidewinderMaze();
    void build();
};
