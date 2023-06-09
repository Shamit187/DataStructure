//
// Created by User on 11/25/2021.
//

#ifndef GRAPHMODULEC___ADJMATRIX_H
#define GRAPHMODULEC___ADJMATRIX_H

#include <vector>
#include <iostream>

class AdjMatrix {

private:

    std::vector<std::vector<double>> adjMatrix;
    const unsigned nodeNumber;
    unsigned edgeNumber;
    const bool isDirected;

public:

    //constructor
    AdjMatrix(unsigned nodeNumber, unsigned edgeNumber, bool isDirected, std::vector<std::vector<double>> edgeList);

    //Utility
    void addEdge(unsigned source, unsigned destination, double weight);
    friend std::ostream& operator<<(std::ostream& os, const AdjMatrix& obj);
    bool edgeExist(unsigned source, unsigned destination);

    //BFS

    //DFS
};


#endif //GRAPHMODULEC___ADJMATRIX_H
