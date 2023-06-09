//
// Created by User on 1/18/2022.
//

#ifndef HASHTABLEANALYSIS_CUSTOMPROBING_H
#define HASHTABLEANALYSIS_CUSTOMPROBING_H
#include <string>
#include <vector>
#include "HashUtil.h"

class CustomProbing{
private:
    std::vector<std::string> kTable;
    std::vector<int> vTable;
    int size;
    int collision;
    int probe;

    int c_1;
    int c_2;

    int Hash(std::string key, int i) {
        return (abs(sdbmHash(key, size) + i * c_1 * basicHash(key) + c_2 * i * i)) % size;
    }

public:
    CustomProbing(int size, int c1, int c2) : size(size) , c_1(c_1), c_2(c_2){
        kTable.resize(size);
        vTable.resize(size);
        collision = 0;
        probe = 0;

        for (auto &x: vTable) {
            x = -1;
        }
    }

    void insert(std::string key, int value) {
        int i = 0;
        int j = Hash(key, i);
        if (vTable[j] < 0) {
            kTable[j] = key;
            vTable[j] = value;
        } else {
            while (vTable[j] >= 0) {
                i++;
                collision++;
                j = Hash(key, i);
            }
            kTable[j] = key;
            vTable[j] = value;
        }
    }

    int search(std::string key) {
        int i = 0;
        int j = Hash(key, i);

        if (vTable[j] == -1) return -1;
        else if (vTable[j] != -2 && kTable[j] == key) {
            probe++;
            return vTable[j];
        } else {
            int search = 0;
            while (vTable[j] != -1 && kTable[j] != key) {
                i++;
                search++;
                j = Hash(key, i);
            }
            if (vTable[j] == -1) return -1;
            else{
                probe += search;
                return vTable[j];
            }
        }
    }

    bool deleteKey(std::string key) {
        int i = 0;
        int j = Hash(key, i);

        if (vTable[j] == -1) return false;
        else if (vTable[j] != -2 && kTable[j] == key) {
            vTable[j] = -2;
            return true;
        } else {
            while (vTable[j] != -1 && kTable[j] != key) {
                i++;
                j = Hash(key, i);
            }
            if (vTable[j] == -1) return false;
            else{
                vTable[j] = -2;
                return true;
            }
        }
    }

    int getCollision() {
        return collision;
    }
    int getProbe() {
        return probe;
    }
    void resetProbe() {
        probe = 0;
    }
};
#endif //HASHTABLEANALYSIS_CUSTOMPROBING_H
