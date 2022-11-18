#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

enum Dir
{
    TOP, BOTTOM, LEFT, RIGHT, FORWARD, BACKWARD
};

struct Pos
{
    int x = 0;
    int y = 0;
    int z = 0;
};

const unsigned int INIT_WINDOW_WIDTH = 800;
const unsigned int INIT_WINDOW_HEIGHT = 500;
const int INIT_WINDOW_POS_X = 10;
const int INIT_WINDOW_POS_Y = 20;

const float FPS_CAP = 60;

extern int currentWindowWidth;
extern int currentWindowHeight;

extern bool thirdPersonView;
extern bool wireframeMode;
extern bool flying;
extern bool mouseLock;

bool isMax(float num1, float num2, float num3);
bool isMin(float num1, float num2, float num3);
int mod(int num1, int num2);

#endif