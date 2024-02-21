#include "newMaze.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

/*int gameMap[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/

int gameMap[mapHeight][mapWidth] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1},
  {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,0,1,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,0,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double playerX = 18, playerY = 2;
double dirX = -1, dirY = 0; // direction vector initially goes left.
double planeX = 0, planeY = 0.66; // plane vector perpendicular to direction vector.

// For fps counter.
double time = 0, oldTime = 0;

movePlayer player = {0, 0, 0};


void drawWallSlice()
{
    double cameraX, rayDirX, rayDirY;

    double fov = 2 * atan(degToRad(0.66/1.0));
    //double betaLeft = fov / 2;
    //double betaRight = 0;
    //double diffAngle = fov / screenWidth;
    double distToScreen = (screenWidth * tan(fov / 2));
    int height;
    double correctDist;
    point hit;

    // Calculating the ray position and direction.
    for (int x = 0; x < screenWidth; x++)
    {
        cameraX = ((2 * x) / (double)(screenWidth)) - 1; // position (fraction) of the x co-ordinate on the camera plane.
        rayDirX = dirX + ((planeX * cameraX)); //pow X component of the ray vecto, 2r.
        rayDirY = dirY + (planeY * cameraX); // Y component of the ray vector.

        hit = getFinalPoint(rayDirX, rayDirY);

        /*if (x < (screenWidth / 2) - 1)
        {
            correctDist = hit.distToPlayer * cos(betaLeft);
            betaLeft -= diffAngle;
        }
        else
        {
            correctDist = hit.distToPlayer * cos(betaRight);
            betaRight += diffAngle;
        }*/
        correctDist = sqrt(pow(hit.distToPlayer, 2) - pow((planeX * cameraX), 2));
        height = ((32.0) / correctDist) * distToScreen;
        int drawStart = (screenHeight >> 1) - (height >> 1);;

        int drawEnd = drawStart + height;

        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}

/*int getWallSliceHeight(point hit)
{
    double fov = 2 * atan(degToRad(0.66/1.0));
    double betaLeft = fov / 2;
    double betaRight = 0;
    double diffAngle = fov / screenWidth;
    double distToScreen = (screenWidth * tan(fov / 2));
    int height;
    double correctDist;

    for (int x = 0; x < screenWidth; x++)
    {
        if (x < (screenWidth / 2) - 1)
        {
            correctDist = hit.distToPlayer * cos(betaLeft);
            betaLeft -= diffAngle;
        }
        else
        {
            correctDist = hit.distToPlayer * cos(betaRight);
            betaRight += diffAngle;
        }
    }

    

    return height;
}*/


point getFinalPoint(double rayDirX, double rayDirY)
{
    // length of ray from player position to first intersection.
    double sideDistX, sideDistY, intX, intY;

    int stepX, stepY, hit, side;

    point intersect;
    vector normVector;

    // Grid cell we are at.
    int mapX = (int)(playerX); // truncates the playerX position.
    int mapY = (int)(playerY);

    // length of ray each step along the x or y axis.
    //double absRayDirX = (rayDirX < 0) ? rayDirX *= -1 : rayDirX;
    //double absRayDirY = (rayDirY < 0) ? rayDirY *= -1 : rayDirY;
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

    //printf("Hit is %d\n", hit);

    if (hit == 1)
    {
        normVector = normalizeVector(rayDirX, rayDirY);
        if (side == 0)
        {
            intX = playerX + normVector.x * (sideDistX - deltaDistX);
            intY = playerY + normVector.y * (sideDistX - deltaDistX);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            printf("intX: %f -----> intY: %f\n", intX, intY);
            intersect.distToPlayer = (sideDistX - deltaDistX);
            //perpWallDist = (sideDistX - deltaDistX);
        }
        else
        {
            intX = playerX + normVector.x * (sideDistY - deltaDistY);
            intY = playerY + normVector.y * (sideDistY - deltaDistY);
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            printf("intX: %f -----> intY: %f\n", intX, intY);
            intersect.distToPlayer = (sideDistY - deltaDistY);
            //perpWallDist = (sideDistY - deltaDistY);
        }
    }
    else
        printf("No hit!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

    // Getting height of a wall slice.
    //int lineHeight = (int)(screenHeight) / perpWallDist;
    //printf("perpWallDist is %d\n", perpWallDist);
    //return lineHeight;

    intersect.x = intX;
    intersect.y = intY;
    return intersect;
}


double degToRad(double degree)
{
    double pi = 3.14159265359;
    if (degree > 306)
        degree -= 360 ;
    else if (degree < 0)
        degree += 360;
    
    return (degree * (pi / 180));
}


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

void movement(SDL_Event event)
{
    player.moveSpeed = 0;
    player.rotSpeed = 0;
    // printf("Move speed id %f\n", moveSpeed);

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        // Rotation
        case SDLK_LEFT:
            player.rotSpeed += degToRad(5.0);
            break;
        case SDLK_RIGHT:
            player.rotSpeed -= degToRad(5.0);
            break;
        // Movement
        case SDLK_UP:
            player.moveSpeed += 0.5;
            player.forward = 1;
            break;
        case SDLK_DOWN:
            player.moveSpeed -= 0.5;
            player.forward = 0;
            break;
        default:
            break;
        }
    }
    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        // Rotation
        case SDLK_LEFT:
            player.rotSpeed -= 0;
            break;
        case SDLK_RIGHT:
            player.rotSpeed += 0;
            break;
        // Movement
        case SDLK_UP:
            player.moveSpeed += 0;
            break;
        case SDLK_DOWN:
            player.moveSpeed -= 0;
            break;
        default:
            break;
        }
    }
}

void moveForward()
{
    //if (player.forward == 1)
    //{
        if (player.moveSpeed != 0)
        {
            if (player.forward == 1)
            {
                if (gameMap[(int)(playerY)][(int)(playerX + (dirX * (player.moveSpeed + 1)))] == 0)
                    playerX += (dirX * player.moveSpeed);
                if (gameMap[(int)(playerY + (dirY * (player.moveSpeed + 1)))][(int)(playerX)] == 0)
                    playerY += (dirY * player.moveSpeed);
            }
            else
            {
                if (gameMap[(int)(playerY)][(int)(playerX + (dirX * (player.moveSpeed - 1)))] == 0)
                    playerX += (dirX * player.moveSpeed);
                if (gameMap[(int)(playerY + (dirY * (player.moveSpeed - 1)))][(int)(playerX)] == 0)
                    playerY += (dirY * player.moveSpeed);
            }
        }
    /*}
    else if (player.forward == 2)
    {
        if (gameMap[(int)(playerY)][(int)(playerX - (dirX * player.moveSpeed))] == 0)
            playerX -= (dirX * player.moveSpeed);
        if (gameMap[(int)(playerY - (dirY * player.moveSpeed))][(int)(playerX)] == 0)
            playerY -= (dirY * player.moveSpeed);
    }*/
}


void moveSideWays()
{
    // Use the rotation matrix.

    /*if (right)
    {
        // First rotate the direction vector.
        double oldDirX = dirX;
        dirX = (dirX * cos(player.rotSpeed)) - (dirY * sin(player.rotSpeed)); // -ve player.rotSpeed is because it's rotation to the right.
        dirY = (oldDirX * sin(-player.rotSpeed)) + (dirY * cos(player.rotSpeed));

        // Rotating the plane.
        double oldPlaneX = planeX;
        planeX = (planeX * cos(-player.rotSpeed)) - (planeY * sin(-player.rotSpeed));
        planeY = (oldPlaneX * sin(-player.rotSpeed)) + (planeY * cos(-player.rotSpeed));
    }
    else
    {*/
        // First rotate the direction vector.
        if (player.rotSpeed != 0)
        {
        double oldDirX = dirX;
        dirX = (dirX * cos(player.rotSpeed)) - (dirY * sin(player.rotSpeed)); // -ve player.rotSpeed is because it's rotation to the right.
        dirY = (oldDirX * sin(player.rotSpeed)) + (dirY * cos(player.rotSpeed));
        
        // Rotating the plane.
        double oldPlaneX = planeX;
        planeX = (planeX * cos(player.rotSpeed)) - (planeY * sin(player.rotSpeed));
        planeY = (oldPlaneX * sin(player.rotSpeed)) + (planeY * cos(player.rotSpeed));
        }
    //}
}


vector normalizeVector(double rayDirX, double rayDirY)
{
    double c = sqrt(pow(rayDirX, 2) + pow(rayDirY, 2));
    vector unit = {(rayDirX / c), (rayDirY / c)};

    return unit;
}
