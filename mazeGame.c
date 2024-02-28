#include "newMaze.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* imageTexture = NULL;
bool instructions = true;

int gameMap[mapHeight][mapWidth] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1},
  {1,0,1,1,0,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,0,1,1,0,0,1},
  {1,0,0,0,0,0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,1,0,0,0,0,1,0,1,1},
  {1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,0,0,1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,1},
  {1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1},
  {1,0,0,1,0,0,1,1,1,0,1,0,0,0,1,0,1,0,1,3,0,0,0,0,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,1,0,1,0,1,0,1,0,1,1},
  {1,1,0,1,0,1,1,0,0,0,1,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1},
  {1,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,1,1},
  {1,1,0,1,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,1,0,1,1,0,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1},
  {1,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,1},
  {1,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1},
  {1,1,0,1,0,1,0,1,1,1,0,1,0,0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1},
  {1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0,1,1},
  {1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1},
  {1,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,1,1,0,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,0,0,0,0,1,1},
  {1,1,0,1,1,0,1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1},
  {1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1},
  {1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1},
  {1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,1,0,1,0,1},
  {1,1,0,1,0,1,0,1,0,0,0,1,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,0,1,1,0,1,0,1},
  {1,1,0,1,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1},
  {1,1,0,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
  {1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1},
  {1,9,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double playerX = 58, playerY = 1;
double dirX = -1, dirY = 0; // direction vector initially goes left.
double planeX = 0, planeY = 0.66; // plane vector perpendicular to direction vector.

// For fps counter.
double time = 0, oldTime = 0;

movePlayer player = {0, 0, 0};


vector getRayDir(double xOnScreen)
{
    vector rayDir;
    // position (fraction) of the x co-ordinate on the camera plane.
    double cameraX = ((2 * xOnScreen) / (double)(screenWidth)) - 1;
    //pow X component of the ray vector.
    double rayDirX = dirX + ((planeX * cameraX));
    // Y component of the ray vector.
    double rayDirY = dirY + (planeY * cameraX); // Y component of the ray vector.

    rayDir.x = rayDirX;
    rayDir.y = rayDirY;

    return rayDir;
}

double checkWall(vector rayDir)
{
    // length of the ray depending on whether we are moving along the x or y axis.
    double sideDistX;
    double sideDistY;

    // steps through the grid.
    int stepX;
    int stepY;

    // Which side are we moving along
    int side;

    // the correct distance to avoid fisheye.
    double perpWallDist;

    // which grid coordinate we are in.
    int mapX = playerX;
    int mapY = playerY;

    double rayDirX = rayDir.x;
    double rayDirY = rayDir.y;

    double absX = (rayDirX < 0) ? rayDirX * - 1 : rayDirX;
    double absY = (rayDirY < 0) ? rayDirY * - 1 : rayDirY;
    // the length change of the ray per unit change in X or Y axis.
    double deltaDistX = (1 / absX);
    double deltaDistY = (1 / absY);

    int hit = 0;

    // Finding the first x or y intersect and defining the step unit increment.
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
            SDL_SetRenderDrawColor(renderer, 220,220,220,255);
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0; // meaning hit a vertical line i.e followed x axis.
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 169,169,169,255);
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1; // hit a horizontal line.
        }

        // Checking for a hit.
        if (gameMap[mapY][mapX] > 0)
            hit = 1;
    }

    if (hit)
    {
        if (side == 0)
            perpWallDist = sideDistX - deltaDistX;
        else
            perpWallDist = sideDistY - deltaDistY;
    }
    else
    {
        printf("Error! No hit!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        exit(EXIT_FAILURE);
    }

    return perpWallDist;
}

void drawWall()
{
    vector ray;
    double rayLen;
    int lineHeight;

    for (int x = 0; x < screenWidth; x++)
    {
        ray = getRayDir(x);
        rayLen = checkWall(ray);

        lineHeight = (double)(screenHeight) / rayLen;

        int drawStart = -(lineHeight / 2) + (screenHeight / 2);
        if (drawStart < 0) drawStart = 0;
        int drawEnd = (lineHeight / 2) + (screenHeight / 2);
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);

    }
}

