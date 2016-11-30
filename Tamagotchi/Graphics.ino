#include <stdbool.h>
#include <string.h>

/*
 * List of all Graphics (16x16 pixel images stored in binary form)
  -egg
  -eggHatch
  -baby
  -baby_open
  -baby_animate
  -teen
  -teen_open
  -teen_animate
  -adult
  -adult_open
  -adult_animate
  -senior
  -senior_open
  -heartWings
  -poo
  -milk
  -bread
  -pie
  -cherries
  -burger
  -drink
  -film
  -dumbbells
  -joystick
  -baseball
  -headphones
  -TV_animate1
  -TV_animate2
  -joystick_animate1
  -joystick_animate2
  -joystick_animateScreen1
  -joystick_animateScreen2
  -music_animate1
  -music_animate2
  -heartEmpty
  -heartFull
  -starEmpty
  -starFull
*/

int empty[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000
};

int egg[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000001111000000,
  0b0000010111100000,
  0b0000100110110000,
  0b0000101110010000,
  0b0001111111111000,
  0b0001111001111000,
  0b0001111001001000,
  0b0001001111011000,
  0b0000100111110000,
  0b0000011100100000,
  0b0000111111110000
};



int eggHatch[16] = {
  0b0000000000000000,
  0b0001110100000010,
  0b0011110000100000,
  0b0001110001111000,
  0b0100100000101000,
  0b0100100000100100,
  0b0101000000011000,
  0b0110001111000000,
  0b0010010110100000,
  0b0000011001100000,
  0b0011111001100100,
  0b0010011111101100,
  0b0001001111001000,
  0b0000100111110000,
  0b0010011000100010,
  0b0000111111110000
};


int baby[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001001001001000,
  0b0001000000001000,
  0b0001000110001000,
  0b0001000000001000,
  0b0001000000001000,
  0b0000100000010000,
  0b0000011111100000
};

int baby_open[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001001001001000,
  0b0001000000001000,
  0b0001000110001000,
  0b0001000110001000,
  0b0001000110001000,
  0b0000100000010000,
  0b0000011111100000
};

int baby_animate[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001000000101000,
  0b0001010000001000,
  0b0001000001101000,
  0b0001111111111000
};


int teen[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001001001001000,
  0b0001000000001000,
  0b0001000110001000,
  0b0011000000011100,
  0b0001000000001000,
  0b0001000000001000,
  0b0000101111010000,
  0b0000101000100000,
  0b0000010000000000
};

int teen_open[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001001001001000,
  0b0001000000001000,
  0b0001000110001000,
  0b0011000110011100,
  0b0001000110001000,
  0b0001000000001000,
  0b0000101111010000,
  0b0000101000100000,
  0b0000010000000000
};

int teen_animate[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001001001001000,
  0b0001000000001000,
  0b0001000110001000,
  0b0011100000001100,
  0b0001000000001000,
  0b0001000000001000,
  0b0000101111010000,
  0b0000010001010000,
  0b0000000000100000
};

int adult[16] = {
  0b0000000000000000,
  0b0001100000110000,
  0b0011110001111000,
  0b0011111111111000,
  0b0010000000001000,
  0b0010010001001000,
  0b0100000000000100,
  0b0100001110000100,
  0b0010000000001000,
  0b0100100000101000,
  0b0011000000111000,
  0b0010000000001000,
  0b0001000000010000,
  0b0000101110100000,
  0b0000101001000000,
  0b0000010000000000
};

int adult_open[16] = {
  0b0000000000000000,
  0b0001100000110000,
  0b0011110001111000,
  0b0011111111111000,
  0b0010000000001000,
  0b0010010001001000,
  0b0100000000000100,
  0b0100001110000100,
  0b0010001110001000,
  0b0100101110101000,
  0b0011000000111000,
  0b0010000000001000,
  0b0001000000010000,
  0b0000101110100000,
  0b0000101001000000,
  0b0000010000000000
};

int adult_animate[16] = {
  0b0000000000000000,
  0b0001100000110000,
  0b0011110001111000,
  0b0011111111111000,
  0b0010000000001000,
  0b0010010001001000,
  0b0100000000000100,
  0b0100001110000100,
  0b0010000000001000,
  0b0010100000100100,
  0b0011100000011000,
  0b0010000000001000,
  0b0001000000010000,
  0b0000101110100000,
  0b0000010010100000,
  0b0000000001000000
};

int senior[16] = {
  0b0000000000000000,
  0b0000000010000000,
  0b0000000001000000,
  0b0000000010000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001110111011000,
  0b0010000000011100,
  0b0010100010001100,
  0b0010000000000100,
  0b0010011110000100,
  0b0001100001101000,
  0b0010101100110100,
  0b0100011111100010,
  0b0010000000000100,
  0b0111000000001110
};

int senior_open[16] = {
  0b0000000000000000,
  0b0000000010000000,
  0b0000000001000000,
  0b0000000010000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001110111011000,
  0b0010000000011100,
  0b0010100010001100,
  0b0010000000000100,
  0b0010011110000100,
  0b0001101101101000,
  0b0010101100110100,
  0b0100011111100010,
  0b0010000000000100,
  0b0111000000001110
};

int senior_animate[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000010000000,
  0b0000000001000000,
  0b0000000010000000,
  0b0000011111100000,
  0b0000100000010000,
  0b0001110111011000,
  0b0010000000011100,
  0b0010100010001100,
  0b0010000000000100,
  0b0010011110000100,
  0b0001100001101000,
  0b0010101100110100,
  0b0100011111100010,
  0b0111000000001110
};

int heartWings[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011111000000,
  0b0000100000100000,
  0b0000011111000000,
  0b0000000000000000,
  0b0010000000001000,
  0b0101011011010100,
  0b1000101111100010,
  0b1000101111100010,
  0b1000111111100010,
  0b1001011111010010,
  0b0110001110001100,
  0b0010000100000100
};

int milk[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000111111100000,
  0b0000111111100000,
  0b0000010001000000,
  0b0000100000100000,
  0b0001000000010000,
  0b0001010001010000,
  0b0001011011010000,
  0b0001010101010000,
  0b0001010001010000,
  0b0001010001010000,
  0b0001000000010000,
  0b0001000000010000,
  0b0000111111100000
};

int bread[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0011111111111100,
  0b0100000000010010,
  0b0100000000010010,
  0b0100000000010010,
  0b0100000000010010,
  0b0010000000100100,
  0b0010000000100100,
  0b0010000000100100,
  0b0010000000100100,
  0b0010000000100100,
  0b0010000000100100,
  0b0010000000100100,
  0b0011111111111100
};

int pie[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000001110000000,
  0b0000010011000000,
  0b0000100110100000,
  0b0001001101010000,
  0b0010011010101000,
  0b0010110101010100,
  0b0011111111111100,
  0b0010000000000100,
  0b0011010101010100,
  0b0010101010101000,
  0b0001111111111000
};

int cherries[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000001100000000,
  0b0000001100000000,
  0b0000000111100000,
  0b0000000010000000,
  0b0000000011000000,
  0b0000000100100000,
  0b0000000100100000,
  0b0000111000111000,
  0b0001111101111100,
  0b0001110101110100,
  0b0001101101101100,
  0b0000111000111000
};

int burger[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000111111110000,
  0b0001010101001000,
  0b0010000000000100,
  0b0011111111111100,
  0b0010011001100100,
  0b0001001001001000,
  0b0011111111111100,
  0b0010000000000100,
  0b0001111111111000
};


int drink[16] = {
  0b0000000000000000,
  0b0000000000100000,
  0b0000000001000000,
  0b0001111111111000,
  0b0001000000001000,
  0b0001111111111000,
  0b0001000000001000,
  0b0001000000001000,
  0b0001000000001000,
  0b0001000000001000,
  0b0000100000010000,
  0b0000100000010000,
  0b0000100000010000,
  0b0000100000010000,
  0b0000100000010000,
  0b0000011111100000
};


int film[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0001100011000000,
  0b0011110111100000,
  0b0011110111100000,
  0b0001100011000000,
  0b0001111111000100,
  0b0010000000101100,
  0b0010000000111100,
  0b0010000000101100,
  0b0001111111000100
};

int dumbbells[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0001100000011000,
  0b0011100000011100,
  0b0111100000011110,
  0b0111111111111110,
  0b0011100000011100,
  0b0001100000011000,
  0b0000000000000000
};

int joystick[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000001110000000,
  0b0000011101000000,
  0b0000011111000000,
  0b0000011111000000,
  0b0000001110000000,
  0b0000000100000000,
  0b0000011111000000,
  0b0000100100100000,
  0b0001000000010000,
  0b0001111111110000,
  0b0001111111110000
};

int baseball[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000001111000000,
  0b0000010000100000,
  0b0000110000110000,
  0b0001001001001000,
  0b0001001001001000,
  0b0001001001001000,
  0b0001001001001000,
  0b0000110000110000,
  0b0000010000100000,
  0b0000001111000000
};

int headphones[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000111111110000,
  0b0001100000011000,
  0b0001000000001000,
  0b0011000000001100,
  0b0010000000000100,
  0b0010000000000100,
  0b0010000000000100,
  0b0111000000001110,
  0b1111000000001111,
  0b1111000000001111,
  0b1111000000001111,
  0b0111000000001110
};

int TV_animate1[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b1111111111111110,
  0b1101010101010110,
  0b1010101010101010,
  0b1101010101010110,
  0b1010101010101010,
  0b1101010101010110,
  0b1010101010101010,
  0b1111111111111110,
  0b0000001010000000,
  0b0000111111100000
};

int TV_animate2[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b1111111111111110,
  0b1010101010101010,
  0b1101010101010110,
  0b1010101010101010,
  0b1101010101010110,
  0b1010101010101010,
  0b1101010101010110,
  0b1111111111111110,
  0b0000001010000000,
  0b0000111111100000
};

int joystick_animate1[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011100000000,
  0b0000111010000000,
  0b0000111110000000,
  0b0000111110000000,
  0b0000011100000000,
  0b0000001000000000,
  0b0000011111000000,
  0b0000100100100000,
  0b0001000000010000,
  0b0001111111110000,
  0b0001111111110000
};

int joystick_animate2[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000111000000,
  0b0000001110100000,
  0b0000001111100000,
  0b0000001111100000,
  0b0000000111000000,
  0b0000000010000000,
  0b0000011111000000,
  0b0000100100100000,
  0b0001000000010000,
  0b0001111111110000,
  0b0001111111110000
};

int joystick_animateScreen1[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b1111111111111111,
  0b1000000000000001,
  0b1000111100000001,
  0b1001000010000001,
  0b1001111110000001,
  0b1001011010000001,
  0b1001111110000001,
  0b1001000010000001,
  0b1000000000000001,
  0b1111111111111111
};

int joystick_animateScreen2[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b1111111111111111,
  0b1000000000000001,
  0b1000000011110001,
  0b1000000100001001,
  0b1000000111111001,
  0b1000000101101001,
  0b1000000111111001,
  0b1000000100001001,
  0b1000000000000001,
  0b1111111111111111
};

int music_animate1[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000011000000000,
  0b0000011110000000,
  0b0000010011000000,
  0b0000010001100000,
  0b0000010000100000,
  0b0000010001000000,
  0b0000010000000000,
  0b0000010000000000,
  0b0000010000000000,
  0b0000010000000000,
  0b0011110000000000,
  0b0111110000000000,
  0b0111110000000000,
  0b0011100000000000
};

int music_animate2[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000011111110000,
  0b0000010000010000,
  0b0000010000010000,
  0b0000011111110000,
  0b0000010000010000,
  0b0000010000010000,
  0b0000010000010000,
  0b0000010000010000,
  0b0011110000010000,
  0b0111110011110000,
  0b0111110111110000,
  0b0011100111110000,
  0b0000000011100000
};

int poo[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000010000,
  0b0000010000100000,
  0b0000100000010000,
  0b0000010100000000,
  0b0000000110000000,
  0b0000001101000000,
  0b0000011110100000,
  0b0000011111100000
};

int heartFull[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0110110000000000,
  0b1011111000000000,
  0b1011111000000000,
  0b1111111000000000,
  0b0111110000000000,
  0b0011100000000000,
  0b0001000000000000
};

int heartEmpty[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0110110000000000,
  0b1001001000000000,
  0b1000001000000000,
  0b1000001000000000,
  0b0100010000000000,
  0b0010100000000000,
  0b0001000000000000
};

int starFull[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0001000000000000,
  0b0010100000000000,
  0b0111010000000000,
  0b1111111000000000,
  0b0111110000000000,
  0b0011100000000000,
  0b0001000000000000
};

int starEmpty[16] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0001000000000000,
  0b0010100000000000,
  0b0100010000000000,
  0b1000001000000000,
  0b0100010000000000,
  0b0010100000000000,
  0b0001000000000000
};

//--------------------- Helper Functions ---------------------
//Used to draw the images stored in the arrays, given an x and y position
void drawGraphic(int a[16] , int x, int y) {
  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++)
    {
      if (a[i] & 1 << j)
      {
        OrbitOledMoveTo(x + (15 - j), y + i);
        OrbitOledDrawPixel();
      }
    }
}

void drawString(char* s, int x, int y){
  OrbitOledMoveTo(x,y);
  OrbitOledDrawString(s);
}

//This is mostly for animations rather than static screen updates
void updateScreen(){
  OrbitOledUpdate();
  OrbitOledClearBuffer();
}

//--------------------- Stats Graphics ---------------------
//Draws empty/full hearts based on hunger stats
void drawHunger(int full) {
  drawString("Hungry",5,0);
  
  int x = 5, y = -1;
  for (int i = 0; i < full; i++)
    drawGraphic(heartFull ,  x + i * 9,  y);
  for (int i = full; i < 5; i++)
    drawGraphic(heartEmpty ,  x + full * 9 + (i - full) * 9,  y);
}

//Draws empty/full diamonds based on happiness stats
void drawHappy(int full) {
  drawString("Happy",5,17);
  
  int x = 5, y = 16;
  if (full < 0)
    full = 0;

  for (int i = 0; i < full; i++)
    drawGraphic(starFull ,  x + i * 9,  y);
  if (full < 0)
    full = 0;
  for (int i = full; i < 5; i++)
    drawGraphic(starEmpty ,  x + full * 9 + (i - full) * 9,  y);
}

//Draws poos
void drawToilet(int toiletCount) {
  for (int i = 0; i < toiletCount; i++) {
    if (i < 4)
      drawGraphic(poo ,  55,  16 - i * 8);
    else
      drawGraphic(poo ,  65,  16 - (i - 4) * 8);
  }
}

//Draws cash in top righthand of screen
void drawMoney(int money) {
  char str[10];
  sprintf(str, "$%d", money);
  drawString(str,128 - strlen(str) * 8,0);
}

//--------------------- Character Graphics ---------------------
//Chooses which character to draw based on its age, given an x and y coordinate
//Mode: 0 normal, 1 animation frame, 2 open mouth (eating)
void drawPet(int age, int x, int y, int mode) {
  switch (age) {
    case 0:
      if (mode == 0)
        drawGraphic(egg ,  x,  y);
      else if (mode == 1)
        drawGraphic(eggHatch,  x,  y);
      break;
    case 1:
      if (mode == 0)
        drawGraphic(baby ,  x,  y);
      else if (mode == 1)
        drawGraphic(baby_animate,  x,  y);
      else if (mode == 2)
        drawGraphic(baby_open, x, y);
      break;
    case 2:
      if (mode == 0)
        drawGraphic(teen ,  x,  y);
      else if (mode == 1)
        drawGraphic(teen_animate,  x,  y);
      else if (mode == 2)
        drawGraphic(teen_open, x, y);
      break;
    case 3:
      if (mode == 0)
        drawGraphic(adult ,  x,  y);
      else if (mode == 1)
        drawGraphic(adult_animate,  x,  y);
      else if (mode == 2)
        drawGraphic(adult_open, x, y);
      break;
    case 4:
      if (mode == 0)
        drawGraphic(senior ,  x,  y);
      else if (mode == 1)
        drawGraphic(senior_animate,  x,  y);
      else if (mode == 2)
        drawGraphic(senior_open, x, y);
      break;
  }
}

//--------------------- Screen Graphics (menus, main screen) ---------------------
void DrawMainScreen(int hunger, int happy, int money, int toilet, int age) {
  //Divider
  OrbitOledMoveTo(55, -1); 
  OrbitOledLineTo(55, 32);

  //Stats
  drawHunger(hunger);
  drawHappy(happy);
  drawMoney(money);
  drawToilet(toilet);

  //Character
  drawPet(age, 93, 15, 0);

  OrbitOledUpdate();
}

//Draw shop menu with arrow beside the current chosen option
void displayShopMenu(int option){
  int x = 11, y1 = 5, y2 = 18, offset = 9; 
  drawString("Food",x,y1);
  drawString("Gifts",x,y2);

  //display the arrow
  OrbitOledMoveTo(x - offset, (option == 0 ? y1 : y2));
  OrbitOledDrawChar('>');
}

//Draw food menu with arrow under the current chosen option
void displayFood(int option, int price, int hungerVal, int happyVal) {
  int y = 10;
  int x = 10;
  drawGraphic(milk ,  x,  y);
  drawGraphic(bread ,  x + 20,  y);
  drawGraphic(pie ,  x + 40,  y);
  drawGraphic(cherries ,  x + 60,  y);
  drawGraphic(burger ,  x + 80,  y);
  drawGraphic(drink ,  x + 100,  y);

  //Display stats of current option
  char str[2];
  sprintf(str, "%d", hungerVal);
  drawString(str,0,0);
  drawGraphic(heartFull ,  8,  -9);
  
  sprintf(str, "%d", happyVal);
  drawString(str,17,0);
  drawGraphic(starFull ,  25,  -9);

  drawMoney(price);

  //Display which option is currently selected
  OrbitOledMoveTo(14 + option * 20, 28);
  OrbitOledDrawChar('^');
}

//Draw gift menu with arrow under the current chosen option
void displayGifts(int option, int price, int happyVal, int age) {
  int y = 10;
  int x = 10;
  drawGraphic(film ,  x,  y);
  drawGraphic(dumbbells ,  x + 20,  y);
  drawGraphic(joystick ,  x + 40,  y);
  drawGraphic(headphones ,  x + 60,  y);
  drawGraphic(baseball ,  x + 80,  y);
  drawPet(age + 1 ,  x + 100,  y, 0);

  //Draw stats of current option
  char str[2];
  sprintf(str, "%d", happyVal);
  drawString(str,0,0);
  drawGraphic(starFull ,  8,  -9);
  
  drawMoney(price);

  //Draw currently selected option
  OrbitOledMoveTo(14 + option * 20, 28);
  OrbitOledDrawChar('^');
}

//Draw game menu with arrow beside the current chosen option
void displyGameMenu(int option){
  int x = 11, y1 = 5, y2 = 18, offset = 9; 

  drawString("Dance",x,y1);
  drawString("Jump",x,y2);

  //display the arrow
  OrbitOledMoveTo(x - offset, (option == 0 ? y1 : y2));
  OrbitOledDrawChar('>');
}

//--------------------- Game start and game end animations ---------------------
//Draw egg
void DrawGameStartEgg() {
  drawPet(0 ,  56,  8, 0); //draw egg
  updateScreen();
}

//Egg hatching
void DrawGameStartHatch() {
  updateScreen();
  delay(500);
  drawPet(0 ,  56,  8, 1); //draw eggHatch
  updateScreen();
  delay(1000);
  updateScreen();
  delay(500);
  drawPet(1 ,  56,  8, 0); //draw baby
  updateScreen();
  delay(1000);
}

void gameOverGraphics(bool dead) {
  if(dead)
  {
    drawString("Your pet died!",13,0);
    drawString("Press button",20,13);
    drawString("to start over",16,23);
  }
  else
  {
    drawGraphic(heartWings ,  56,  -4);
    drawString("Press button",20, 13);
    drawString("to start over",16,23);
  }
}

//--------------------- Animations for things that are bought from the shops ---------------------
void foodAnimations(int option, int age) {
  //Food moves down the screen and the pet eats it
  for (int i = 0; i < 15; i++) {
    drawPet(age, 56, 15, 0);

    switch (option) {
      case 0: //milk
        drawGraphic(milk ,  72,  i);
        break;
      case 1: //bread
        drawGraphic(bread ,  72,  i);
        break;
      case 2: //pie
        drawGraphic(pie ,  72,  i);
        break;
      case 3: //cherries
        drawGraphic(cherries ,  72,  i);
        break;
      case 4: //burger
        drawGraphic(burger ,  72,  i);
        break;
      case 5: //drink
        drawGraphic(drink ,  72,  i);
        break;
    }

    updateScreen();
    delay(100);
  }

  drawPet(age, 56, 15, 2);
  OrbitOledUpdate(); //Don't clear screen here - just draw open mouth
  delay(500);

  drawPet(age, 56, 15, 0);
  updateScreen();
  delay(700);
}


void giftAnimations(int option, int age) {
  //Animate the pet using the gift based on the given option
  for (int i = 0; i < 3; i++) {

    switch (option) {
      case 0: //film
        drawGraphic(TV_animate1, 70, 0);
        break;
      case 1: //dumbbells
        drawGraphic(dumbbells, 68, 0);
        break;
      case 2: //joystick
        drawGraphic(joystick_animate1, 71, 15);
        drawGraphic(joystick_animateScreen1, 70, 0);
        break;
      case 3: //headphones
        drawGraphic(music_animate1, 82, -2);
        drawGraphic(music_animate2, 68, 5);
        break;
      case 4: //baseball
        drawGraphic(baseball, 68, 0);
        break;
    }
    if (option != 5)
      drawPet(age, 50, 10, 0);
    else
      drawPet(age, 56, 10, 0);
    updateScreen();
    delay(500);

    switch (option) {
      case 0: //film
        drawGraphic(TV_animate2, 70, 0);
        break;
      case 1: //dumbbells
        drawGraphic(dumbbells, 68, 7);
        break;
      case 2: //joystick
        drawGraphic(joystick_animate2, 71, 15);
        drawGraphic(joystick_animateScreen2, 70, 0);
        break;
      case 3: //headphones
        drawGraphic(music_animate2, 82, -2);
        drawGraphic(music_animate1, 68, 5);
        break;
      case 4: //baseball
        drawGraphic(baseball, 68, 7);
        break;
    }
    if (option != 5)
      drawPet(age, 50, 10, 1);
    else
      drawPet(age + 1, 56, 10, 1);
    updateScreen();
    delay(500);
  }
}


//--------------------- Functions specific to minigames ---------------------
//Jump Minigame functions
void drawHurdle(int x, int hurdleHeight) {
  for (int j = 0; j < hurdleHeight; j++) {
    OrbitOledMoveTo(x, 32 - j);
    OrbitOledDrawPixel();
  }
}

int checkPetBit(int age, int xcor, int ycor) {
  switch (age) {
    case 0:
      return (egg[xcor] & 1 << (15 - ycor)) ? 1 : 0;
    case 1:
      return (baby[xcor] & 1 << (15 - ycor)) ? 1 : 0;
    case 2:
      return (teen[xcor] & 1 << (15 - ycor)) ? 1 : 0;
    case 3:
      return (adult[xcor] & 1 << (15 - ycor)) ? 1 : 0;
    case 4:
      return (senior[xcor] & 1 << (15 - ycor)) ? 1 : 0;
    default:
      return 0;
  }
}

//Dance Minigame functions
void animateDance(uint8_t pattern) {
  switch(pattern) {
  case 0:
    OrbitOledMoveTo(5,5);
    OrbitOledDrawString("A");
    drawPet(player.age, 56, 15, 1);
    updateScreen();
    delay(500);
    break;
  case 1:
    OrbitOledMoveTo(40,5);
    OrbitOledDrawString("B");
    drawPet(player.age, 56, 15, 1);
    updateScreen();
    delay(500);
    break;
  case 2:
    OrbitOledMoveTo(80,5);
    OrbitOledDrawString("shake");
    drawPet(player.age, 56, 15, 1);
    updateScreen();
    delay(500);
    break;
  }
}
