#include "newMaze.h"


int main()
{
    SDL_Event e;
	bool quit = false;
	SDL_Rect screen = {0, 0, screenWidth, screenHeight};
	SDL_Rect map = {1440, 720, 480, 240};
	bool showMap = true;

	if (!init())
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		if (!loadMedia())
			exit(EXIT_FAILURE);

		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDL_RenderClear(renderer);

		// Render the instructions page.
		SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(8000);

		SDL_RenderClear(renderer);
		while( quit == false )
		{
			while( SDL_PollEvent( &e ) )
			{
				if( e.type == SDL_QUIT )
					quit = true;
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
				{
					if (showMap)
						showMap = false;
					else
						showMap = true;
				}
                movement(e);
            }

			move();
			// Clear the screen
    		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    		SDL_RenderClear(renderer);

			SDL_RenderSetViewport(renderer, &screen);

			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			drawUpperLower();
			drawWall();
			if (showMap)
			{
            	SDL_RenderSetViewport(renderer, &map);
            	renderMiniMap();
			}

			SDL_RenderPresent(renderer);
		}
	}

	closeDown();
}
