#include "newMaze.h"


int main()
{
    SDL_Event e;
	bool quit = false;

	if (!init())
	{
		exit(EXIT_FAILURE);
	}
	else
	{

		while( quit == false )
		{
			while( SDL_PollEvent( &e ) )
			{
				if( e.type == SDL_QUIT )
					quit = true;
                movement(e);
            }

			moveSideWays();
			moveForward();
			// Clear the screen
    		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    		SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			drawUpperLower();
			drawWallSlice();

			SDL_RenderPresent(renderer);
		}
	}

	closeDown();
}
