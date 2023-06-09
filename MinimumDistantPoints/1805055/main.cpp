#include <iostream>
#include <fstream>
#include "point2D.h"
#include "randomArrayGenerators.h"
#include "minDist.h"


int main() {
    std::vector<point2D> data;
    int option;

    std::cout << "1. Read from file" << std::endl;
    std::cout << "2. Read from console" << std::endl;

    std::cin >> option;

    switch(option){
        case 1: {
            std::ifstream readFile;
            readFile.open("input.txt");
            if(!readFile){
                std::cout << "File not found" << std::endl;
            }
            int size;
            readFile >> size;

            int x, y;
            for(int i = 0; i < size; i++){
                readFile >> x >> y;
                point2D newPoint{x, y, i};
                data.push_back(newPoint);
            }
            readFile.close();
            break;
        }
        case 2: {
            std::cout << "Size: ";
            int size;
            std::cin >> size;

            int x, y;
            for (int i = 0; i < size; i++) {
                std::cin >> x >> y;
                point2D newPoint{x, y, i};
                data.push_back(newPoint);
            }

            break;
        }
        default: {
            std::cout << "Wrong option" << std::endl;
            break;
        }
    }

    auto data_without_id1 = data;
    auto data_without_id2 = data;


    auto minTuple = minDist(data);
    int id1 = std::get<1>(minTuple);
    int id2 = std::get<2>(minTuple);

    data_without_id1.erase(data_without_id1.begin()+ (id1));
    data_without_id2.erase(data_without_id2.begin()+ (id2));


    auto min1Tuple = minDist(data_without_id1);
    auto min2Tuple = minDist(data_without_id2);


    if(std::get<0>(min1Tuple) < std::get<0>(min2Tuple)){
        id1 = std::get<1>(min1Tuple);
        id2 = std::get<2>(min1Tuple);
        std::cout << id1 << " " << id2 << std::endl;
        std::cout << std::get<0>(min1Tuple) << std::endl;
    }else{
        id1 = std::get<1>(min2Tuple);
        id2 = std::get<2>(min2Tuple);
        std::cout << id1 << " " << id2 << std::endl;
        std::cout.precision(4);
        std::cout << std::fixed << std::get<0>(min2Tuple) << std::endl;
    }

}
