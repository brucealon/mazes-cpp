
#pragma once

class Maze {
private:
    const unsigned short N       = 1;
    const unsigned short S       = 2;
    const unsigned short E       = 4;
    const unsigned short W       = 8;
    const unsigned short Visited = 16;

    int mWidth;
    int mHeight;
    unsigned short *mMaze;

    void initialize();
    void clear_visited();

public:
    Maze();
    Maze(int w, int h);
    ~Maze();

    void reset();
    void traverse();
    bool is_valid();

    int width();
    int height();

    unsigned short get(int x, int y);
    void set(int x, int y, unsigned short value);
    void block_cell(int x, int y);

    void add_path_north(int x, int y);
    void add_path_south(int x, int y);
    void add_path_east(int x, int y);
    void add_path_west(int x, int y);

    bool has_north_wall(int x, int y);
    bool has_south_wall(int x, int y);
    bool has_east_wall(int x, int y);
    bool has_west_wall(int x, int y);

    bool has_north_door(int x, int y);
    bool has_south_door(int x, int y);
    bool has_east_door(int x, int y);
    bool has_west_door(int x, int y);

    void visit(int x, int y);
    bool visited(int x, int y);
};
