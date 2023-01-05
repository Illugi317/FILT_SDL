
#include <game.h>
#include <camera.h>
bool Game_init(SDL_Renderer *renderer, int width, int height)
{
    Grid grid = {0};

    int margin = -1;
    grid.rect.w = MIN(width - margin * 2, height - margin * 2);
    grid.rect.h = grid.rect.w;

    grid.background_color = (SDL_Color){0, 0, 0, 255};
    
    grid.border = 1;
    grid.border_color = (SDL_Color){255, 255, 255, 255};

    grid.x_cells = 100;
    grid.y_cells = 100;

    grid.cellsBorder = 1;
    grid.cellsBorderColor = (SDL_Color){255, 255, 255, 255};
    //SDL_RenderSetScale(renderer, 5, 5);
    Grid_ajustSize(&grid);
    Grid_align(&grid, width, height);

    //create camera
    Camera camera = {0};
    camera.rect.x = 240;
    camera.rect.y = 100;
    camera.rect.w = CAMERA_WIDTH;
    camera.rect.h = CAMERA_HEIGHT;
    camera.vel_x = 0;
    camera.vel_y = 0;
    //camera_init(&camera, CAMERA_WIDTH, CAMERA_HEIGHT);
    //SDL_RenderSetViewport(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    if(!Grid_init(&grid))
    {
        fprintf(stderr, "Error: Grid_init() failed!\n");
        return false;
    }

    FPSmanager fpsManager;
    SDL_initFramerate(&fpsManager);
    SDL_setFramerate(&fpsManager, 10);

    bool quit = false;

    while(!quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            // Camera handle event 
            camera_handle_event(&event, &camera);
	        //if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
            //{
            //    //Adjust the velocity
            //    switch( event.key.keysym.sym )
            //    {
            //        case SDLK_UP: camera.vel_y -= CAMERA_SPEED; break;
            //        case SDLK_DOWN: camera.vel_y += CAMERA_SPEED; break;
            //        case SDLK_LEFT: camera.vel_x -= CAMERA_SPEED; break;
            //        case SDLK_RIGHT: camera.vel_x += CAMERA_SPEED; break;
            //    }
            //}
            ////If a key was released
            //else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
            //{
            //    //Adjust the velocity
            //    switch( event.key.keysym.sym )
            //    {
            //        case SDLK_UP: camera.vel_y += CAMERA_SPEED; break;
            //        case SDLK_DOWN: camera.vel_y -= CAMERA_SPEED; break;
            //        case SDLK_LEFT: camera.vel_x += CAMERA_SPEED; break;
            //        case SDLK_RIGHT: camera.vel_x -= CAMERA_SPEED; break;
            //    }
            //}

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
        
        //camera update
        //printf("camera.vel_x: %d\n", camera.vel_x);
        //camera_debug(&camera);
        camera_move(&camera);
        
        SDL_SetRenderDrawColor(renderer, COLOR_BREAKUP(grid.background_color));
        
        SDL_RenderClear(renderer);
        
        Grid_render(&grid, renderer);
        
        //camera_render(&camera, renderer);
        
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
        SDL_RenderDrawRect(renderer, &camera.rect);


        SDL_RenderPresent(renderer);
        SDL_RenderSetViewport(renderer, &camera.rect);
        //update
        //Grid_randomize_colors(&grid);
        SDL_framerateDelay(&fpsManager);
    }

    return true;

}