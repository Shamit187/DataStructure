//
// Created by User on 3/16/2021.
//

#ifndef INC_3_14_21_LINKEDLIST_PILLOWPASSINGWRAPPER_H
#define INC_3_14_21_LINKEDLIST_PILLOWPASSINGWRAPPER_H
#include "LinkedList.h"

struct Player{
    unsigned int playerId;
    unsigned int reflexTime;
    bool isActive;
    unsigned int timeElapsed;

    friend std::ostream& operator<<(std::ostream& os, const Player& obj){
        os << "Player ID: " << obj.playerId << " :: ";
        os << "Reflex Time: " << obj.reflexTime << std::endl;
        return os;
    }

    bool operator==(const Player& lhs) const{
        return(playerId == lhs.playerId);
    }
};


class PillowPassingWrapper {
private:
    LinkedList<Player> playerData;
    LinkedList<Player>::iterator currentPlayer;
    unsigned int currentTime;
    bool isReversed;

public:

    //constructor
    PillowPassingWrapper();

    //adder
    void add(unsigned int id, unsigned int time);

    //remover
    void eliminate(unsigned int time);

    //getter
    unsigned int getCurrentPlayer(unsigned int time);
    bool getDirection() const;
    unsigned int playerNumber();
    void printPossibleSequence();

    //setter
    void changeDirection();

    //overloads
    friend std::ostream& operator<<(std::ostream& os, const PillowPassingWrapper& obj);
};


#endif //INC_3_14_21_LINKEDLIST_PILLOWPASSINGWRAPPER_H
