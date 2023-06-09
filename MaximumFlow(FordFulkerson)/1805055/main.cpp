#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>

#define INF 99999

void printGraph(const std::vector< std::vector<int> >& graph){
    int vertex = graph.size();

    std::cout << "x\t";

    for(int i = 0; i < vertex; i++)
        std::cout << i << '\t' ;
    std::cout << std::endl;

    for(int i = 0; i < vertex; i++){
        std::cout << i << '\t';
        for(int j = 0; j < vertex; j++)
            std::cout << graph[i][j] << '\t';
        std::cout << std::endl;
    }
}

bool bfs(const std::vector< std::vector<int> >& graph, int start, int end, std::vector<int>& parent)
{
    int vertex = graph.size();

    std::vector<bool> visited;
    visited.resize(vertex, false);

    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while (!q.empty()){
        int u = q.front(); q.pop();

        for (int v = 0; v < vertex; v++)
        {
            if (!visited[v] && graph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[end];
}

void dfs(const std::vector< std::vector<int> >& graph, int start, std::vector<bool>& visited)
{
    visited[start] = true;
    for (int i = 0; i < graph.size(); i++)
        if (graph[start][i] && !visited[i])
            dfs(graph, i, visited);
}

std::vector<bool> bfs(const std::vector< std::vector<int> >& graph, int start)
{
    int vertex = graph.size();

    std::vector<bool> visited;
    visited.resize(vertex, false);

    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()){
        int u = q.front(); q.pop();

        for (int v = 0; v < vertex; v++)
        {
            if (!visited[v] && graph[u][v] > 0)
            {
                q.push(v);
                visited[v] = true;
            }
        }
    }

    return visited;
}

int fordFulkerson(std::vector< std::vector<int> > graph, int start, int end, std::vector<bool>& minCutSet){
    int vertex = graph.size();

    std::vector< std::vector<int> > rGraph;
    rGraph.resize(vertex, std::vector<int>(vertex, 0));
    for (int u = 0; u < vertex; u++){
        for (int v = 0; v < vertex; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    std::vector<int> parent;
    parent.resize(vertex, -1);

    int max_flow = 0;

    while(bfs(rGraph, start, end, parent)){
        int path_flow = INF;

        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            path_flow = (path_flow < rGraph[u][v]) ? path_flow : rGraph[u][v];
        }

        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;

        //debug
        //std::cout << std::endl;
        //printGraph(rGraph);
    }

    std::vector<bool> visited = bfs(rGraph, start);
    for(int i = 0; i < vertex; i++){
        if(visited[i]) minCutSet[i] = true;
    }

    return max_flow;
}

void baseBallProblem(std::vector<int>& wins, std::vector<int>& left, std::vector< std::vector<int> >& matchLeft, int x, std::vector<std::string>& teams){
    //maximum winnableLim
    int maxWin = wins[x] + left[x];
    int highestWin = 0;
    int highestWinner = 0;
    for(int i = 0; i < wins.size(); i++){
        if(highestWin < wins[i]) {
            highestWin = wins[i];
            highestWinner = i;
        }
    }

    //produce graph
    int n = wins.size();
    int vertex = 1 + (n * (n-1) / 2) + n + 1;
    int f = (n * (n-1) / 2) + 1;
    std::vector< std::vector<int> > graph;
    graph.resize(vertex, std::vector<int>(vertex, 0));

    //connecting matches
    int matchNumber = 1;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            graph[0][matchNumber] = matchLeft[i][j];
            graph[matchNumber][f + i] = INF;
            graph[matchNumber][f + j] = INF;

            matchNumber++;
        }
    }

    //connecting teams
    for(int i = 0; i < n; i++){
        if(i == x){
            graph[f + x][vertex - 1] = maxWin;
        }else{
            graph[f + i][vertex - 1] = maxWin - wins[i];
        }
    }

    //use Ford Fulkerson
    std::vector<bool> minCutSet;
    minCutSet.resize(vertex, false);
    int flow = fordFulkerson(graph, 0, vertex - 1, minCutSet);
    int saturationFlow = 0;
    for(int i = 0; i < vertex; i++){
        saturationFlow += graph[0][i];
    }

    if(flow < saturationFlow){
        std::cout << teams[x] << " is eliminated." << std::endl;
        std::cout << "They can win at most " << wins[x] << " + " << left[x] << " = " << wins[x]+left[x] << " games." << std::endl;
        if(wins[x] + left[x] < highestWin){
            std::cout << teams[highestWinner] << " has won a total of " << highestWin << " games." << std::endl;
            std::cout << "They play each other 0 times." << std::endl;
            std::cout << "So on average, each of the teams wins " << highestWin << "/1 = " << highestWin << " games." << std::endl;
        }
        else{
            std::vector<int> teamsAbove;
            int teamsAboveWin = 0;
            int matchesLeftForThem = 0;
            for(int i = 0; i < n; i++){
                if(minCutSet[f + i]) teamsAbove.push_back(i);
            }
            for(int i = 0; i < teamsAbove.size(); i++){
                teamsAboveWin += wins[teamsAbove[i]];
                for(int j = i + 1; j < teamsAbove.size(); j++){
                    matchesLeftForThem += matchLeft[teamsAbove[i]][teamsAbove[j]];
                }
            }
            for(int i = 0; i < teamsAbove.size(); i++){
                std::cout << teams[teamsAbove[i]];
                if(i == teamsAbove.size() - 1) std::cout << " ";
                else if(i == teamsAbove.size() - 2) std::cout << " and ";
                else std::cout << ",";
            }
            std::cout << "have won a total of " << teamsAboveWin << " games." << std::endl;
            std::cout << "They play each other " << matchesLeftForThem << " times." << std::endl;
            std::cout << "So on average, each of the teams wins " << (teamsAboveWin + matchesLeftForThem) << "/" << teamsAbove.size() << " = " << (teamsAboveWin + matchesLeftForThem)/ (teamsAbove.size() + 0.0) << " games." << std::endl;
        }
        std::cout << std::endl;
    }
}

int main() {
    /*
    int vertex;
    std::cin >> vertex;

    std::vector< std::vector<int> > graph;
    graph.resize(vertex, std::vector<int>(vertex, 0));

    int edge;
    std::cin >> edge;

    for(int i = 0; i < edge; i++){
        int u, v, wt;
        std::cin >> u >> v >> wt;

        graph[u][v] = wt;
    }

    printGraph(graph);

    std::vector<bool> minCutSet;
    std::cout << fordFulkerson(graph, 0, 4, minCutSet);
    return 0;
    */

    /*
    int team;
    std::cin >> team;
    std::vector<std::string> teams;
    std::vector<int> wins;
    std::vector<int> left;
    std::vector< std::vector<int> > matchLeft;
    matchLeft.resize(team, std::vector<int>(team, 0));

    for(int i = 0; i < team; i++){
        std::string teamName;
        int win, a, l;
        std::cin >> teamName >> win >> a >> l;
        teams.push_back(teamName);
        wins.push_back(win);
        left.push_back(l);
        for(int j = 0; j < team; j++){
            std::cin >> matchLeft[i][j];
        }
    }

    for(int i = 0; i < team; i++){
        baseBallProblem(wins, left, matchLeft, i, teams);
    }
    */

    int team;
    std::cin >> team;
    std::vector<std::string> teams;
    std::vector<int> wins;
    std::vector<int> left;
    std::vector< std::vector<int> > matchLeft;
    matchLeft.resize(team, std::vector<int>(team, 0));

    for(int i = 0; i < team; i++){
        std::string teamName;
        int win, a, l;
        std::cin >> teamName >> win >> a >> l;
        teams.push_back(teamName);
        wins.push_back(win);
        left.push_back(l);
        for(int j = 0; j < team; j++){
            std::cin >> matchLeft[i][j];
        }
    }

    for(int i = 0; i < team; i++){
        baseBallProblem(wins, left, matchLeft, i, teams);
    }
}