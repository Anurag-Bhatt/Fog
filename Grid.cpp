#include "Headers/Grid.h"
#include "Grid.h"

Grid::Grid( int gridOrder, int vPadding, int hPadding, std::pair<int,int> dimensions)
{
    // Do other constructor things
    m_gridDimensions = dimensions;
    m_gridOrder     = gridOrder;
    m_gridSize = m_gridOrder * m_gridOrder;
    m_cellWidth     = m_gridDimensions.first/m_gridOrder;
    m_cellHeight    = m_gridDimensions.second/m_gridOrder;
    
    m_cellVerticalPadding = vPadding;
    m_cellHorizontalPadding = hPadding;

    SDL_Color m_cellColor = {.r = 255, .g = 255, .b = 255, .a = 255}; // WHITE

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

            m_cells.push_back({newRectangle, m_cellColor});

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

void Grid::handleMouseInput(SDL_Event &e)
{
    if(e.type == SDL_EVENT_MOUSE_MOTION && e.button.button == SDL_BUTTON_LEFT){
        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        std::cout << "Mouse Position: " << mouseX << ", " << mouseY << "\n";
        int mX = (int)mouseX/(m_cellWidth + m_cellHorizontalPadding);
        int mY = (int)mouseY/(m_cellHeight + m_cellVerticalPadding);

        std::cout << "Cell Position: " << mX << ", " << mY << "\n";
        for(Cell &cell : m_cells){
            SDL_Color color = {.r = 255, .g = 0, .b = 0, .a = 255};
            
            if(cell.isMouseInside(mouseX, mouseY)){
                cell.setColor(color);
            }
        }

    }
}
