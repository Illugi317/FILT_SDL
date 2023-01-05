#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#define GRID_MAX_X 100
#define GRID_MAX_Y 100

struct Cell
{
    // Rect dimensions and color
    SDL_Rect rect;
    SDL_Color rect_color;

    // Border dimensions and color
    SDL_Rect border;
    SDL_Color border_color;
};
typedef struct Cell Cell;

struct Grid
{
    // x, y, width, height
    SDL_Rect rect;

    // Grid background color
    SDL_Color background_color;

    // Grid border thickness & color

    unsigned int border;
    SDL_Color border_color;

    // Number of cells over x and y axis
    int x_cells;
    int y_cells;

    unsigned int cellsBorder;
    SDL_Color cellsBorderColor;

    // Cell array
    Cell cells[GRID_MAX_X][GRID_MAX_Y];
};
typedef struct Grid Grid;

bool Grid_ajustSize(Grid *grid);
void Grid_align(Grid *grid, int screen_width, int screen_height);

SDL_Color random_color();
bool Grid_init(Grid *grid);
void Grid_initCell(Grid *grid, Cell *cell, int i, int j, SDL_Color color, SDL_Color bordercolor);

void Grid_render(Grid *grid, SDL_Renderer *renderer);
void Grid_renderCell(Cell *cell, SDL_Renderer *renderer);


#endif // GRID_H