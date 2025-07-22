#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"

const int INF = std::numeric_limits<int>::max();

class Graph {
private:
    int V;
    std::vector<std::list<std::pair<int, int>>> adj;
    bool is_directed;

public:
    Graph(int vertices, bool directed = false);
    int getV() const;
    void addEdge(int u, int v, int w = 1);
    const std::list<std::pair<int, int>>& getAdj(int u) const;
    void print() const;
    void BFS(int s);
    void DFS(int s);
    void dijkstra(int src);

private:
    void DFS_util(int u, std::vector<bool>& visited);
};

#endif