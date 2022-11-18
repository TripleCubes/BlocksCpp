#include "globals.h"

int currentWindowWidth = INIT_WINDOW_WIDTH;
int currentWindowHeight = INIT_WINDOW_HEIGHT;

bool thirdPersonView = false;
bool wireframeMode = false;
bool flying = true;
bool mouseLock = true;

bool isMax(float num1, float num2, float num3)
{
    if (num1 == 0)
    {
        return false;
    }
    if ((num1 < num2 && num2 != 0) || (num1 < num3 && num3 != 0))
    {
        return false;
    }
    return true;
}

bool isMin(float num1, float num2, float num3)
{
    if (num1 == 0)
    {
        return false;
    }
    if ((num1 > num2 && num2 != 0) || (num1 > num3 && num3 != 0))
    {
        return false;
    }
    return true;
}

int mod(int num1, int num2)
{
    int result = num1 % num2;
    if (result < 0)
    {
        result += num2;
    }
    return result;
}