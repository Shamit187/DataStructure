//
// Created by User on 11/25/2021.
//

#ifndef GRAPHMODULEC___FILEUTILITY_H
#define GRAPHMODULEC___FILEUTILITY_H

#include <stdlib.h>
#include <vector>
#include <fstream>
#include "HeaderFiles/AdjListW.h"
#include "HeaderFiles/AdjList.h"
#include <time.h>
#include "HeaderFiles/AdjMatrix.h"

int randomNumber(int min, int max){
    //max exclusive
    srand(time(NULL));
    return min + rand() % (max - min);
}

AdjListW generateWtGraphFromFile(const char* _filename, bool isDirected){

    std::ifstream readableFile;
    readableFile.open(_filename);

    if (!readableFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    int nodeNumber;
    int edgeNumber;

    std::vector<std::vector<double>> edgeList;
    readableFile >> nodeNumber >> edgeNumber;
    edgeList.resize(edgeNumber, std::vector<double>(3));

    for(int i = 0; i < edgeNumber; i++) {
        readableFile >> edgeList[i][0] >> edgeList[i][1] >> edgeList[i][2];
    }
    readableFile.close();

    return {isDirected, static_cast<unsigned int>(nodeNumber), static_cast<unsigned int>(edgeNumber), edgeList};
}

AdjListW generateWtGraphFromNonWtFile(const char* _filename, bool isDirected){

    std::ifstream readableFile;
    readableFile.open(_filename);

    if (!readableFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    int nodeNumber;
    int edgeNumber;

    std::vector<std::vector<double>> edgeList;
    readableFile >> nodeNumber >> edgeNumber;
    edgeList.resize(edgeNumber, std::vector<double>(3));

    for(int i = 0; i < edgeNumber; i++) {
        readableFile >> edgeList[i][0] >> edgeList[i][1];
        edgeList[i][2] = 0;
    }
    readableFile.close();

    return {isDirected, static_cast<unsigned int>(nodeNumber), static_cast<unsigned int>(edgeNumber), edgeList};
}

AdjList generateGraphFromFile(const char* _filename){
    std::ifstream readableFile;
    readableFile.open(_filename);
    if (!readableFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    int nodeNumber;
    int edgeNumber;

    std::vector<std::vector<unsigned>> edgeList;
    readableFile >> nodeNumber >> edgeNumber;
    edgeList.resize(edgeNumber, std::vector<unsigned>(2));

    for(int i = 0; i < edgeNumber; i++) {
        readableFile >> edgeList[i][0] >> edgeList[i][1];
    }
    readableFile.close();

    return {true, static_cast<unsigned int>(nodeNumber), static_cast<unsigned int>(edgeNumber), edgeList};
}

void generateRandomGraph(unsigned nodeNumber, unsigned edgeNumber, const char* _filename){
    std::ofstream writingFile;
    writingFile.open(_filename);
    if(!writingFile) {
        std::cout << "Unable to open file";
        exit(1);
    }
    writingFile << nodeNumber << " " << edgeNumber << std::endl;
    AdjMatrix graph(nodeNumber, 0, false, std::vector<std::vector<double>>(0));

    srand(time(NULL));
    int edge = 0;
    while(edge < edgeNumber){
        unsigned u = rand() % nodeNumber;
        unsigned v = rand() % nodeNumber;
        while(u == v){
            v = rand() % nodeNumber;
        }
        if(!graph.edgeExist(u, v)){
            graph.addEdge(u, v, 1);
            writingFile << u << " " << v << " " << (1 + rand()%100 ) / 100.0 << std::endl;
            edge++;
        }
    }
}
#endif //GRAPHMODULEC___FILEUTILITY_H
