
#pragma once

class Maze {
protected:
    const unsigned short N = 1;
    const unsigned short S = 2;
    const unsigned short E = 4;
    const unsigned short W = 8;

    int mWidth;
    int mHeight;
    unsigned short *mMaze;

    void initialize();

public:
    virtual void build() = 0;
    void reset();

    int width();
    int height();

    unsigned short get(int x, int y);
    void set(int x, int y, unsigned short value);

    bool has_north(int x, int y);
    bool has_south(int x, int y);
    bool has_east(int x, int y);
    bool has_west(int x, int y);
};
