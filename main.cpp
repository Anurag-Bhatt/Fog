#include <SDL3/SDL_events.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <stack>
#include <utility>

#include "Headers/Grid.h"

/*
    TODOS:

        - Make SDL windows -- done with a box
        - Make a grid -- done

        - Make better grid walls, currentyl walls are just padding - dpne
            but we need to connect cells incase they are  - not done

        - Make that grid interactable
            - alternates between color when a cell is clicked - done
            - starting points and ending point?
            - what else?


        Lets refactor the code right now

*/

const int screenWidth = 1920;
const int screenHeight = 1080;

void pollEvents(SDL_Event &event);

int main(int argc, char* argv[]) {
    
    // Initialization
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = SDL_CreateWindow("SDL3 Project",screenWidth, screenHeight, 0);
    if (win == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    SDL_SetWindowResizable(win, true);

    SDL_Renderer* ren = SDL_CreateRenderer(win, NULL);
    if (ren == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    int orderOfGrid = 20;
    int horizontalPadding   = 5;
    int verticalPadding     = 5;


    Grid grid(orderOfGrid, horizontalPadding, verticalPadding, std::make_pair(640, 480));
    grid.generateGrid();
    std::cout << "Size of grid: " << grid.getGridSize() << " \n";

    SDL_Event e;
    bool quit = false;

    // Main render loop
    while (!quit) {
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN) {
                /* the pressed key was Escape? */
                if (e.key.key == SDLK_ESCAPE) {
                    quit = true;
                }
            }
            grid.handleMouseInput(e);
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(ren); // Clear the renderer

        // Drawing grid based on position and color
        grid.drawGrid(ren);
       
        SDL_RenderPresent(ren); // Render the screen
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
