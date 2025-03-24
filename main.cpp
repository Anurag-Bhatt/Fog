#include <SDL3/SDL_events.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <stack>
#include <utility>

/*
    TODOS:

        - Make SDL windows -- done with a box
        - Make a grid -- done

        - Make better grid walls, currentyl walls are just padding
            but we need to connect cells incase they are 

        - Make that grid interactable
            - alternates between color when a cell is clicked
            - starting points and ending point?
            - what else?

*/

const int screenWidth = 1920;
const int screenHeight = 1080;

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
    int cellWidth   = 640/orderOfGrid;
    int cellHeight  = 480/orderOfGrid;

    int horizontalPadding   = 5;
    int verticalPadding     = 5;

    // Grid of cells
    std::vector<Cell> Grid;
    std::stack<Cell> gridStack;
    std::vector<std::pair<int,int>> visitedCells;

    for(int i = 0; i < orderOfGrid; i++){
        for(int j = 0; j < orderOfGrid; j++){
            
            SDL_Color cellColor = {.r = 255, .g = 255, .b = 255, .a = 255}; // GREEN
    
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

            float mouseX, mouseY;
            if(e.type == SDL_EVENT_MOUSE_MOTION){
                
                SDL_GetMouseState(&mouseX, &mouseY);
                // std::cout << "Mouse Position: " << mouseX << ", " << mouseY << "\n";

            }


            if(e.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                
                SDL_GetMouseState(&mouseX, &mouseY);
                if(e.button.button == SDL_BUTTON_LEFT){

                    int mX = (int)mouseX/(cellWidth + horizontalPadding);
                    int mY = (int)mouseY/(cellHeight + verticalPadding);

                    std::cout << "Cell Position: " << mX << ", " << mY << "\n";

                    std::cout << "Mouse button left pressed\n";
                    if((mX < 20 && mX > 0) && (mY < 20 && mY > 0)){
                    Grid[mY + (mX * 20)].color = {.r = 255, .g = 0, .b = 0, .a = 0};
                    }
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

