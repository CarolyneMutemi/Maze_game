#include "mazes.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void drawMap()
{
    int x, y;
    SDL_Rect cube;
    x = 0;
    y = 0;


    for (int yCor = 0; yCor < mapY; yCor++)
    {
        for (int xCor = 0; xCor < mapX; xCor++)
        {
            cube.x = x;
            cube.y = y;
            cube.w = cubeUnit;
            cube.h = cubeUnit;

            if (gameMap[yCor][xCor] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
                SDL_RenderDrawRect(renderer, &cube);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &cube);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
            }
            
            cube.x = x + 1;
            cube.y = y + 1;
            cube.w = cubeUnit - 1;
            cube.h = cubeUnit - 1;

            SDL_RenderFillRect(renderer, &cube);

            x += 64;
            printf("Cube.x = %d, cube.y = %d, cube.w = %d, cube.h = %d\n", cube.x, cube.y, cube.w, cube.h);
        }
        x = 0;
        y += 64;
        printf("Y %d\n", yCor);
    }
}

void drawPlayer()
{
    SDL_Rect player = {playerX - 3 , playerY - 3, 6, 6};

    SDL_RenderFillRect(renderer, &player);
}

void drawLineOfSight(coordinates wall)
{
    SDL_RenderDrawLine(renderer, playerX, playerY, wall.x, wall.y);
}


int main()
{
	SDL_Event e;
	bool quit = false;
    coordinates wall;
    // int keys[256] = {0};
    // const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

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
                else
                    rotateAndMove(e);
            }

            wall = getWallHeight(viewAngle);

			// Clear the screen
    		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    		SDL_RenderClear(renderer);

			drawMap();
            drawPlayer();
            drawLineOfSight(wall);
            printf("ViewAngle is %f\n", viewAngle);

			SDL_RenderPresent(renderer);

		}
	}

	closeDown();
}
