#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <iostream>
#include <vector>


/*
    TODOS:

        - Make SDL windows -- done with a box
        - Make a grid
        - Make that grid interactable

*/

const int screenWidth = 640;
const int screenHeight = 480;

struct Cell{

    int xPos = 0, yPos = 0;
    int width, height;

    SDL_Color color;

    Cell(int x, int y,  int w, int h, SDL_Color col)
    : width(w), height(h), color(col) 
    {
        xPos = x;
        yPos = y;
    }

};

// void CheckMouseInput(SDL_Event &e);



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

    // Event Handling
    SDL_Event e;
    bool quit = false;

    int orderOfGrid = 20;

    // 20 * 20 grid
    int cellWidth   = screenWidth/orderOfGrid;
    int cellHeight  = screenHeight/orderOfGrid;

    int horizontalPadding   = 5;
    int verticalPadding     = 5;

    // Grid of cells
    std::vector<Cell> Grid;

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            
            SDL_Color cellColor = {.r = 0, .g = 255, .b = 0, .a = 255}; // GREEN
    
            Grid.push_back({i * (cellWidth + horizontalPadding), 
                            j * (cellHeight + verticalPadding), 
                            cellWidth, cellHeight, cellColor});

        }   
    }

    std::cout << "Size of grid: " << Grid.size() << " \n";

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
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(ren); // Clear the renderer

        
        for(int i = 0; i < Grid.size(); i++){
            Cell currentCell = Grid[i];
            SDL_FRect currentRectanlge;

            currentRectanlge.x = currentCell.xPos;
            currentRectanlge.y = currentCell.yPos;
            currentRectanlge.w = currentCell.width;
            currentRectanlge.h = currentCell.height;

            // Set render draw color to green
            SDL_SetRenderDrawColor(ren, currentCell.color.r, currentCell.color.g, currentCell.color.b, currentCell.color.a); 
            SDL_RenderFillRect(ren, &currentRectanlge); // Render the rectangle
        }


        SDL_RenderPresent(ren); // Render the screen
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

