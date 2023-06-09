//
// Created by User on 6/7/2021.
//

#ifndef SORTCOMPARISON1_GENERATOR_H
#define SORTCOMPARISON1_GENERATOR_H
#include <random>

int* randomGenerator(int size){
    std::random_device rd;
    std::mt19937 gen(rd());

    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = gen() % (size * 5);
    }
    return arr;
}

int* ascendGenerator(int size){
    std::random_device rd;
    std::mt19937 gen(rd());

    int* arr = new int[size];
    int value = gen() % 5;
    for(int i = 0; i < size; i++){
        arr[i] = value;
        value += gen() % 5;
    }
    return arr;
}

int* descendGenerator(int size){
    std::random_device rd;
    std::mt19937 gen(rd());

    int* arr = new int[size];
    int value = size * 5 + gen() % 5;
    for(int i = 0; i < size; i++){
        arr[i] = value;
        value -= gen() % 5;
    }
    return arr;
}

int* copyArray(int* arr, int size){
    int* arr2 = new int[size];
    for(int i = 0; i < size; i++){
        arr2[i] = arr[i];
    }
    return arr2;
}
#endif //SORTCOMPARISON1_GENERATOR_H
