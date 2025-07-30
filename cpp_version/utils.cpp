#include "utils.h"

// --- HÀM TRUNG GIAN ĐỂ TÌM SỐ ĐỈNH ---
int get_num_vertices(const AdjacencyList& al) {
    if (al.empty()) return 0;
    int max_vertex = 0;
    for (std::map<int, std::vector<int>>::const_iterator it = al.begin(); it != al.end(); ++it) {
        int u = it->first;
        const std::vector<int>& neighbors = it->second;
        if (u > max_vertex) max_vertex = u;
        for (size_t i = 0; i < neighbors.size(); ++i) {
            if (neighbors[i] > max_vertex) max_vertex = neighbors[i];
        }
    }
    return max_vertex + 1;
}

// --- HÀM CHUYỂN ĐỔI ĐỒ THỊ (12 converters) ---

// 1. Từ Ma trận kề (AM)
AdjacencyList am_to_al(const AdjacencyMatrix& am) {
    AdjacencyList al;
    for (size_t i = 0; i < am.size(); ++i) {
        al[i] = std::vector<int>();
        for (size_t j = 0; j < am[i].size(); ++j) {
            for (int k = 0; k < am[i][j]; ++k) {
                al[i].push_back(j);
            }
        }
    }
    return al;
}
ExtendedAdjacencyList am_to_eal(const AdjacencyMatrix& am) {
    ExtendedAdjacencyList eal;
    for(size_t i = 0; i < am.size(); ++i) eal[i] = EAL_Data();
    for (size_t i = 0; i < am.size(); ++i) {
        for (size_t j = 0; j < am[i].size(); ++j) {
            for (int k = 0; k < am[i][j]; ++k) {
                Edge edge(i, j);
                eal[i].out.push_back(edge);
                eal[j].in.push_back(edge);
            }
        }
    }
    return eal;
}
AdjacencyMap am_to_amap(const AdjacencyMatrix& am) {
    AdjacencyMap amap;
    for(size_t i = 0; i < am.size(); ++i) amap[i] = AMap_Data();
    for (size_t i = 0; i < am.size(); ++i) {
        for (size_t j = 0; j < am[i].size(); ++j) {
            if (am[i][j] > 0) {
                Edge edge(i, j);
                amap[i].out[j] = edge;
                amap[j].in[i] = edge;
            }
        }
    }
    return amap;
}

// 2. Từ Danh sách kề (AL)
AdjacencyMatrix al_to_am(const AdjacencyList& al) {
    int num_vertices = get_num_vertices(al);
    AdjacencyMatrix am(num_vertices, std::vector<int>(num_vertices, 0));
    for (std::map<int, std::vector<int>>::const_iterator it = al.begin(); it != al.end(); ++it) {
        int u = it->first;
        const std::vector<int>& neighbors = it->second;
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int v = neighbors[i];
            if (u < num_vertices && v < num_vertices) am[u][v]++;
        }
    }
    return am;
}
ExtendedAdjacencyList al_to_eal(const AdjacencyList& al) { return am_to_eal(al_to_am(al)); }
AdjacencyMap al_to_amap(const AdjacencyList& al) { return am_to_amap(al_to_am(al)); }

// 3. Từ DS Kề Mở Rộng (EAL)
AdjacencyMatrix eal_to_am(const ExtendedAdjacencyList& eal) {
    int num_vertices = eal.size();
    AdjacencyMatrix am(num_vertices, std::vector<int>(num_vertices, 0));
    for (std::map<int, EAL_Data>::const_iterator it = eal.begin(); it != eal.end(); ++it) {
        const EAL_Data& data = it->second;
        for (size_t i = 0; i < data.out.size(); ++i) {
            const Edge& edge = data.out[i];
            if (edge.u < num_vertices && edge.v < num_vertices) am[edge.u][edge.v]++;
        }
    }
    return am;
}
AdjacencyList eal_to_al(const ExtendedAdjacencyList& eal) { return am_to_al(eal_to_am(eal)); }
AdjacencyMap eal_to_amap(const ExtendedAdjacencyList& eal) { return am_to_amap(eal_to_am(eal)); }

// 4. Từ Map Kề (AMap)
AdjacencyMatrix amap_to_am(const AdjacencyMap& amap) {
    int num_vertices = amap.size();
    AdjacencyMatrix am(num_vertices, std::vector<int>(num_vertices, 0));
    for (std::map<int, AMap_Data>::const_iterator it = amap.begin(); it != amap.end(); ++it) {
        int u = it->first;
        const AMap_Data& data = it->second;
        for (std::map<int, Edge>::const_iterator it_out = data.out.begin(); it_out != data.out.end(); ++it_out) {
            int v = it_out->first;
             if (u < num_vertices && v < num_vertices) am[u][v]++;
        }
    }
    return am;
}
AdjacencyList amap_to_al(const AdjacencyMap& amap) { return am_to_al(amap_to_am(amap)); }
ExtendedAdjacencyList amap_to_eal(const AdjacencyMap& amap) { return am_to_eal(amap_to_am(amap)); }

// --- HÀM CHUYỂN ĐỔI CÂY (6 converters) ---
AdjacencyListTree ap_to_al_tree(const ParentArray& parents) {
    AdjacencyListTree adj;
    int num_nodes = parents.size();
    for (int i = 0; i < num_nodes; ++i) adj[i] = std::vector<int>();
    for (int i = 0; i < num_nodes; ++i) {
        if (parents[i] != -1) {
            adj[parents[i]].push_back(i);
            adj[i].push_back(parents[i]);
        }
    }
    return adj;
}
FCNS al_tree_to_fcns(const AdjacencyListTree& adj, int root) {
    int num_nodes = adj.size();
    FCNS fcns(std::vector<int>(num_nodes, -1), std::vector<int>(num_nodes, -1));
    if (num_nodes == 0) return fcns;
    std::map<int, std::vector<int>> child_map;
    std::queue<int> q;
    std::set<int> visited;
    q.push(root);
    visited.insert(root);
    std::vector<int> traversal_order;
    traversal_order.push_back(root);
    int head = 0;
    while(head < traversal_order.size()){
        int u = traversal_order[head++];
        if (adj.count(u)) {
            const std::vector<int>& neighbors = adj.at(u);
            for(size_t i = 0; i < neighbors.size(); ++i){
                int v = neighbors[i];
                if(visited.find(v) == visited.end()){
                    visited.insert(v);
                    child_map[u].push_back(v);
                    traversal_order.push_back(v);
                }
            }
        }
    }
    for(int i = 0; i < num_nodes; ++i){
        if(!child_map[i].empty()){
            fcns.first[i] = child_map[i][0];
            for(size_t j = 0; j < child_map[i].size() - 1; ++j){
                fcns.second[child_map[i][j]] = child_map[i][j+1];
            }
        }
    }
    return fcns;
}
FCNS ap_to_fcns(const ParentArray& parents) {
    if (parents.empty()) return FCNS();
    AdjacencyListTree adj = ap_to_al_tree(parents);
    int root = -1;
    for(size_t i=0; i<parents.size(); ++i) if(parents[i] == -1) {root = i; break;}
    if(root == -1 && !parents.empty()) root = 0;
    if(root == -1) return FCNS();
    return al_tree_to_fcns(adj, root);
}
ParentArray al_tree_to_ap(const AdjacencyListTree& adj, int root) {
    int num_nodes = adj.size();
    ParentArray parents(num_nodes, -1);
    if(num_nodes == 0) return parents;
    std::queue<int> q;
    std::set<int> visited;
    q.push(root);
    visited.insert(root);
    parents[root] = -1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(adj.count(u)){
            const std::vector<int>& neighbors = adj.at(u);
            for(size_t i=0; i < neighbors.size(); ++i){
                int v = neighbors[i];
                if(visited.find(v) == visited.end()){
                    visited.insert(v);
                    parents[v] = u;
                    q.push(v);
                }
            }
        }
    }
    return parents;
}
AdjacencyListTree fcns_to_al_tree(const FCNS& fcns) {
    AdjacencyListTree adj;
    int num_nodes = fcns.first.size();
    for(int i=0; i < num_nodes; ++i) adj[i] = {};
    for(int i=0; i < num_nodes; ++i){
        int child = fcns.first[i];
        while(child != -1){
            adj[i].push_back(child);
            adj[child].push_back(i);
            child = fcns.second[child];
        }
    }
    return adj;
}
ParentArray fcns_to_ap(const FCNS& fcns) {
    AdjacencyListTree adj = fcns_to_al_tree(fcns);
    int num_nodes = fcns.first.size();
    if(num_nodes == 0) return {};
    std::vector<bool> is_child(num_nodes, false);
    for(int i=0; i<num_nodes; ++i){
        int child = fcns.first[i];
        while(child != -1){
            is_child[child] = true;
            child = fcns.second[child];
        }
    }
    int root = -1;
    for(int i=0; i<num_nodes; ++i) if(!is_child[i]) {root = i; break;}
    if(root == -1) return {};
    return al_tree_to_ap(adj, root);
}

// --- HÀM IN ẤN ---
void print_am(const AdjacencyMatrix& matrix, const std::string& title) {
    std::cout << title << std::endl;
    for (size_t i=0; i < matrix.size(); ++i) {
        std::cout << "  ";
        for (size_t j=0; j < matrix[i].size(); ++j) std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
}
void print_al(const AdjacencyList& al, const std::string& title) {
    std::cout << title << std::endl;
    for (std::map<int, std::vector<int>>::const_iterator it = al.begin(); it != al.end(); ++it) {
        std::cout << "  " << it->first << ": ";
        const std::vector<int>& neighbors = it->second;
        for (size_t i = 0; i < neighbors.size(); ++i) std::cout << neighbors[i] << " ";
        std::cout << std::endl;
    }
}
void print_eal(const ExtendedAdjacencyList& eal, const std::string& title) {
     std::cout << title << std::endl;
     for (std::map<int, EAL_Data>::const_iterator it = eal.begin(); it != eal.end(); ++it) {
        std::cout << "  " << it->first << ":\n    out: ";
        const std::vector<Edge>& out_edges = it->second.out;
        for(size_t i=0; i<out_edges.size(); ++i) std::cout << "(" << out_edges[i].u << "->" << out_edges[i].v << ") ";
        std::cout << "\n    in:  ";
        const std::vector<Edge>& in_edges = it->second.in;
        for(size_t i=0; i<in_edges.size(); ++i) std::cout << "(" << in_edges[i].u << "->" << in_edges[i].v << ") ";
        std::cout << std::endl;
     }
}
void print_amap(const AdjacencyMap& amap, const std::string& title) {
    std::cout << title << std::endl;
     for (std::map<int, AMap_Data>::const_iterator it = amap.begin(); it != amap.end(); ++it) {
        std::cout << "  " << it->first << ":\n    out: ";
        const std::map<int, Edge>& out_edges = it->second.out;
        for(std::map<int, Edge>::const_iterator it_out = out_edges.begin(); it_out != out_edges.end(); ++it_out) std::cout << it_out->first << ":(" << it_out->second.u << "->" << it_out->second.v << ") ";
        std::cout << "\n    in:  ";
        const std::map<int, Edge>& in_edges = it->second.in;
        for(std::map<int, Edge>::const_iterator it_in = in_edges.begin(); it_in != in_edges.end(); ++it_in) std::cout << it_in->first << ":(" << it_in->second.u << "->" << it_in->second.v << ") ";
        std::cout << std::endl;
     }
}
void print_ap(const ParentArray& ap, const std::string& title) {
    std::cout << title << " [ ";
    for(size_t i = 0; i < ap.size(); ++i) std::cout << (ap[i] == -1 ? "N" : std::to_string(ap[i])) << " ";
    std::cout << "]" << std::endl;
}
void print_al_tree(const AdjacencyListTree& al, const std::string& title) {
    std::cout << title << std::endl;
    for (std::map<int, std::vector<int>>::const_iterator it = al.begin(); it != al.end(); ++it) {
        std::cout << "  " << it->first << ": ";
        const std::vector<int>& neighbors = it->second;
        for (size_t i = 0; i < neighbors.size(); ++i) std::cout << neighbors[i] << " ";
        std::cout << std::endl;
    }
}
void print_fcns(const FCNS& fcns, const std::string& title) {
    std::cout << title << ":" << std::endl;
    std::cout << "  FC: [ ";
    for(size_t i=0; i<fcns.first.size(); ++i) std::cout << (fcns.first[i] == -1 ? "N" : std::to_string(fcns.first[i])) << " ";
    std::cout << "]" << std::endl;
    std::cout << "  NS: [ ";
    for(size_t i=0; i<fcns.second.size(); ++i) std::cout << (fcns.second[i] == -1 ? "N" : std::to_string(fcns.second[i])) << " ";
    std::cout << "]" << std::endl;
}
std::vector<int> get_transpose(const std::vector<int>& p) {
    if (p.empty()) return std::vector<int>();
    std::vector<int> transpose;
    int max_part = p[0];
    for (int i = 1; i <= max_part; ++i) {
        int count = 0;
        for (size_t j = 0; j < p.size(); ++j) {
            if (p[j] >= i) {
                count++;
            }
        }
        transpose.push_back(count);
    }
    return transpose;
}
void print_diagram(const std::vector<int>& p, const std::string& title) {
    std::cout << "  " << title << ":" << std::endl;
    if (p.empty()) return;
    for (size_t i = 0; i < p.size(); ++i) {
        std::cout << "    " << std::string(p[i], '*') << std::endl;
    }
}