//
// Created by User on 11/24/2021.
//

#include "../HeaderFiles/AdjList.h"

AdjList::AdjList(bool isDirected, unsigned nodeNumber, unsigned edgeNumber, std::vector<std::vector<unsigned>> edgeList)
: nodeNumber(nodeNumber), edgeNumber(edgeNumber), isDirected(isDirected) {
    adjList.resize(nodeNumber, std::vector<unsigned>(0));

    for(int i = 0; i < edgeNumber; i++){
        unsigned v = edgeList[i][0];
        unsigned u = edgeList[i][1];

        adjList[v].push_back(u);
        if(!isDirected) adjList[u].push_back(v);
    }
}

AdjList::~AdjList() {

}

std::vector<int> AdjList::bfs(unsigned int source, int returnType) {
    std::vector<int> color;
    color.resize(nodeNumber, ADJLNW_WHITE);

    std::vector<int> distance;
    distance.resize(nodeNumber, ADJLNW_INF);

    std::vector<int> parent;
    parent.resize(nodeNumber, ADJLNW_INF);

    color[source] = ADJLNW_GRAY;
    distance[source] = 0;

    std::queue<int> queue;
    queue.push(source);

    while(!queue.empty()){
        unsigned v = queue.front(); queue.pop();
        for(unsigned u: adjList[v]){
            if (color[u] == ADJLNW_WHITE){
                color[u] = ADJLNW_GRAY;
                distance[u] = distance[v] + 1;
                parent[u] = v;
                queue.push(u);
            }
        }
        color[v] = ADJLNW_BLACK;
    }
    if(returnType == ADJLNW_DISTANCE){
        return distance;
    }else if(returnType == ADJLNW_PARENT){
        return parent;
    }else if(returnType == ADJLNW_COLOR){
        return color;
    }else{
        return std::vector<int>(0);
    }
}

AdjList AdjList::bfsTree(unsigned int source) {
    AdjList BFSTree(true, nodeNumber, 0, std::vector<std::vector<unsigned>>(0));

    std::vector<int> color;
    color.resize(nodeNumber, ADJLNW_WHITE);

    color[source] = ADJLNW_GRAY;

    std::queue<int> queue;
    queue.push(source);

    while(!queue.empty()){
        unsigned v = queue.front(); queue.pop();
        for(unsigned u: adjList[v]){
            if (color[u] == ADJLNW_WHITE){
                color[u] = ADJLNW_GRAY;
                BFSTree.addEdge(v, u);
                queue.push(u);
            }
        }
        color[v] = ADJLNW_BLACK;
    }
    return BFSTree;
}

//dumbest Algorithm to exist
std::vector<AdjList> AdjList::bfsForrest() {
    std::vector<AdjList> treeList;

    std::vector<int> globalColor;
    globalColor.resize(nodeNumber, ADJLNW_WHITE);

    for(int i = 0; i < nodeNumber; i++){
        if(globalColor[i] == ADJLNW_WHITE){
            AdjList BFSTree(true, nodeNumber, 0, std::vector<std::vector<unsigned>>(0));

            globalColor[i] = ADJLNW_GRAY;

            std::queue<int> queue;
            queue.push(i);

            while(!queue.empty()){
                unsigned v = queue.front(); queue.pop();
                for(unsigned u: adjList[v]){
                    if (globalColor[u] == ADJLNW_WHITE){
                        globalColor[u] = ADJLNW_GRAY;
                        BFSTree.addEdge(v, u);
                        queue.push(u);
                    }
                }
                globalColor[v] = ADJLNW_BLACK;
            }
            treeList.push_back(BFSTree);
        }
    }

    return treeList;
}

unsigned AdjList::bfsDistance(unsigned int source, unsigned int destination) {
    int distance = bfs(source, ADJLNW_DISTANCE).at(destination);
    if (distance == ADJLNW_INF) throw NotConnected();
    return distance;
}

void AdjList::addEdge(unsigned int source, unsigned int destination) {
    adjList[source].push_back(destination);
    if(!isDirected) adjList[destination].push_back(source);
}

std::ostream &operator<<(std::ostream &os, const AdjList &obj) {
    for(int i = 0; i < obj.nodeNumber; i++){
        os << "vertex: " << i << std::endl << "Connected vertex: ";
        for(unsigned v: obj.adjList[i]){
            os << v << " ";
        }
        os << std::endl;
    }
    return os;
}

