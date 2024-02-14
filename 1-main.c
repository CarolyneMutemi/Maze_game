#include "mazes.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main()
{
	SDL_Event e;
	bool quit = false;
	// int keys[256] = {0};
	// const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (!init())
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    	SDL_RenderClear(renderer);

		drawUpperLower();
		drawWalls();
		rotate(e);

		SDL_RenderPresent(renderer);

		SDL_Delay(10000);*/

		while( quit == false )
		{
			while( SDL_PollEvent( &e ) )
			{
				if( e.type == SDL_QUIT )
					quit = true;
				else
				{
					rotateAndMove(e);
				}
            }

			// Clear the screen
    		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    		SDL_RenderClear(renderer);

			drawUpperLower();
			drawWalls();
			//printf("ViewAngle is %f\n", viewAngle);

			SDL_RenderPresent(renderer);

		}
	}

	closeDown();
}
