
#pragma once

#include "maze.h"

class BTMaze : public Maze {
public:
    BTMaze();
    BTMaze(int x, int y);
    ~BTMaze();
    void build();
};
