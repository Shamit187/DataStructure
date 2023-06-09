//
// Created by User on 6/17/2021.
//

#ifndef MINIMUMDISTANCE_MINDIST_H
#define MINIMUMDISTANCE_MINDIST_H

#include "point2D.h"
#include <tuple>

std::tuple<double, int, int> minMidStrip(std::vector<point2D>& data, double d){
    std::tuple<double, int, int> minTuple(distance(data[0], data[data.size() - 1]), data[0].id, data[data.size() - 1].id);
    double min = d;
    qsort(data, Y_AXIS);
    double dist;
    for(int i = 0; i < data.size(); i++){
        for(int j = i + 1; j < data.size() && (data[j].y - data[i].y) <= d; j++){
            dist = distance(data[j], data[i]);
            if(dist <= min){
                min = dist;
                minTuple = std::make_tuple(min, data[i].id, data[j].id);
            }
        }
    }
    return minTuple;
}

std::tuple<double, int, int> minDistRecursion(std::vector<point2D>& data, int low, int high){
    if((high - low) < 3){
        double min = distance(data[low], data[high]);
        std::tuple<double, int, int> minTuple(min,data[low].id,data[high].id);
        double dist;
        for(int i = low; i <= high; i++){
            for(int j = i + 1; j <= high; j++){
                dist = distance(data[j], data[i]);
                if(dist < min){
                    min = dist;
                    minTuple = std::make_tuple(min, data[i].id, data[j].id);
                }
            }
        }
        return minTuple;
    }

    int midPointIndex = (high + low) / 2;
    point2D midPoint = data[midPointIndex];
    std::tuple<double, int, int> minDistLeft = minDistRecursion(data, low, midPointIndex);
    std::tuple<double, int, int> minDistRight = minDistRecursion(data, midPointIndex + 1, high);
    std::tuple<double, int, int> minTuple = minDistLeft;
    if(std::get<0>(minDistLeft) > std::get<0>(minDistRight)){
        minTuple = minDistRight;
    }
    double d = std::get<0>(minTuple);

    std::vector<point2D> midStrip;

    for(int i = low; i <= high; i++){
        if(abs(data[i].x - midPoint.x) <= d){
            midStrip.push_back(data[i]);
        }
    }

    std::tuple<double, int, int> minDistMid = minMidStrip(midStrip, d);
    if(std::get<0>(minTuple) > std::get<0>(minDistMid)){
        minTuple = minDistMid;
    }
    return minTuple;
}

std::tuple<double, int, int> minDist(std::vector<point2D>& data){
    qsort(data, X_AXIS);
//    for(point2D& x: data){
//        std::cout << x.x << "\t" << x.y << std::endl;
//    }
//    std::cout << std::endl;
    return minDistRecursion(data, 0, data.size() - 1);
}

#endif //MINIMUMDISTANCE_MINDIST_H
