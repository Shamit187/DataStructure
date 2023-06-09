//
// Created by User on 1/18/2022.
//

#ifndef HASHTABLEANALYSIS_CHAINHASH_H
#define HASHTABLEANALYSIS_CHAINHASH_H

#include <string>
#include <vector>
#include "HashUtil.h"

class ChainHashEntry{
public:
    std::string key;
    int value;
    ChainHashEntry* next;
    ChainHashEntry(std::string key, int value) : key(std::move(key)), value(value) { next = nullptr;}
};

class ChainHash {
private:
    std::vector <ChainHashEntry *> table;
    int totalCollision;
    int size;
    int probe;

    int hash(std::string &key){
        //j = polyRollHash(key, size, 5);
        //j = djbHash(key, size);
        //j = sdbmHash(key, size);
        return sdbmHash(key, size);
    }

public:
    ChainHash(int size): size(size){
        table.resize(size);
        totalCollision = 0;
        probe = 0;

        for(auto& x: table){
            x = nullptr;
        }
    }

    void insert(std::string key, int value);
    int search(std::string key);
    bool deleteKey(std::string key);

    int getCollision(){return totalCollision;}
    int getProbe(){return probe;}
    void resetProbe(){probe = 0;}

    ~ChainHash();
};

void ChainHash::insert(std::string key, int value) {
    int j = hash(key);

    if(table[j] == nullptr){
        auto* newEntry = new ChainHashEntry(key, value);
        table[j] = newEntry;
    }
    else{
        totalCollision++;
        auto* current = table[j];
        while (current -> next != nullptr){
            current = current -> next;
        }
        auto* newEntry = new ChainHashEntry(key, value);
        current -> next = newEntry;
    }
}

int ChainHash::search(std::string key) {
    int j = hash(key);

    if(table[j] == nullptr) return -1;
    else if(table[j] -> key == key){
        probe++;
        return table[j] -> value;
    }

    else{
        int search = 1;
        ChainHashEntry* current = table[j];

        while(current -> next != nullptr){
            search++;
            current = current->next;
            if(current -> key == key){
                probe += search;
                return current -> value;
            }
        }
    }
    return -1;
}

bool ChainHash::deleteKey(std::string key) {
    int j = hash(key);

    if(table[j] == nullptr) return false;
    else if(table[j] -> key == key){
        delete table[j];
        table[j] = nullptr;
    }
    else{
        ChainHashEntry* current = table[j];
        ChainHashEntry* parent = nullptr;

        while(current -> next != nullptr){
            parent = current;
            current = current->next;
            if(current -> key == key){
                parent->next = current->next;
                delete current;
                return true;
            }
        }
    }
    return false;
}

ChainHash::~ChainHash() {
    for(int i = 0; i < table.size(); i++){
        if(table[i] == nullptr) continue;
        ChainHashEntry* current = table[i];
        std::vector<ChainHashEntry*> deleter;
        deleter.push_back(current);
        while(current -> next != nullptr){
            current = current -> next;
            deleter.push_back(current);
        }
        for(auto& x: deleter){
            delete x;
        }
    }
}

#endif //HASHTABLEANALYSIS_CHAINHASH_H
