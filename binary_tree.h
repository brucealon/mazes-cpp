
class BTMaze {
private:
    int mWidth;
    int mHeight;
    unsigned short *mMaze;

public:
    BTMaze();
    BTMaze(int w, int h);
    ~BTMaze();

    void build();
    void reset();

    int width();
    int height();

    unsigned short get(int x, int y);
    void set(int x, int y, unsigned short value);

    bool has_north(int x, int y);
    bool has_south(int x, int y);
    bool has_east(int x, int y);
    bool has_west(int x, int y);

private:
    void initialize();
};
