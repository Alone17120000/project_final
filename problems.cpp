#include "problems.h"
#include "utils.h"
#include "graph.h"

// --- Bài toán 1 ---
void find_partitions(int n, int k, int max_val, std::vector<int>& p) {
    if (k == 0) {
        if (n == 0) {
            std::cout << "Phan hoach: ";
            for (size_t i = 0; i < p.size(); ++i) {
                std::cout << p[i] << (i == p.size() - 1 ? "" : " + ");
            }
            std::cout << std::endl;
            print_diagram(p, "- Bieu do Ferrers (F)");
            std::vector<int> t = get_transpose(p);
            print_diagram(t, "- Bieu do chuyen vi (F^T)");
            std::cout << "----------------------------------------" << std::endl;
        }
        return;
    }
    for (int i = std::min(n, max_val); i >= 1; --i) {
        if (n - i >= k - 1) {
            p.push_back(i);
            find_partitions(n - i, k - 1, i, p);
            p.pop_back();
        }
    }
}
void solve_problem_1() {
    int n, k;
    std::cout << "--- Bai toan 1: In bieu do Ferrers & chuyen vi ---" << std::endl;
    std::cout << "Nhap n: ";
    std::cin >> n;
    std::cout << "Nhap k: ";
    std::cin >> k;
    if (n > 0 && k > 0 && n >= k) {
        std::vector<int> current_partition;
        find_partitions(n, k, n - k + 1, current_partition);
    } else {
        std::cout << "Khong co phan hoach nao hop le." << std::endl;
    }
}

// --- Bài toán 2 ---
int countPartitions(int n, int k) {
    if (k <= 0 || n <= 0 || k > n) return 0;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (i < j) dp[i][j] = 0;
            else if (i == j) dp[i][j] = 1;
            else dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j];
        }
    }
    return dp[n][k];
}
void solve_problem_2() {
    int n, k;
    std::cout << "\n--- Bai toan 2: So sanh p_k(n) va p_max(n,k) ---" << std::endl;
    std::cout << "Nhap so n: ";
    std::cin >> n;
    std::cout << "Nhap so k: ";
    std::cin >> k;
    int p_k_n = countPartitions(n, k);
    std::cout << "So phan hoach cua " << n << " thanh " << k << " phan (p_k(n)): " << p_k_n << std::endl;
    std::cout << "So phan hoach cua " << n << " co phan tu lon nhat la " << k << " (p_max(n,k)): " << p_k_n << std::endl;
}

// --- Bài toán 3 ---
// (Các hàm phụ trợ cho Bài toán 3)
bool is_self_conjugate(const std::vector<int>& p) {
    if (p.empty()) return true;
    std::vector<int> transpose = get_transpose(p);
    return p == transpose;
}
void find_odd_distinct_partitions(int n, int max_odd, std::vector<int>& p, int& count) {
    if (n == 0) {
        count++;
        return;
    }
    if (n < 0 || max_odd <= 0) return;
    for (int i = max_odd; i >= 1; i -= 2) {
        if (n - i >= 0) {
            p.push_back(i);
            find_odd_distinct_partitions(n - i, i - 2, p, count);
            p.pop_back();
        }
    }
}
void solve_problem_3() {
    int n;
    std::cout << "\n--- Bai toan 3: Phan hoach tu lien hop ---" << std::endl;
    std::cout << "Nhap n: ";
    std::cin >> n;
    int sc_count = 0;
    std::vector<int> p;
    find_odd_distinct_partitions(n, n % 2 == 0 ? n - 1 : n, p, sc_count);
    std::cout << "So phan hoach tu lien hop cua " << n << " la: " << sc_count << std::endl;
}

// --- Bài toán 4 ---
// (Các hàm phụ trợ cho Bài toán 4)
using AdjacencyMatrix = std::vector<std::vector<int>>;
using AdjacencyList = std::vector<std::list<int>>;
AdjacencyList matrixToList(const AdjacencyMatrix& matrix, bool is_multigraph = false) {
    int V = matrix.size();
    AdjacencyList adjList(V);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matrix[i][j] > 0) {
                if(is_multigraph){
                    for(int k=0; k < matrix[i][j]; ++k){
                        adjList[i].push_back(j);
                    }
                } else {
                     adjList[i].push_back(j);
                }
            }
        }
    }
    return adjList;
}
void printAdjList(const AdjacencyList& list, const std::string& title) {
    std::cout << title << ":" << std::endl;
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << "  adj[" << i << "] -> ";
        for (int node : list[i]) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
}
void printAdjMatrix(const AdjacencyMatrix& matrix, const std::string& title) {
    std::cout << title << ":" << std::endl;
    for (const auto& row : matrix) {
        std::cout << "  ";
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}
void solve_problem_4() {
    std::cout << "\n--- Bai toan 4: Chuyen doi bieu dien do thi ---" << std::endl;
    std::cout << "\n** Truong hop Don do thi **" << std::endl;
    AdjacencyMatrix matrix_in = {
        {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0}
    };
    printAdjMatrix(matrix_in, "Ma tran ke ban dau:");
    AdjacencyList list_out = matrixToList(matrix_in, false);
    printAdjList(list_out, "\nChuyen sang Danh sach ke:");
    
    std::cout << "\n** Truong hop Da do thi **" << std::endl;
    AdjacencyMatrix multi_matrix_in = {
        {0, 2, 0}, {2, 0, 3}, {0, 3, 0}
    };
    printAdjMatrix(multi_matrix_in, "Ma tran ke (da do thi) ban dau:");
    AdjacencyList multi_list_out = matrixToList(multi_matrix_in, true);
    printAdjList(multi_list_out, "\nChuyen sang Danh sach ke:");
}

// --- Bài toán 5 ---
bool is_tree(const Graph& g) {
    int V = g.getV();
    if (V == 0) return true;
    std::vector<bool> visited(V, false);
    int edge_count = 0;
    int component_count = 0;
    for(int i = 0; i < V; ++i) {
        if(!visited[i]) {
            component_count++;
            if(component_count > 1) return false;
            std::queue<int> q;
            q.push(i);
            visited[i] = true;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(const auto& edge : g.getAdj(u)){
                    edge_count++;
                    int v = edge.first;
                    if(!visited[v]){
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    edge_count /= 2;
    return (edge_count == V - 1);
}
void solve_problem_5() {
    std::cout << "\n--- Bai toan 5: Lam bai tap trong sach [Val21] ---" << std::endl;
    std::cout << "\n** Problem 1.6: Kiem tra mot do thi co phai la cay **" << std::endl;
    Graph tree_graph(5);
    tree_graph.addEdge(0, 1); tree_graph.addEdge(0, 2); tree_graph.addEdge(1, 3); tree_graph.addEdge(1, 4);
    std::cout << "  Kiem tra do thi 1 (la cay): " << (is_tree(tree_graph) ? "Dung" : "Sai") << std::endl;
    
    std::cout << "\n** Exercise 1.7: Sinh cay nhi phan hoan chinh **" << std::endl;
    int n_nodes = 7;
    Graph complete_binary_tree(n_nodes);
    for(int i=0; i < n_nodes; ++i){
        if (2*i + 1 < n_nodes) complete_binary_tree.addEdge(i, 2*i + 1);
        if (2*i + 2 < n_nodes) complete_binary_tree.addEdge(i, 2*i + 2);
    }
    std::cout << "  Cay nhi phan hoan chinh voi " << n_nodes << " dinh:" << std::endl;
    complete_binary_tree.print();
}

// --- Bài toán 6 ---
// (Các hàm và biến phụ trợ cho Bài toán 6)
namespace Problem6 {
    std::vector<TED_Node*> postorder_nodes1, postorder_nodes2;
    std::vector<std::vector<int>> tree_dist_memo;
    void postorder_traverse_and_id(TED_Node* node, std::vector<TED_Node*>& nodes, int& counter) {
        if (!node) return;
        for (TED_Node* child : node->children) {
            postorder_traverse_and_id(child, nodes, counter);
        }
        node->postorder_id = counter++;
        nodes.push_back(node);
    }
}
int calculate_tree_edit_distance(TED_Node* root1, TED_Node* root2) {
    using namespace Problem6;
    postorder_nodes1.clear(); postorder_nodes2.clear();
    int counter = 0;
    postorder_traverse_and_id(root1, postorder_nodes1, counter);
    counter = 0;
    postorder_traverse_and_id(root2, postorder_nodes2, counter);
    int n1 = postorder_nodes1.size();
    int n2 = postorder_nodes2.size();
    tree_dist_memo.assign(n1 + 1, std::vector<int>(n2 + 1, 0));
    for (int i = 1; i <= n1; i++) tree_dist_memo[i][0] = i;
    for (int j = 1; j <= n2; j++) tree_dist_memo[0][j] = j;
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            int cost_sub = (postorder_nodes1[i-1]->label == postorder_nodes2[j-1]->label) ? 0 : 1;
            int cost_del = tree_dist_memo[i - 1][j] + 1;
            int cost_ins = tree_dist_memo[i][j - 1] + 1;
            int cost_replace = tree_dist_memo[i - 1][j - 1] + cost_sub;
            tree_dist_memo[i][j] = std::min({cost_del, cost_ins, cost_replace});
        }
    }
    return tree_dist_memo[n1][n2];
}
void solve_problem_6() {
    std::cout << "\n--- Bai toan 6: Tree Edit Distance ---" << std::endl;
    TED_Node* t1_a = new TED_Node("a"); TED_Node* t1_c = new TED_Node("c");
    TED_Node* t1_f = new TED_Node("f", {t1_a, t1_c});
    TED_Node* t2_b = new TED_Node("b"); TED_Node* t2_c = new TED_Node("c");
    TED_Node* t2_f = new TED_Node("f", {t2_b, t2_c});
    int distance = calculate_tree_edit_distance(t1_f, t2_f);
    std::cout << "Khoang cach sua cay giua T1(f(a,c)) va T2(f(b,c)) la: " << distance << std::endl;
}

// --- Bài toán 7 ---
void preorder_traversal(TreeNode* root) {
    if (root == nullptr) return;
    std::cout << root->val << " ";
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}
void inorder_traversal(TreeNode* root) {
    if (root == nullptr) return;
    inorder_traversal(root->left);
    std::cout << root->val << " ";
    inorder_traversal(root->right);
}
void postorder_traversal(TreeNode* root) {
    if (root == nullptr) return;
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    std::cout << root->val << " ";
}
void solve_problem_7() {
    std::cout << "\n--- Bai toan 7: Duyet Cay ---" << std::endl;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2); root->right = new TreeNode(3);
    root->left->left = new TreeNode(4); root->left->right = new TreeNode(5);
    std::cout << "Cay nhi phan mau: (Goc 1, con trai (2 -> 4,5), con phai 3)" << std::endl;
    std::cout << "Pre-order: "; preorder_traversal(root); std::cout << std::endl;
    std::cout << "In-order:  "; inorder_traversal(root); std::cout << std::endl;
    std::cout << "Post-order:"; postorder_traversal(root); std::cout << std::endl;
}

// --- Bài toán 8 ---
void solve_problem_8() {
    std::cout << "\n--- Bai toan 8: BFS tren Do thi don ---" << std::endl;
    Graph g(4); g.addEdge(0, 1); g.addEdge(0, 2); g.addEdge(1, 3);
    g.print(); g.BFS(0);
}

// --- Bài toán 9 ---
void solve_problem_9() {
    std::cout << "\n--- Bai toan 9: BFS tren Da do thi ---" << std::endl;
    Graph g(3); g.addEdge(0, 1); g.addEdge(0, 1); g.addEdge(1, 2);
    g.print(); g.BFS(0);
}

// --- Bài toán 10 ---
void solve_problem_10() {
    std::cout << "\n--- Bai toan 10: BFS tren Do thi tong quat ---" << std::endl;
    Graph g(3); g.addEdge(0, 1); g.addEdge(1, 1); g.addEdge(1, 2);
    g.print(); g.BFS(0);
}

// --- Bài toán 11 ---
void solve_problem_11() {
    std::cout << "\n--- Bai toan 11: DFS tren Do thi don ---" << std::endl;
    Graph g(4); g.addEdge(0, 1); g.addEdge(0, 2); g.addEdge(1, 3);
    g.print(); g.DFS(0);
}

// --- Bài toán 12 ---
void solve_problem_12() {
    std::cout << "\n--- Bai toan 12: DFS tren Da do thi ---" << std::endl;
    Graph g(3); g.addEdge(0, 1); g.addEdge(0, 1); g.addEdge(1, 2);
    g.print(); g.DFS(0);
}

// --- Bài toán 13 ---
void solve_problem_13() {
    std::cout << "\n--- Bai toan 13: DFS tren Do thi tong quat ---" << std::endl;
    Graph g(3); g.addEdge(0, 1); g.addEdge(1, 1); g.addEdge(1, 2);
    g.print(); g.DFS(0);
}

// --- Bài toán 14 ---
void solve_problem_14() {
    std::cout << "\n--- Bai toan 14: Dijkstra tren Do thi don ---" << std::endl;
    Graph g(4); g.addEdge(0, 1, 1); g.addEdge(0, 3, 4); g.addEdge(1, 2, 2); g.addEdge(2, 3, 1);
    g.print(); g.dijkstra(0);
}

// --- Bài toán 15 ---
void solve_problem_15() {
    std::cout << "\n--- Bai toan 15: Dijkstra tren Da do thi ---" << std::endl;
    Graph g(3); g.addEdge(0, 1, 5); g.addEdge(0, 1, 10); g.addEdge(1, 2, 2);
    g.print(); g.dijkstra(0);
}

// --- Bài toán 16 ---
void solve_problem_16() {
    std::cout << "\n--- Bai toan 16: Dijkstra tren Do thi tong quat ---" << std::endl;
    Graph g(3); g.addEdge(0, 1, 5); g.addEdge(1, 1, 10); g.addEdge(1, 2, 2);
    g.print(); g.dijkstra(0);
}