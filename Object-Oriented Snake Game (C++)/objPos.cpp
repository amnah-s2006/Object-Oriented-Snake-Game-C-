#include "objPos.h"

objPos::objPos() // default constructor
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0;
}

objPos::objPos(int xPos, int yPos, char sym) // constructor to create postion with x,y,sym
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos::objPos(const objPos& other) // copy constructor
{
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;
}

objPos& objPos::operator=(const objPos& other) // assignment operator
{
    if (this != &other)
    {
        pos->x = other.pos->x;
        pos->y = other.pos->y;
        symbol = other.symbol;
    }
    return *this;
}

objPos::~objPos() // destructor
{
    delete pos;
}

// setting the object's position and sym using another objPos object
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// setting the object's position and sym directly
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// returns full objPos object
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

// returns stored sym
char objPos::getSymbol() const
{
    return symbol;
}

// comparing positions
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// if 2 positions match, return symbol, if not 0 will be returned
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if (isPosEqual(refPos))
        return symbol;
    else
        return 0;
}