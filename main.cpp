#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

#include <iostream>
#include <stdio.h>

// window dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* args[])
{
    // stinky boilerplate
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Event e;

    bool running = true;

    if (SDL_Init(SDL_INIT_VIDEO < 0)) {
        // ha loser ur window doesnt work
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("SDL initialized successfully!\n");
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Error initializing SDL_image: %s\n", IMG_GetError());
        return 1;
    } else {
        printf("SDL_image initialized successfully!\n");
    }

    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "DSA Visualizer");
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    if (window == NULL || renderer == NULL) {
        printf("Error creating window or renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    } else {
        printf("SDL2 window and renderer initialized successfully!\n");
    }

    // finally looping
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        SDL_RenderClear(renderer);

        int distance = 75;
        int numCircles = 7;
        int radius = 1;

        int totalHeight = (numCircles - 1) * distance;

        int startingYCord = (SCREEN_HEIGHT - totalHeight) / 2;
        int xCord = (SCREEN_WIDTH - radius) / 2;

        for (int i = 0; i < numCircles; i++) {
            int yCord = startingYCord + i * distance;
            filledCircleRGBA(renderer, xCord, yCord, radius, 0, 120, 120, 255);
        }

        rectangleRGBA(renderer, 100, 100, 200, 200, 255, 0, 0, 255);

        SDL_RenderPresent(renderer);
    }

    // bye bye
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}