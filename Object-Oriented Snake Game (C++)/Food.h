#ifndef FOOD_H
#define FOOD_H

#include <cstdlib> // to use rand()
#include "objPosArrayList.h" // for using the objPosArrayList and objPos class

class Food
{
private:
    objPosArrayList* foodBucket; // dynamic food storage list
    
    // board width and height
    int boardSizeX;
    int boardSizeY;

public:
    // this is a constructor!!
    // purpose: initialize board sizes and create empty food lists
    Food(int boardX, int boardY)
    {
        boardSizeX = boardX;
        boardSizeY = boardY;
        foodBucket = new objPosArrayList();
    }

    // this is a destructor!!
    // purpose: frees heap memory associated with the food list
    ~Food()
    {
        delete foodBucket;
    }

    // this will generate a count of the number of the food objects while AVOIDING the snake and any existing food overlapping
    void generateFoodBucket(const objPosArrayList &snakeBody, int count)
    {
        delete foodBucket;
        foodBucket = new objPosArrayList();

        for (int i = 0; i < count; i++)
        {
            bool overlap;
            objPos newFood;

            do
            {
                int x = (std::rand() % (boardSizeX - 2)) + 1;
                int y = (std::rand() % (boardSizeY - 2)) + 1;

                char sym = '+';
                if (i == 0)
                {
                    sym = '$';
                }

                newFood.setObjPos(x, y, sym); // newFood object is where the values will be stored

                overlap = false;

                // FIRST CHECK
                // check if the position is overlapping with the snake body
                for (int j = 0; j < snakeBody.getSize(); j++)
                {
                    objPos seg = snakeBody.getElement(j);
                    if (newFood.isPosEqual(&seg))
                    {
                        overlap = true;
                        break;
                    }
                }

                // SECOND CHECK
                // ONLY check food overlapping if the snake check has passed
                if (!overlap)
                {
                    for (int k = 0; k < foodBucket->getSize(); k++)
                    {
                        objPos existing = foodBucket->getElement(k);
                        if (newFood.isPosEqual(&existing))
                        {
                            overlap = true;
                            break;
                        }
                    }
                }

            } while (overlap);

            foodBucket->insertTail(newFood);
        }
    }

    objPosArrayList* getFoodBucket() const // returning a pointer to the list containing all the food items
    {
        return foodBucket;
    }
};

#endif