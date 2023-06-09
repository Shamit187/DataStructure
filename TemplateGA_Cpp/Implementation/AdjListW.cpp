//
// Created by User on 11/25/2021.
//
#include "../HeaderFiles/AdjListW.h"

AdjListW::AdjListW(bool isDirected, unsigned int nodeNumber, unsigned int edgeNumber, std::vector<std::vector<double>> edgeList)
: isDirected(isDirected),nodeNumber(nodeNumber),edgeNumber(edgeNumber) {
    adjList.resize(nodeNumber, std::vector<edge>(0));

    for(int i = 0; i < edgeNumber; i++){
        unsigned v = edgeList[i][0];
        unsigned u = edgeList[i][1];
        double wt = edgeList[i][2];

        adjList[v].push_back(edge{v, u, wt});
        if(!isDirected) adjList[u].push_back(edge{u, v, wt});
    }
}

std::vector<int> AdjListW::BFS(unsigned int source, int returnType) {
    std::vector<int> color;
    color.resize(nodeNumber, ADJLST_WHITE);

    std::vector<int> distance;
    distance.resize(nodeNumber, ADJLST_INF);

    std::vector<int> parent;
    parent.resize(nodeNumber, ADJLST_INF);

    color[source] = ADJLST_GRAY;
    distance[source] = 0;

    std::queue<int> queue;
    queue.push(source);

    while(!queue.empty()){
        unsigned v = queue.front(); queue.pop();
        for(auto u: adjList[v]){
            if (color[u.destination] == ADJLST_WHITE){
                color[u.destination] = ADJLST_GRAY;
                distance[u.destination] = distance[v] + 1;
                parent[u.destination] = v;
                queue.push(u.destination);
            }
        }
        color[v] = ADJLST_BLACK;
    }
    if(returnType == ADJLST_DISTANCE){
        return distance;
    }else if(returnType == ADJLST_PARENT){
        return parent;
    }else if(returnType == ADJLST_COLOR){
        return color;
    }else{
        return std::vector<int>(0);
    }
}

std::vector<int> AdjListW::DFS(unsigned int source, int returnType) {
    std::stack<int> vertexStack;

    std::vector<int> color;
    color.resize(nodeNumber, ADJLST_WHITE);

    std::vector<int> discover;
    discover.resize(nodeNumber, ADJLST_INF);

    std::vector<int> finish;
    finish.resize(nodeNumber, ADJLST_INF);

    std::vector<int> parent;
    parent.resize(nodeNumber, ADJLST_INF);

    int time = 0;

    vertexStack.push(source);
    color[source] = ADJLST_GRAY;
    discover[source] = ++time;

    while(!vertexStack.empty()){
        int v = vertexStack.top(); vertexStack.pop();

        if (color[v] == ADJLST_GRAY){

            color[v] = ADJLST_GREEN;
            vertexStack.push(v);

            for(auto u: adjList[v]){
                if(color[u.destination] == ADJLST_WHITE){
                    color[u.destination] = ADJLST_GRAY;
                    discover[u.destination] = ++time;
                    vertexStack.push(u.destination);
                    parent[u.destination] = v;
                }
            }

        }else if(color[v] == ADJLST_GREEN){
            color[v] = ADJLST_BLACK;
            finish[v] = ++time;
        }
    }

    switch (returnType) {
        case ADJLST_COLOR:
            return color;
        case ADJLST_DISCOVER:
            return discover;
        case ADJLST_FINISH:
            return finish;
        case ADJLST_PARENT:
            return parent;
        default:
            return std::vector<int>(0);
    }
}

void AdjListW::addEdge(unsigned int source, unsigned int destination, double wt) {
    adjList[source].push_back(edge{source, destination, wt});
    if(!isDirected) adjList[destination].push_back(edge{destination, source, wt});
    edgeNumber++;
}

std::ostream &operator<<(std::ostream &os, const AdjListW &obj) {
    os << std::endl << "Graph Description" << std::endl;
    os << "-----------------\n";
    os << "Node: " << obj.nodeNumber << " Total Edge: " << obj.edgeNumber << std::endl << std::endl;
    for(int i = 0; i < obj.nodeNumber; i++){
        os << "Vertex: " << i << std::endl;
        for(auto v: obj.adjList[i]){
            os << v.destination << "(" << v.weight << ") ";
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

AdjListW AdjListW::BFSTree(unsigned int source) {
    AdjListW bfsTree(true, nodeNumber, 0, std::vector<std::vector<double>>(0));

    std::vector<int> color;
    color.resize(nodeNumber, ADJLST_WHITE);

    color[source] = ADJLST_GRAY;

    std::queue<int> queue;
    queue.push(source);

    while(!queue.empty()){
        unsigned v = queue.front(); queue.pop();
        for(auto u: adjList[v]){
            if (color[u.destination] == ADJLST_WHITE){
                bfsTree.addEdge(v, u.destination, u.weight);
                color[u.destination] = ADJLST_GRAY;
                queue.push(u.destination);
            }
        }
        color[v] = ADJLST_BLACK;
    }

    return bfsTree;
}

bool AdjListW::edgeExist(unsigned int source, unsigned int destination) {
    for(auto e: adjList[source]){
        if(e.destination == destination) return true;
    }
    return false;
}

double AdjListW::edgeWeight(unsigned int source, unsigned int destination) {
    for(auto e: adjList[source]){
        if(e.destination == destination) return e.weight;
    }
    throw EdgeNonExistent();
}

AdjListW AdjListW::transpose() {
    if(!isDirected) throw InvalidTranspose();
    AdjListW transposedGraph(isDirected, nodeNumber, 0, std::vector<std::vector<double>>(0));
    for(int i = 0; i < nodeNumber; i++){
        for(auto v: adjList[i]){
            transposedGraph.addEdge(v.destination, i, v.weight);
        }
    }
    return transposedGraph;
}

std::vector<std::vector<int>> AdjListW::bipartiteSet() {
    if(isDirected) throw InvalidBipartite();
    std::vector<std::vector<int>> set;
    set.resize(2,std::vector<int>(0));

    unsigned source = 0;
    std::vector<int> color;
    color.resize(nodeNumber, ADJLST_WHITE);
    std::queue<int> queue;
    for(int source = 0; source < nodeNumber; source++){
        if(color[source] == ADJLST_WHITE){
            color[source] = ADJLST_GREEN;
            queue.push(source);
            set[0].push_back(source);

            while(!queue.empty()){
                unsigned v = queue.front(); queue.pop();
                int colorScheme;
                if(color[v] == ADJLST_GREEN) colorScheme = ADJLST_RED;
                else colorScheme = ADJLST_GREEN;
                for(auto u: adjList[v]){
                    if (color[u.destination] == ADJLST_WHITE){
                        color[u.destination] = colorScheme;
                        queue.push(u.destination);
                        if(colorScheme == ADJLST_GREEN) set[0].push_back(u.destination);
                        else set[1].push_back(u.destination);
                    }if (color[u.destination] != colorScheme) throw InvalidBipartite();
                }
            }
        }
    }
    return set;
}

bool AdjListW::isConnected() {
    std::vector<int> result = BFS(0, ADJLST_COLOR);
    for(auto &v: result){
        if(v == ADJLST_WHITE)return false;
    }
    return true;
}

AdjListW AdjListW::DFSTree(unsigned int source) {
    AdjListW dfsTree(true, nodeNumber, 0, std::vector<std::vector<double>>(0));
    std::stack<int> vertexStack;

    std::vector<int> color;
    color.resize(nodeNumber, ADJLST_WHITE);

    vertexStack.push(source);
    color[source] = ADJLST_GRAY;

    while(!vertexStack.empty()){
        int v = vertexStack.top(); vertexStack.pop();

        if (color[v] == ADJLST_GRAY){

            color[v] = ADJLST_GREEN;
            vertexStack.push(v);

            for(auto u: adjList[v]){
                if(color[u.destination] == ADJLST_WHITE){
                    color[u.destination] = ADJLST_GRAY;
                    vertexStack.push(u.destination);
                    dfsTree.addEdge(v, u.destination, u.weight);
                }
            }

        }else if(color[v] == ADJLST_GREEN){
            color[v] = ADJLST_BLACK;
        }
    }

    return dfsTree;
}

std::vector<int> AdjListW::topologicalSort() {
    std::vector<int> sortedList;
    std::stack<int> vertexStack;

    std::vector<int> color;
    color.resize(nodeNumber, ADJLST_WHITE);

    for(int i = 0; i < nodeNumber; i++){
        if(color[i] == ADJLST_WHITE){
            vertexStack.push(i);
            color[i] = ADJLST_GRAY;

            while(!vertexStack.empty()){
                int v = vertexStack.top(); vertexStack.pop();

                if (color[v] == ADJLST_GRAY){

                    color[v] = ADJLST_GREEN;
                    vertexStack.push(v);

                    for(auto u: adjList[v]){
                        if(color[u.destination] == ADJLST_WHITE){
                            color[u.destination] = ADJLST_GRAY;
                            vertexStack.push(u.destination);
                        }else if(color[u.destination] == ADJLST_GRAY || color[u.destination] == ADJLST_GREEN){
                            throw TopologicalSortUnavailable();
                        }
                    }

                }else if(color[v] == ADJLST_GREEN){
                    color[v] = ADJLST_BLACK;
                    sortedList.push_back(v);
                }
            }
        }
    }

    for(int i = 0; i < nodeNumber/2; i++){
        std::swap(sortedList[i], sortedList[nodeNumber - i - 1]);
    }

    return sortedList;
}

std::vector<std::vector<int>> AdjListW::DFSComponent(std::vector<int> DFSDirection) {
    std::vector<std::vector<int>> componentList;
    componentList.resize(1, std::vector<int>(0));

    //init
    std::stack<int> vertexStack;

    std::vector<int> color;
    color.resize(nodeNumber, ADJLST_WHITE);

    std::vector<int> components;
    components.resize(nodeNumber, -1);
    int componentNumber = 0;

    for(auto source: DFSDirection){
        if(color[source] == ADJLST_WHITE){
            vertexStack.push(source);
            color[source] = ADJLST_GRAY;

            while(!vertexStack.empty()){
                int v = vertexStack.top(); vertexStack.pop();

                if (color[v] == ADJLST_GRAY){

                    color[v] = ADJLST_GREEN;
                    vertexStack.push(v);

                    for(auto u: adjList[v]){
                        if(color[u.destination] == ADJLST_WHITE){
                            color[u.destination] = ADJLST_GRAY;
                            vertexStack.push(u.destination);
                        }
                    }

                }else if(color[v] == ADJLST_GREEN){
                    color[v] = ADJLST_BLACK;
                    components[v] = source;
                }
            }

            if(componentNumber != 0){
                componentList.push_back(std::vector<int>(0));
            }
            for(int i = 0; i < nodeNumber; i++){
                if(components[i] == source){
                    componentList[componentNumber].push_back(i);
                }
            }
            componentNumber++;
        }
    }

    return componentList;
}

std::vector<int> AdjListW::DFSAll(int returnType) {
    std::vector<int> color;
    color.resize(nodeNumber, ADJLST_WHITE);

    std::vector<int> discover;
    discover.resize(nodeNumber, ADJLST_INF);

    std::vector<int> finish;
    finish.resize(nodeNumber, ADJLST_INF);

    std::vector<int> parent;
    parent.resize(nodeNumber, ADJLST_INF);

    int time = 0;
    for(int source = 0; source < nodeNumber; source++){
        if(color[source] == ADJLST_WHITE){
            std::stack<int> vertexStack;
            vertexStack.push(source);
            color[source] = ADJLST_GRAY;
            discover[source] = ++time;

            while(!vertexStack.empty()){
                int v = vertexStack.top(); vertexStack.pop();

                if (color[v] == ADJLST_GRAY){

                    color[v] = ADJLST_GREEN;
                    vertexStack.push(v);

                    for(auto u: adjList[v]){
                        if(color[u.destination] == ADJLST_WHITE){
                            color[u.destination] = ADJLST_GRAY;
                            discover[u.destination] = ++time;
                            vertexStack.push(u.destination);
                            parent[u.destination] = v;
                        }
                    }

                }else if(color[v] == ADJLST_GREEN){
                    color[v] = ADJLST_BLACK;
                    finish[v] = ++time;
                }
            }
        }
    }

    switch (returnType) {
        case ADJLST_COLOR:
            return color;
        case ADJLST_DISCOVER:
            return discover;
        case ADJLST_FINISH:
            return finish;
        case ADJLST_PARENT:
            return parent;
        default:
            return std::vector<int>(0);
    }
}

std::vector<std::vector<int>> AdjListW::StronglyConnectedComponent() {
    std::vector<int> finishTime = DFSAll(ADJLST_FINISH);
    std::priority_queue<nodeKeySort> Q;
    for(int i = 0; i < nodeNumber; i++){
        Q.push({i, finishTime[i]});
    }
    for(int i = 0; i < nodeNumber; i++){
        finishTime[i] = Q.top().node; Q.pop();
    }
    /*
    for(auto v: finishTime){
        std::cout << v << " ";
    }std::cout << std::endl;
    */

    AdjListW graph_T = transpose();
    return graph_T.DFSComponent(finishTime);
}

std::string AdjListW::edgeFormatPrint() {
    std::string printer;
    printer += std::to_string(nodeNumber);
    printer += " ";
    printer += std::to_string(edgeNumber);
    printer += "\n";
    for(auto list: adjList){
        if(list.empty()) continue;
        for(auto e: list){
            printer += std::to_string(e.source);
            printer += " ";
            printer += std::to_string(e.destination);
            printer += " ";
            printer += std::to_string(e.weight);
            printer += "\n";
        }
    }
    return printer;
}

std::string AdjListW::edgeFormatPrintWithoutEdge() {
    std::string printer;
    printer += std::to_string(nodeNumber);
    printer += " ";
    printer += std::to_string(edgeNumber);
    printer += "\n";
    for(auto list: adjList){
        if(list.empty()) continue;
        for(auto e: list){
            printer += std::to_string(e.source);
            printer += " ";
            printer += std::to_string(e.destination);
            printer += "\n";
        }
    }
    return printer;
}
