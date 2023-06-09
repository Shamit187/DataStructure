#include "AdjList.h"

int main() {

    //AdjList graph = generateRandomGraph(true, 10, 15, "../mst.txt");
    AdjList graph = generateGraphFromFile("../mst.txt", false);

    /*
    unsigned nodeNumber, edgeNumber;
    std::cin >> nodeNumber >> edgeNumber;
    std::vector< std::vector<double> >edgeList;
    edgeList.resize(edgeNumber, std::vector<double>(3));
    for(int i = 0; i < edgeNumber; i++){
        std::cin >> edgeList[i][0] >> edgeList[i][1] >> edgeList[i][2];
    }
    AdjList graph(false, nodeNumber, edgeNumber, edgeList);
    */

    /*
    std::cout << graph;
    std::vector<int> dfs = graph.DFS(0, ADJLST_FINISH);
    std::vector<int> dfsAll = graph.DFS(0, ADJLST_FINISH);
    std::vector<int> bfs = graph.BFS(0, ADJLST_DISTANCE);
    std::vector<int> bfsAll = graph.BFS(0, ADJLST_DISTANCE);
     */

    std::vector<edge> primMST = graph.primMST(0);
    std::vector<edge> kruskalMST = graph.kruskalMST();

    //print total weight
    double totalWt = 0;
    for(int i = 0; i < primMST.size(); i++){
        totalWt += primMST[i].weight;
    }
    std::cout << "Cost of the minimum spanning tree : " << totalWt << std::endl;

    //print Prim
    std::cout << "List of edges selected by Prim\'s:{";
    for(int i = 0; i < primMST.size(); i++){
        std::cout << "(" << primMST[i].source << "," << primMST[i].destination << ")";
        if(i != primMST.size() - 1) std::cout << ",";
    }
    std::cout << "}";
    std::cout << std::endl;

    //print Kruskal
    std::cout << "List of edges selected by Kruskal\'s:{";
    for(int i = 0; i < kruskalMST.size(); i++){
        std::cout << "(" << kruskalMST[i].source << "," << kruskalMST[i].destination << ")";
        if(i != kruskalMST.size() - 1) std::cout << ",";
    }
    std::cout << "}";
    std::cout << std::endl;
}
