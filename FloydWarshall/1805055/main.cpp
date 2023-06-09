#include <iostream>
#include <vector>
#define INF 100001

std::vector< std::vector<int> >floydWarshallAlgorithm(std::vector< std::vector<int> >weightedMatrix, int vertexNumber){
    for (int k = 0; k < vertexNumber; k++) {
        for (int i = 0; i < vertexNumber; i++) {
            for (int j = 0; j < vertexNumber; j++) {
                if (weightedMatrix[i][k] + weightedMatrix[k][j] < weightedMatrix[i][j])
                    weightedMatrix[i][j] = weightedMatrix[i][k] + weightedMatrix[k][j];
            }
        }
    }

    return weightedMatrix;
}

void printGraph(std::vector< std::vector<int> >weightedMatrix, int vertexNumber){
    for(int i = 0; i < vertexNumber; i++){
        for(int j = 0; j < vertexNumber; j++){
            if(weightedMatrix[i][j] == INF) std::cout << "INF" << '\t';
            else std::cout << weightedMatrix[i][j] << '\t';
        }
        std::cout << std::endl;
    }
}

int main() {
    int vertexNumber, edgeNumber;
    std::cin >> vertexNumber >> edgeNumber;

    std::vector< std::vector<int> >weightedMatrix;
    weightedMatrix.resize(vertexNumber, std::vector<int>(vertexNumber, INF));

    for(int i = 0; i < vertexNumber; i++){
        weightedMatrix[i][i] = 0;
    }

    for(int i = 0; i < edgeNumber; i++){
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;

        weightedMatrix[u][v] = w;
    }

    printGraph(floydWarshallAlgorithm(weightedMatrix, vertexNumber), vertexNumber);
}


