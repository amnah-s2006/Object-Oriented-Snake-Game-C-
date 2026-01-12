#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Food;

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        void getPlayerPos(objPos &returnPos) const; 
        objPosArrayList* getPlayerPosList() const;
        int getPlayerLength() const;

        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here
        void setFood(Food* thisFoodRef);

    private:
        objPosArrayList* playerPosList; // the snake body, with it's head t the index 0       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* mainFoodRef;
};

#endif
