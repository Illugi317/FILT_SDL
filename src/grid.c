#include <grid.h>

bool Grid_ajustSize(Grid *grid)
{
    if(!grid->rect.w || !grid->rect.h || !grid->x_cells || !grid->y_cells)
    {
        fprintf(stderr, "Grid dimensions or number of cells not initialised !\n");
        return false;
    }

    // Init rect
    int interspaceWidth = grid->x_cells * grid->cellsBorder * 2;
    grid->rect.w -= (grid->rect.w - (grid->border * 2) - interspaceWidth) % grid->x_cells;

    int interspaceHeigth = grid->y_cells * grid->cellsBorder * 2;
    grid->rect.h -= (grid->rect.h - (grid->border * 2) - interspaceHeigth) % grid->y_cells;

    return true;
}
void Grid_align(Grid *grid, int screen_width, int screen_height)
{
    grid->rect.x = (screen_width - grid->rect.w) / 2;
    grid->rect.y = (screen_height - grid->rect.h) / 2;
}

SDL_Color random_color()
{
    SDL_Color color;
    color.r = rand() % 255;
    color.g = rand() % 255;
    color.b = rand() % 255;
    color.a = 255;
    return color;
}

bool Grid_init(Grid *grid)
{
    if(!grid->rect.w || !grid->rect.h || !grid->x_cells || !grid->y_cells)
    {
        fprintf(stderr, "Grid dimensions or number of cells not initialised !\n");
        return false;
    }
    if(grid->x_cells > GRID_MAX_X || grid->y_cells > GRID_MAX_Y)
    {
        fprintf(stderr, "Grid number of cells (%d,%d) is greater than (%d,%d) !\n",
                grid->x_cells, grid->y_cells,
                GRID_MAX_X, GRID_MAX_Y);
        return false;
    }
    //init all the cells
    for(int i = 0; i < grid->x_cells; i++)
    {
        for(int j = 0; j < grid->y_cells; j++)
        {

            Grid_initCell(grid, &grid->cells[i][j], i, j,  random_color(), grid->cellsBorderColor);
        }
    }
    return true;
}


void Grid_initCell(Grid *grid, Cell *cell, int i, int j, SDL_Color color, SDL_Color bordercolor)
{
    // Init rect
    int interspaceWidth = grid->x_cells * grid->cellsBorder * 2;
    cell->rect.w = (grid->rect.w - (grid->border * 2) - interspaceWidth) / grid->x_cells;

    int interspaceHeigth = grid->y_cells * grid->cellsBorder * 2;
    cell->rect.h = (grid->rect.h - (grid->border * 2) - interspaceHeigth) / grid->x_cells;

    cell->rect.x = grid->rect.x + grid->border + grid->cellsBorder + (grid->cellsBorder * 2 + cell->rect.w) * i;
    cell->rect.y = grid->rect.y + grid->border + grid->cellsBorder + (grid->cellsBorder * 2 + cell->rect.h) * j;

    // Init rectColor
    cell->rect_color = color;

    // Init border
    cell->border.w = cell->rect.w + grid->cellsBorder * 2;
    cell->border.h = cell->rect.h + grid->cellsBorder * 2;
    cell->border.x = cell->rect.x - grid->cellsBorder;
    cell->border.y = cell->rect.y - grid->cellsBorder;

    // Init borderColor
    cell->border_color = bordercolor;
}

void Grid_render(Grid *grid, SDL_Renderer *renderer)
{
    if(grid->border != 0)
    {
        SDL_SetRenderDrawColor(renderer, grid->border_color.r, grid->border_color.g, grid->border_color.b, grid->border_color.a);
        SDL_RenderFillRect(renderer, &grid->rect);
    }

    for(int i = 0; i < grid->x_cells; i++)
    {
        for(int j = 0; j < grid->y_cells; j++)
        {
            Grid_renderCell(&grid->cells[i][j], renderer);
        }
    }
}
void Grid_renderCell(Cell *cell, SDL_Renderer *renderer)
{
    if(cell->border.x != cell->rect.x)
    {
        SDL_SetRenderDrawColor(renderer, cell->border_color.r, cell->border_color.g, cell->border_color.b, cell->border_color.a);
        SDL_RenderFillRect(renderer, &cell->border);
    }
    SDL_SetRenderDrawColor(renderer, cell->rect_color.r, cell->rect_color.g, cell->rect_color.b, cell->rect_color.a);
    SDL_RenderFillRect(renderer, &cell->rect);
}

void Grid_randomize_colors(Grid *grid)
{
    for(int i = 0; i < grid->x_cells; i++)
    {
        for(int j = 0; j < grid->y_cells; j++)
        {
            grid->cells[i][j].rect_color = random_color();
        }
    }
}