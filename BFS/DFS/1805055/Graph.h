//
// Created by User on 5/2/2021.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <vector>
#include <queue>
#include <stack>

struct GraphNode{
    bool isVisited;
    unsigned pieceOfChotha;
    std::vector<unsigned > connectedNodes;
};

class Graph{
private:

    std::vector<GraphNode>AdjList;

public:

    Graph(unsigned numberOfNodes){
        for(int i = 0; i < numberOfNodes; i++){
            GraphNode newNode;
            newNode.isVisited = false;
            newNode.pieceOfChotha = 0;
            AdjList.push_back(newNode);
        }
    }

    void addRoad(unsigned city1, unsigned city2){
        AdjList[city1].connectedNodes.push_back(city2);
        AdjList[city2].connectedNodes.push_back(city1);
    }

    void addChotha(unsigned city, int chothaPiece){
        AdjList[city].pieceOfChotha += chothaPiece;
    }

    void resetVisit(){
        for(auto & i : AdjList){
            i.isVisited = false;
        }
    }

    unsigned searchConnectedBFS(unsigned node){
        if(AdjList[node].isVisited)
            return 0;

        unsigned totalChothas = 0;
        std::queue<unsigned> Q;
        Q.push(node);
        AdjList[node].isVisited = true;
        totalChothas += AdjList[node].pieceOfChotha;

        while(!Q.empty()){
            unsigned presentNode = Q.front();
            Q.pop();
            if(AdjList[presentNode].connectedNodes.empty())
                break;

            for(unsigned x: AdjList[presentNode].connectedNodes){
                if(AdjList[x].isVisited)
                    continue;
                Q.push(x);
                AdjList[x].isVisited = true;
                totalChothas += AdjList[x].pieceOfChotha;
            }
        }

        return totalChothas;
    }

    unsigned searchConnectedDFS(unsigned node){
        if(AdjList[node].isVisited)
            return 0;

        unsigned totalChothas = 0;
        std::stack<unsigned>  S;
        S.push(node);
        AdjList[node].isVisited = true;
        totalChothas += AdjList[node].pieceOfChotha;

        while (!S.empty()){
            unsigned presentNode = S.top();
            S.pop();
            if(AdjList[presentNode].connectedNodes.empty())
                break;

            for(unsigned x: AdjList[presentNode].connectedNodes){
                if(AdjList[x].isVisited)
                    continue;
                S.push(x);
                AdjList[x].isVisited = true;
                totalChothas += AdjList[x].pieceOfChotha;
            }
        }

        return totalChothas;
    }
};
#endif //GRAPH_GRAPH_H
