//
// Created by User on 6/17/2021.
//

#ifndef MINIMUMDISTANCE_POINT2D_H
#define MINIMUMDISTANCE_POINT2D_H

#include <vector>
#include "cmath"
#define X_AXIS 0
#define Y_AXIS 1

struct point2D{
    int x;
    int y;
    int id;
};

bool isBigger(point2D& a, point2D& b, int& mode){
    if (mode == X_AXIS){
        if(a.x == b.x){
            return a.y >= b.y;
        }else{
            return a.x >= b.x;
        }
    }
    else if(mode == Y_AXIS){
        if(a.y == b.y){
            return a.x >= b.x;
        }else{
            return a.y >= b.y;
        }
    }
}

double distance(point2D& a, point2D& b){
    return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int quickSortPartition(std::vector<point2D>& data, int low, int high, int& mode) {
    point2D pivot = data[high];
    int partitionPoint = low - 1;
    for(int i = low; i <= high; i++){
        if(isBigger(pivot, data[i], mode)){
            partitionPoint++;
            std::swap(data[i], data[partitionPoint]);
        }
    }
//    std::swap(data[high], data[partitionPoint + 1]);
    return partitionPoint;
}

void qsortRecursion(std::vector<point2D>& data, int low, int high, int& mode){
    if(low >= high)
        return;

    int pivotPoint = quickSortPartition(data, low, high, mode);
    qsortRecursion(data, low, pivotPoint - 1, mode);
    qsortRecursion(data, pivotPoint + 1, high, mode);
}

void qsort(std::vector<point2D>& data, int mode){
    qsortRecursion(data, 0, data.size() - 1, mode);
}
#endif //MINIMUMDISTANCE_POINT2D_H
