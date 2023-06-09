//
// Created by User on 11/24/2021.
//

#ifndef GRAPHMODULEC___ADJLIST_H
#define GRAPHMODULEC___ADJLIST_H

#include <vector>
#include <queue>
#include <ostream>
#include "CustomExceptions.h"

#define ADJLNW_WHITE 0
#define ADJLNW_GRAY 1
#define ADJLNW_BLACK 2
#define ADJLNW_INF -1

#define ADJLNW_DISTANCE 0
#define ADJLNW_PARENT 1
#define ADJLNW_COLOR 2

class AdjList {
private:

    std::vector<std::vector<unsigned>> adjList;
    unsigned nodeNumber;
    unsigned edgeNumber;
    const bool isDirected;

public:

    //Constructor
    AdjList(bool isDirected, unsigned nodeNumber, unsigned edgeNumber, std::vector<std::vector<unsigned>> edgeList);
    virtual ~AdjList();

    //Tools
    void addEdge(unsigned source, unsigned destination);
    friend std::ostream& operator<<(std::ostream& os, const AdjList& obj);

    //BFS based algorithms
    std::vector<int> bfs(unsigned source, int returnType);
    AdjList bfsTree(unsigned source);
    std::vector<AdjList> bfsForrest ();
    unsigned bfsDistance(unsigned source, unsigned destination);
};


#endif //GRAPHMODULEC___ADJLIST_H
