#include <iostream> 
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

GameMechs* mainGameMechs;
Player*    mainPlayer;
Food*      mainFood;

using namespace std;

#define DELAY_CONST 100000 // delay between screens

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

// intializing game components
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    mainGameMechs = new GameMechs();
    mainPlayer    = new Player(mainGameMechs);

    mainFood = new Food(mainGameMechs->getBoardSizeX(),
                        mainGameMechs->getBoardSizeY());

    mainPlayer->setFood(mainFood);

    mainFood->generateFoodBucket(*mainPlayer->getPlayerPosList(), 5);
}

// keyboard input handel
void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        mainGameMechs->setInput(MacUILib_getChar());
    }
}

// game updates (movement, direction, exitflag)
void RunLogic(void)
{
    mainPlayer->updatePlayerDir();
    mainPlayer->movePlayer();

    exitFlag = mainGameMechs->getExitFlagStatus();    
}

// draws the game
void DrawScreen(void)
{
    MacUILib_clearScreen();

    int maxX = mainGameMechs->getBoardSizeX();
    int maxY = mainGameMechs->getBoardSizeY();

    objPosArrayList* body  = mainPlayer->getPlayerPosList();
    objPosArrayList* foods = mainFood->getFoodBucket();

    for (int y = 0; y < maxY; y++)
    {
        for (int x = 0; x < maxX; x++)
        {
            if (x == 0 || x == maxX - 1 || y == 0 || y == maxY - 1)
            {
                MacUILib_printf("#");
            }
            else
            {
                bool printed = false;

                // Snake Body
                for (int i = 0; i < body->getSize(); i++)
                {
                    objPos seg = body->getElement(i);
                    if (seg.pos->x == x && seg.pos->y == y)
                    {
                        MacUILib_printf("%c", seg.getSymbol());
                        printed = true;
                        break;
                    }
                }

                // Food
                if (!printed)
                {
                    for (int j = 0; j < foods->getSize(); j++)
                    {
                        objPos f = foods->getElement(j);
                        if (f.pos->x == x && f.pos->y == y)
                        {
                            MacUILib_printf("%c", f.getSymbol());
                            printed = true;
                            break;
                        }
                    }
                }

                // Empty
                if (!printed)
                {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }

    // game instrctions
    MacUILib_printf("Welcome to Amnah and Alisha's 2SH4 Snake Game!\n");
    MacUILib_printf("Controls: W A S D = move | F = respawn food | X = exit\n");
    MacUILib_printf("Score: %d\n", mainGameMechs->getScore());
}

// delay to slow game loop
void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); 
}

// cleaning dynamic memory
void CleanUp(void)
{
    MacUILib_clearScreen();

    // shut down message
    if (mainGameMechs->getLoseFlagStatus())
    {
        MacUILib_printf("YOU LOST! Your snake tried to eat itself!\n");
    }
    else
    {
        MacUILib_printf("Thanks for playing!\n");
    }


    delete mainPlayer;
    delete mainGameMechs;
    delete mainFood;

    MacUILib_uninit();
}