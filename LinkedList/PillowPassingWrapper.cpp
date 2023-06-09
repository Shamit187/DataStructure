//
// Created by User on 3/16/2021.
//

#include "PillowPassingWrapper.h"

PillowPassingWrapper::PillowPassingWrapper()
    :currentTime(0), isReversed(false), currentPlayer(nullptr){
}

void PillowPassingWrapper::add(unsigned int id, unsigned int time) {
    Player newInput{};
    newInput.isActive = false;
    newInput.playerId = id;
    newInput.reflexTime = time;
    newInput.timeElapsed = 0;
    playerData.add(newInput);
}

void PillowPassingWrapper::eliminate(unsigned int time) {
    Player deleteThisPlayer = *currentPlayer;
    if(currentPlayer == playerData.end() && !isReversed){
        currentPlayer = playerData.begin();
    }else if(currentPlayer == playerData.begin() && isReversed){
        currentPlayer = playerData.end();
    }else if(!isReversed){
        currentPlayer++;
    }else{
        currentPlayer--;
    }
    playerData.remove(deleteThisPlayer);
}

unsigned int PillowPassingWrapper::getCurrentPlayer(unsigned int time) {
    if(currentTime == 0){
        currentPlayer = playerData.begin();
    }
    int timeElapsed = time - currentTime;
    if((*currentPlayer).isActive){
        timeElapsed -= ((*currentPlayer).reflexTime - (*currentPlayer).timeElapsed);
    }else {
        timeElapsed -= (*currentPlayer).reflexTime;
    }
    while(timeElapsed > 0){
        (*currentPlayer).isActive = false;
        (*currentPlayer).timeElapsed = 0;
        if(currentPlayer == playerData.end() && !isReversed){
            currentPlayer = playerData.begin();
        }else if(currentPlayer == playerData.begin() && isReversed){
            currentPlayer = playerData.end();
        }else if(!isReversed){
            currentPlayer++;
        }else{
            currentPlayer--;
        }
        timeElapsed -= (*currentPlayer).reflexTime;
    }
    (*currentPlayer).timeElapsed = timeElapsed + (*currentPlayer).reflexTime;
    (*currentPlayer).isActive = true;
    currentTime = time;
    return (*currentPlayer).playerId;
}

bool PillowPassingWrapper::getDirection() const {
    return !isReversed;
}

std::ostream &operator<<(std::ostream &os, const PillowPassingWrapper &obj) {
    os << obj.playerData ;
    return os;
}

void PillowPassingWrapper::changeDirection() {
    isReversed = !isReversed;
}

unsigned int PillowPassingWrapper::playerNumber() {
    return playerData.length();
}

void PillowPassingWrapper::printPossibleSequence() {
    LinkedList<Player>::iterator printIter = currentPlayer;
    LinkedList<Player>::iterator rem = printIter;
    do{
        std::cout << (*printIter).playerId;
        if (printIter == playerData.end() && !isReversed) {
            printIter = playerData.begin();
        } else if (printIter == playerData.begin() && isReversed) {
            printIter = playerData.end();
        } else if (!isReversed) {
            printIter++;
        } else {
            printIter--;
        }
        if(printIter != rem){
            std::cout << ", " ;
        }
    }while(printIter != rem);
}


