#include "mazes.h"

double cubeUnit = 64;
int bitsToShift  = 6;
const int mapX = 5;
const int mapY = 5;
int playerX = 96;
int playerY  = 160;
int distToScreen = 277;
const double FOV = (PI / 3);
double viewAngle = (0.5 * PI);
bool colour = false;

int gameMap[5][5] = 
{
    {1,1,1,1,1},
    {1,0,1,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1}
};


coordinates findHorizIntersection(double alpha, double beta)
{
    // printf("Inside findHorizontal function!\n");
    int IntersectX, IntersectY, yInc, xInc, gridX, gridY;
    double rayDist, correctDist, omega;
    coordinates horizontal;

    horizontal.x = 10000;
    horizontal.y = 10000;
    horizontal.dist = 100000;

    // Finding first intersect's Y co-ordinate.

    // In case we get a negative angle it should circle back.
    if (alpha < 0)
        alpha = (2*PI) - alpha;
    if (alpha > (2 * PI))
        alpha -= (2 * PI);

    if (alpha < PI && alpha > 0) // If ray is facing upwards.
    {
        // printf("Alpha is less than PI.\n");
        IntersectY = ((playerY >> bitsToShift) << bitsToShift) - 1;
        yInc = -cubeUnit; // Finding Y increment
        // printf("First Intersect Y is: %d\n", IntersectY);
        // printf("Y step is: %d\n", yInc);
    }
    else if (alpha > PI && alpha < (2 * PI)) // If ray is facing downwards.
    {
        // printf("Alpha is greater than PI.\n");
        IntersectY = ((playerY >> bitsToShift) << bitsToShift) + cubeUnit;
        yInc = cubeUnit; // Finding Y increment
        // printf("First Intersect X is: %d\n", IntersectY);
        // printf("Y step is: %d\n", yInc);
    }
    else // If ray is horizontal
    {
        printf("Alpha is about 180 or 0 0r 360.");
        return horizontal; // return Infinity.
    }
    
    // Finding first intersect's X co-ordinate.
    if (alpha < (0.5 * PI) || alpha > (1.5 * PI)) // If right.
    {
        if (alpha > PI)
            omega = (2 * PI) - alpha;
        else
            omega = alpha;
        // printf("Alpha is on the right.\n");
        if (tan(alpha) > 100)
        {
            IntersectX = playerX;
            xInc = 0;
        }
        else
        {
            IntersectX = playerX + ((double)(abs(playerY - IntersectY) / tan(omega)));
            xInc = cubeUnit / tan(omega); // Finding X increment
            // printf("First Intersect X is: %d\n", IntersectX);
            // printf("X step is: %d\n", xInc);
        }
    }
    else // If left.
    {
        if (alpha < PI)
            omega = PI - alpha;
        else
            omega = alpha - PI;

        if (tan(alpha) > 100)
        {
            IntersectX = playerX;
            xInc = 0;
        }
        else
        {
            // printf("Alpha is on the left.\n");
            IntersectX = playerX - ((double)(abs(playerY - IntersectY) / tan(omega)));
            // printf("OMega is: %f\n", omega);
            xInc = -(cubeUnit / tan(omega)); // Finding X increment
            // printf("First Intersect X is: %d\n", IntersectX);
            // printf("X step is: %d\n", xInc);
        }
    }

    // Turn unit co-ordinates to grid co-ordinates.
    gridX = IntersectX >> bitsToShift;
    gridY = IntersectY >> bitsToShift;


    // Checking for a wall.
    while ((gridX < mapX && gridX >= 0) && (gridY < mapY && gridY >= 0) && gameMap[gridY][gridX] == 0)
    {
        IntersectX += xInc;
        IntersectY += yInc;
        //printf("(Inside While)Intersect X is: %d (Inside While)Intersect Y is: %d\n", IntersectX, IntersectY);

        gridX = IntersectX >> bitsToShift;
        gridY = IntersectY >> bitsToShift;
        // printf("(Inside While)Grid X is: %d\n", gridX);
        // printf("(Inside While)Grid Y is: %d\n", gridY);
    }

    printf("Grid X is: %d Grid Y is: %d\n", gridX, gridY);

    if (gridX >= mapX || gridY >= mapY || gridX < 0 || gridY < 0)
    {
        printf("Past the map!!");
        return horizontal; // return Infinity.
    }
    
    // Finding actual ray distance
    rayDist = sqrt(pow((playerX - IntersectX), 2) + pow((playerY - IntersectY), 2));
    //rayDist = abs(playerX - IntersectX) / cos(omega);
    correctDist = rayDist * cos(beta);

    //printf("Ray length is %f\n", rayDist);
    printf("Corrected ray length is %f\n", correctDist);

    horizontal.x = IntersectX;
    horizontal.y = IntersectY;
    horizontal.dist = (int)(correctDist);

    return horizontal;
}

double getBeta(double alpha)
{
    double beta = alpha - viewAngle;
    printf("Beta is %f\n", beta);
    return beta;
}


coordinates getWallHeight(double alpha)
{
    // printf("Inside getWallHeight func!\n");
    int projectedHeight;
    double actualDist;
    coordinates correct;

    double beta = getBeta(alpha);
    coordinates horizontal = findHorizIntersection(alpha, beta);
    coordinates vertical = findVertiIntersection(alpha, beta);
    int horiz = horizontal.dist;
    int verti = vertical.dist;
    printf("Horizontal dist is: %d Vertical dist is: %d\n and Alpha is %f\n", horiz, verti, alpha);

    if (horiz >= verti)
    {
        actualDist = (double)(verti);
        colour = false;
        correct = vertical;
    }
    else
    {
        actualDist = (double)(horiz);
        colour = true;
        correct = horizontal;
    }

    // printf("Final Distance is: %f\n", actualDist);

    projectedHeight = (int)(((double)(cubeUnit) / actualDist) * 256); // Bitshifting (256) instead of multiplying with 277.

    printf("Projected height is: %d\n", projectedHeight);

    correct.dist = projectedHeight;
    return correct;
}

void moveForward(double viewAlpha, bool forward)
{
    int xStep, yStep, newX, newY, gridX, gridY;
    double viewOmega;

    newX = playerX;
    newY = playerY;

    if (viewAlpha < 0)
        viewAlpha += (2*PI);
    if (viewAlpha > (2 * PI))
        viewAlpha -= (2 * PI);

    if (viewAlpha > (PI / 2) && viewAlpha <= PI)
        viewOmega = PI - viewAlpha;
    else if (viewAlpha > PI && viewAlpha <= (1.5 * PI))
        viewOmega = viewAlpha - PI;
    else if (viewAlpha > (1.5 * PI) && viewAlpha <= (2 * PI))
        viewOmega = (2 * PI) - viewAlpha;
    else
        viewOmega = viewAlpha;
    

    xStep = abs((int)(cos(viewOmega) * 10.0));
    yStep = abs((int)(sin(viewOmega) * 10.0));

    if (forward)
    {
        if (viewAlpha <= PI) 
            newY -= yStep;
        else
            newY += yStep;

        if (viewAlpha <= (PI /2) || viewAlpha >= (PI * 1.5))
            newX += xStep;
        else
            newX -= xStep;     
    }
    else
    {
        if (viewAlpha <= PI)
            newY += yStep;
        else
            newY -= yStep;

        if (viewAlpha <= (PI /2) || viewAlpha >= (PI * 1.5))
            newX -= xStep;
        else
            newX += xStep; 
    }


    // Handling collision.
    gridX = newX >> bitsToShift;
    gridY = newY >> bitsToShift;

    if (gameMap[gridY][gridX] == 0)
    {
        playerX = newX;
        playerY = newY;
    }
}


void moveSideWays(double viewAlpha, bool right)
{
    int xStep, yStep, newX, newY, gridX, gridY;
    double moveOmega;

    newX = playerX;
    newY = playerY;

    if (viewAlpha < 0)
        viewAlpha += (2*PI);
    if (viewAlpha > (2 * PI))
        viewAlpha -= (2 * PI);

    if (viewAlpha < (PI / 2) && viewAlpha != 0)
        moveOmega = (PI /2) - viewAlpha;
    else if (viewAlpha > (PI /2) && viewAlpha < PI)
        moveOmega = viewAlpha - (PI / 2);
    else if (viewAlpha > PI && viewAlpha < (1.5 * PI))
        moveOmega = viewAlpha - PI;
    else if (viewAlpha > (1.5 * PI) && viewAlpha != (2 * PI))
        moveOmega = viewAlpha - (1.5 * PI);
    else
        moveOmega = viewAlpha;



    xStep = abs((int)(cos(moveOmega) * 5.0));
    yStep = abs((int)(sin(moveOmega) * 5.0));

    if (right)
    {
        if (viewAlpha == (PI / 2))
            newX += 5;
        else if (viewAlpha == (1.5 * PI))
            newX -= 5;
        else if (viewAlpha == 0 || viewAlpha == (2 * PI))
            newY += 5;
        else if (viewAlpha == PI)
            newY -= 5;
        else if (viewAlpha < PI)
            newX += xStep;
        else
            newX -= xStep;

        if (viewAlpha != 0 && viewAlpha != (2 * PI) && (viewAlpha < (PI / 2) || viewAlpha > (PI * 1.5)))
            newY += yStep;
        else if (viewAlpha != PI && viewAlpha > (PI / 2) && viewAlpha < (PI * 1.5) && xStep != 0)
            newY -= (yStep * 8);
    }
    else
    {
        if (viewAlpha == (PI / 2))
            newX -= 5;
        else if (viewAlpha == (1.5 * PI) || xStep == 0)
            newX += 5;
        else if (viewAlpha == 0 || viewAlpha == (2 * PI))
            newY -= 5;
        else if (viewAlpha == PI)
            newY += 5;
        else if (viewAlpha < PI)
            newX -= xStep;
        else
            newX += xStep;

        if (viewAlpha != 0 && viewAlpha != (2 * PI) && (viewAlpha < (PI / 2) || viewAlpha > (PI * 1.5)))
            newY -= yStep;
        else if (viewAlpha != PI && viewAlpha > (PI / 2) && viewAlpha < (PI * 1.5) && xStep != 0)
            newY += (yStep * 8);
    }


    // Handling collision.
    gridX = newX >> bitsToShift;
    gridY = newY >> bitsToShift;

    if (gameMap[gridY][gridX] == 0)
    {
        playerX = newX;
        playerY = newY;
    }
}

