#include <iostream>
#include "Graph.h"
#include <fstream>

int main() {
    int cityNumber;
    int roadNumber;
    int chotha;
    int frndNumber;
    std::ofstream solutionFile("solution.txt");

    std::cin >> cityNumber >> roadNumber >> chotha >> frndNumber;

    Graph cityGraph(10);

    for(int i = 0 ; i < roadNumber; i++){
        int city1;
        int city2;
        std::cin >> city1 >> city2;
        cityGraph.addRoad(city1, city2);
    }

    int totalPiece = 0;
    for(int i = 0; i < chotha; i++){
        int chothaPiece;
        int city;
        std::cin >> city >> chothaPiece;
        cityGraph.addChotha(city, chothaPiece);
        totalPiece += chothaPiece;
    }

    int* collectedPiece = new int[frndNumber];
    int* startingCities = new int[frndNumber];
    for(int i = 0; i < frndNumber; i++){
        int frnd;
        int startingCity;
        std::cin >> startingCity >> frnd;
        startingCities[frnd] = startingCity;
    }

    solutionFile << std::endl;
    solutionFile << "Solving using BFS" << std::endl;
    solutionFile << std::endl;

    int totalFoundChotha = 0;
    for(int i = 0; i < frndNumber; i++){
        collectedPiece[i] = cityGraph.searchConnectedBFS(startingCities[i]);
        totalFoundChotha += collectedPiece[i];
    }
    if(totalFoundChotha == totalPiece){
        solutionFile << "Mission Accomplished" << std::endl;
    }else{
        solutionFile << "Mission Impossible" << std::endl;
    }
    solutionFile << totalFoundChotha << " out of " << totalPiece << " pieces are collected" << std::endl;
    for(int i = 0; i < frndNumber; i++){
        solutionFile << i << " collected " << collectedPiece[i] << " pieces" << std::endl;
    }

    cityGraph.resetVisit();

    solutionFile << std::endl;
    solutionFile << "Solving using DFS" << std::endl;
    solutionFile << std::endl;

    totalFoundChotha = 0;
    for(int i = 0; i < frndNumber; i++){
        collectedPiece[i] = cityGraph.searchConnectedDFS(startingCities[i]);
        totalFoundChotha += collectedPiece[i];
    }
    if(totalFoundChotha == totalPiece){
        solutionFile << "Mission Accomplished" << std::endl;
    }else{
        solutionFile << "Mission Impossible" << std::endl;
    }
    solutionFile << totalFoundChotha << " out of " << totalPiece << " pieces are collected" << std::endl;
    for(int i = 0; i < frndNumber; i++){
        solutionFile << i << " collected " << collectedPiece[i] << " pieces" << std::endl;
    }

    solutionFile.close();
}




















