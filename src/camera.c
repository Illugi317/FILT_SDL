#include <stdio.h>
#include <stdbool.h>
#include <camera.h>
#include <grid.h>


void camera_init(Camera *camera, int width, int height)
{
    camera->rect.x = 500;
    camera->rect.y = 500;
    camera->rect.w = width;
    camera->rect.h = height;
    camera->vel_x = 0;
    camera->vel_y = 0;
}
void camera_handle_event(SDL_Event *e, Camera *camera)
{
    //If a key was pressed
	if( e->type == SDL_KEYDOWN && e->key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e->key.keysym.sym )
        {
            case SDLK_UP: camera->vel_y -= CAMERA_SPEED; printf("PRESSING UP\n"); break;
            case SDLK_DOWN: camera->vel_y += CAMERA_SPEED; printf("PRESSING DOWN\n"); break;
            case SDLK_LEFT: camera->vel_x -= CAMERA_SPEED; printf("PRESSING LEFT\n"); break;
            case SDLK_RIGHT: camera->vel_x += CAMERA_SPEED; printf("PRESSING RIGHT\n"); break;
        }
    }
    //If a key was released
    else if( e->type == SDL_KEYUP && e->key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e->key.keysym.sym )
        {
            case SDLK_UP: camera->vel_y += CAMERA_SPEED; printf("RELEASING UP\n"); break;
            case SDLK_DOWN: camera->vel_y -= CAMERA_SPEED; printf("RELEASING DOWN\n"); break;
            case SDLK_LEFT: camera->vel_x += CAMERA_SPEED; printf("RELEASING LEFT\n"); break;
            case SDLK_RIGHT: camera->vel_x -= CAMERA_SPEED; printf("RELEASING RIGHT\n"); break;
        }
    }
}

void camera_move(Camera *camera)
{
    //Move the camera left or right
    camera->rect.x += camera->vel_x;
    //If the camera went too far to the left or right
    if( ( camera->rect.x < 0 ) || ( camera->rect.x + camera->rect.w > 1000 ) )
    {
        //move back
        camera->rect.x -= camera->vel_x;
    }
    //Move the camera up or down
    camera->rect.y += camera->vel_y;
    //If the camera went too far up or down
    if( ( camera->rect.y < 0 ) || ( camera->rect.y + camera->rect.h > 1000 ) )
    {
        //move back
        camera->rect.y -= camera->vel_y;
    }
}
void camera_render(Camera *camera, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    //SDL_SetRenderTarget(renderer, &camera->rect);
    SDL_RenderDrawRect(renderer, &camera->rect);
}

void camera_debug(Camera *camera)
{
    printf("Camera: x: %d, y: %d, w: %d, h: %d, vel_x: %d, vel_y: %d\n", camera->rect.x, camera->rect.y, camera->rect.w, camera->rect.h, camera->vel_x, camera->vel_y);
}
