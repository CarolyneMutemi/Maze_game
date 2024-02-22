#include "newMaze.h"

void movement(SDL_Event event)
{
    player.moveSpeed = 0;
    player.rotSpeed = 0;

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        // Rotation
        case SDLK_LEFT:
            player.rotSpeed += degToRad(0.5);
            break;
        case SDLK_RIGHT:
            player.rotSpeed -= degToRad(0.5);
            break;
        // Movement
        case SDLK_UP:
            player.moveSpeed += 0.05;
            player.forward = 1;
            break;
        case SDLK_DOWN:
            player.moveSpeed -= 0.05;
            player.forward = 0;
            break;
        default:
            break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        // Rotation
        case SDLK_LEFT:
            player.rotSpeed = 0;
            break;
        case SDLK_RIGHT:
            player.rotSpeed = 0;
            break;
        // Movement
        case SDLK_UP:
            player.moveSpeed = 0;
            break;
        case SDLK_DOWN:
            player.moveSpeed = 0;
            break;
        default:
            break;
        }
    }
}

void moveForward()
{
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
}


void moveSideWays()
{
    // Use the rotation matrix.
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
}

void move()
{
    if (player.moveSpeed)
        moveForward();
    if (player.rotSpeed)
        moveSideWays();
}