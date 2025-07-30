#include "problems.h"
#include "utils.h"
#include "graph.h"
#include <numeric> // Dùng cho std::iota
#include <algorithm> // Dùng cho std::next_permutation

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
    std::cout << "\n--- Bai toan 1: In bieu do Ferrers & chuyen vi ---" << std::endl;
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

// --- Bài toán 2 (ĐÃ SỬA) ---
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

int countPartitionsMax(int n, int k) {
    if (k <= 0 || n <= 0 || k > n) return 0;
    int target_sum = n - k;
    std::vector<std::vector<int>> dp(target_sum + 1, std::vector<int>(k + 1, 0));
    for (int j = 0; j <= k; ++j) {
        dp[0][j] = 1;
    }
    for (int i = 1; i <= target_sum; ++i) {
        for (int j = 1; j <= k; ++j) {
            dp[i][j] = dp[i][j - 1];
            if (i >= j) {
                dp[i][j] += dp[i - j][j];
            }
        }
    }
    return dp[target_sum][k];
}

void solve_problem_2() {
    int n, k;
    std::cout << "\n--- Bai toan 2: So sanh p_k(n) va p_max(n,k) ---" << std::endl;
    std::cout << "Nhap so n: ";
    std::cin >> n;
    std::cout << "Nhap so k: ";
    std::cin >> k;
    int p_k_n = countPartitions(n, k);
    int p_max_n_k = countPartitionsMax(n, k);

    std::cout << "So phan hoach cua " << n << " thanh " << k << " phan (p_k(n)): " << p_k_n << std::endl;
    std::cout << "So phan hoach cua " << n << " co phan tu lon nhat la " << k << " (p_max(n,k)): " << p_max_n_k << std::endl;
    if (p_k_n == p_max_n_k) {
        std::cout << "=> Ket qua: p_k(n) = p_max(n,k). Dinh ly duoc chung minh." << std::endl;
    } else {
        std::cout << "=> Ket qua: p_k(n) != p_max(n,k). Co loi trong tinh toan." << std::endl;
    }
}

// --- Bài toán 3 (ĐÃ SỬA) ---
bool is_self_conjugate(const std::vector<int>& p) {
    if (p.empty()) return true;
    return p == get_transpose(p);
}
void find_sc_partitions_k_parts(int n, int k, int max_val, std::vector<int>& p, std::vector<std::vector<int>>& results) {
    if (k == 0) {
        if (n == 0) {
            if (is_self_conjugate(p)) {
                results.push_back(p);
            }
        }
        return;
    }
    for (int i = std::min(n, max_val); i >= 1; --i) {
        if (n - i >= k - 1) {
            p.push_back(i);
            find_sc_partitions_k_parts(n - i, k - 1, i, p, results);
            p.pop_back();
        }
    }
}
void find_odd_distinct_partitions(int n, int max_odd, std::vector<int>& p, int& count) {
    if (n == 0) {
        count++;
        return;
    }
    if (n < 0 || max_odd < 1) {
        return;
    }
    find_odd_distinct_partitions(n, max_odd - 2, p, count);
    p.push_back(max_odd);
    find_odd_distinct_partitions(n - max_odd, max_odd - 2, p, count);
    p.pop_back();
}
void solve_problem_3() {
    int n, k;
    std::cout << "\n--- Bai toan 3: Phan hoach tu lien hop ---" << std::endl;
    std::cout << "Nhap n: ";
    std::cin >> n;
    std::cout << "Nhap k: ";
    std::cin >> k;
    std::cout << "(a) Cac phan hoach tu lien hop cua " << n << " co " << k << " phan:" << std::endl;
    std::vector<std::vector<int>> sc_partitions;
    std::vector<int> p1;
    find_sc_partitions_k_parts(n, k, n - k + 1, p1, sc_partitions);
    if(sc_partitions.empty()) {
        std::cout << "  (khong co)" << std::endl;
    } else {
        for (size_t i = 0; i < sc_partitions.size(); ++i) {
            const std::vector<int>& part = sc_partitions[i];
            std::cout << "  - ";
            for(size_t j = 0; j < part.size(); ++j) std::cout << part[j] << (j == part.size()-1 ? "" : " + ");
            std::cout << std::endl;
        }
    }
    std::cout << "=> Tong so: " << sc_partitions.size() << std::endl;
    std::cout << "\n(c) So phan hoach tu lien hop (theo dinh ly):" << std::endl;
    int odd_distinct_count = 0;
    std::vector<int> p3;
    int start_odd = (n > 0 && n % 2 == 0) ? n - 1 : n;
    find_odd_distinct_partitions(n, start_odd, p3, odd_distinct_count);
    std::cout << "  So phan hoach cua " << n << " thanh cac phan tu le va phan biet la: " << odd_distinct_count << std::endl;
    std::cout << "=> So luong phan hoach tu lien hop cua " << n << " la: " << odd_distinct_count << std::endl;
}

// --- Bài toán 4 (ĐÃ SỬA) ---
void solve_problem_4() {
    std::cout << "\n--- Bai toan 4: Chuyen doi bieu dien do thi va cay ---" << std::endl;
    std::cout << "\n--- I. DO THI ---" << std::endl;

    AdjacencyMatrix am_simple = { {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0} };
    AdjacencyMatrix am_multi = { {0, 2, 0}, {2, 0, 1}, {0, 1, 0} };
    AdjacencyMatrix am_general = { {0, 1, 0}, {1, 1, 1}, {0, 1, 0} };

    std::cout << "\n** Truong hop 1: Don do thi **" << std::endl;
    print_am(am_simple, "Dau vao (Ma tran ke):");
    AdjacencyList al_s = am_to_al(am_simple);
    print_al(al_s, "\n-> AM sang AL:");
    ExtendedAdjacencyList eal_s = am_to_eal(am_simple);
    print_eal(eal_s, "\n-> AM sang EAL:");
    AdjacencyMap amap_s = am_to_amap(am_simple);
    print_amap(amap_s, "\n-> AM sang AMap:");
    print_am(al_to_am(al_s), "\n-> (Kiem tra) AL sang AM:");

    std::cout << "\n\n** Truong hop 2: Da do thi **" << std::endl;
    print_am(am_multi, "Dau vao (Ma tran ke):");
    ExtendedAdjacencyList eal_m = am_to_eal(am_multi);
    print_eal(eal_m, "\n-> AM sang EAL:");
    print_al(eal_to_al(eal_m), "\n-> (Kiem tra) EAL sang AL:");

    std::cout << "\n\n** Truong hop 3: Do thi tong quat **" << std::endl;
    print_am(am_general, "Dau vao (Ma tran ke):");
    AdjacencyMap amap_g = am_to_amap(am_general);
    print_amap(amap_g, "\n-> AM sang AMap:");
    print_am(amap_to_am(amap_g), "\n-> (Kiem tra) AMap sang AM:");

    std::cout << "\n\n--- II. CAY ---" << std::endl;
    ParentArray ap_in(6);
    ap_in[0] = -1; ap_in[1] = 0; ap_in[2] = 0; ap_in[3] = 1; ap_in[4] = 1; ap_in[5] = 2;
    AdjacencyListTree al_in = ap_to_al_tree(ap_in);
    FCNS fcns_in = ap_to_fcns(ap_in);

    std::cout << "\n** Dau vao **" << std::endl;
    print_ap(ap_in, "Mang cha (AP):");
    print_al_tree(al_in, "Danh sach ke (AL_Tree):");
    print_fcns(fcns_in, "Con ca - Em ke (FCNS):");

    std::cout << "\n** Kiem tra chuyen doi **" << std::endl;
    print_ap(fcns_to_ap(al_tree_to_fcns(ap_to_al_tree(ap_in), 0)), "-> Kiem tra (AP -> AL -> FCNS -> AP):");
    print_fcns(al_tree_to_fcns(fcns_to_al_tree(ap_to_fcns(ap_in)), 0), "-> Kiem tra (AP -> FCNS -> AL -> FCNS):");
    print_al_tree(ap_to_al_tree(al_tree_to_ap(fcns_to_al_tree(fcns_in), 0)), "-> Kiem tra (FCNS -> AL -> AP -> AL):");
}

// --- Bài toán 5 ---
// Problem 1.1: Tính kích thước (số cạnh) của đồ thị
void problem_1_1() {
    std::cout << "\n--- Problem 1.1: Tinh so canh cua do thi ---" << std::endl;
    
    auto size_of_Kn = [](int n) {
        if (n < 2) return 0;
        return n * (n - 1) / 2;
    };

    auto size_of_Kpq = [](int p, int q) {
        return p * q;
    };

    int n = 5;
    int p = 3, q = 4;
    std::cout << "  - So canh cua K_" << n << ": " << size_of_Kn(n) << std::endl;
    std::cout << "  - So canh cua K_" << p << "," << q << ": " << size_of_Kpq(p, q) << std::endl;
}

// Problem 1.2: Xác định đồ thị hai phía
void problem_1_2() {
    std::cout << "\n--- Problem 1.2: Xac dinh do thi hai phia ---" << std::endl;
    
    auto is_Cn_bipartite = [](int n) {
        return n > 0 && n % 2 == 0;
    };
        
    auto is_Kn_bipartite = [](int n) {
        return n > 0 && n <= 2;
    };
        
    std::cout << "  - C_4 la do thi hai phia: " << (is_Cn_bipartite(4) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - C_5 la do thi hai phia: " << (is_Cn_bipartite(5) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - K_2 la do thi hai phia: " << (is_Kn_bipartite(2) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - K_3 la do thi hai phia: " << (is_Kn_bipartite(3) ? "Dung" : "Sai") << std::endl;
}

// Problem 1.3: Liệt kê cây khung
void problem_1_3() {
    std::cout << "\n--- Problem 1.3: Liet ke cay khung ---" << std::endl;
    
    int num_vertices = 7;
    std::vector<std::pair<int, int>> edges;
    edges.push_back({0,1}); edges.push_back({0,2}); edges.push_back({1,3});
    edges.push_back({1,4}); edges.push_back({2,3}); edges.push_back({2,5});
    edges.push_back({3,4}); edges.push_back({3,5}); edges.push_back({4,6});
    edges.push_back({5,6});
    
    int num_edges_in_tree = num_vertices - 1;
    
    std::vector<int> p(edges.size());
    std::iota(p.begin(), p.end(), 0);

    std::vector<std::vector<std::pair<int, int>>> spanning_trees;
    std::vector<bool> v(edges.size());
    std::fill(v.begin() + num_edges_in_tree, v.end(), true);

    do {
        std::vector<std::pair<int, int>> current_combo;
        for (int i = 0; i < edges.size(); ++i) {
            if (!v[i]) {
                current_combo.push_back(edges[i]);
            }
        }

        // Kiểm tra tính liên thông bằng BFS
        std::map<int, std::list<int>> adj;
        for(size_t i = 0; i < current_combo.size(); ++i) {
            adj[current_combo[i].first].push_back(current_combo[i].second);
            adj[current_combo[i].second].push_back(current_combo[i].first);
        }
        
        std::set<int> visited;
        std::queue<int> q;
        q.push(0);
        visited.insert(0);
        
        while(!q.empty()){
            int u = q.front(); q.pop();
            for (std::list<int>::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
                if (visited.find(*it) == visited.end()) {
                    visited.insert(*it);
                    q.push(*it);
                }
            }
        }
        
        if (visited.size() == num_vertices) {
            spanning_trees.push_back(current_combo);
        }
    } while (std::next_permutation(v.begin(), v.end()));

    std::cout << "  - Tim thay " << spanning_trees.size() << " cay khung cho do thi trong Hinh 1.30." << std::endl;
    std::cout << "  - Vi du 3 cay khung dau tien:" << std::endl;
    for (size_t i = 0; i < std::min((size_t)3, spanning_trees.size()); ++i) {
        std::cout << "    + Cay khung " << i + 1 << ": ";
        for (size_t j = 0; j < spanning_trees[i].size(); ++j) {
            std::cout << "(" << spanning_trees[i][j].first << "," << spanning_trees[i][j].second << ") ";
        }
        std::cout << std::endl;
    }
}

// Problem 1.6: Kiểm tra một đồ thị có phải là cây hay không
bool is_tree(Graph& g) {
    int v = g.getV();
    if (v == 0) return true;

    // 1. Kiểm tra tính liên thông
    if (!g.isConnected()) {
        return false;
    }

    // 2. Kiểm tra số cạnh = số đỉnh - 1
    int edge_count = 0;
    for (int i = 0; i < v; ++i) {
        edge_count += g.getAdj(i).size();
    }
    // Chia 2 vì mỗi cạnh được đếm 2 lần trong đồ thị vô hướng
    if (edge_count / 2 != v - 1) {
        return false;
    }

    return true;
}

void problem_1_6() {
    std::cout << "\n--- Problem 1.6: Kiem tra mot do thi co phai la cay ---" << std::endl;
    Graph tree_graph(5);
    tree_graph.addEdge(0, 1); tree_graph.addEdge(0, 2); tree_graph.addEdge(1, 3); tree_graph.addEdge(1, 4);
    
    Graph non_tree_graph(3); // Có chu trình
    non_tree_graph.addEdge(0, 1); non_tree_graph.addEdge(1, 2); non_tree_graph.addEdge(2, 0);
    
    std::cout << "  - Do thi 1 co phai la cay? -> " << (is_tree(tree_graph) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - Do thi 2 co phai la cay? -> " << (is_tree(non_tree_graph) ? "Dung" : "Sai") << std::endl;
}

// Exercise 1.7: Sinh cây nhị phân hoàn chỉnh
void exercise_1_7() {
    std::cout << "\n--- Exercise 1.7: Sinh cay nhi phan hoan chinh ---" << std::endl;
    
    int n_nodes = 7;
    Graph complete_binary_tree(n_nodes);
    for(int i = 0; i < n_nodes; ++i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n_nodes) complete_binary_tree.addEdge(i, left);
        if (right < n_nodes) complete_binary_tree.addEdge(i, right);
    }
    
    std::cout << "  - Cay nhi phan hoan chinh voi " << n_nodes << " dinh:" << std::endl;
    complete_binary_tree.print();
}


// Hàm chính để chạy các bài toán
void solve_problem_5() {
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "                 BAI TOAN 5" << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    // Problems [Val21, p. 39]
    problem_1_1();
    problem_1_2();
    problem_1_3();
    problem_1_6();
    
    // Exercises [Val21, p. 40]
    exercise_1_7();
}
// --- Bài toán 6 ---
void solve_problem_6() {
    std::cout << "\n--- Bai toan 6: Tree Edit Distance ---" << std::endl;
    std::cout << "  (Bai toan 6 hien tai phuc tap, logic C++ se duoc hoan thien sau)" << std::endl;
}

// --- Bài toán 7 (ĐÃ SỬA) ---
void preorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    std::cout << root->val << " ";
    preorder_traversal(root->left.get());
    preorder_traversal(root->right.get());
}
void inorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    inorder_traversal(root->left.get());
    std::cout << root->val << " ";
    inorder_traversal(root->right.get());
}
void postorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    postorder_traversal(root->left.get());
    postorder_traversal(root->right.get());
    std::cout << root->val << " ";
}
void top_down_traversal(TreeNode* root) {
    if (!root) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* node = q.front();
        q.pop();
        std::cout << node->val << " ";
        if(node->left) q.push(node->left.get());
        if(node->right) q.push(node->right.get());
    }
}
void solve_problem_7() {
    std::cout << "\n--- Bai toan 7: Duyet Cay ---" << std::endl;
    // Sửa lại để tương thích C++11 (thay std::make_unique)
    std::unique_ptr<TreeNode> root(new TreeNode(1));
    root->left.reset(new TreeNode(2));
    root->right.reset(new TreeNode(3));
    root->left->left.reset(new TreeNode(4));
    root->left->right.reset(new TreeNode(5));
    
    std::cout << "Cay nhi phan mau: (Goc 1, con trai (2 -> 4,5), con phai 3)" << std::endl;
    std::cout << "Pre-order: "; preorder_traversal(root.get()); std::cout << std::endl;
    std::cout << "In-order:  "; inorder_traversal(root.get()); std::cout << std::endl;
    std::cout << "Post-order:"; postorder_traversal(root.get()); std::cout << std::endl;
    std::cout << "Top-down (BFS):"; top_down_traversal(root.get()); std::cout << std::endl;
}

// --- Bài toán 8-10 (Gộp và sửa) ---
void solve_problem_8_10() {
    std::cout << "\n--- Bai toan 8: BFS tren Do thi don ---" << std::endl;
    Graph g8(4); g8.addEdge(0, 1); g8.addEdge(0, 2); g8.addEdge(1, 3);
    g8.analyzeGraph(); g8.BFS(0);
    std::cout << "\n--- Bai toan 9: BFS tren Da do thi ---" << std::endl;
    Graph g9(3); g9.addEdge(0, 1); g9.addEdge(0, 1); g9.addEdge(1, 2);
    g9.analyzeGraph(); g9.BFS(0);
    std::cout << "\n--- Bai toan 10: BFS tren Do thi tong quat ---" << std::endl;
    Graph g10(3); g10.addEdge(0, 1); g10.addEdge(1, 1); g10.addEdge(1, 2);
    g10.analyzeGraph(); g10.BFS(0);
    std::cout << "\n--- Bo sung: BFS tren Do thi co huong ---" << std::endl;
    Graph g_dir(4, true);
    g_dir.addEdge(0, 1); g_dir.addEdge(0, 2); g_dir.addEdge(1, 3); g_dir.addEdge(3, 0);
    g_dir.analyzeGraph(); g_dir.BFS(0);
}

// --- Bài toán 11-13 (Gộp và sửa) ---
void solve_problem_11_13() {
    std::cout << "\n--- Bai toan 11: DFS tren Do thi don ---" << std::endl;
    Graph g11(4); g11.addEdge(0, 1); g11.addEdge(0, 2); g11.addEdge(1, 3);
    g11.analyzeGraph(); g11.DFS(0);
    std::cout << "\n--- Bai toan 12: DFS tren Da do thi ---" << std::endl;
    Graph g12(3); g12.addEdge(0, 1); g12.addEdge(0, 1); g12.addEdge(1, 2);
    g12.analyzeGraph(); g12.DFS(0);
    std::cout << "\n--- Bai toan 13: DFS tren Do thi tong quat ---" << std::endl;
    Graph g13(3); g13.addEdge(0, 1); g13.addEdge(1, 1); g13.addEdge(1, 2);
    g13.analyzeGraph(); g13.DFS(0);
    std::cout << "\n--- Bo sung: DFS tren Do thi co huong ---" << std::endl;
    Graph g_dir(4, true);
    g_dir.addEdge(0, 1); g_dir.addEdge(1, 2); g_dir.addEdge(2, 0); g_dir.addEdge(2, 3); g_dir.addEdge(3, 3);
    g_dir.analyzeGraph(); g_dir.DFS(2);
}

// --- Bài toán 14-16 (Gộp) ---
void solve_problem_14_16() {
    std::cout << "\n--- Bai toan 14: Dijkstra tren Do thi don ---" << std::endl;
    Graph g(9);
    g.addEdge(0, 1, 4); g.addEdge(0, 7, 8); g.addEdge(1, 2, 8); g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7); g.addEdge(2, 5, 4); g.addEdge(2, 8, 2); g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14); g.addEdge(4, 5, 10); g.addEdge(5, 6, 2); g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6); g.addEdge(7, 8, 7);
    g.analyzeGraph(); g.dijkstra(0);
    
    std::cout << "\n--- Bai toan 15: Dijkstra tren Da do thi ---" << std::endl;
    Graph g15(3);
    g15.addEdge(0, 1, 5); g15.addEdge(0, 1, 10); g15.addEdge(1, 2, 2);
    g15.analyzeGraph(); g15.dijkstra(0);

    std::cout << "\n--- Bai toan 16: Dijkstra tren Do thi tong quat ---" << std::endl;
    Graph g16(3);
    g16.addEdge(0, 1, 5); g16.addEdge(1, 1, 10); g16.addEdge(1, 2, 2);
    g16.analyzeGraph(); g16.dijkstra(0);
}