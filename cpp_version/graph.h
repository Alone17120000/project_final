#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"

const int INF = std::numeric_limits<int>::max();


struct WeightedEdge {
    int u, v, w;
};

class Graph {
private:
    int V;
    std::map<int, std::list<std::pair<int, int>>> adj;
    std::vector<WeightedEdge> edge_list;
    bool is_directed;

    void DFS_util(int u, std::vector<bool>& visited, std::map<int, int>& prev, std::vector<int>& traversal_order);
    void isConnected_util(int u, std::vector<bool>& visited);
    std::string getPath(int src, int dest, const std::map<int, int>& prev) const;

public:
    Graph(int vertices, bool directed = false);
    int getV() const;
    void addEdge(int u, int v, int w = 1);
    const std::list<std::pair<int, int>>& getAdj(int u) const;
    void print() const;
    
    void BFS(int s);
    void DFS(int s);
    bool isConnected();
    void analyzeGraph();
    void dijkstra(int src);
};
   
#endif