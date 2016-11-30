#include <stdbool.h>
#include <string.h>
#include<limits.h>

//Bottom button: gameInputState.buttons[0]
//Top button: gameInputState.buttons[1]
//Switches: down is 0, up is 1
//Left switch: gameInputState.switches[1]
//Right switch: gameInputState.switches[0]
//Potentiometer: 0 - 4095

//gameUiPages
const uint8_t MainScreen    = 0;  //Displays Tamagotchi and Information
const uint8_t ShopMenu      = 1;  //Shop for Food or Gifts
const uint8_t FoodMenu      = 2;  //Can pick among various Foods
const uint8_t GiftMenu      = 3;  //Can pick among various Gifts
const uint8_t GameMenu      = 4;  //Can pick among various Games
const uint8_t GameOver      = 5;  //Game over screen
const uint8_t StartScreen   = 6;  //Welcome screen (egg hatching)
const uint8_t DanceGame     = 7;  //Dance game
const uint8_t JumpGame      = 8;  //Jump game

/*
   GameMenu1 etc
   How many games will there be?
*/
const uint8_t NumberOfPages = 9;  //To be increased with number of games.
uint32_t gameUiPage = MainScreen;

int GlobalOption = 0;

//Hardware info

const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 2;
const uint32_t Switches[2] = { PA_7, PA_6 };  //List of switches to be used
const uint32_t Buttons[2] = {PE_0, PD_2 };   //List of Buttons to be used
const uint32_t Potentiometer = PE_3;
const float PotentiometerMaxValue = 4095;

//Approximately 175 loops per second
const uint32_t secondTick = 175;
const uint32_t hungerLimit = secondTick * 60 * 5; //5 minutes
const uint32_t happyLimit = secondTick * 60 * 7; //7 minutes
const uint32_t toiletLimit = secondTick * 60 * 8; //8 minutes

int HUNGER_MIN = 0;
int HAPPY_MIN = 0;
const uint32_t TOILET_MAX = 8;
const uint32_t toiletShakeRequire = 50;

const uint32_t foodPrices[6][3] = {{100, 1, 0}, //milk
  {200, 2, 0}, //bread
  {300, 2, 1}, //pie
  {400, 2, 1}, //cherries
  {600, 3, 2}, //burger
  {200, 1, 1}
}; //drink
const uint32_t giftPrices[6][2] = {{100, 1}, //film
  {200, 2}, //dumbbells
  {300, 1}, //joystick
  {200, 3}, //headphones
  {400, 2}, //baseball
  {1000, 1}
}; //evolution

//End game
bool dead = false;


const uint8_t EGG = 0;
const uint8_t BABY = 1;
const uint8_t TEEN = 2;
const uint8_t ADULT = 3;
const uint8_t SENIOR = 4;



typedef struct PlayerStats
{
  //Age ranges from 0 (egg) to 4 (senior)
  int age;
  //Hunger ranges from 0 to 5
  int hunger;
  uint32_t hungerCounter;
  //Happiness ranges from 0 to 5 - can be obtained from playing games and buying gifts
  int happy;
  uint32_t happyCounter;
  //Number of poos onscreen ranges from 0 to 8
  int toilet;
  uint32_t toiletCounter;
  //Money can be obtained from playing games
  uint32_t money;
} Player;
Player player;
#define RED RED_LED
#define GREEN GREEN_LED

//Need to handle - if hearts below a certain level, change LED to red

struct ButtonState
{
  bool state;
  bool isRising;
};

static struct InputState
{
  bool                switches[2];
  struct ButtonState  buttons[2];
  float               potentiometer;
} gameInputState;


//Initialization
void GameUIInit()
{
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);

  gameInputState = { 0 };
  player = {1, 5, 0, 5, 0, 0, 0, 9999}; //{0,5,0,5,0,0,0,0}
  //activeGame = { 0 };


  //Set the hardware we're using to INPUT mode
  for (int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for (int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void goToPage(int page) {
  OrbitOledClearBuffer();
  OrbitOledClear();
  gameUiPage = page;
}

int shakeCounter = 0;

void handleMainScreen() {
  //display health/happy statusd
  //display tamagotchi
  StatsTick();

  DrawMainScreen(player.hunger, player.happy, player.money, player.toilet, player.age);
  OrbitOledUpdate();

  if (dead)
    goToPage(GameOver);
  //Serial.println(gameInputState.buttons[0].isRising);
  if (gameInputState.buttons[0].isRising) {
    goToPage(ShopMenu);
  }
  else if (gameInputState.buttons[1].isRising) {
    goToPage(GameMenu);
  }
}



void StatsTick() {
  player.hungerCounter++;
  player.happyCounter++;
  player.toiletCounter++;

  if (player.hungerCounter >= hungerLimit) {
    player.hunger--;
    if (player.hunger < HUNGER_MIN)
      dead = true;
    player.hungerCounter = 0;
    OrbitOledClearBuffer();
    OrbitOledClear();
  }
  if (player.happyCounter >= happyLimit) {
    player.happy--;
    if (player.happy < HAPPY_MIN) //player dies when really unhappy...?
      dead = true;
    player.happyCounter = 0;
    OrbitOledClearBuffer();
    OrbitOledClear();
  }
  if (player.toiletCounter >= toiletLimit) {
    player.toilet++;
    if (player.toilet > TOILET_MAX)
      dead = true;
    player.toiletCounter = 0;
    OrbitOledClearBuffer();
    OrbitOledClear();
  }


  if (ShakeIsShaking()) {
    shakeCounter++;
  }
  if (shakeCounter >= toiletShakeRequire)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    player.toilet = 0;
    Serial.println(player.toilet);
    shakeCounter = 0;
  }

}


void handleShopMenu() {
  int x = 11, y1 = 5, y2 = 18, offset = 9; //where am I putting this
  int option = gameInputState.potentiometer / (PotentiometerMaxValue / 2 + 1);
  if (option != GlobalOption) {
    OrbitOledClear();
    GlobalOption = option;
  }
  OrbitOledMoveTo(x, y1);
  OrbitOledDrawString("Food");

  //change x and y coordinates
  OrbitOledMoveTo(x, y2);
  OrbitOledDrawString("Gifts");

  //display the arrow
  OrbitOledMoveTo(x - offset, (option == 0 ? y1 : y2));
  OrbitOledDrawChar('>');

  if (gameInputState.buttons[0].isRising && option == 0) {
    goToPage(FoodMenu);
  }
  else if (gameInputState.buttons[0].isRising && option == 1) {
    goToPage(GiftMenu);
  }

  if (gameInputState.buttons[1].isRising) {
    goToPage(MainScreen);
  }
}


int eatFood(int value) {
  player.hunger += value;
  if (player.hunger > 5)
    player.hunger = 5;
}

int gainHappy(int value) {
  player.happy += value;
  if (player.happy > 5)
    player.happy = 5;
}

void handleFoodMenu() {
  //display food options
  //display blablabla
  int option = gameInputState.potentiometer / (PotentiometerMaxValue / 6 + 1.0);
  if (option != GlobalOption) {
    OrbitOledClear();
    GlobalOption = option;
  }
  displayFood(option, foodPrices[option][0], foodPrices[option][1], foodPrices[option][2]);
  if (gameInputState.buttons[0].isRising) {
    //lose money
    if (player.money >= foodPrices[option][0])
    {
      player.money -= foodPrices[option][0];
      eatFood(foodPrices[option][1]);
      gainHappy(foodPrices[option][2]);
      foodAnimations(option, player.age);
    }
    //display food
    //isFood = true >> eating animation? >> gain hunger/happy

    goToPage(MainScreen);
  }

  if (gameInputState.buttons[1].isRising) {
    goToPage(MainScreen);
  }
}
void handleGiftMenu() {
  //display food options
  //display blablabla
  int option = gameInputState.potentiometer / (PotentiometerMaxValue / 6 + 1.0);
  if (player.age == SENIOR && option == 5) //no more evolution at senior stage
    option = 4;
  if (option != GlobalOption) {
    OrbitOledClear();
    GlobalOption = option;
  }
  displayGifts(option, giftPrices[option][0], giftPrices[option][1], player.age);
  if (gameInputState.buttons[0].isRising) {
    //lose money
    if (player.money >= giftPrices[option][0])
    {
      player.money -= giftPrices[option][0];
      gainHappy(giftPrices[option][1]);
      giftAnimations(option, player.age);
      if (option == 5)
        player.age++;
    }

    goToPage(MainScreen);
  }

  if (gameInputState.buttons[1].isRising) {
    goToPage(MainScreen);
  }
}
void handleGameMenu() {
  int x = 11, y1 = 5, y2 = 18, offset = 9; //where am I putting this
  int option = gameInputState.potentiometer / (PotentiometerMaxValue / 2 + 1);
  if (option != GlobalOption) {
    OrbitOledClear();
    GlobalOption = option;
  }
  OrbitOledMoveTo(x, y1);
  OrbitOledDrawString("Dance");

  //change x and y coordinates
  OrbitOledMoveTo(x, y2);
  OrbitOledDrawString("Jump");

  //display the arrow
  OrbitOledMoveTo(x - offset, (option == 0 ? y1 : y2));
  OrbitOledDrawChar('>');

  if (gameInputState.buttons[0].isRising && option == 0) {
    initDanceGame();
    goToPage(DanceGame);
  }
  else if (gameInputState.buttons[0].isRising && option == 1) {
    goToPage(JumpGame);
  }

  if (gameInputState.buttons[1].isRising) {
    goToPage(MainScreen);
  }
}

void handleDanceGame() {
  uint8_t reward = danceGame();
  if (reward) {
    player.money += reward;
    gameUiPage = MainScreen;
  }
}

const uint16_t petHeight = 16;
const uint32_t maxHeight = 0;
const uint32_t vx = 2;
const uint16_t hurdleHeight = 8;
const uint16_t xstart = 5;
const int slow = 15;
const int numOfHurdles = 4;
const int screenSizeY = 32;
bool isJumping = false;
uint32_t vy = 0;
uint32_t y = petHeight;
int slowcnt = 0;
int jumpGame = 6;
int hurdle[numOfHurdles] = {0};
int hurdleIdx = 0;
int level = 0;

static void clearGameVar() {
  //jumpGame
  isJumping = false;
  vy = 0;
  y = petHeight;
  for (int i = 0; i < numOfHurdles; i++)
    hurdle[i] = 0;
  hurdleIdx = 0;
  slowcnt = 0;

  //All
  level = 1;
}

static void handleJumpGame() {

  if (slowcnt == slow - level) {

    OrbitOledClearBuffer();
    OrbitOledClear();
    slowcnt = 0;

    //jumping
    if (vy != 0) {
      y -= vy;
      if (y == petHeight) {
        vy = 0;
        isJumping = false;
      }
      if (y == maxHeight) vy = -vy;
    }

    //hurdle generation

    if (rand() % 30 == 0 && !hurdle[hurdleIdx]) {
      hurdle[hurdleIdx] = 128;
      hurdleIdx = (hurdleIdx + 1) % numOfHurdles;
    }

    //draw pet
    drawPet(player.age, xstart, y, 0);

    //collision detection

    for (int j = 0; j < numOfHurdles; j++) {
      if (hurdle[j] >= xstart && xstart + petHeight >= hurdle[j] && y + petHeight >= screenSizeY - hurdleHeight) {
        for (int i = 0; i < y + petHeight + hurdleHeight - screenSizeY; i++) {
          if (checkPetBit(player.age, hurdle[j] - xstart, i)) {
            OrbitOledClear();
            OrbitOledMoveTo(5, 15);
            OrbitOledDrawString("Game Over");
            slowcnt = -1000000;
            break;
          }
        }
      }
    }

    //draw hurdle
    for (int i = 0; i < numOfHurdles; i++) {
      if (hurdle[i] != 0) {
        drawHurdle(hurdle[i], hurdleHeight);
        hurdle[i] -= vx;
      }
    }
  }
  else
    slowcnt++;

  if (gameInputState.buttons[0].isRising && !isJumping) {
    vy = 1;
    isJumping = true;
  }
  else if (gameInputState.buttons[1].isRising) {
    clearGameVar();
    handleMainScreen();
    //handleExitMenu(jumpGame);
  }
}

static void handleExitMenu(int game) {
  //exit menu
}

//reads input on each tick, need one check per hardware element
static void uiInputTick()
{
  //switches
  for (int i = 0; i < SwitchCount; ++i )
    gameInputState.switches[i] = digitalRead(Switches[i]);

  //buttons
  for (int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameInputState.buttons[i].state;
    gameInputState.buttons[i].state = digitalRead(Buttons[i]);
    gameInputState.buttons[i].isRising = (!previousState && gameInputState.buttons[i].state);
  }

  //potentiometer
  gameInputState.potentiometer = analogRead(Potentiometer);


  //  player.hunger++;
  //  //Max integer: 2147483647
  //  Serial.println(player.hunger);
  //  struct PlayerStats
  //{

}

void handleGameOver() {
  gameOverGraphics();
  OrbitOledUpdate();
  if (gameInputState.buttons[0].isRising || gameInputState.buttons[1].isRising) {
    dead = false;
    player = {EGG, 5, 0, 5, 0, 0, 0, 0};
    goToPage(MainScreen);
  }
}

void handleGameStart() {
  gameStartEgg();
  for (int i = 2000; i > 1; i /= 2)
  {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    delay(i);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    delay(i);
  }
  gameStartHatch();
  delay(1300);
  player.age = BABY;
  goToPage(MainScreen);
}

//changes game state on each tick
void GameUITick()
{
  uiInputTick();

  switch (gameUiPage) {

    case StartScreen:
      handleGameStart();
      break;

    case ShopMenu:
      handleShopMenu();
      break;

    case FoodMenu:
      handleFoodMenu();
      break;

    case GiftMenu:
      handleGiftMenu();
      break;

    case GameMenu:
      handleGameMenu();
      //handleJumpGame();
      break;

    case MainScreen:
      handleMainScreen();
      break;

    case GameOver:
      handleGameOver();
      break;

    case DanceGame:
      handleDanceGame();
      //handleMainScreen();
      break;

    case JumpGame:
      handleJumpGame();
      break;
  }
  OrbitOledUpdate();
}



