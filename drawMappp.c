#include "newMaze.h"

int cubeUnit = 32;

void drawMap()
{
    int x, y;
    SDL_Rect cube;
    x = 0;
    y = 0;


    for (int yCor = 0; yCor < mapHeight; yCor++)
    {
        for (int xCor = 0; xCor < mapWidth; xCor++)
        {
            cube.x = x;
            cube.y = y;
            cube.w = cubeUnit;
            cube.h = cubeUnit;

            if (gameMap[yCor][xCor] != 0)
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

            x += cubeUnit;
            // printf("Cube.x = %d, cube.y = %d, cube.w = %d, cube.h = %d\n", cube.x, cube.y, cube.w, cube.h);
        }
        x = 0;
        y += cubeUnit;
        // printf("Y %d\n", yCor);
    }
}

void drawPlayer()
{
    SDL_Rect player = {(cubeUnit * playerX) - 3 , (cubeUnit * playerY) - 3, 6, 6};

    SDL_RenderFillRect(renderer, &player);
}

void drawLineOfSight()
{
    double cameraX, rayDirX, rayDirY;
    point intersect;

    for (int x = 0; x < screenWidth; x++)
    {
        cameraX = ((2 * x) / (double)(screenWidth)) - 1; // position (fraction) of the x co-ordinate on the camera plane.
        rayDirX = dirX + (planeX * cameraX); // X component of the ray vector.
        rayDirY = dirY + (planeY * cameraX); // Y component of the ray vector.

        intersect = getFinalPoint(rayDirX, rayDirY);
        SDL_RenderDrawLine(renderer, (playerX * cubeUnit), (playerY * cubeUnit), (intersect.x * cubeUnit), (intersect.y * cubeUnit));
    }
}

int main()
{
	SDL_Event e;
	bool quit = false;
    // coordinates wall;
    // int keys[256] = {0};
    //const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

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

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    		SDL_RenderClear(renderer);

			drawMap();
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawPlayer();
            drawLineOfSight();
            //printf("PlayerX: %d PlayerY: %d\n", playerX, playerY);
            SDL_RenderPresent(renderer);

		}
	}

	closeDown();
}
