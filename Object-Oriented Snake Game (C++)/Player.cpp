#include "Player.h"
#include "Food.h"

// this is a constructor to set up the player in the center o the board
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();

    // finding center of board
    int midX = mainGameMechsRef->getBoardSizeX() / 2;
    int midY = mainGameMechsRef->getBoardSizeY() / 2;

    // starting position
    objPos start(midX, midY, '*');
    playerPosList->insertHead(start);

    mainFoodRef = nullptr;
}

Player::~Player() // destructor
{
    delete playerPosList;
}

// returning player head position
void Player::getPlayerPos(objPos &returnPos) const
{
    returnPos = playerPosList->getHeadElement();
}

// returning full list of player body positions
objPosArrayList* Player::getPlayerPosList() const
{
    return playerPosList;
}

// returning length of snake
int Player::getPlayerLength() const
{
    return playerPosList->getSize();
}

// this is where the code will read the latest user input to update the directions/movement of the player
void Player::updatePlayerDir()
{
    char in = mainGameMechsRef->getInput();

    switch (in)
    {
        case 'w':
        case 'W':
            myDir = UP;
            break;

        case 's':
        case 'S':
            myDir = DOWN;
            break;

        case 'a':
        case 'A':
            myDir = LEFT;
            break;

        case 'd':
        case 'D':
            myDir = RIGHT;
            break;

        case 'x':
        case 'X':
            mainGameMechsRef->setExitTrue();
            break;

        // this key will regenerate 5 food items
        case 'f':
        case 'F':
            if (mainFoodRef != nullptr)
            {
                mainFoodRef->generateFoodBucket(*playerPosList, 5);
            }
            break;

        default:
            break;
    }

    mainGameMechsRef->clearInput(); // preventing repeated movements
}

// this will move the snake, check for collisions, handles food, and updates score
void Player::movePlayer()
{
    if (myDir == STOP)
        return;

    objPos head = playerPosList->getHeadElement();

    int x = head.pos->x;
    int y = head.pos->y;

    int maxX = mainGameMechsRef->getBoardSizeX();
    int maxY = mainGameMechsRef->getBoardSizeY();

    switch (myDir)
    {
        case UP:
            y--; 
            break;

        case DOWN:
            y++;
            break;

        case LEFT:
            x--; 
            break;

        case RIGHT:
            x++; 
            break;

        default:
            break;
    }
    
    // this is our wraparound logic
    if (x < 0)
        x = maxX - 1;

    if (x >= maxX)
        x = 0;

    if (y < 0)
        y = maxY - 1;

    if (y >= maxY)
        y = 0;

    // collision check
    for (int i = 0; i < playerPosList->getSize(); i++)
    {
        objPos seg = playerPosList->getElement(i);
        if (seg.pos->x == x && seg.pos->y == y)
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            return;
        }
    }

    objPos newHead(x, y, '*');

    bool ateNormal  = false;
    bool ateSpecial = false;

    // checking if the head touches food
    if (mainFoodRef != nullptr)
    {
        objPosArrayList* foods = mainFoodRef->getFoodBucket();

        for (int i = 0; i < foods->getSize(); i++)
        {
            objPos f = foods->getElement(i);

            if (newHead.isPosEqual(&f))
            {
                if (f.getSymbol() == '$')
                {
                    ateSpecial = true;
                    for (int k = 0; k < 10; k++)
                    {
                        mainGameMechsRef->incrementScore();
                    }
                }
                else
                {
                    ateNormal = true;
                    mainGameMechsRef->incrementScore();
                }

                break;
            }
        }
    }

    playerPosList->insertHead(newHead);

    // if it eats normal food --> +1
    // otherwise --> the tail will be removed to ensure same size
    if (!ateNormal)
    {
        playerPosList->removeTail();
    }

    // regenerating the food bucket after eating food
    if (ateNormal || ateSpecial)
    {
        if (mainFoodRef != nullptr)
        {
            mainFoodRef->generateFoodBucket(*playerPosList, 5);
        }
    }
}

void Player::setFood(Food* thisFoodRef)
{
    mainFoodRef = thisFoodRef;
}