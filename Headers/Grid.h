#pragma once

#include <iostream>

#include <vector>
#include <stack>
#include <utility>

#include <Cell.h>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>


class Grid{

public:
    Grid(int gridOrder, int vPadding, int hPadding, std::pair<int,int> dimensions);
    ~Grid();

    void generateGrid();
    void drawGrid(SDL_Renderer* ren);

    int getGridSize();
    int getGridOrder();

    void handleInput(SDL_Event &e);

    void handleMouseInput(SDL_Event &e);
    void handleKyeboardInput(SDL_Event &e);


private:

    std::vector<Cell> m_cells;
    std::pair<int,int> m_gridDimensions;

    int m_gridSize;
    int m_gridOrder;

    int m_cellWidth;
    int m_cellHeight;
    int m_cellHorizontalPadding;
    int m_cellVerticalPadding;

    SDL_Color m_cellColor;

    SDL_Color m_OccupiedColor;
    SDL_Color m_UnoccupiedColor;

    // Will use later while making algorithm
    std::stack<Cell> m_gridStack;
    std::vector<std::pair<int,int>> m_visitedCells;

};