#include <iostream>
#include "DoubleHasing.h"
#include "CustomProbing.h"
#include "ChainHash.h"
#include "HashUtil.h"

#include <fstream>

int main() {
    /*
    int i = 1; //value starts with 1
    for(const auto& x: randomWordGenerator(10000, 7)){
        std::cout << x << "\t" <<
        i++ << "\t" <<
        polyRollHash(x, 10000, 4) << "\t" <<
        djbHash(x, 10000) << "\t" <<
        sdbmHash(x, 10000) << "\t" <<
        basicHash(x) << "\t" <<
        std::endl;
    }
     */

    /*
    int collision = 0;
    double probe = 0.0;

    for(int count = 0; count < 20; count++) {
        int i = 1;
        int len = 10000;
        ChainHash hashTable(len);
        std::vector<std::string> wordList = randomWordGenerator(len, 7);
        for(const auto& x: wordList){
            hashTable.insert(x, i++);
        }

        int search = random(0, 20);
        for(int j = 0; j < 1000; j++){
            int value = hashTable.search(wordList[search]);
            if( value != search + 1 ) std::cout << "Oh damn" << std::endl;
            search += random(0, 20);
            search %= len;
        }

        collision += hashTable.getCollision();
        probe += (hashTable.getProbe() / 1000.0);
        std::cout << hashTable.getCollision() << "\t" << hashTable.getProbe() / 1000.0 << std::endl;
        hashTable.resetProbe();
    }
    */

    /*
    int collision = 0;
    double probe = 0.0;
    for(int count = 0; count < 20; count++) {
        int i = 1;
        int len = 10000;
        DoubleHash hashTable(20011);
        std::vector<std::string> wordList = randomWordGenerator(len, 7);
        for (const auto &x: wordList) {
            hashTable.insert(x, i++);
        }

        int search = random(0, 20);
        for (int j = 0; j < 1000; j++) {
            int value = hashTable.search(wordList[search]);
            if (value != search + 1) std::cout << "Oh damn" << std::endl;
            search += random(0, 20);
            search %= len;
        }

        collision += hashTable.getCollision();
        probe += (hashTable.getProbe() / 1000.0);
        std::cout << hashTable.getCollision() << "\t" << hashTable.getProbe() / 1000.0 << std::endl;
        hashTable.resetProbe();
    }
    std::cout << std::endl << collision / 20.0 << "\t" << probe / 20.0 << std::endl;
    */


    int collision = 0;
    double probe = 0.0;
    for(int count = 0; count < 20; count++) {
        int i = 1;
        int len = 10000;
        CustomProbing hashTable(20011, 2, 4);
        std::vector<std::string> wordList = randomWordGenerator(len, 7);
        for (const auto &x: wordList) {
            hashTable.insert(x, i++);
        }

        int search = random(0, 20);
        for (int j = 0; j < 1000; j++) {
            int value = hashTable.search(wordList[search]);
            if (value != search + 1) std::cout << "Oh damn" << std::endl;
            search += random(0, 20);
            search %= len;
        }
        collision += hashTable.getCollision();
        probe += (hashTable.getProbe() / 1000.0);

        std::cout << hashTable.getCollision() << "\t" << hashTable.getProbe() / 1000.0 << std::endl;
        hashTable.resetProbe();
    }
    std::cout << std::endl << collision / 20.0 << "\t" << probe / 20.0 << std::endl;

    return 0;
}
