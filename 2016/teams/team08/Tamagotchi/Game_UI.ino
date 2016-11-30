//To hack the game for testing purposes:
//Under the "Game Constants" section, set startingCash = 9999 or any other value to start the game off with extra cash
//To decrease the time it takes for things to happen, under the "Game Constants" section, set secondTick = 3 or any small number
//To skip the intro screen where the egg hatches, under "gameUiPages" set gameUiPage = MainScreen
//Also in the function "handleGameOver()", change the last line to goToPage(MainScreen) to skip intro in future generations

#include <stdbool.h>
#include <string.h>
#include<limits.h>

//--------------------- Hardware info ---------------------
const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 2;
const uint32_t Switches[2] = { PA_7, PA_6 };  //List of switches to be used
const uint32_t Buttons[2] = {PE_0, PD_2 };   //List of Buttons to be used
const uint32_t Potentiometer = PE_3;
const float PotentiometerMaxValue = 4095;
const uint8_t screenSizeY = 32;
const uint8_t screenSizeX = 128;
#define RED RED_LED
#define GREEN GREEN_LED

//--------------------- gameUiPages ---------------------
const uint8_t MainScreen    = 0;  //Displays Tamagotchi and Information
const uint8_t ShopMenu      = 1;  //Shop for Food or Gifts
const uint8_t FoodMenu      = 2;  //Can pick among various Foods
const uint8_t GiftMenu      = 3;  //Can pick among various Gifts
const uint8_t GameMenu      = 4;  //Can pick among various Games
const uint8_t GameOver      = 5;  //Game over screen
const uint8_t StartScreen   = 6;  //Welcome screen (egg hatching)
const uint8_t DanceGame     = 7;  //Dance game
const uint8_t JumpGame      = 8;  //Jump game
//Initialize the game on the start screen
uint32_t gameUiPage = StartScreen;

//--------------------- Game Constants ---------------------
const uint32_t startingCash = 0;

//Evolution stages
const uint8_t BABY = 1;
const uint8_t TEEN = 2;
const uint8_t ADULT = 3;
const uint8_t SENIOR = 4;

//Time tickers (for timing hunger, happiness, toilet, and old age death)
//Approximately 175 loops per second
const uint32_t secondTick = 175;
const uint32_t hungerLimit = secondTick * 60 * 5; //5 minutes
const uint32_t happyLimit = secondTick * 60 * 7; //7 minutes
const uint32_t toiletLimit = secondTick * 60 * 8; //8 minutes
const uint32_t oldAgeLimit = secondTick * 60 * 5; //After evolving to old person, only 5 minutes before they pass away

const uint32_t toiletShakeRequire = 50; //Shake for a bit before cleaning toilet
const uint32_t minigame_moneyMod = 50;  //Each level of any minigame gives $50. Bonus for clearing all levels.

//If any of the following are reached, the pet dies
const int HUNGER_MIN = 0;
const int HAPPY_MIN = 0;
const uint32_t TOILET_MAX = 8;

//Shop item prices and stats
//Food: {price, hunger increase, happy increase}
const uint32_t foodPrices[6][3] = {
  {100, 1, 0}, //milk
  {200, 2, 0}, //bread
  {400, 1, 2}, //pie
  {300, 1, 1}, //cherries
  {600, 3, 2}, //burger
  {200, 0, 1}  //drink
};
//Gifts: {price, happy increase}
const uint32_t giftPrices[6][2] = {
  {100, 1}, //film
  {200, 2}, //dumbbells
  {300, 1}, //joystick
  {200, 3}, //headphones
  {400, 2}, //baseball
  {1000, 0} //evolution
};

//--------------------- Game Variables ---------------------
int globalOption = 0; //Used to toggle which option is chosen in the shop menus
bool dead = false; //Toggle if the game ends

//Player stats
struct PlayerStats {
  int age; //Age ranges from 1 (baby) to 4 (senior)
  int hunger;//Hunger ranges from 0 to 5
  int happy; //Happiness ranges from 0 to 5 - can be obtained from playing games and buying gifts
  int toilet; //Number of poos onscreen ranges from 0 to 8
  uint32_t money; //Money can be obtained from playing games
} player;

//Tickers (timers)
struct TickerTimers {
  uint32_t hunger;
  uint32_t happy;
  uint32_t toilet;
  uint32_t oldAge; //When the player gets to old age
  uint32_t shake; //Shake ticker
} ticker;

struct ButtonState {
  bool state;
  bool isRising;
};

static struct InputState {
  bool                switches[2];
  struct ButtonState  buttons[2];
  float               potentiometer;
} gameInputState;


//--------------------- Initialization ---------------------
void GameUIInit()
{
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);

  //Initialize all structs
  gameInputState = { 0 };
  player = {BABY, 5, 5, 0, startingCash};
  ticker = {0};

  //Set the hardware we're using to INPUT mode
  for (int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for (int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);

  //Set LED to output
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}



//--------------------- Handling Player Stats ---------------------
//Stats ticker (happy, hunger, toilet, old age, shaking)
void StatsTick() {
  ticker.hunger++;
  ticker.happy++;
  ticker.toilet++;
  if (player.age == 4)
    ticker.oldAge++;

  //Toggle lights based on pet's health
  if (player.hunger < 3 || player.happy < 3 || player.toilet > 4) {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
  }
  if (player.hunger >= 3 && player.happy >= 3 && player.toilet <= 4) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
  }

  //If the pet is too neglected, it dies (yes, it can die from lack of happiness)
  if (ticker.hunger >= hungerLimit) {
    player.hunger--;
    if (player.hunger < HUNGER_MIN)
      dead = true;
    ticker.hunger = 0;
    OrbitOledClearBuffer();
    OrbitOledClear();
  }
  if (ticker.happy >= happyLimit) {
    player.happy--;
    if (player.happy < HAPPY_MIN)
      dead = true;
    ticker.happy = 0;
    OrbitOledClearBuffer();
    OrbitOledClear();
  }
  if (ticker.toilet >= toiletLimit) {
    player.toilet++;
    if (player.toilet > TOILET_MAX)
      dead = true;
    ticker.toilet = 0;
    OrbitOledClearBuffer();
    OrbitOledClear();
  }

  //Shake counter - if the screen is shaken, the poos are cleared
  if (ShakeIsShaking())
    ticker.shake++;
  if (ticker.shake >= toiletShakeRequire)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    player.toilet = 0;
    ticker.shake = 0;
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

//--------------------- Handling all the screens ---------------------
//Used to toggle which page to go to
void goToPage(int page) {
  OrbitOledClearBuffer();
  OrbitOledClear();
  gameUiPage = page;
}
void handleMainScreen() {
  StatsTick();

  //Display all stats and pet
  DrawMainScreen(player.hunger, player.happy, player.money, player.toilet, player.age);

  //If the pet dies from negligence or old age, go to game over
  if (dead || ticker.oldAge >= oldAgeLimit)
    goToPage(GameOver);

  //Handle input - go to menus (top button for shops, bottom button for games)
  if (gameInputState.buttons[0].isRising)
    goToPage(ShopMenu);
  else if (gameInputState.buttons[1].isRising)
    goToPage(GameMenu);
}

//Menu to choose between food shop and gifts shop
void handleShopMenu() {
  //Use potentiometer to toggle between options
  int option = gameInputState.potentiometer / (PotentiometerMaxValue / 2 + 1);
  if (option != globalOption) {
    OrbitOledClear();
    globalOption = option;
  }

  //Display graphics
  displayShopMenu(option);

  if (gameInputState.buttons[0].isRising && option == 0)
    goToPage(FoodMenu);
  else if (gameInputState.buttons[0].isRising && option == 1)
    goToPage(GiftMenu);

  //Back button
  if (gameInputState.buttons[1].isRising)
    goToPage(MainScreen);
}

void handleFoodMenu() {
  //Use potentiometer to toggle between options
  int option = gameInputState.potentiometer / (PotentiometerMaxValue / 6 + 1.0);
  if (option != globalOption) {
    OrbitOledClear();
    globalOption = option;
  }

  //Display graphics
  displayFood(option, foodPrices[option][0], foodPrices[option][1], foodPrices[option][2]);

  if (gameInputState.buttons[0].isRising) {
    if (player.money >= foodPrices[option][0]) //If player has enough money, decrement money and change stats
    {
      player.money -= foodPrices[option][0];
      eatFood(foodPrices[option][1]);
      gainHappy(foodPrices[option][2]);
      foodAnimations(option, player.age);
    }

    goToPage(MainScreen);
  }

  //Back button
  if (gameInputState.buttons[1].isRising)
    goToPage(MainScreen);
}

void handleGiftMenu() {
  //Use potentiometer to toggle between options
  int option = gameInputState.potentiometer / (PotentiometerMaxValue / 6 + 1.0);
  if (player.age == SENIOR && option == 5) //no more evolution at senior stage, so take this option out of the menu
    option = 4;
  if (option != globalOption) {
    OrbitOledClear();
    globalOption = option;
  }
  
  //Display graphics
  displayGifts(option, giftPrices[option][0], giftPrices[option][1], player.age);
  
  if (gameInputState.buttons[0].isRising) {
    //lose money
    if (player.money >= giftPrices[option][0]) //If player has enough money, decrement money and change stats
    {
      player.money -= giftPrices[option][0];
      gainHappy(giftPrices[option][1]);
      giftAnimations(option, player.age);
      if (option == 5) //Evolution
        player.age++;
    }

    //Back button
    goToPage(MainScreen);
  }

  if (gameInputState.buttons[1].isRising) {
    goToPage(MainScreen);
  }
}

//Choose between games
void handleGameMenu() {
  //Use potentiometer to toggle between options
  int option = gameInputState.potentiometer / (PotentiometerMaxValue / 2 + 1);
  if (option != globalOption) {
    OrbitOledClear();
    globalOption = option;
  }

  //Display graphics
  displyGameMenu(option);

  if (gameInputState.buttons[0].isRising && option == 0) {
    initDanceGame();
    goToPage(DanceGame);
  }
  else if (gameInputState.buttons[0].isRising && option == 1) {
    initJumpGame();
    goToPage(JumpGame);
  }

  //Back button
  if (gameInputState.buttons[1].isRising)
    goToPage(MainScreen);
}

void handleDanceGame() {
  int reward = danceGame();
  if (reward != -1) {
    player.money += reward*minigame_moneyMod;
    gameUiPage = MainScreen;
  }
}

void handleJumpGame() {
  int reward = jumpGame();
  if (reward != -1) {
    player.money += reward*minigame_moneyMod;
    gameUiPage = MainScreen;
  }
}


//--------------------- Game start and end ---------------------
//This is run once at the beginning - it's an animation
void handleGameStart() {
  DrawGameStartEgg();
  for (int i = 2000; i > 1; i /= 2)
  {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    delay(i);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    delay(i);
  }
  DrawGameStartHatch();
  delay(1300);
  goToPage(MainScreen);
}

//This is run at the end, when the pet either dies from neglection or old age.
//Player can start over by pressing a button
void handleGameOver() {
  gameOverGraphics(dead); //Either dead from neglection or old age
  OrbitOledUpdate();
  if (gameInputState.buttons[0].isRising || gameInputState.buttons[1].isRising) {
    //Reset all stats
    dead = false;
    player = {BABY, 5, 5, 0, startingCash};
    ticker = {0};
    goToPage(StartScreen);
  }
}


//--------------------- Hardware Element Check ---------------------
//Taken from Rollen's code
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

}

//--------------------- Overall Ticker ---------------------
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
      break;

    case MainScreen:
      handleMainScreen();
      break;

    case GameOver:
      handleGameOver();
      break;

    case DanceGame:
      handleDanceGame();
      break;

    case JumpGame:
      handleJumpGame();
      break;
  }
  OrbitOledUpdate();
}



