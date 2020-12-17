
#include <iostream>
#include "binary_tree.h"
#include "SDL2/SDL.h"

void draw_maze_sdl(BTMaze *maze) {
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
    for (unsigned int mx = 0; mx < maze->width(); mx++) {
        for (unsigned int my = 0; my < maze->height(); my++) {
            unsigned int x = (mx * lineLen) + mazeOffset;
            unsigned int y = (my * lineLen) + mazeOffset;
            if (maze->has_north(mx, my)) {
                SDL_RenderDrawLine(renderer, x, y, x + lineLen, y);
            }
            if (maze->has_south(mx, my)) {
                SDL_RenderDrawLine(renderer, x, y + lineLen, x + lineLen, y + lineLen);
            }
            if (maze->has_east(mx, my)) {
                SDL_RenderDrawLine(renderer, x + lineLen, y, x + lineLen, y + lineLen);
            }
            if (maze->has_west(mx, my)) {
                SDL_RenderDrawLine(renderer, x, y, x, y + lineLen);
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

void draw_maze_ascii(BTMaze *maze) {
    std::cout << "\n\n";
    for (unsigned int y = 0; y < maze->height(); y++) {
        for (unsigned int x = 0; x < maze->width(); x++) {
            std::cout << maze->get(x, y) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

int main(int argc, char **argv) {
    BTMaze maze{30, 30};
    maze.build();

    draw_maze_sdl(&maze);
    draw_maze_ascii(&maze);

    return 0;
}

