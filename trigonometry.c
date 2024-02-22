#include "newMaze.h"

double degToRad(double degree)
{
    double pi = 3.14159265359;
    if (degree > 306)
        degree -= 360 ;
    else if (degree < 0)
        degree += 360;
    
    return (degree * (pi / 180));
}




vector normalizeVector(double rayDirX, double rayDirY)
{
    double c = sqrt(pow(rayDirX, 2) + pow(rayDirY, 2));
    vector unit = {(rayDirX / c), (rayDirY / c)};

    return unit;
}
