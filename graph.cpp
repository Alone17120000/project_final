#include "graph.h"

Graph::Graph(int vertices, bool directed) : V(vertices), adj(vertices), is_directed(directed) {}

int Graph::getV() const { return V; }

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    if (!is_directed) {
        adj[v].push_back({u, w});
    }
}

const std::list<std::pair<int, int>>& Graph::getAdj(int u) const {
    return adj[u];
}

void Graph::print() const {
    for (int i = 0; i < V; ++i) {
        std::cout << "  Dinh " << i << ": ";
        for (const auto& edge : adj[i]) {
            std::cout << "-> " << edge.first << "(w:" << edge.second << ") ";
        }
        std::cout << std::endl;
    }
}

void Graph::BFS(int s) {
    std::cout << "\n--- Thuat toan BFS (bat dau tu " << s << ") ---" << std::endl;
    std::vector<bool> visited(V, false);
    std::queue<int> queue;
    visited[s] = true;
    queue.push(s);
    std::cout << "Thu tu duyet: ";
    while (!queue.empty()) {
        int u = queue.front();
        std::cout << u << " ";
        queue.pop();
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
        }
    }
    std::cout << std::endl;
}

void Graph::DFS_util(int u, std::vector<bool>& visited) {
    visited[u] = true;
    std::cout << u << " ";
    for (const auto& edge : adj[u]) {
        int v = edge.first;
        if (!visited[v]) {
            DFS_util(v, visited);
        }
    }
}

void Graph::DFS(int s) {
    std::cout << "\n--- Thuat toan DFS (bat dau tu " << s << ") ---" << std::endl;
    std::vector<bool> visited(V, false);
    std::cout << "Thu tu duyet: ";
    DFS_util(s, visited);
    std::cout << std::endl;
}

void Graph::dijkstra(int src) {
    std::cout << "\n--- Thuat toan Dijkstra (bat dau tu " << src << ") ---" << std::endl;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::vector<int> dist(V, INF);
    pq.push({0, src});
    dist[src] = 0;
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    std::cout << "Khoang cach ngan nhat:" << std::endl;
    for (int i = 0; i < V; ++i)
        std::cout << "  Tu " << src << " toi " << i << " la " << (dist[i] == INF ? "INF" : std::to_string(dist[i])) << std::endl;
}