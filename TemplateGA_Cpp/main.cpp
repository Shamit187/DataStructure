#include <iostream>
#include "HeaderFiles/AdjList.h"
#include "HeaderFiles/AdjListW.h"
#include "HeaderFiles/FileUtility.h"
#include "HeaderFiles/AdjMatrix.h"

int main() {

    //generateRandomGraph(6, 20, "../Input/input_2.txt");


    AdjListW graph = generateWtGraphFromNonWtFile("../Input/Graph_input.txt",true);
    //std::cout << graph.isConnected() << std::endl;
    /*
    std::cout << graph.BFSTree(0);
    std::cout << graph.DFSTree(0);

    try {
        auto set = graph.bipartiteSet();
        for(int i = 0; i < 2; i++){
            std::cout << "Set " << i << ": \n";
            for(auto v: set[i]){
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
     */

    /*
    try{
        std::vector<int> sortList = graph.topologicalSort();
        for(auto v: sortList){
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
    */

    /*
    std::vector<int> direction(10);
    for(int i = 0; i < 10; i++){
        direction[i] = i;
    }
    std::vector<std::vector<int>> componentList = graph.DFSComponent(direction);
    for(int i = 0; i < componentList.size(); i++){
        for(auto v: componentList[i]){
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
     */

    /*
    std::vector<std::vector<int>> SCC = graph.StronglyConnectedComponent();
    for(auto list: SCC){
        for(auto v: list){
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    */

    std::cout << graph.edgeFormatPrintWithoutEdge();
    std::cout << graph;

    return 0;
}
