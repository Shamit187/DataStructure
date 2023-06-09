//
// Created by User on 11/25/2021.
//

#include "../HeaderFiles/AdjMatrix.h"

AdjMatrix::AdjMatrix(unsigned nodeNumber, unsigned edgeNumber,bool isDirected, std::vector<std::vector<double>> edgeList)
: nodeNumber(nodeNumber), edgeNumber(edgeNumber), isDirected(isDirected) {
    adjMatrix.resize(nodeNumber, std::vector<double>(nodeNumber));
    //initialize everything with zero
    for(int i = 0; i < nodeNumber; i++){
        for(int j = 0; j < nodeNumber; j++){
            adjMatrix[i][j] = 0;
        }
    }

    for(int i = 0; i < edgeNumber; i++){
        unsigned v = edgeList[i][0];
        unsigned u = edgeList[i][1];
        double wt = edgeList[i][2];

        adjMatrix[v][u] = wt;
        if(!isDirected) adjMatrix[u][v] = wt;
    }
}

void AdjMatrix::addEdge(unsigned int source, unsigned int destination, double weight) {
    if(adjMatrix[source][destination] != 0){
        std::cout << "Edge already exist" << std::endl;
        return;
    }

    adjMatrix[source][destination] = weight;
    if(!isDirected) adjMatrix[destination][source] = weight;
    edgeNumber++;
}

std::ostream &operator<<(std::ostream &os, const AdjMatrix& obj) {
    for(int v = 0; v < obj.nodeNumber; v++){
        os << "Vertex: " << v << std::endl;
        os << "Connected vertices: ";
        for(int u = 0; u < obj.nodeNumber; u++){
            if(obj.adjMatrix[v][u] != 0) os << u << "(" << obj.adjMatrix[v][u] << ") " ;
        }
        os << std::endl;
    }
    return os;
}

bool AdjMatrix::edgeExist(unsigned int source, unsigned int destination) {
    if(adjMatrix[source][destination] == 0) return false;
    else return true;
}
