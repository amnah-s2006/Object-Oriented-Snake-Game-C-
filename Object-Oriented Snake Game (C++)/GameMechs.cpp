#include "GameMechs.h"

GameMechs::GameMechs() // this is our default constructor
{
    srand(time(NULL));

    boardSizeX = 30;
    boardSizeY = 15;

    input    = 0;
    exitFlag = false;
    loseFlag = false;
    score    = 0;
}

GameMechs::GameMechs(int boardX, int boardY) // this constructor will intialize board size using the given parameters
{
    srand(time(NULL));

    boardSizeX = boardX;
    boardSizeY = boardY;

    input    = 0;
    exitFlag = false;
    loseFlag = false;
    score    = 0;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag; // returns true when player requests exit
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag; // returns true when the lose condition is met
}

char GameMechs::getInput() const
{
    return input; // returns the recent input key
}

int GameMechs::getScore() const
{
    return score; // returns current score
}

void GameMechs::incrementScore()
{
    score++; // increase score by 1
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX; // gets board width
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY; // gets board height
}

void GameMechs::setExitTrue()
{
    exitFlag = true; // sets exit flag to true to end game
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; // loseflag will be set to true indicating snake collision
}

void GameMechs::setInput(char this_input)
{
    input = this_input; // stores user's input character
}

void GameMechs::clearInput()
{
    input = 0; // clears input to ensure movement does not repeat
}

// this is the food generation where only one blocked position is avoided 
void GameMechs::generateFood(const objPos &blockOff)
{
    int Xnew, Ynew;

    do
    {
        Xnew = (rand() % (boardSizeX - 2)) + 1;
        Ynew = (rand() % (boardSizeY - 2)) + 1;

        food.setObjPos(Xnew, Ynew, '+');
    }
    while (food.isPosEqual(&blockOff));
}

// returns position of the food
objPos GameMechs::getFoodPos() const
{
    return food.getObjPos();
}

// checking entire snake body and ensures food does not spawn on any segments
void GameMechs::generateFood(const objPosArrayList &blockOffList)
{
    int Xnew, Ynew;
    bool overlap;

    do
    {
        Xnew = (rand() % (boardSizeX - 2)) + 1;
        Ynew = (rand() % (boardSizeY - 2)) + 1;

        food.setObjPos(Xnew, Ynew, '+');

        overlap = false;

        for (int i = 0; i < blockOffList.getSize(); i++)
        {
            objPos segment = blockOffList.getElement(i);

            if (food.isPosEqual(&segment))
            {
                overlap = true;
                break;
            }
        }
    }
    while (overlap);
}