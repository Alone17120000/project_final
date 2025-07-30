#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <list>
#include <queue>
#include <utility>
#include <limits>
#include <cmath>
#include <map>
#include <set>
#include <memory>
#include <iomanip>


struct Edge {
    int u, v;
    Edge(int from = -1, int to = -1) : u(from), v(to) {}
};

struct TreeNode {
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct TED_Node {
    std::string label;
    std::vector<std::unique_ptr<TED_Node>> children;
    int postorder_id;
    int leftmost_leaf_id;
    TED_Node(std::string lbl) : label(lbl), postorder_id(-1), leftmost_leaf_id(-1) {}
    TED_Node(std::string lbl, std::vector<std::unique_ptr<TED_Node>> ch) : label(std::move(lbl)), children(std::move(ch)), postorder_id(-1), leftmost_leaf_id(-1) {}
};


using AdjacencyMatrix = std::vector<std::vector<int>>;
using AdjacencyList = std::map<int, std::vector<int>>;
struct EAL_Data { std::vector<Edge> in; std::vector<Edge> out; };
using ExtendedAdjacencyList = std::map<int, EAL_Data>;
struct AMap_Data { std::map<int, Edge> in; std::map<int, Edge> out; };
using AdjacencyMap = std::map<int, AMap_Data>;

using ParentArray = std::vector<int>;
using FCNS = std::pair<std::vector<int>, std::vector<int>>;
using AdjacencyListTree = std::map<int, std::vector<int>>;


// Bài 1, 3
std::vector<int> get_transpose(const std::vector<int>& p);
void print_diagram(const std::vector<int>& p, const std::string& title);

// Bài 4 - Đồ thị (12 hàm)
AdjacencyList am_to_al(const AdjacencyMatrix& am);
ExtendedAdjacencyList am_to_eal(const AdjacencyMatrix& am);
AdjacencyMap am_to_amap(const AdjacencyMatrix& am);
AdjacencyMatrix al_to_am(const AdjacencyList& al);
ExtendedAdjacencyList al_to_eal(const AdjacencyList& al);
AdjacencyMap al_to_amap(const AdjacencyList& al);
AdjacencyMatrix eal_to_am(const ExtendedAdjacencyList& eal);
AdjacencyList eal_to_al(const ExtendedAdjacencyList& eal);
AdjacencyMap eal_to_amap(const ExtendedAdjacencyList& eal);
AdjacencyMatrix amap_to_am(const AdjacencyMap& amap);
AdjacencyList amap_to_al(const AdjacencyMap& amap);
ExtendedAdjacencyList amap_to_eal(const AdjacencyMap& amap);

// Bài 4 - Cây (6 hàm)
AdjacencyListTree ap_to_al_tree(const ParentArray& parents);
FCNS al_tree_to_fcns(const AdjacencyListTree& adj, int root);
FCNS ap_to_fcns(const ParentArray& parents);
ParentArray al_tree_to_ap(const AdjacencyListTree& adj, int root);
AdjacencyListTree fcns_to_al_tree(const FCNS& fcns);
ParentArray fcns_to_ap(const FCNS& fcns);

// Bài 4 - In ấn
void print_am(const AdjacencyMatrix& matrix, const std::string& title);
void print_al(const AdjacencyList& al, const std::string& title);
void print_eal(const ExtendedAdjacencyList& eal, const std::string& title);
void print_amap(const AdjacencyMap& amap, const std::string& title);
void print_ap(const ParentArray& ap, const std::string& title);
void print_al_tree(const AdjacencyListTree& al, const std::string& title);
void print_fcns(const FCNS& fcns, const std::string& title);

#endif // UTILS_H