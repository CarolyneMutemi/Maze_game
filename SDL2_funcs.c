#include "mazes.h"

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error while initializing SDL! SDL_Error: %s\n", SDL_GetError());
        return false;
	}

	window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenX, screenY, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Unsuccessful creating window! SDL_Error: %s\n", SDL_GetError());
        return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Error creating the renderer! SDL_Error: %s\n", SDL_GetError());
        return false;
	}
    return true;
}

void closeDown()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawUpperLower()
{
    // Draw upper part (red)
    SDL_Rect upperRect = { 0, 0, screenX, screenY / 2 };
    SDL_SetRenderDrawColor(renderer, 119, 136, 153, 255); // red
    SDL_RenderFillRect(renderer, &upperRect);

    // Draw lower part (green)
    SDL_Rect lowerRect = { 0, screenY / 2, screenX, screenY / 2 };
    SDL_SetRenderDrawColor(renderer, 178, 190, 181, 255); // green
    SDL_RenderFillRect(renderer, &lowerRect);
}

void drawWalls()
{
    double alpha;
    int y1, y2, height;
    double angleDiff = (FOV / screenX);

    alpha = viewAngle + (FOV / 2);
    for (int x = 0; x < screenX; x++)
    {
        printf("X is ----------------> %d\n", x);
        if (!colour)
		    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	    else
		    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	    height = getWallHeight(alpha).dist;
	    y1 = (screenY >> 1) - (height >> 1);
        y2 = y1 + height;

        // printf("Height is: %d at length unit: %d with alpha as %f\n", height, x, alpha);
        alpha -= angleDiff;
        SDL_RenderDrawLine(renderer, x, y1, x, y2);
    }
}

void rotateAndMove(SDL_Event event, const Uint8 *keyboard_state_array)
{
    if (event.type == SDL_KEYDOWN)
    {
        // Set the key state to pressed
        //  keys[event.key.keysym.scancode] = 1;
        if (keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_D])
        {
            moveForward(viewAngle, true);
            moveSideWays(viewAngle, true);

        }
        else if (keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_A])
        {
            moveForward(viewAngle, true);
            moveSideWays(viewAngle, false);
        }
        else if (keyboard_state_array[SDL_SCANCODE_S] && keyboard_state_array[SDL_SCANCODE_D])
        {
            moveForward(viewAngle, false);
            moveSideWays(viewAngle, true);
        }
        else if (keyboard_state_array[SDL_SCANCODE_S] && keyboard_state_array[SDL_SCANCODE_A])
        {
            moveForward(viewAngle, false);
            moveSideWays(viewAngle, false);
        }
        switch (event.key.keysym.sym)
        {
        // Rotation
        case SDLK_LEFT:
            viewAngle += 0.1745329;
            if (viewAngle > (2 * PI))
                viewAngle -= (2 * PI);
            break;
        case SDLK_RIGHT:
            viewAngle -= 0.1745329;
            if (viewAngle < 0)
                viewAngle += (2 * PI);
            break;
        // Movement
        case SDLK_w:
            moveForward(viewAngle, true);
            break;
        case SDLK_s:
            moveForward(viewAngle, false);
            break;
        case SDLK_a:
            moveSideWays(viewAngle, false);
            break;
        case SDLK_d:
            moveSideWays(viewAngle, true);
            break;
        default:
            break;
        }
    }
    /*else if(event.type == SDL_KEYUP)
    {
        // Set the key state to released
        keys[event.key.keysym.scancode] = 0;
    }

    if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_D])
    {
        moveForward(viewAngle, true);
        moveSideWays(viewAngle, true);
    }
    else if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_A])
    {
        moveForward(viewAngle, true);
        moveSideWays(viewAngle, false);
    }
    else if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_D])
    {
        moveForward(viewAngle, false);
        moveSideWays(viewAngle, true);
    }
    else if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_A])
    {
        moveForward(viewAngle, false);
        moveSideWays(viewAngle, false);
    }
    else if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_W])
    {}
    else if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D])
    {}
    else if (SDL_SCANCODE_LEFT)
    {
        viewAngle += 0.1745329;
        if (viewAngle > (2 * PI))
            viewAngle -= (2 * PI);
    }
    else if (SDL_SCANCODE_RIGHT)
    {
        viewAngle -= 0.1745329;
        if (viewAngle < 0)
            viewAngle += (2 * PI);
    }
    else if (SDL_SCANCODE_W)
    {
        moveForward(viewAngle, true);
    }
    else if (SDL_SCANCODE_S)
    {
        moveForward(viewAngle, false);
    }
    else if (SDL_SCANCODE_D)
    {
        moveSideWays(viewAngle, true);
    }
    else if (SDL_SCANCODE_A)
    {
        moveSideWays(viewAngle, false);
    }*/
}

