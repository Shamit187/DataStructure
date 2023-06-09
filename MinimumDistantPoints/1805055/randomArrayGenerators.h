//
// Created by User on 6/17/2021.
//

#ifndef MINIMUMDISTANCE_RANDOMARRAYGENERATORS_H
#define MINIMUMDISTANCE_RANDOMARRAYGENERATORS_H

#include <random>
#include "point2D.h"
#define X_SORTED 0
#define Y_SORTED 1
#define RANDOM 2

std::vector<point2D> randomPoints(int size, int max_limit, int min_limit, int mode){
    std::random_device rd;
    std::mt19937 gen(rd());
    int Xvalue;
    int Yvalue;
    std::vector<point2D> newData;
    for(int i = 0; i < size; i++){
        Xvalue = gen() % (max_limit - min_limit + 1) + min_limit;
        Yvalue = gen() % (max_limit - min_limit + 1) + min_limit;
        point2D newPoint{Xvalue, Yvalue, i};
        newData.push_back(newPoint);
    }
    return newData;
}


#endif //MINIMUMDISTANCE_RANDOMARRAYGENERATORS_H
