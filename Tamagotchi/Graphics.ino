#include <stdbool.h>
#include <string.h>

/*
 * void OrbitOledSetDrawColor(char clr);
void  OrbitOledSetDrawMode(int mod);
int   OrbitOledGetDrawMode();
char *  OrbitOledGetStdPattern(int ipat);
void  OrbitOledSetFillPattern(char * pbPat);

void  OrbitOledMoveTo(int xco, int yco);
void  OrbitOledGetPos(int * pxco, int * pyco);
void  OrbitOledDrawPixel();
char  OrbitOledGetPixel();
void  OrbitOledLineTo(int xco, int yco);
void  OrbitOledDrawRect(int xco, int yco);
void  OrbitOledFillRect(int xco, int yco);
void  OrbitOledGetBmp(int dxco, int dyco, char * pbBmp);
void  OrbitOledPutBmp(int dxco, int dyco, char * pbBmp);
void  OrbitOledPutBmpFlipped(int dxco, int dyco, char * pbBmp);
void  OrbitOledDrawChar(char ch);
void  OrbitOledDrawString(char * sz);

 */
/*Graphics
-egg
-baby
-teen
-adult
-senior
-poo
-milk
-bread
-pie
-cherries
-burger
-drink
-heartEmpty
-heartFull
*/

//Screen is 128x32 pixels

int empty[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int egg[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0},
{0,0,0,0,1,0,0,1,1,0,1,1,0,0,0,0},
{0,0,0,0,1,0,1,1,1,0,0,1,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0},
{0,0,0,1,0,0,1,1,1,1,0,1,1,0,0,0},
{0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,0},
{0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
};

int eggHatch[16][16] = {
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0},
{0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0},
{0,1,0,0,0,1,0,1,1,0,1,0,0,0,0,0},
{0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0},
{0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0},
{0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},
{0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0},
{0,0,0,1,0,0,1,1,1,1,0,1,1,0,0,0},
{0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,0},
{0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
};


int baby[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
};


int teen[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0},
{0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0},
{0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
};

int adult[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0},
{0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
{0,1,0,0,1,0,0,0,0,0,1,0,1,0,0,0},
{0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0},
{0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
};

int senior[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,1,1,1,0,1,1,1,0,1,1,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0},
{0,0,1,0,1,0,0,0,1,0,0,0,1,1,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,0,1,0,0,1,1,1,1,0,0,0,0,1,0,0},
{0,0,0,1,1,0,0,0,0,1,1,0,1,0,0,0},
{0,0,1,0,1,0,1,1,0,0,1,1,0,1,0,0},
{0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0}
};

int milk[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0},
{0,0,0,1,0,1,1,0,1,1,0,1,0,0,0,0},
{0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0},
{0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0},
{0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0}
};

int bread[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0},
{0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0},
{0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0},
{0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0},
{0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0},
{0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0},
{0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0},
{0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0}
};

int pie[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0},
{0,0,0,0,1,0,0,1,1,0,1,0,0,0,0,0},
{0,0,0,1,0,0,1,1,0,1,0,1,0,0,0,0},
{0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0},
{0,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0},
{0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0}
};

int cherries[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0},
{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0},
{0,0,0,1,1,1,0,1,0,1,1,1,0,1,0,0},
{0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,0},
{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0}
};

int burger[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,0},
{0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0}
};


int drink[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0}
};

int poo[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0}
};

int heartFull[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},
{1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}
};

int heartEmpty[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}
};

void drawGraphic(int a[16][16] , int x, int y){
  for(int i=0;i<16;i++)
  for(int j=0;j<16;j++)
  {
    if(a[i][j])
    {
      OrbitOledMoveTo(x+j,y+i);
      OrbitOledDrawPixel();
    }
  }
}

void DrawMainScreen(int hunger, int happy, int money, int toilet, int age){
  OrbitOledMoveTo(55, -1);
  OrbitOledLineTo(55, 32);

  drawHunger(hunger);
  drawHappy(happy);
  drawMoney(money);
  drawToilet(toilet);

  int characterX=93;
  int characterY=15;
  switch(age){
     case 0:
       drawGraphic(egg ,  characterX,  characterY);
     break;
     case 1:
       drawGraphic(baby ,  characterX,  characterY);
     break;
     case 2:
       drawGraphic(teen ,  characterX,  characterY);
     break;
     case 3:
       drawGraphic(adult ,  characterX,  characterY);
     break;
     case 4:
       drawGraphic(senior ,  characterX,  characterY);
     break;
  }
  //draw poop?
}

void drawHunger(int full){
  OrbitOledMoveTo(5, 0);
  OrbitOledDrawString("Hungry\n");
  int x=5,y=-1;
  
  for(int i=0;i<full;i++)
    drawGraphic(heartFull ,  x+i*9,  y);
  for (int i=full;i<5;i++)
    drawGraphic(heartEmpty ,  x+full*9+(i-full)*9,  y);
}

void drawHappy(int full){
  OrbitOledMoveTo(5, 17);
  OrbitOledDrawString("Happy\n");
  int x=5,y=16;

  if(full<0)
    full=0;
  
  for(int i=0;i<full;i++)
    drawGraphic(heartFull ,  x+i*9,  y);
  if(full<0)
    full=0;
  for (int i=full;i<5;i++)
    drawGraphic(heartEmpty ,  x+full*9+(i-full)*9,  y);
}

void drawToilet(int toiletCount){
  
  for(int i=0;i<toiletCount;i++){
    if(i<4)
      drawGraphic(poo ,  55,  16-i*8);
    else
      drawGraphic(poo ,  65,  16-(i-4)*8);
  }
}

void drawMoney(int money){
  char str[10];
  sprintf(str,"$%d",money);

  OrbitOledMoveTo(128-strlen(str)*8,0);
  
  OrbitOledDrawString(str);
}

void displayFood(int option, int price){
  int y=10;
  drawGraphic(milk ,  10,  y);
  drawGraphic(bread ,  10+20,  y);
  drawGraphic(pie ,  30+20,  y);
  drawGraphic(cherries ,  50+20,  y);
  drawGraphic(burger ,  70+20,  y);
  drawGraphic(drink ,  90+20,  y);

  OrbitOledMoveTo(14+option*20,28);
  OrbitOledDrawChar('^');

  drawMoney(price);
}

void gameOverGraphics(){
  OrbitOledMoveTo(13, 0);
  OrbitOledDrawString("Your pet died!");
  OrbitOledMoveTo(20, 12);
  OrbitOledDrawString("Press button ");
  OrbitOledMoveTo(16, 22);
  OrbitOledDrawString("to start over");
}

void gameStartEgg(){
  OrbitOledClearBuffer();
  OrbitOledClear();
  drawGraphic(egg ,  56,  8);
  OrbitOledUpdate();
}

void gameStartHatch(){
  OrbitOledClearBuffer();
  OrbitOledClear();
  delay(500);
  drawGraphic(eggHatch ,  56,  8);
  OrbitOledUpdate();
  delay(1000);
  OrbitOledClearBuffer();
  OrbitOledClear();
  OrbitOledUpdate();
  delay(500);
  drawGraphic(baby ,  56,  8);
  OrbitOledUpdate();
  delay(1000);
}

void drawSomething()
{
//displayFood();
//OrbitOledMoveTo(30,10);
//drawHunger(3);
//drawHappy(3);

//drawGraphic(egg ,  10,  10);
//drawGraphic(baby ,  10+20,  10);
//drawGraphic(teen ,  30+20,  10);
//drawGraphic(adult ,  50+20,  10);
//drawGraphic(senior ,  70+20,  10);
//drawGraphic(poo ,  90+20,  10);
//
//OrbitOledMoveTo(0,5);
//OrbitOledDrawChar('>');
//
//OrbitOledMoveTo(7,5);
//OrbitOledDrawString("Food\n");
//OrbitOledMoveTo(7,18);
//OrbitOledDrawString("Gifts\n");
//OrbitOledMoveTo(55, 0);
//OrbitOledLineTo(55, 32);
//OrbitOledPutBmp(16,8,hi);

//
//drawGraphic(milk ,  10,  5);
//  drawGraphic(egg ,  10+20,  5);
//  drawGraphic(baby ,  30+20,  5);
//  drawGraphic(teen ,  50+20,  5);
//  drawGraphic(adult ,  70+20,  5);
//  drawGraphic(senior ,  90+20,  5);
//
//  //int option = gameInputState.potentiometer/(PotentiometerMaxValue/6 + 1.0);
//  OrbitOledMoveTo(14+0*20,25);
//  OrbitOledDrawChar('^');
//  OrbitOledMoveTo(14+1*20,25);
//  OrbitOledDrawChar('^');
//  OrbitOledMoveTo(14+2*20,25);
//  OrbitOledDrawChar('^');
//  OrbitOledMoveTo(14+3*20,25);
//  OrbitOledDrawChar('^');
//  OrbitOledMoveTo(14+4*20,25);
//  OrbitOledDrawChar('^');
//  OrbitOledMoveTo(14+5*20,25);
//  OrbitOledDrawChar('^');

//for(int i=0;i<40;i++)
//{
//
//  OrbitOledClear();
//drawGraphic(baby ,  30+i,  10);
//OrbitOledUpdate();
//delay(100);
// 
//}
  //drawGraphic(test,20,20);
  //OrbitOledDrawString("Welcome to RPS");
  OrbitOledUpdate();
}

