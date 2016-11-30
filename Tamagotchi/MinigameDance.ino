#include <stdbool.h>
#include <stdlib.h>

//Variables for Dance Game
const uint8_t dance_maxLevel = 15;


bool dance_lose;
bool dance_start;
bool dance_play;
bool dance_animate;
bool dance_update;
uint8_t dance_level;
uint8_t dance_actionCount;
uint16_t dance_shakeCount;
uint8_t dance_pattern[dance_maxLevel] = {0};

void initDanceGame() {

  dance_lose = false;
  dance_start = false;
  dance_play = false;
  dance_update = false;
  dance_animate = false;
  dance_level = 0;
  dance_shakeCount = 0;
  dance_actionCount = 0;
  for(int i = 0; i < dance_maxLevel; i++) {
    dance_pattern[i] = 0;
  }
}

int danceGameStart() {
  dance_start = true;
    
  //Display instructions
  drawString("Copy the Pattern", 0, 12);
  updateScreen();
  delay(2000);
  drawString("A up | B down", 0, 12);
  updateScreen();
  delay(2000);
  drawString("shake board", 0, 12);
  updateScreen();
  delay(2000);
    
  dance_pattern[0] = rand()%3;
  return -1;
}

int danceGameEnd() {
  if (dance_lose) {
    drawString("Game Over", 5, 15);
    updateScreen();
    delay(2000);
    return dance_level;
  }
  else {
    drawString("You Win!", 5, 15);
    updateScreen();
    delay(2000);
    return dance_level+10;
  }
}

int danceLevelUp() {
  //game logic
  dance_level++;
  dance_actionCount = 0;
  dance_play = false;

  //feedback to the user
  drawString("OK!", 40, 5);
  drawPet(player.age, 56, 15, 0);
  updateScreen();
  delay(500);

  //end the game if you exceed maximum number of levels
  if (dance_level > dance_maxLevel)
      return danceGameEnd();

  //otherwise generate the new level
  dance_pattern[dance_level] = rand()%3;
  //less likely to get same pattern twice in a row (1/9)
  if (dance_pattern[dance_level] == dance_pattern[dance_level-1])
    dance_pattern[dance_level] = rand()%3;
  return -1;
}

int danceGame() {
    
  //check if the game is starting/ending
  if(!dance_start)
    return danceGameStart();
  if(dance_lose)
    return danceGameEnd();
  
  //if player actions aren't being taken
  if (!dance_play && !dance_lose) {
    //show the dance steps
    for (int i = -1; i <= dance_level; i++){
      if (i == -1) 
        drawString("Ready...", 25, 5);
      else
        animateDance(dance_pattern[i]);
    
      //pause to let the player think
      drawPet(player.age, 56, 15, 0);
      updateScreen();
      delay(500);
    } 
    dance_play = true;
  }

  //take player actions
  if (dance_play) {
    //Ask for input  
    drawPet(player.age, 56, 15, 0);
    if (dance_actionCount==0)
        drawString("Go!", 40, 5);
    else
      drawString("then...", 40, 5);
    OrbitOledUpdate();
    //take user input
    if (gameInputState.buttons[0].isRising) {
      OrbitOledClearBuffer();
      animateDance(0);
      if (dance_pattern[dance_actionCount]!=0) {
          dance_lose = true;
          dance_play = false;
      }
      dance_actionCount++;
    }
    else if (gameInputState.buttons[1].isRising) {
      OrbitOledClearBuffer();
      animateDance(1);
      if (dance_pattern[dance_actionCount]!=1) {
          dance_lose = true;
          dance_play = false;
      }
      dance_actionCount++;
    }
    else if (dance_shakeCount == 50) {
      dance_shakeCount = 0;
      OrbitOledClearBuffer();
      animateDance(2);
      if (dance_pattern[dance_actionCount]!=2) {
          dance_lose = true;
          dance_play = false;
      }
      dance_actionCount++;
    }
    else if (ShakeIsShaking()) {
      dance_shakeCount++;
    }

    //level up
    if (!dance_lose && dance_actionCount > dance_level) {
        return danceLevelUp();
    }      

  }
  return -1;
}
