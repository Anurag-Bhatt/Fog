#include "Headers/Cell.h"
#include "Cell.h"


Cell::Cell(SDL_FRect cell, SDL_Color col){

    m_cell = cell;
    m_color = col;
}

Cell::~Cell()
{
}

void Cell::draw(SDL_Renderer *ren)
{
    // Set render draw cell color
    SDL_SetRenderDrawColor(ren, m_color.r, m_color.g, m_color.b, m_color.a);

    // Render the rectangle
    SDL_RenderFillRect(ren, &m_cell); 
}
Walls Cell::getWalls()
{
    return m_wall;
}

void Cell::setWalls(Walls wall)
{
    m_wall = wall;
}

void Cell::setColor(SDL_Color cellColor)
{
    m_color = cellColor;
}

SDL_Color Cell::getColor()
{
    return m_color;
}

bool Cell::isMouseInside(float mouseX, float mouseY)
{
    return ((mouseX >= m_cell.x && mouseX < m_cell.x + m_cell.w) &&
    (mouseY >= m_cell.y && mouseY < m_cell.y + m_cell.h));
}
