#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
// this will be our constructor!!!
objPosArrayList::objPosArrayList(){
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity]; // we are now allocating heap memory 
    listSize = 0; // currently we are using an empty list
}

// this will be our destructor!!! 
objPosArrayList::~objPosArrayList(){
    delete[] aList; // this will free our heap memory
}

// we will now be returning the # of valid items that are present in our list
int objPosArrayList::getSize() const {
    return listSize; // returning the list size counter
}

// we will now be inserting a new element where our index = 0
void objPosArrayList::insertHead(objPos thisPos){
    if (listSize >= arrayCapacity)
        return; // this will see there's no space and will ignore the insertion

    for (int i = listSize; i > 0; i--){ // we will shifting the elements 
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos; // new element will become the head
    listSize++;
}

// will now be removing an element where our index = 0
void objPosArrayList::removeHead(){
    if (listSize <= 0)
        return; // there is nothing to remove 
    
    for (int i = 0; i < listSize - 1; i++){ // we will be shifting everything left one position so that the index = 0 becomes available
        aList[i] = aList[i + 1];
    }

    listSize--; // one less valid element
}

// we will now be getting the element of the HEAD
objPos objPosArrayList::getHeadElement() const{
    return aList[0];
}

// will now be getting the element of the TAIL
objPos objPosArrayList::getTailElement() const{
    return aList[listSize - 1];
}

// we will now be getting an element at a specific index 
objPos objPosArrayList::getElement(int index) const{
    return aList[index];
}

void objPosArrayList::insertTail(objPos thisPos){
    if (listSize >= arrayCapacity)
        return; // there is no more space, so we ignore the insertion

    // the next free slot becomes the new tail
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeTail(){
    if (listSize <= 0)
        return; // there is nothing to remove

    listSize--;
}