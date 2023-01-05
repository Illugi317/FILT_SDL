#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#define CAMERA_WIDTH 200
#define CAMERA_HEIGHT 200 

static const int CAMERA_SPEED = 10;

struct Camera
{
    SDL_Rect rect;
    int vel_x;
    int vel_y;
};
typedef struct Camera Camera;

void camera_init(Camera *camera, int x, int y);
void camera_handle_event(SDL_Event *e, Camera *camera);
void camera_move(Camera *camera);
void camera_render(Camera *camera, SDL_Renderer *renderer);
void camera_debug(Camera *camera);
#endif