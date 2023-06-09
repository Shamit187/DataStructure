//
// Created by User on 11/25/2021.
//

#ifndef GRAPHMODULEC___ADJLISTW_H
#define GRAPHMODULEC___ADJLISTW_H

#include "CustomExceptions.h"
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <string>

#define ADJLST_WHITE 0
#define ADJLST_GRAY 1
#define ADJLST_BLACK 2
#define ADJLST_GREEN 3
#define ADJLST_RED 4

#define ADJLST_INF -1

#define ADJLST_DISTANCE 0
#define ADJLST_PARENT 1
#define ADJLST_COLOR 2
#define ADJLST_DISCOVER 3
#define ADJLST_FINISH 4

struct edge{
    unsigned source;
    unsigned destination;
    double weight;
};

struct nodeKeySort{
    int node;
    int key;

    bool operator<(const nodeKeySort& rhs) const{
        return key < rhs.key;
    }
};


class AdjListW {

private:

    std::vector<std::vector<edge>> adjList;
    const bool isDirected;
    unsigned nodeNumber;
    unsigned edgeNumber;

public:

    //constructor
    AdjListW(bool isDirected, unsigned int nodeNumber, unsigned int edgeNumber, std::vector<std::vector<double>> edgeList);

    //Utility
    void addEdge(unsigned source, unsigned destination, double wt);
    friend std::ostream& operator<<(std::ostream& os, const AdjListW& obj);
    bool edgeExist(unsigned source, unsigned destination);
    double edgeWeight(unsigned source, unsigned destination);
    AdjListW transpose();
    std::string edgeFormatPrint();
    std::string edgeFormatPrintWithoutEdge();

    //BFS Algorithms
    std::vector<int> BFS(unsigned source, int returnType);
    AdjListW BFSTree(unsigned source);
    std::vector<std::vector<int>> bipartiteSet();
    bool isConnected();

    //DFS Algorithms
    std::vector<int> DFS(unsigned int source, int returnType);
    std::vector<int> DFSAll(int returnType);
    AdjListW DFSTree(unsigned source);
    std::vector<int> topologicalSort();
    std::vector<std::vector<int>> DFSComponent(std::vector<int>DFSDirection);
    std::vector<std::vector<int>> StronglyConnectedComponent();
};


#endif //GRAPHMODULEC___ADJLISTW_H