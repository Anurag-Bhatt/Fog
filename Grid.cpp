#include "Headers/Grid.h"
#include "Grid.h"

Grid::Grid( int gridOrder, int vPadding, int hPadding, std::pair<int,int> dimensions)
{
    // Do other constructor things
    m_gridDimensions        = dimensions;
    m_gridOrder             = gridOrder;
    m_gridSize              = m_gridOrder * m_gridOrder;
    m_cellWidth             = m_gridDimensions.first/m_gridOrder;
    m_cellHeight            = m_gridDimensions.second/m_gridOrder;
    
    m_cellVerticalPadding   = vPadding;
    m_cellHorizontalPadding = hPadding;

    // Supposed to be white but it turns out be yellow
    m_cellColor = {.r = 255, .g = 255, .b = 255, .a = 255};


    m_UnoccupiedColor = {.r = 255, .g = 255, .b = 255, .a = 255}; // white for unblocked cells
    m_OccupiedColor = {.r = 255, .g = 0, .b = 0, .a = 255};       // Red for blocked cells
    
}

Grid::~Grid()
{
}

void Grid::generateGrid()
{

    for(int i = 0; i < m_gridOrder; i++){
        for(int j = 0; j < m_gridOrder; j++){
            
            SDL_FRect newRectangle;

            newRectangle.x = i * (m_cellWidth + m_cellHorizontalPadding);
            newRectangle.y = j * (m_cellHeight + m_cellVerticalPadding);
            newRectangle.w = m_cellWidth;
            newRectangle.h = m_cellHeight;

            m_cells.push_back({newRectangle, m_UnoccupiedColor});

        }   
    }
}

void Grid::drawGrid(SDL_Renderer* ren)
{
    // call draw() function on each cell
    for(int i = 0; i < m_gridSize; i++){
       
        m_cells.at(i).draw(ren);
    }
}

int Grid::getGridSize()
{
    return m_gridSize;
}

int Grid::getGridOrder()
{
    return m_gridOrder;
}

void Grid::handleInput(SDL_Event &e)
{
    handleMouseInput(e);
    handleKyeboardInput(e);
}

void Grid::handleMouseInput(SDL_Event &e)
{
    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    std::cout << "Mouse Position: " << mouseX << ", " << mouseY << "\n";
    int mX = (int)mouseX/(m_cellWidth + m_cellHorizontalPadding);
    int mY = (int)mouseY/(m_cellHeight + m_cellVerticalPadding);

    uint32_t mouseState = SDL_GetMouseState(NULL, NULL);

    if(mouseState & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)){
        std::cout << "Left Mouse Pressed\n";
        std::cout << "Cell Position: " << mX << ", " << mY << "\n";
        for(Cell &cell : m_cells){
            if(cell.isMouseInside(mouseX, mouseY)){
                cell.setColor(m_OccupiedColor);
            }
        }
    }
    // Right Mouse
    else if(mouseState & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT)){
        std::cout << "Right Mouse Pressed\n";
        std::cout << "Cell Position: " << mX << ", " << mY << "\n";
        for(Cell &cell : m_cells){
            if(cell.isMouseInside(mouseX, mouseY)){
                cell.setColor(m_UnoccupiedColor);
            }
        }
    }
}

void Grid::handleKyeboardInput(SDL_Event &e)
{
    if(e.type = SDL_EVENT_KEY_DOWN){
        if(e.key.key == SDLK_R){
            std::cout << "Reseting Grid...\n";
            for(Cell &cell : m_cells){
                cell.setColor(m_UnoccupiedColor);
                SDL_Delay(10);
                
            }
        }
    }
}
