#pragma once

#include <SDL3/SDL.h>

struct Walls{
    bool top;
    bool bottom;
    bool left;
    bool right;
};


class Cell{

public:
    Cell(SDL_FRect m_cell, SDL_Color col);
    ~Cell();

    // Draws the cell and padding with cell's color
    void draw(SDL_Renderer *ren);

    // Sets and gets all the walls.
    Walls getWalls();
    void setWalls(Walls wall);

    void setColor(SDL_Color cellColor);
    SDL_Color getColor();
    bool isMouseInside(float mouseX, float mouseY);

private:

    SDL_Color m_color;
    SDL_FRect m_cell;

    Walls m_wall;
};