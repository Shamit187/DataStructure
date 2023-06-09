#include "AdjList.h"

int main() {
    int nodeNumber, edgeNumber;
    std::cin >> nodeNumber >> edgeNumber;
    std::vector< std::vector <double> >edgeList;
    edgeList.resize(edgeNumber, std::vector<double>(3));
    bool negativeFlag = false;
    for(int i = 0; i < edgeNumber; i++){
        std::cin >> edgeList[i][0] >> edgeList[i][1] >> edgeList[i][2];
        if(edgeList[i][2] < 0) negativeFlag = true;
    }
    AdjList graph(true, nodeNumber, edgeNumber, edgeList);
    int source, destination;
    std::cin >> source >> destination;

    if(negativeFlag){
        std::vector<int>nodes = graph.BellmanFord(source, destination);
        if(nodes.empty()){
            std::cout << "The graph contains a negative cycle" << std::endl;
        }else{
            std::cout << "The graph does not contain a negative cycle" << std::endl;
            std::cout << "Shortest path cost: " << nodes[nodes.size() - 1] << std::endl;
            for(int i = nodes.size() - 2; i >= 0; i--){
                std::cout << nodes[i] ;
                if(i!= 0) std::cout << " -> ";
            }
            std::cout << std::endl;
        }
    }
    else{
        std::vector<int>nodes = graph.BellmanFord(source, destination);
        std::cout << "Shortest path cost: " << nodes[nodes.size() - 1] << std::endl;
        for(int i = nodes.size() - 2; i >= 0; i--){
            std::cout << nodes[i] ;
            if(i!= 0) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}
