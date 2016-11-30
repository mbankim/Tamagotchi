#include <stdbool.h>

//slightly unintuitive b/c the top/bottom of the screen is 0/32 respectively
//left -> right is 0 -> 128

const uint8_t imgSize = 16;
const uint8_t jump_maxHeight = 0;
const uint8_t jump_x = 5;
const uint8_t jump_vx = 1;
const uint8_t jump_hurdleHeight = 8;
const uint8_t jump_slowRate = 20;       //determines rate at which hurdles approach. lower is faster, adjusted with level
const uint8_t jump_hurdleGenRate = 30;  //determines rate of hurdles generation, lower is faster, adjusted using level
const uint8_t jump_numOfHurdles = 6;    //max possible number of hurdles on screen
const uint8_t jump_maxLevel = 15;

bool jump_isJumping;
uint8_t jump_y;
uint8_t jump_vy;
uint8_t jump_level;
uint8_t jump_slowCount;                  //counter for slowRate
uint8_t jump_hurdleIdx;                  //keeps track of next hurdle to generate
uint8_t jump_hurdle[jump_numOfHurdles];
int jump_hurdleCnt;                      //counts total hurdles jumped for level

void initJumpGame() {
  jump_isJumping = false;
  jump_vy = 0;
  jump_y = imgSize;
  jump_slowCount = 0;
  jump_hurdleIdx = 0;
  jump_level = 0;
  jump_hurdleCnt = 0;
  for(int i = 0; i < jump_numOfHurdles; i++) 
      jump_hurdle[i] = 0;
}

uint8_t jumpGameEnd() {
  if (jump_level < jump_maxLevel) {
      drawString("Game Over", 5, 15);
      updateScreen();
      delay(2000);
      return jump_level;
    }
  else {
    drawString("You Win!", 5, 15);
    updateScreen();
    delay(2000);
    return jump_level+10;
  }
}

int jump_checkCollision(int age, int xcor, int ycor) {
  switch (age) {
    case 0:
      return (egg[ycor] & 1 << xcor) ? 1 : 0;
    case 1:
      return (baby[ycor] & 1 << xcor) ? 1 : 0;
    case 2:
      return (teen[ycor] & 1 << xcor) ? 1 : 0;
    case 3:
      return (adult[ycor] & 1 << xcor) ? 1 : 0;
    case 4:
      return (senior[ycor] & 1 << xcor) ? 1 : 0;
    default:
      return 0;
  }
}

uint8_t jumpGame() {

  if (jump_slowCount == jump_slowRate - jump_level*2) {
    OrbitOledClearBuffer();
    
    //jumping
    if (jump_vy != 0) {
      //negative due to axis flip
      jump_y -= jump_vy;
      
      //completes the jump
      if (jump_y == imgSize) {
        jump_vy = 0;
        jump_isJumping = false;
      }
      //peak of jump, reverse vy
      if (jump_y == jump_maxHeight) jump_vy = -jump_vy;
    }

    //move hurdles
    for(int i = 0; i < jump_numOfHurdles; i++) {
      if (jump_hurdle[i]) {
        jump_hurdle[i] -= jump_vx;
        if (jump_hurdle[i] < 0)
          jump_hurdle[i] = 0;
        if (jump_hurdle[i] == 0)
          jump_hurdleCnt++;
      }
    }

    //hurdle generation
    int prevHurdleX = jump_hurdle[(jump_hurdleIdx+jump_numOfHurdles-1)%jump_numOfHurdles];          //location of previously generated hurdle
    int maxHurdleX =  imgSize*jump_vx/jump_vy + (jump_maxLevel - jump_level) + imgSize;             //maximum distance to place next hurdle
    if (!jump_hurdle[jump_hurdleIdx] && screenSizeX - prevHurdleX > maxHurdleX && rand()%(jump_hurdleGenRate-jump_level*2) == 0) {
      jump_hurdle[jump_hurdleIdx] = screenSizeX;
      jump_hurdleIdx = (jump_hurdleIdx + 1) % jump_numOfHurdles;
    }

    //draw hurdles
    for (int i = 0; i < jump_numOfHurdles; i++) {
      if (jump_hurdle[i] != 0) {
        drawHurdle(jump_hurdle[i], jump_hurdleHeight);
      }
    }
    
    //draw pet
    drawPet(player.age, jump_x, jump_y, 0);
    OrbitOledUpdate();
    jump_slowCount = 0;

    //collision detection
    for (int j = 0; j < jump_numOfHurdles; j++) {
      if (jump_hurdle[j] - jump_x < imgSize && jump_hurdle[j] - jump_x >= 0) {
        for (int i = 0; i < jump_y - jump_hurdleHeight; i++) {
          if (jump_checkCollision(player.age, imgSize - (jump_hurdle[j] - jump_x), imgSize-i)) {
            return jumpGameEnd();
          }
        }
      }
    }
  }
  else
    jump_slowCount++;

  //check level
  if (jump_hurdleCnt >= jump_numOfHurdles*(1+jump_level)/2) {
      jump_level++;
      jump_hurdleCnt /= 2;
      if (jump_level > jump_maxLevel)
          return jumpGameEnd();
  }
  
    
  //receive user input
  if (gameInputState.buttons[0].isRising && !jump_isJumping) {
    jump_vy = 1;
    jump_isJumping = true;
  }
  else if (gameInputState.buttons[1].isRising) {
    return jumpGameEnd();
  }
    
  return 1;
}







