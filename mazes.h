#ifndef MAZE_H
#define MAZE_H
#define PI 3.14159
#define screenX  320
#define screenY  320

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

extern double cubeUnit;
extern int bitsToShift;
extern int playerX, playerY, distToScreen;
extern const int mapX, mapY;
extern const double FOV;
extern double viewAngle;
extern int gameMap[5][5];
extern bool colour;
extern SDL_Window* window;
extern SDL_Renderer* renderer;

typedef struct coordinates {
    int x;
    int y;
    int dist;
} coordinates;

coordinates findHorizIntersection(double alpha, double beta);
coordinates findVertiIntersection(double alpha, double beta);
coordinates getWallHeight(double alpha);
double getBeta(double alpha);
bool init();
void closeDown();
void drawUpperLower();
void drawWalls();
void rotateAndMove(SDL_Event event);
void moveForward(double viewAlpha, bool forward);
void moveSideWays(double viewAlpha, bool right);
void drawMap();
void drawPlayer();
void drawLineOfSight(coordinates wall);


#endif