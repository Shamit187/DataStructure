//
// Created by User on 1/18/2022.
//

#ifndef HASHTABLEANALYSIS_HASHUTIL_H
#define HASHTABLEANALYSIS_HASHUTIL_H

#include <iostream>
#include <vector>
#include <string>
#include <random>

int random(int min, int max){
    std::random_device rand;
    std::mt19937 gen(rand());

    return min + gen() % (max - min);
}

std::vector <std::string> randomWordGenerator(int size, int wordLen){
    std::vector<std::string> list;
    list.resize(size);

    int i = 0;
    while(i < size){
        std::string newString;
        newString.resize(wordLen);

        for(int x = 0; x < wordLen; x++){
            newString[x] = 'a' + random(0, 26);
        }

        bool flag = false;
        for(int j = 0; j < i; j++){
            if(list[j] == newString)
                flag = true;
        }

        if(flag) continue;
        else{
            list[i++] = newString;
        }
    }

    return list;
}

int basicHash(std::string key){
    int sum = 0;

    for(const auto& ch: key){
        sum += ch - 'a';
    }

    return sum;
}

int polyRollHash(std::string key, int len, int p){
    long sum = 0;
    long pow = 1;

    for(const auto& ch: key){
        sum += (ch -'a') * pow;
        pow = pow * p;
    }

    return sum % len;
}

int polySumHash(std::string key, int len){
    long int sum = 0;

    for(const auto& ch: key){
        sum += pow(ch - 'a', 3);
    }

    return sum;
}

int djbHash(std::string key, int len){
    unsigned long sum = 0;

    for(const auto& ch: key){
        sum = sum * 33 + (ch - 'a');
    }

    return sum % len;
}

int sdbmHash(std::string key, int len){
    unsigned long hash = 0;
    for(const auto& ch: key){
        hash = hash * 65599 + (ch - 'a');
    }
    return hash % len;
}

#endif //HASHTABLEANALYSIS_HASHUTIL_H
