
#include <iostream>
#include "maze.h"
#include "aldous_broder.h"
#include "binary_tree.h"
#include "sidewinder.h"
#include "dijkstra.h"
#include "SDL2/SDL.h"

void draw_maze_sdl(Maze *maze) {
    int windowWidth = 800;
    int windowHeight = 800;
    int mazeOffset = 25;

    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Maze", 0, 0, windowWidth, windowHeight, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int lineLen = (windowWidth - (mazeOffset * 2)) / maze->width();
    for (int mx = 0; mx < maze->width(); mx++) {
        for (int my = 0; my < maze->height(); my++) {
            int x = (mx * lineLen) + mazeOffset;
            int y = (my * lineLen) + mazeOffset;
            if (maze->has_north_wall(mx, my)) {
                SDL_RenderDrawLine(renderer, x, y, x + lineLen, y);
            }
            if (maze->has_south_wall(mx, my)) {
                SDL_RenderDrawLine(renderer, x, y + lineLen, x + lineLen, y + lineLen);
            }
            if (maze->has_east_wall(mx, my)) {
                SDL_RenderDrawLine(renderer, x + lineLen, y, x + lineLen, y + lineLen);
            }
            if (maze->has_west_wall(mx, my)) {
                SDL_RenderDrawLine(renderer, x, y, x, y + lineLen);
            }
            if (maze->visited(mx, my)) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_Rect visited {x + (lineLen / 2) - 2, y + (lineLen / 2) - 2, 4, 4};
                SDL_RenderFillRect(renderer, &visited);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
        }
    }

    SDL_RenderPresent(renderer);

    int running = 1;
    while(running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            }
        }
    }
}

void run_test(std::string name, void (*builder)(Maze *)) {
    Maze maze{30, 30};
    builder(&maze);

    if (!maze.is_valid()) {
        std::cout << name << " maze is NOT valid.\n" << maze;
    }
    maze.block_cell(5, 5);
    if (maze.is_valid()) {
        std::cout << name << " maze should not be valid but is.\n" << maze;
    }
}

void run_tests() {
    int count = 100;
    std::cout << "Testing " << count << " iterations of each builder.\n";

    for (int x = 0; x < count; x++) {
        run_test("Binary tree",   build_bt_maze);
        run_test("Sidewinder",    build_sidewinder_maze);
        run_test("Aldous-Broder", build_aldousbroder_maze);
    }
    std::cout << "Testing complete.\n";
}

int main(int argc, char **argv) {
    run_tests();

    Maze maze{20, 20};
    build_aldousbroder_maze(&maze);
    DijkstraMaze dMaze{&maze};
    dMaze.longest_path();
    std::cout << maze;
    CellDistance f = dMaze.farthest();
    std::cout << "New Origin: " << f.xStart << "," << f.yStart << "\n";
    std::cout << "Distance to 0, 0 = " << dMaze.distance(0, 0) << "\n";
    std::printf("Farthest is %d to %d,%d\n", f.distance, f.xEnd, f.yEnd);

    return 0;
}

