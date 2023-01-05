/*
	Filt game thingy (hopefully)
	by: Illugi git@illugi317
*/

// Includes
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <game.h>

// Defines

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

int main(int argc, char *argv[])
{
	// Unused argc, argv
	(void)argc;
	(void)argv;


    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not be initialized!\n"
                        "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

	// Create window
	SDL_Window *window = SDL_CreateWindow("Filt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL)
	{
		fprintf(stderr, "Window could not be created!\n"
						"SDL_Error: %s\n", SDL_GetError());
		return 0;
	}
	else
	{
		// Create renderer
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			fprintf(stderr, "Renderer could not be created!\n"
							"SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Game loop starts here
			Game_init(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			//gamestart
			SDL_DestroyRenderer(renderer);
		}

		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return 0;
}