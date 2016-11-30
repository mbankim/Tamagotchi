#include<stdbool.h>
#include <time.h>
#include <stdlib.h>

//0,12,22
//Around 15 letters across the screen
const uint8_t maxLevel = 20;
uint8_t pattern[maxLevel] = {0};
uint8_t danceLevel;
bool lose;
bool started;
bool playerDancing;
bool danceAnim;
uint8_t age;
uint8_t score;
uint8_t playerActCnt;
uint16_t shakeDanceCount;

void initDanceGame() {
  danceLevel = 0;
  shakeDanceCount = 0;
  lose = false;
  started = false;
  playerDancing = false;
  danceAnim = false;
  for(int i = 0; i < maxLevel; i++) {
    pattern[i] = 0;
  }
  score = 0;
  playerActCnt = 0;
}



uint8_t danceGameStart() {
  started = true;
  OrbitOledClear();
  OrbitOledClearBuffer();
  //Display instructions
  OrbitOledMoveTo(0,0);
  OrbitOledDrawString("Copy the pattern");
  OrbitOledUpdate();
  OrbitOledClearBuffer();
  delay(1000);
  OrbitOledMoveTo(0,12);
  OrbitOledDrawString("A up | B down");
  OrbitOledUpdate();
  OrbitOledClearBuffer();
  delay(1000);
  OrbitOledMoveTo(0,12);
  OrbitOledDrawString("shake board");
  OrbitOledUpdate();
  OrbitOledClearBuffer();
  
  pattern[0] = rand()%3;
  delay(1000);
  return 0;
}


uint8_t danceGame(){
  if(!started)
    return danceGameStart();
  if(lose)
    return danceGameEnd();
  
  if (!playerDancing && !lose) {
    OrbitOledClear();
    OrbitOledClearBuffer();
    for (int i = -1; i <= level; i++){
      drawPet(player.age, 56, 15, 0);
      if (i == -1) {
        OrbitOledMoveTo(25, 5);
        OrbitOledDrawString("Ready...");
      }
      else if (pattern[i] == 0){
        OrbitOledMoveTo(5,5);
        OrbitOledDrawString("A");
      }
      else if (pattern[i] == 1){
        OrbitOledMoveTo(40,5);
        OrbitOledDrawString("B");
      }
      else if (pattern[i] == 2){
        OrbitOledMoveTo(80,5);
        OrbitOledDrawString("shake");
      }

      OrbitOledUpdate();
      OrbitOledClearBuffer();
      delay(500);
      drawPet(player.age, 56, 15, 0);
      OrbitOledUpdate();
      delay(500);
    }
    playerDancing = true;
  }


  if (playerDancing) {
    OrbitOledClearBuffer();
    drawPet(player.age, 56, 15, 0);
    OrbitOledMoveTo(40, 5);
    if (playerActCnt==0)
      OrbitOledDrawString("Go!");
    else
      OrbitOledDrawString("Then...");
    if (playerDancing && gameInputState.buttons[0].isRising) {
      animateDance(0);
      if (pattern[playerActCnt]!=0) {
          lose = true;
          playerDancing = false;
      }
      playerActCnt++;
    }
    else if (playerDancing && gameInputState.buttons[1].isRising) {
      animateDance(1);
      if (pattern[playerActCnt]!=1) {
          lose = true;
          playerDancing = false;
      }
      playerActCnt++;
    }
    else if (shakeDanceCount == 50) {
      shakeDanceCount = 0;
      animateDance(2);
      if (pattern[playerActCnt]!=2) {
          lose = true;
          playerDancing = false;
      }
      playerActCnt++;
    }
    else if (ShakeIsShaking()) {
      shakeDanceCount++;
    }

    if (!lose && playerActCnt > level) {
        OrbitOledClearBuffer();
        drawPet(player.age, 56, 15, 0);
        level++;
        playerActCnt = 0;
        playerDancing = false;
        pattern[level] = rand()%3;
        //less likely to get same pattern twice in a row
        if (pattern[level] == pattern[level-1] && rand()%2 == 0)
          pattern[level] = rand()%3;
        if (level > maxLevel)
            danceGameEnd();
    }
  }
  return 0;
}

uint8_t danceGameEnd() {
  OrbitOledClear();
  OrbitOledClearBuffer();
  if (lose) {
    OrbitOledMoveTo(5, 15);
    OrbitOledDrawString("Game Over");
    OrbitOledUpdate();
    delay(2000);
    OrbitOledClear();
    OrbitOledClearBuffer();
    return level*5;
  }
  else {
    OrbitOledMoveTo(5, 15);
    OrbitOledDrawString("You Win!");
    delay(2000);
    return level*20;
  }
}

void animateDance(uint8_t dpattern) {
  OrbitOledClearBuffer();
  switch(dpattern) {
  case 0:
    OrbitOledMoveTo(5,5);
    OrbitOledDrawString("A");
    drawPet(player.age, 56, 15, 1);
    OrbitOledUpdate();
    delay(500);
    break;
  case 1:
    OrbitOledMoveTo(40,5);
    OrbitOledDrawString("B");
    drawPet(player.age, 56, 15, 1);
    OrbitOledUpdate();
    delay(500);
    break;
  case 2:
    OrbitOledMoveTo(80,5);
    OrbitOledDrawString("shake");
    drawPet(player.age, 56, 15, 1);
    OrbitOledUpdate();
    delay(500);
    break;
  }
}

