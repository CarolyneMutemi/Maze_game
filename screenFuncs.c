#include "newMaze.h"

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error while initializing SDL! SDL_Error: %s\n", SDL_GetError());
        return false;
	}

	window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
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
    SDL_Rect upperRect = { 0, 0, screenWidth, screenHeight / 2 };
    SDL_SetRenderDrawColor(renderer, 119, 136, 153, 255); // red
    SDL_RenderFillRect(renderer, &upperRect);

    // Draw lower part (green)
    SDL_Rect lowerRect = { 0, screenHeight / 2, screenWidth, screenHeight / 2 };
    SDL_SetRenderDrawColor(renderer, 178, 190, 181, 255); // green
    SDL_RenderFillRect(renderer, &lowerRect);
}

SDL_Texture* loadTexture(const char *path)
{
    // The final texture.
    SDL_Texture *newTexture = NULL;

    // Load the image at the given path.
    SDL_Surface *loadedSurface = IMG_Load(path);

    if (!loadedSurface)
    {
        printf("Failed to load the image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    else
    {
        // Create texture from surface.
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!newTexture)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path,SDL_GetError());
        }

        // Free the converted surface.
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool loadMedia()
{
    // Loading success flag.
    bool success = true;

    // Load PNG texture
    imageTexture = loadTexture("mazeInstructions.png");
    if (!imageTexture)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

    return success;
}
