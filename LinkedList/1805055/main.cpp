#include "LinkedList.h"
#include "PillowPassingWrapper.h"

int main() {

    /*
    //checking LinkedList
    LinkedList<int> myData1;
    for(int i = 0; i < 10; i++){
        myData1.add(i);
    }
    std::cout << myData1;
    LinkedList<int> myData2(myData1);
    std::cout << myData2;

    LinkedList<int>::iterator index = myData1.begin();
    while(index != myData1.end()){
        std::cout << *index << " ";
        index++;
    }
    std::cout << *index << std::endl;

    LinkedList<int>::iterator j = myData1.end();
    while(index != myData1.begin()){
        std::cout << *j << " ";
        try{
           j--;
        }catch(std::exception& e){
            std::cout << std::endl << "Standard Exception: " << e.what() << std::endl;
            break;
        }
    }

    for(unsigned int i = 0; i < 10; i++){
        std::cout << myData1.getElement(i) << " ";
    }
    std::cout << std::endl;
    for(unsigned int i = 0; i < 10; i++){
        std::cout << myData1[i] << " ";
        myData1[i] = i * 20;
    }
    std::cout << std::endl;
    for(unsigned int i = 0; i < 10; i++){
        std::cout << myData1.getElement(i) << " ";
    }
    std::cout << std::endl;

    myData2.add(2);
    std::cout << myData2.length() << std::endl;
    try {
        myData2.remove(4);
        std::cout << myData2.length() << std::endl;
        myData2.remove(2);
        std::cout << myData2.length() << std::endl;
        myData2.removeAt(3);
        std::cout << myData2.length() << std::endl;
        myData2.removeAt(6);
        std::cout << myData2.length() << std::endl;
    }catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }
    std::cout << myData2;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    //checking Game
     */

    /*
    //PillowPassingTest
    PillowPassingWrapper game1;
    game1.add(1, 2);
    game1.add(2,5);
    game1.add(3,3);
    game1.add(4,4);
    game1.add(5,2);

    std::cout << game1;
    for(int i = 1; i < 40; i++){
        std::cout << "time = " << i << "\t player = " << game1.getCurrentPlayer(i) << std::endl;
        if(i == 20 || i == 30){
            game1.eliminate(i);
        }
        if(i == 25){
            game1.changeDirection();
        }
    }
    std::cout << game1;
    */

    unsigned int numberOfPlayers;
    std::cin >> numberOfPlayers;
    PillowPassingWrapper mainGame;
    for(int i = 0; i < numberOfPlayers; i++){
        int reflexTime;
        std::cin >> reflexTime;
        mainGame.add(i + 1, reflexTime);
    }
    char option;
    unsigned int timeStamp;
    bool gameOver = false;
    while(!gameOver){
        std::cin >> timeStamp;
        std::cin >> option;
        switch(option){
            case 'M':
                std::cout << "Player " << mainGame.getCurrentPlayer(timeStamp) << " has been eliminated at t=" << timeStamp << std::endl;
                mainGame.eliminate(timeStamp);
                if(mainGame.playerNumber() == 1){
                    std::cout << "Game over : Player " << mainGame.getCurrentPlayer(timeStamp) << " wins!!" << std::endl;
                    gameOver = true;
                }
                break;
            case 'R':
                mainGame.getCurrentPlayer(timeStamp);
                mainGame.changeDirection();
                break;
            case 'I':
                if(mainGame.playerNumber() == 1){
                    break;
                }
                unsigned int reflexTime;
                std::cin >> reflexTime;
                mainGame.add(++numberOfPlayers, reflexTime);
                break;
            case 'P':
                std::cout << "Player " << mainGame.getCurrentPlayer(timeStamp) << " is holding the pillow at t=" << timeStamp << std::endl;
                break;
            case 'F':
                if(mainGame.playerNumber() == 1){
                    std::cout << "Game over : Player " << mainGame.getCurrentPlayer(timeStamp) << " wins!!" << std::endl;
                } else{
                    std::cout << "Game over : Player " << mainGame.getCurrentPlayer(timeStamp)
                                << " is holding the pillow at t=" << timeStamp
                                << ", pillow passing sequence = Player ";
                    mainGame.printPossibleSequence();
                    std::cout << std::endl;
                }
                gameOver = true;
                break;

        }
    }
}
