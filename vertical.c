#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "mazes.h"

coordinates findVertiIntersection(double alpha, double beta)
{
    int IntersectX, IntersectY, yInc, xInc, gridX, gridY;
    double rayDist, correctDist, omega;
    coordinates vertical;

    vertical.x = 10000;
    vertical.y = 10000;
    vertical.dist = 100000;

    // In case we get a negative angle it should circle back.
    if (alpha < 0)
        alpha = (2*PI) - alpha;
    if (alpha > (2 * PI))
        alpha -= (2 * PI);

    // First find omega for smooth trigonometry.
    if (alpha < PI && alpha > (PI /2))
        omega = PI - alpha;
    else if (alpha > PI && alpha < (1.5 * PI))
        omega = alpha - PI;
    else if (alpha > (PI * 1.5))
        omega = (2 * PI) - alpha;
    else
        omega = alpha;


    // Finding first intersect's X co-ordinate.
    if (alpha == (0.5 * PI) || alpha == (1.5 * PI) || tan(alpha) > 100) // when vertical it won't hit any vertical line.
    {
        printf("it's vertical");
        return vertical; // return a very big number.
    }

    // Finding first X co-ordinate!!
    if (alpha < (0.5 * PI) || alpha > (1.5 * PI))
    {
        IntersectX = ((playerX >> bitsToShift) << bitsToShift) + cubeUnit;
        xInc = cubeUnit;
    }
    else
    {
        IntersectX = ((playerX >> bitsToShift) << bitsToShift) - 1;
        xInc = -cubeUnit;
    }

    // Finding first Y co-ordinate!!
    if (alpha < PI) // facing up
    {
        IntersectY = playerY - ((double)(abs(playerX - IntersectX)) * tan(omega));
        yInc = -(cubeUnit * tan(omega));
    }
    else if (alpha > PI) // Facing down.
    {
        IntersectY = playerY + ((double)(abs(playerX - IntersectX)) * tan(omega));
        yInc = cubeUnit * tan(omega);
    }
    else // It's horizontal
    {
        IntersectY = playerY;
        yInc = 0;
    }

    // Turn unit co-ordinates to grid co-ordinates.
    gridX = IntersectX >> bitsToShift;
    gridY = IntersectY >> bitsToShift;

    // Checking for a wall.
    while ((gridX < mapX && gridX >= 0) && (gridY < mapY && gridY >= 0) && gameMap[gridY][gridX] == 0)
    {
        IntersectX += xInc;
        IntersectY += yInc;
        // printf("(Inside While)Intersect X is: %d\n", IntersectX);
        // printf("(Inside While)Intersect Y is: %d\n", IntersectY);

        gridX = IntersectX >> bitsToShift;
        gridY = IntersectY >> bitsToShift;
        // printf("(Inside While)Grid X is: %d\n", gridX);
        // printf("(Inside While)Grid Y is: %d\n", gridY);
    }

    if (gridX >= mapX || gridY >= mapY || gridX < 0 || gridY < 0)
    {
        printf("Past the map!!");
        return vertical; // return Infinity.
    }

    // Finding actual ray distance
    rayDist = sqrt(pow((playerX - IntersectX), 2) + pow((playerY - IntersectY), 2));
    //rayDist = abs(playerX - IntersectX) / cos(omega);
    correctDist = rayDist * cos(beta);

    //printf("Ray length is %f\n", rayDist);
    //printf("Corrected ray length is %f\n", correctDist);

    vertical.x = IntersectX;
    vertical.y = IntersectY;
    vertical.dist = (int)(correctDist);

    return vertical;
}