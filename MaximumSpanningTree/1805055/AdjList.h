#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <stack>

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

class vertexKey{
public:
    unsigned vertex;
    double key;
    unsigned from;

    vertexKey(unsigned int vertex, double key, unsigned int from) : vertex(vertex), key(key), from(from) {}
    vertexKey(){}

    bool operator==(vertexKey &rhs){return key == rhs.key;}
    bool operator<(vertexKey &rhs){return key > rhs.key;}
    bool operator>(vertexKey &rhs){return key < rhs.key;}
    vertexKey& operator=(vertexKey &rhs){
        vertex = rhs.vertex;
        key = rhs.key;
        from = rhs.from;
        return *this;
    }
};

struct edge{
    unsigned source;
    unsigned destination;
    double weight;
};

template<typename T>
class Heap{
private:
    std::vector<T> data;

    static int parent(int x){
        x++;
        x /= 2;
        x--;
        if(x < 0)
            return -1;
        return x;
    }
    static int left(int x){
        x++;
        x = 2 * x;
        x--;
        return x;
    }
    static int right(int x){
        x++;
        x = 2 * x;
        return x;
    }

public:
    Heap() {
        data.resize(0);
    }
    T remove(){
        T returnValue = data[0];
        data[0] = data[data.size() - 1];
        data.pop_back();

        int present = 0;

        while(left(present) < data.size() && (data[left(present)] > data[present] || ( right(present) != data.size() && data[right(present)] > data[present]))){
            if(right(present) == data.size()){
                std::swap(data[left(present)], data[present]);
                present = right(present);
            }else{
                (data[left(present)] > data[right(present)]) ?
                (present = left(present), std::swap(data[parent(present)], data[present])):
                (present = right(present), std::swap(data[parent(present)], data[present]));
            }
        }
        return returnValue;
    }
    void insert(T value){
        data.push_back(value);
        int present = data.size() - 1;
        while(parent(present) != -1 && data[parent(present)] < data[present]){
            std::swap(data[parent(present)], data[present]);
            present = parent(present);
        }
    }
};

class disjointDataSet{
private:
    std::vector<unsigned>root;

public:
    disjointDataSet(unsigned size){
        root.resize(size, 0);
        for(int i = 0; i < size; i++) root[i] = i;
    }

    unsigned find(unsigned i){
        while(root[i] != i){
            root[i] = root[root[i]];
            i = root[i];
        }
        return root[i];
    }
    void unionSet(unsigned a, unsigned b){
        unsigned c = find(a);
        unsigned d = find(b);
        root[c] = root[d];
    }
};

class AdjList{
private:
    std::vector< std::vector<edge> > adjList;
    const unsigned nodeNumber;
    unsigned edgeNumber;
    const bool isDirected;

public:
    AdjList(bool isDirected, unsigned nodeNumber, unsigned edgeNumber, std::vector< std::vector<double> > edgeList)
            :isDirected(isDirected), nodeNumber(nodeNumber), edgeNumber(edgeNumber){
        adjList.resize(nodeNumber, std::vector<edge>(0));
        for(int i = 0 ; i < edgeNumber; i++){
            unsigned u = edgeList[i][0];
            unsigned v = edgeList[i][1];
            double wt = edgeList[i][2];

            adjList[u].push_back(edge{u, v, wt});
            if(!isDirected) adjList[v].push_back(edge{v, u, wt});
        }
    }

    void addEdge(unsigned source, unsigned destination, double wt){
        adjList[source].push_back(edge{source, destination, wt});
        if(!isDirected) adjList[destination].push_back(edge{destination, source, wt});
        edgeNumber++;
    }
    friend std::ostream &operator<<(std::ostream &os, const AdjList &obj) {
        os << std::endl << "Graph Description" << std::endl;
        os << "-----------------\n";
        os << "Node: " << obj.nodeNumber << " Total Edge: " << obj.edgeNumber << std::endl << std::endl;
        for(int i = 0; i < obj.nodeNumber; i++){
            os << "Vertex: " << i << std::endl;
            for(int j = 0; j < obj.adjList[i].size(); j++){
                edge v = obj.adjList[i][j];
                os << v.destination << "(" << v.weight << ") ";
            }
            os << std::endl;
        }
        os << std::endl;
        return os;
    }

    std::vector<int> BFS(unsigned source, int returnType){
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
            for(int i = 0; i < adjList[v].size(); i++){
                edge u = adjList[v][i];
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
    std::vector<int> BFSAll(int returnType){
        std::vector<int> color;
        color.resize(nodeNumber, ADJLST_WHITE);

        std::vector<int> distance;
        distance.resize(nodeNumber, ADJLST_INF);

        std::vector<int> parent;
        parent.resize(nodeNumber, ADJLST_INF);

        for(int source = 0; source < nodeNumber; source++){
            if(color[source] != ADJLST_WHITE) continue;

            color[source] = ADJLST_GRAY;
            distance[source] = 0;

            std::queue<int> queue;
            queue.push(source);

            while(!queue.empty()){
                unsigned v = queue.front(); queue.pop();
                for(int i = 0; i < adjList[v].size(); i++){
                    edge u = adjList[v][i];
                    if (color[u.destination] == ADJLST_WHITE){
                        color[u.destination] = ADJLST_GRAY;
                        distance[u.destination] = distance[v] + 1;
                        parent[u.destination] = v;
                        queue.push(u.destination);
                    }
                }
                color[v] = ADJLST_BLACK;
            }
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

    bool edgeExist(unsigned source, unsigned destination) {
        for(int i = 0; i < adjList[source].size(); i++){
            if(adjList[source][i].destination == destination) return true;
        }
        return false;
    }

    std::vector<int> DFS(unsigned source, int returnType){
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

                for(int i = 0; i < adjList[v].size(); i++){
                    edge u = adjList[v][i];
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
    std::vector<int> DFSAll(int returnType){
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

                        for(int i = 0; i < adjList[v].size(); i++){
                            edge u = adjList[v][i];
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

    std::vector<edge> primMST(unsigned source){
        //init
        Heap<vertexKey> heap;
        std::vector<bool> vertexVisited;
        vertexVisited.resize(nodeNumber, false);
        vertexVisited[source] = true;
        std::vector<double> vertexKey;
        vertexKey.resize(nodeNumber, FLT_MAX);
        vertexKey[source] = -1;
        std::vector<edge> mstTree;

        //inserting adj of source
        for(int i = 0; i < adjList[source].size(); i++){
            edge v = adjList[source][i];
            heap.insert({v.destination, v.weight, v.source});
            vertexKey[v.destination] = v.weight;
        }

        //actual prim loop
        while(mstTree.size() < nodeNumber - 1){
            class vertexKey v = heap.remove();
            if(vertexVisited[v.vertex]) continue;

            //else
            mstTree.push_back({v.from, v.vertex, v.key});
            vertexVisited[v.vertex] = true;

            //now add its adj
            for(int i = 0; i < adjList[v.vertex].size(); i++){
                edge u = adjList[v.vertex][i];
                if(u.weight < vertexKey[u.destination]){
                    vertexKey[u.destination] = u.weight;
                    heap.insert({u.destination, u.weight, u.source});
                }
            }
        }

        return mstTree;
    }
    std::vector<edge> kruskalMST(){
        //take the edges and sort them
        std::vector<vertexKey> edgeList;
        for(int v = 0 ; v < nodeNumber; v++){
            for(int i = 0; i < adjList[v].size(); i++){
                edge e = adjList[v][i];
                edgeList.push_back({e.destination, e.weight, e.source});
            }
        }
        std::sort(edgeList.begin(), edgeList.end());
        for(int i = 0; i < edgeList.size()/2; i++){
            std::swap(edgeList[i], edgeList[edgeList.size() - 1 - i]);
        }

        //now add edges one by one checking map
        std::vector<edge> mstTree;
        disjointDataSet vertexMap(nodeNumber);
        for(int i = 0; i < edgeList.size(); i++){
            if(mstTree.size() == nodeNumber - 1) break;
            vertexKey v = edgeList[i];
            unsigned source = v.from;
            unsigned destination = v.vertex;
            if(vertexMap.find(source) != vertexMap.find(destination)){
                vertexMap.unionSet(source, destination);
                mstTree.push_back({source, destination, v.key});
            }
        }
        return mstTree;
    }

};

AdjList generateRandomGraph(bool isDirected, unsigned nodeNumber, unsigned edgeNumber, const char* _filename){
    std::ofstream writingFile;
    writingFile.open(_filename);
    if(!writingFile) {
        std::cout << "Unable to open file";
        exit(1);
    }
    writingFile << nodeNumber << " " << edgeNumber << std::endl;
    AdjList graph(isDirected, nodeNumber, 0, std::vector<std::vector<double>>(0));

    srand(time(NULL));
    int edge = 0;
    while(edge < edgeNumber){
        unsigned u = rand() % nodeNumber;
        unsigned v = rand() % nodeNumber;
        while(u == v){
            v = rand() % nodeNumber;
        }
        if(!graph.edgeExist(u, v)){
            graph.addEdge(u, v, 1);
            writingFile << u << " " << v << " " << (1 + rand()%100 ) / 100.0 << std::endl;
            edge++;
        }
    }

    return graph;
}
AdjList generateGraphFromFile(const char* _filename, bool isDirected){
    std::ifstream readableFile;
    readableFile.open(_filename);

    if (!readableFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    int nodeNumber;
    int edgeNumber;

    std::vector<std::vector<double>> edgeList;
    readableFile >> nodeNumber >> edgeNumber;
    edgeList.resize(edgeNumber, std::vector<double>(3));

    for(int i = 0; i < edgeNumber; i++) {
        readableFile >> edgeList[i][0] >> edgeList[i][1] >> edgeList[i][2];
    }
    readableFile.close();

    return {isDirected, static_cast<unsigned int>(nodeNumber), static_cast<unsigned int>(edgeNumber), edgeList};
}