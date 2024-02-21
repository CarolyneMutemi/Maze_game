#ifndef MAZE_H
#define MAZE_H
#define mapWidth 60
#define mapHeight 30
#define screenWidth 1920
#define screenHeight 960

#include <math.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct vector {
    double x;
    double y;
} vector;

typedef struct point {
    double x;
    double y;
    double distToPlayer;
} point;

typedef struct movePlayer {
    double moveSpeed; // pixels per second.
    double rotSpeed; // radians per second.
    int forward;
} movePlayer;

extern int gameMap[mapHeight][mapWidth];
extern double playerX, playerY, dirX, dirY, planeX, planeY, time, oldTime;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int cubeUnit;
extern movePlayer player;

void drawWallSlice();
bool init();
void closeDown();
void drawUpperLower();
void movement(SDL_Event event);
void moveForward();
void moveSideWays();
void drawPlayer();
void drawMap();
void drawLineOfSight();
point getFinalPoint(double rayDirX, double rayDirY);
vector normalizeVector(double rayDirx, double rayDirY);
double degToRad(double degree);
//int getWallSliceHeight(point hit);

#endif