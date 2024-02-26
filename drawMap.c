#include "newMaze.h"

int cubeUnit = 8;

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

point getFinalPoint(double rayDirX, double rayDirY)
{
    // length of ray from player position to first intersection.
    double sideDistX, sideDistY, intX, intY;

    int stepX, stepY, hit, side;

    point intersect;
    vector normVector;

    // Grid cell we are at.
    int mapX = playerX; // truncates the playerX position.
    int mapY = playerY;

    // length of ray each step along the x or y axis.
    double deltaDistX = (rayDirX == 0) ? INFINITY : sqrt(1 + ((rayDirY * rayDirY)/(rayDirX*rayDirX)));
    double deltaDistY = (rayDirY == 0) ? INFINITY : sqrt(1 + ((rayDirX * rayDirX)/(rayDirY*rayDirY)));

    hit = 0; // zero if collision has not occurred, else 1.

    // getting first distance and steps.
    if (rayDirX < 0)
    {
        stepX = -1; // left side.
        sideDistX = (playerX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1; // right side.
        sideDistX = ((mapX + 1.0) - playerX) * deltaDistX;
    }

    if (rayDirY < 0)
    {
        stepY = -1; // upwards.
        sideDistY = (playerY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1; // downwards.
        sideDistY = ((mapY + 1.0) - playerY) * deltaDistY;
    }

    // Check for a hit.
    while (hit == 0 && (mapX + 1) < mapWidth && (mapY + 1) < mapHeight && (mapX - 1) >= 0 && (mapY - 1) >= 0)
    {
        // choosing which axis intersection to follow - x or y.
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0; // meaning hit a vertical line i.e followed x axis.
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1; // hit a horizontal line.
        }

        // Checking for a hit.
        if (gameMap[mapY][mapX] > 0)
            hit = 1;
    }

    if (hit == 1)
    {
        normVector = normalizeVector(rayDirX, rayDirY);
        if (side == 0)
        {
            intX = playerX + normVector.x * (sideDistX - deltaDistX);
            intY = playerY + normVector.y * (sideDistX - deltaDistX);
        }
        else
        {
            intX = playerX + normVector.x * (sideDistY - deltaDistY);
            intY = playerY + normVector.y * (sideDistY - deltaDistY);
        }
    }
    else
        printf("No hit!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

    intersect.x = intX;
    intersect.y = intY;
    return intersect;
}

void drawLineOfSight()
{
    double rayDirX, rayDirY;
    point intersect;
    vector ray;

    for (int x = 0; x < screenWidth; x++)
    {
    ray = getRayDir(x);
    rayDirX = ray.x;
    rayDirY = ray.y;

    intersect = getFinalPoint(rayDirX, rayDirY);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, (playerX * cubeUnit), (playerY * cubeUnit), (intersect.x * cubeUnit), (intersect.y * cubeUnit));
    }
}

void renderMiniMap()
{
    drawMap();
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    drawPlayer();
    drawLineOfSight();
}
