#include "graph.h"

Graph::Graph(int vertices, bool directed) : V(vertices), is_directed(directed) {}

int Graph::getV() const { return V; }

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(std::make_pair(v, w));
    if (!is_directed) {
        adj[v].push_back(std::make_pair(u, w));
    }
    WeightedEdge edge = {u, v, w};
    edge_list.push_back(edge);
}

const std::list<std::pair<int, int>>& Graph::getAdj(int u) const {
    static const std::list<std::pair<int, int>> empty_list;
    std::map<int, std::list<std::pair<int, int>> >::const_iterator it = adj.find(u);
    if (it == adj.end()) {
        return empty_list;
    }
    return it->second;
}

void Graph::print() const {
    for (int i = 0; i < V; ++i) {
        std::cout << "  Dinh " << i << ": ";
        if (adj.count(i)) {
             for (std::list<std::pair<int, int>>::const_iterator it = adj.at(i).begin(); it != adj.at(i).end(); ++it) {
                std::cout << "-> " << it->first << "(w:" << it->second << ") ";
            }
        }
        std::cout << std::endl;
    }
}

void Graph::BFS(int s) {
    if (s >= V) { std::cout << "Dinh bat dau khong hop le!" << std::endl; return; }
    std::cout << "\n--- Thuat toan BFS (bat dau tu " << s << ") ---" << std::endl;
    std::map<int, int> dist;
    std::map<int, int> prev;
    for(int i=0; i<V; ++i) { dist[i] = INF; prev[i] = -1; }

    std::queue<int> queue;
    std::vector<int> traversal_order;
    dist[s] = 0;
    queue.push(s);

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        traversal_order.push_back(u);
        const std::list<std::pair<int, int>>& neighbors = getAdj(u);
        for (std::list<std::pair<int, int>>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
            int v = it->first;
            if (dist.count(v) && dist[v] == INF) {
                dist[v] = dist[u] + 1;
                prev[v] = u;
                queue.push(v);
            }
        }
    }
    std::cout << "\n--- KET QUA CUOI CUNG (BFS)---" << std::endl;
    std::cout << "Thu tu duyet: ";
    for(size_t i=0; i<traversal_order.size(); ++i) std::cout << traversal_order[i] << " ";
    std::cout << std::endl;
    for(int i=0; i<V; ++i){
        std::cout << "Duong di ngan nhat (theo so canh) tu " << s << " toi " << i << " la: " << getPath(s, i, prev) << " (Do dai: " << (dist.count(i) && dist[i] != INF ? std::to_string(dist[i]) : "INF") << ")" << std::endl;
    }
}

void Graph::DFS_util(int u, std::vector<bool>& visited, std::map<int, int>& prev, std::vector<int>& traversal_order) {
    visited[u] = true;
    traversal_order.push_back(u);
    const std::list<std::pair<int, int>>& neighbors = getAdj(u);
    for (std::list<std::pair<int, int>>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
        int v = it->first;
        if (!visited[v]) {
            prev[v] = u;
            DFS_util(v, visited, prev, traversal_order);
        }
    }
}

void Graph::DFS(int s) {
    if (s >= V) { std::cout << "Dinh bat dau khong hop le!" << std::endl; return; }
    std::cout << "\n--- Thuat toan DFS (bat dau tu " << s << ") ---" << std::endl;
    std::vector<bool> visited(V, false);
    std::map<int, int> prev;
    for(int i=0; i<V; ++i) prev[i] = -1;
    std::vector<int> traversal_order;
    DFS_util(s, visited, prev, traversal_order);

    std::cout << "\n--- KET QUA CUOI CUNG (DFS)---" << std::endl;
    std::cout << "Thu tu duyet: ";
    for (size_t i=0; i<traversal_order.size(); ++i) std::cout << traversal_order[i] << " ";
    std::cout << std::endl;
    for(int i=0; i<V; ++i){
         std::cout << "Duong di tim thay tu " << s << " toi " << i << " la: " << getPath(s, i, prev) << std::endl;
    }
}

void Graph::isConnected_util(int u, std::vector<bool>& visited) {
    visited[u] = true;
    const std::list<std::pair<int, int>>& neighbors = getAdj(u);
    for (std::list<std::pair<int, int>>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
        if (!visited[it->first]) {
            isConnected_util(it->first, visited);
        }
    }
}

bool Graph::isConnected() {
    if (V <= 1) return true;
    std::vector<bool> visited(V, false);
    
    int start_node = -1;
    for (int i=0; i<V; ++i) {
        if (!getAdj(i).empty()) {
            start_node = i;
            break;
        }
    }
    if (start_node == -1) return true;

    isConnected_util(start_node, visited);
    for (int i = 0; i < V; i++) {
        if (!getAdj(i).empty() && !visited[i]) return false;
    }
    return true;
}

void Graph::analyzeGraph() {
    std::cout << "\n--- Phan tich do thi ---" << std::endl;
    std::cout << "So dinh: " << V << std::endl;
    
    int edge_count = 0;
    if (is_directed) {
        edge_count = edge_list.size();
    } else {
        for(int i=0; i<V; ++i) edge_count += getAdj(i).size();
        edge_count /= 2;
    }
    std::cout << "So canh: " << edge_count << std::endl;
    std::cout << "Tinh lien thong: " << (isConnected() ? "Lien thong" : "Khong lien thong") << std::endl;
    
    bool has_parallel = false;
    std::map<std::pair<int, int>, int> edge_counts;
    for (size_t i = 0; i < edge_list.size(); ++i) {
        int u = std::min(edge_list[i].u, edge_list[i].v);
        int v = std::max(edge_list[i].u, edge_list[i].v);
        edge_counts[std::make_pair(u, v)]++;
        if (edge_counts[std::make_pair(u, v)] > 1) {
            has_parallel = true;
            break;
        }
    }
    std::cout << "Canh song song: " << (has_parallel ? "Co" : "Khong") << std::endl;

    bool has_loop = false;
    for (size_t i = 0; i < edge_list.size(); ++i) {
        if (edge_list[i].u == edge_list[i].v) {
            has_loop = true;
            break;
        }
    }
    std::cout << "Canh khuyen: " << (has_loop ? "Co" : "Khong") << std::endl;
}

std::string Graph::getPath(int src, int dest, const std::map<int, int>& prev) const {
    if (prev.find(dest) == prev.end() || (prev.at(dest) == -1 && dest != src)) return "N/A";
    std::string path_str = "";
    int current = dest;
    std::vector<int> path_vec;
    while (current != -1) {
        path_vec.push_back(current);
        if(prev.find(current) == prev.end()) break;
        current = prev.at(current);
    }
    std::reverse(path_vec.begin(), path_vec.end());

    for(size_t i=0; i<path_vec.size(); ++i){
        path_str += std::to_string(path_vec[i]) + (i == path_vec.size()-1 ? "" : " -> ");
    }
    if(path_str.empty() && dest == src) return std::to_string(src);
    if(path_vec.empty() || path_vec[0] != src) return "N/A";

    return path_str;
}

void Graph::dijkstra(int src) {
    if (src >= V) { std::cout << "Dinh bat dau khong hop le!" << std::endl; return; }
    std::cout << "\n--- Thuat toan Dijkstra (bat dau tu " << src << ") ---" << std::endl;
    std::map<int, int> dist;
    std::map<int, int> prev;
    for(int i=0; i<V; ++i) { dist[i] = INF; prev[i] = -1; }
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    dist[src] = 0;
    pq.push(std::make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (dist.count(u) && d > dist[u]) continue;

        const std::list<std::pair<int, int>>& neighbors = getAdj(u);
        for (std::list<std::pair<int, int>>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
            int v = it->first;
            int weight = it->second;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }
    
    std::cout << "\n--- KET QUA CUOI CUNG ---" << std::endl;
    for(int i=0; i<V; ++i){
        std::cout << "Duong di ngan nhat tu " << src << " toi " << i << " la: " << getPath(src, i, prev) << " (Do dai: " << (dist[i] == INF ? "INF" : std::to_string(dist[i])) << ")" << std::endl;
    }
}