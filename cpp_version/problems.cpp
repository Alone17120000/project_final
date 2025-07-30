#include "problems.h"
#include "utils.h"
#include "graph.h"
#include <iterator> 
#include <map>
#include <set>
#include <memory>
#include <algorithm> 
#include <iomanip> 
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

// --- Bài toán 3 ---
bool is_self_conjugate(const std::vector<int>& p) {
    if (p.empty()) return true;
    return p == get_transpose(p);
}
void find_sc_partitions_k_parts(int n, int k, int max_val, std::vector<int>& p, std::vector<std::vector<int>>& results) {
    if (k == 0) {
        if (n == 0 && is_self_conjugate(p)) {
            results.push_back(p);
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
    if (n < 0 || max_odd < 1) return;
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

// --- Bài toán 4 ---
void solve_problem_4() {
    std::cout << "\n--- Bai toan 4: Chuyen doi bieu dien do thi va cay ---" << std::endl;
    std::cout << "\n--- I. DO THI (12 converters) ---" << std::endl;
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
    std::cout << "\n\n--- II. CAY (6 converters) ---" << std::endl;
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
void problem_1_1() {
    std::cout << "\n--- Problem 1.1: Tinh so canh cua do thi ---" << std::endl;
    auto size_of_Kn = [](int n) { return n < 2 ? 0 : n * (n - 1) / 2; };
    auto size_of_Kpq = [](int p, int q) { return p * q; };
    int n = 5, p = 3, q = 4;
    std::cout << "  - So canh cua K_" << n << ": " << size_of_Kn(n) << std::endl;
    std::cout << "  - So canh cua K_" << p << "," << q << ": " << size_of_Kpq(p, q) << std::endl;
}
void problem_1_2() {
    std::cout << "\n--- Problem 1.2: Xac dinh do thi hai phia ---" << std::endl;
    auto is_Cn_bipartite = [](int n) { return n > 0 && n % 2 == 0; };
    auto is_Kn_bipartite = [](int n) { return n > 0 && n <= 2; };
    std::cout << "  - C_4 la do thi hai phia: " << (is_Cn_bipartite(4) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - C_5 la do thi hai phia: " << (is_Cn_bipartite(5) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - K_2 la do thi hai phia: " << (is_Kn_bipartite(2) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - K_3 la do thi hai phia: " << (is_Kn_bipartite(3) ? "Dung" : "Sai") << std::endl;
}
void problem_1_3() {
    std::cout << "\n--- Problem 1.3: Liet ke cay khung ---" << std::endl;
    int num_vertices = 7;
    std::vector<std::pair<int, int> > edges;
    edges.push_back(std::make_pair(0,1)); edges.push_back(std::make_pair(0,2)); edges.push_back(std::make_pair(1,3));
    edges.push_back(std::make_pair(1,4)); edges.push_back(std::make_pair(2,3)); edges.push_back(std::make_pair(2,5));
    edges.push_back(std::make_pair(3,4)); edges.push_back(std::make_pair(3,5)); edges.push_back(std::make_pair(4,6));
    edges.push_back(std::make_pair(5,6));
    int num_edges_in_tree = num_vertices - 1;
    std::vector<bool> v(edges.size());
    std::fill(v.begin() + num_edges_in_tree, v.end(), true);
    int count = 0;
    do {
        std::vector<std::pair<int, int>> current_combo;
        for (int i = 0; i < edges.size(); ++i) if (!v[i]) current_combo.push_back(edges[i]);
        Graph g(num_vertices);
        for(size_t i = 0; i < current_combo.size(); ++i) g.addEdge(current_combo[i].first, current_combo[i].second);
        if (g.isConnected()) {
            count++;
        }
    } while (std::next_permutation(v.begin(), v.end()));
    std::cout << "  - Tong so cay khung tim thay: " << count << std::endl;
}
bool is_tree(Graph& g) {
    int v = g.getV();
    if (v == 0) return true;
    if (!g.isConnected()) return false;
    int edge_count = 0;
    for (int i = 0; i < v; ++i) edge_count += g.getAdj(i).size();
    return (edge_count / 2 == v - 1);
}
void problem_1_6() {
    std::cout << "\n--- Problem 1.6: Kiem tra mot do thi co phai la cay ---" << std::endl;
    Graph tree_graph(5);
    tree_graph.addEdge(0, 1); tree_graph.addEdge(0, 2); tree_graph.addEdge(1, 3); tree_graph.addEdge(1, 4);
    Graph non_tree_graph(3);
    non_tree_graph.addEdge(0, 1); non_tree_graph.addEdge(1, 2); non_tree_graph.addEdge(2, 0);
    std::cout << "  - Do thi 1 co phai la cay? -> " << (is_tree(tree_graph) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - Do thi 2 co phai la cay? -> " << (is_tree(non_tree_graph) ? "Dung" : "Sai") << std::endl;
}
void exercise_1_7() {
    std::cout << "\n--- Exercise 1.7: Sinh cay nhi phan hoan chinh ---" << std::endl;
    int n_nodes = 7;
    Graph g(n_nodes);
    for(int i = 0; i < n_nodes; ++i) {
        if (2*i + 1 < n_nodes) g.addEdge(i, 2*i + 1);
        if (2*i + 2 < n_nodes) g.addEdge(i, 2*i + 2);
    }
    std::cout << "  - Cay nhi phan hoan chinh voi " << n_nodes << " dinh:" << std::endl;
    g.print();
}
void solve_problem_5() {
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "                 BAI TOAN 5" << std::endl;
    std::cout << "=====================================================" << std::endl;
    problem_1_1();
    problem_1_2();
    problem_1_3();
    problem_1_6();
    exercise_1_7();
}

// --- Bài toán 6 ---

namespace Problem6 {
    // Biến toàn cục cho các phương pháp, được reset mỗi lần gọi
    std::vector<TED_Node*> postorder1, postorder2;
    int min_cost_global;

    // Cấu trúc để làm key cho map trong D&C
    struct NodeRange {
        int i1, j1, i2, j2;
        bool operator<(const NodeRange& other) const {
            if (i1 != other.i1) return i1 < other.i1;
            if (j1 != other.j1) return j1 < other.j1;
            if (i2 != other.i2) return i2 < other.i2;
            return j2 < other.j2;
        }
    };
    std::map<NodeRange, int> memo; // Bộ nhớ cho D&C/QHD
}

// --- Các hàm tiền xử lý ---
void postorder_traverse_and_id(TED_Node* node, std::vector<TED_Node*>& nodes) {
    if (!node) return;
    for (size_t i = 0; i < node->children.size(); ++i) {
        postorder_traverse_and_id(node->children[i].get(), nodes);
    }
    node->postorder_id = nodes.size();
    nodes.push_back(node);
}

void calculate_leftmost_leaf_ids(const std::vector<TED_Node*>& nodes) {
    for (size_t i = 0; i < nodes.size(); ++i) {
        TED_Node* node = nodes[i];
        if (node->children.empty()) {
            node->leftmost_leaf_id = node->postorder_id;
        } else {
            // Sửa lại logic: leftmost leaf của một node là leftmost leaf của con đầu tiên
            node->leftmost_leaf_id = nodes[node->children[0]->postorder_id]->leftmost_leaf_id;
        }
    }
}

// --- (a) Backtracking ---
void backtrack_recursive(int k, int current_cost, std::map<TED_Node*, TED_Node*>& mapping, std::set<TED_Node*>& used_nodes) {
    using namespace Problem6;
    if (k == postorder1.size()) {
        int final_cost = current_cost + (postorder2.size() - used_nodes.size());
        if (final_cost < min_cost_global) {
            min_cost_global = final_cost;
        }
        return;
    }

    TED_Node* u = postorder1[k];

    // Lựa chọn 1: Xóa u
    backtrack_recursive(k + 1, current_cost + 1, mapping, used_nodes);

    // Lựa chọn 2: Ánh xạ u sang v
    for (size_t i = 0; i < postorder2.size(); ++i) {
        TED_Node* v = postorder2[i];
        if (used_nodes.find(v) == used_nodes.end()) { // Nếu v chưa được sử dụng
            int sub_cost = (u->label == v->label) ? 0 : 1;
            mapping[u] = v;
            used_nodes.insert(v);
            backtrack_recursive(k + 1, current_cost + sub_cost, mapping, used_nodes);
            used_nodes.erase(v); // Quay lui
            mapping.erase(u);
        }
    }
}
int solve_backtracking() {
    using namespace Problem6;
    min_cost_global = postorder1.size() + postorder2.size();
    std::map<TED_Node*, TED_Node*> mapping;
    std::set<TED_Node*> used_nodes;
    backtrack_recursive(0, 0, mapping, used_nodes);
    return min_cost_global;
}


// --- (b) Branch-&-Bound ---
void branch_and_bound_recursive(int k, int current_cost, std::map<TED_Node*, TED_Node*>& mapping, std::set<TED_Node*>& used_nodes) {
    using namespace Problem6;
    if (current_cost >= min_cost_global) { // Cắt tỉa
        return;
    }
    if (k == postorder1.size()) {
        int final_cost = current_cost + (postorder2.size() - used_nodes.size());
        if (final_cost < min_cost_global) {
            min_cost_global = final_cost;
        }
        return;
    }

    TED_Node* u = postorder1[k];

    // Lựa chọn 1: Xóa u
    branch_and_bound_recursive(k + 1, current_cost + 1, mapping, used_nodes);

    // Lựa chọn 2: Ánh xạ u sang v
    for (size_t i = 0; i < postorder2.size(); ++i) {
        TED_Node* v = postorder2[i];
        if (used_nodes.find(v) == used_nodes.end()) {
            int sub_cost = (u->label == v->label) ? 0 : 1;
            mapping[u] = v;
            used_nodes.insert(v);
            branch_and_bound_recursive(k + 1, current_cost + sub_cost, mapping, used_nodes);
            used_nodes.erase(v);
            mapping.erase(u);
        }
    }
}
int solve_branch_and_bound() {
    using namespace Problem6;
    min_cost_global = postorder1.size() + postorder2.size();
    std::map<TED_Node*, TED_Node*> mapping;
    std::set<TED_Node*> used_nodes;
    branch_and_bound_recursive(0, 0, mapping, used_nodes);
    return min_cost_global;
}


// --- (c) Divide-&-Conquer ---
int solve_divide_and_conquer_recursive(int i, int j) {
    using namespace Problem6;
    if (i == -1 && j == -1) return 0;
    if (i == -1) return j + 1;
    if (j == -1) return i + 1;

    TED_Node* u = postorder1[i];
    TED_Node* v = postorder2[j];
    int cost_sub = (u->label == v->label) ? 0 : 1;

    int cost_del = solve_divide_and_conquer_recursive(i - 1, j) + 1;
    int cost_ins = solve_divide_and_conquer_recursive(i, j - 1) + 1;
    int cost_rep = solve_divide_and_conquer_recursive(i - 1, j - 1) + cost_sub;

    return std::min({cost_del, cost_ins, cost_rep});
}
int solve_divide_and_conquer() {
    using namespace Problem6;
    return solve_divide_and_conquer_recursive(postorder1.size() - 1, postorder2.size() - 1);
}


// --- (d) Dynamic Programming ---
int solve_dynamic_programming() {
    using namespace Problem6;
    int n1 = postorder1.size();
    int n2 = postorder2.size();
    std::vector<std::vector<int>> fd(n1 + 1, std::vector<int>(n2 + 1, 0));

    // Khởi tạo hàng và cột 0
    for (int i = 1; i <= n1; i++) fd[i][0] = i;
    for (int j = 1; j <= n2; j++) fd[0][j] = j;

    // Tính toán ma trận
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            TED_Node* u = postorder1[i - 1];
            TED_Node* v = postorder2[j - 1];
            int cost_sub = (u->label == v->label) ? 0 : 1;

            if (u->leftmost_leaf_id == postorder1[i - 1]->leftmost_leaf_id &&
                v->leftmost_leaf_id == postorder2[j - 1]->leftmost_leaf_id)
            {
                int cost_del = fd[i - 1][j] + 1;
                int cost_ins = fd[i][j - 1] + 1;
                int cost_rep = fd[i - 1][j - 1] + cost_sub;
                fd[i][j] = std::min({cost_del, cost_ins, cost_rep});
            } else {
                int i_lm = u->leftmost_leaf_id;
                int j_lm = v->leftmost_leaf_id;

                int term_del = fd[i - 1][j] + 1;
                int term_ins = fd[i][j - 1] + 1;
                // Công thức Zhang-Shasha gốc
                int term_rep = fd[i_lm - 1][j_lm - 1] + (fd[i-1][j-1] - fd[i_lm-1][j_lm-1]) + cost_sub;
                fd[i][j] = std::min({term_del, term_ins, term_rep});
            }
        }
    }
    
    std::cout << "\n  Bang quy hoach dong (forest_dist) fd[i][j]:" << std::endl;
    std::cout << "        ";
    for(int j=0; j<n2; ++j) std::cout << std::setw(4) << postorder2[j]->label << " ";
    std::cout << std::endl;
    for (int i = 0; i <= n1; ++i) {
        if (i > 0) std::cout << std::setw(4) << postorder1[i-1]->label << " | ";
        else std::cout << "   _ | ";
        for (int j = 0; j <= n2; ++j) {
            std::cout << std::setw(4) << fd[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return fd[n1][n2];
}


// --- HÀM CHÍNH CHO BÀI 6 ---
void solve_problem_6() {
    std::cout << "\n--- Bai toan 6: Tree Edit Distance ---" << std::endl;
    std::cout << "So sanh T1 = f(a,c) va T2 = f(b,c)" << std::endl;
    
    // Tạo cây T1
    std::unique_ptr<TED_Node> t1_f(new TED_Node("f"));
    t1_f->children.push_back(std::unique_ptr<TED_Node>(new TED_Node("a")));
    t1_f->children.push_back(std::unique_ptr<TED_Node>(new TED_Node("c")));

    // Tạo cây T2
    std::unique_ptr<TED_Node> t2_f(new TED_Node("f"));
    t2_f->children.push_back(std::unique_ptr<TED_Node>(new TED_Node("b")));
    t2_f->children.push_back(std::unique_ptr<TED_Node>(new TED_Node("c")));

    // Tiền xử lý cây một lần
    // <<< SỬA LỖI TẠI ĐÂY: Sửa postorder_nodes1 thành postorder1 >>>
    Problem6::postorder1.clear(); 
    Problem6::postorder2.clear();
    postorder_traverse_and_id(t1_f.get(), Problem6::postorder1);
    postorder_traverse_and_id(t2_f.get(), Problem6::postorder2);
    
    // Tính toán leftmost_leaf_ids sau khi có postorder traversal
    calculate_leftmost_leaf_ids(Problem6::postorder1);
    calculate_leftmost_leaf_ids(Problem6::postorder2);
    
    std::cout << "\n(a) Giai bang Backtracking:" << std::endl;
    int distance_bt = solve_backtracking();
    std::cout << "   Khoang cach sua cay la: " << distance_bt << std::endl;

    std::cout << "\n(b) Giai bang Branch-&-Bound:" << std::endl;
    int distance_bnb = solve_branch_and_bound();
    std::cout << "   Khoang cach sua cay la: " << distance_bnb << std::endl;

    std::cout << "\n(c) Giai bang Divide-&-Conquer (De quy co ban):" << std::endl;
    int distance_dc = solve_divide_and_conquer();
    std::cout << "   Khoang cach sua cay la: " << distance_dc << std::endl;

    std::cout << "\n(d) Giai bang Dynamic Programming (Thuat toan Zhang-Shasha):" << std::endl;
    int distance_dp = solve_dynamic_programming();
    std::cout << "   Khoang cach sua cay la: " << distance_dp << std::endl;

    std::cout << "\n=> Ket qua cuoi cung (tu DP):" << std::endl;
    std::cout << "   Chi phi toi thieu la 1, tuong ung voi viec thay the nhan 'a' bang 'b'" << std::endl;
}


// --- Bài toán 7 ---
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

// --- Bài toán 8-10 ---
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
// --- Bài toán 11-13 ---
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
// --- Bài toán 14-16 ---
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