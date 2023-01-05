
#include <game.h>

bool Game_init(SDL_Renderer *renderer, int width, int height)
{
    Grid grid = {0};

    int margin = -1;
    grid.rect.w = MIN(width - margin * 2, height - margin * 2);
    grid.rect.h = grid.rect.w;
    printf("grid.rect.w = %d", grid.rect.w);

    grid.background_color = (SDL_Color){0, 0, 0, 255};
    
    grid.border = 1;
    grid.border_color = (SDL_Color){255, 255, 255, 255};

    grid.x_cells = 100;
    grid.y_cells = 100;

    grid.cellsBorder = 1;
    grid.cellsBorderColor = (SDL_Color){255, 255, 255, 255};

    Grid_ajustSize(&grid);
    Grid_align(&grid, width, height);
    if(!Grid_init(&grid))
    {
        fprintf(stderr, "Error: Grid_init() failed!\n");
        return false;
    }

    FPSmanager fpsManager;
    SDL_initFramerate(&fpsManager);
    SDL_setFramerate(&fpsManager, 30);

    bool quit = false;

    while(!quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, COLOR_BREAKUP(grid.background_color));
        SDL_RenderClear(renderer);

        Grid_render(&grid, renderer);

        SDL_RenderPresent(renderer);

        SDL_framerateDelay(&fpsManager);
    }

    return true;

}