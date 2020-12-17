
#include <iostream>

class BTMaze {
private:
    unsigned int mWidth;
    unsigned int mHeight;
    unsigned short *maze;

public:
    BTMaze();
    BTMaze(unsigned int w, unsigned int h);
    ~BTMaze();
    void build();
    void reset();
    unsigned int width();
    unsigned int height();
    unsigned short get(unsigned int x, unsigned int y);
    void set(unsigned int x, unsigned int y, unsigned short value);
    bool has_north(unsigned int x, unsigned int y);
    bool has_south(unsigned int x, unsigned int y);
    bool has_east(unsigned int x, unsigned int y);
    bool has_west(unsigned int x, unsigned int y);

private:
    void initialize();
};
