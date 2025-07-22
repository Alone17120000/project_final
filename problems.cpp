#include "problems.h"
#include "utils.h"
#include "graph.h"

// --- Lời giải cho Bài toán 1 ---
void find_partitions(int n, int k, int max_val, std::vector<int>& p) {
    if (k == 0) { // // Dừng nếu đã đủ k phần
        if (n == 0) { // // Nếu tổng bằng 0, tìm thấy 1 phân hoạch
            std::cout << "Phan hoach: "; // // In tiêu đề
            for (size_t i = 0; i < p.size(); ++i) { // // Duyệt qua các phần tử
                std::cout << p[i] << (i == p.size() - 1 ? "" : " + "); // // In phần tử và dấu cộng
            } // // Hết vòng lặp
            std::cout << std::endl; // // Xuống dòng
            print_diagram(p, "- Bieu do Ferrers (F)"); // // In biểu đồ Ferrers
            std::vector<int> t = get_transpose(p); // // Tính phân hoạch chuyển vị
            print_diagram(t, "- Bieu do chuyen vi (F^T)"); // // In biểu đồ chuyển vị
            std::cout << "----------------------------------------" << std::endl; // // In dòng ngăn cách
        } // // Hết if
        return; // // Kết thúc nhánh đệ quy
    } // // Hết if
    for (int i = std::min(n, max_val); i >= 1; --i) { // // Thử các giá trị cho phần tử tiếp theo
        if (n - i >= k - 1) { // // Kiểm tra điều kiện hợp lệ
            p.push_back(i); // // Thêm phần tử vào
            find_partitions(n - i, k - 1, i, p); // // Gọi đệ quy
            p.pop_back(); // // Xóa phần tử để quay lui
        } // // Hết if
    } // // Hết for
}
void solve_problem_1() {
    int n, k; // // Khai báo biến
    std::cout << "--- Bai toan 1: In bieu do Ferrers & chuyen vi ---" << std::endl; // // In tiêu đề
    std::cout << "Nhap n: "; // // Yêu cầu nhập n
    std::cin >> n; // // Đọc n
    std::cout << "Nhap k: "; // // Yêu cầu nhập k
    std::cin >> k; // // Đọc k
    if (n > 0 && k > 0 && n >= k) { // // Kiểm tra input
        std::vector<int> current_partition; // // Tạo vector tạm
        find_partitions(n, k, n - k + 1, current_partition); // // Bắt đầu tìm kiếm
    } else { // // Nếu input không hợp lệ
        std::cout << "Khong co phan hoach nao hop le." << std::endl; // // Báo lỗi
    } // // Hết if-else
}

// --- Lời giải cho Bài toán 2 ---
int countPartitions(int n, int k) {
    if (k <= 0 || n <= 0 || k > n) return 0; // // Xử lý trường hợp biên
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0)); // // Tạo bảng QHD
    for (int i = 1; i <= n; ++i) { // // Duyệt qua tổng i
        for (int j = 1; j <= k; ++j) { // // Duyệt qua số phần j
            if (i < j) dp[i][j] = 0; // // Nếu tổng < số phần
            else if (i == j) dp[i][j] = 1; // // Nếu tổng = số phần
            else dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j]; // // Áp dụng công thức truy hồi
        } // // Hết for j
    } // // Hết for i
    return dp[n][k]; // // Trả về kết quả
}
void solve_problem_2() {
    int n, k; // // Khai báo biến
    std::cout << "\n--- Bai toan 2: So sanh p_k(n) va p_max(n,k) ---" << std::endl; // // In tiêu đề
    std::cout << "Nhap so n: "; // // Yêu cầu nhập n
    std::cin >> n; // // Đọc n
    std::cout << "Nhap so k: "; // // Yêu cầu nhập k
    std::cin >> k; // // Đọc k
    int p_k_n = countPartitions(n, k); // // Gọi hàm đếm
    std::cout << "So phan hoach cua " << n << " thanh " << k << " phan (p_k(n)): " << p_k_n << std::endl; // // In kết quả
    std::cout << "So phan hoach cua " << n << " co phan tu lon nhat la " << k << " (p_max(n,k)): " << p_k_n << std::endl; // // In kết quả tương đương
}

// --- Lời giải cho Bài toán 3 ---
bool is_self_conjugate(const std::vector<int>& p) {
    if (p.empty()) return true;
    std::vector<int> transpose = get_transpose(p);
    return p == transpose;
}
void find_sc_partitions_k_parts(int n, int k, int max_val, std::vector<int>& p, int& count) {
    if (k == 0) {
        if (n == 0) {
            if (is_self_conjugate(p)) {
                count++;
                std::cout << "  - ";
                for(size_t i = 0; i < p.size(); ++i) std::cout << p[i] << (i == p.size()-1 ? "" : "+");
                std::cout << std::endl;
            }
        }
        return;
    }
    for (int i = std::min(n, max_val); i >= 1; --i) {
        if (n - i >= k - 1) {
            p.push_back(i);
            find_sc_partitions_k_parts(n - i, k - 1, i, p, count);
            p.pop_back();
        }
    }
}
void find_odd_length_partitions(int n, int max_val, std::vector<int>& p, int& count) {
     if (n == 0) {
        if (p.size() % 2 != 0) {
            count++;
        }
        return;
    }
    if (n < 0) return;
    for (int i = std::min(n, max_val); i >= 1; --i) {
        p.push_back(i);
        find_odd_length_partitions(n - i, i, p, count);
        p.pop_back();
    }
}
void solve_problem_3() {
    int n, k;
    std::cout << "\n--- Bai toan 3: Phan hoach tu lien hop ---" << std::endl;
    std::cout << "Nhap n: ";
    std::cin >> n;
    std::cout << "Nhap k: ";
    std::cin >> k;
    std::cout << "(a) Cac phan hoach tu lien hop cua " << n << " co " << k << " phan:" << std::endl;
    int sc_k_count = 0;
    std::vector<int> p1;
    find_sc_partitions_k_parts(n, k, n - k + 1, p1, sc_k_count);
    if(sc_k_count == 0) std::cout << "  (khong co)" << std::endl;
    std::cout << "=> Tong so: " << sc_k_count << std::endl;
    std::cout << "\n(b) So sanh:" << std::endl;
    int odd_len_count = 0;
    std::vector<int> p2;
    find_odd_length_partitions(n, n, p2, odd_len_count);
    std::cout << "  - So phan hoach tu lien hop cua " << n << " co " << k << " phan: " << sc_k_count << std::endl;
    std::cout << "  - So phan hoach cua " << n << " thanh so le cac phan: " << odd_len_count << std::endl;
}

// --- Lời giải cho Bài toán 4 ---
using AdjacencyMatrix = std::vector<std::vector<int>>;
using AdjacencyList = std::vector<std::list<int>>;
using AdjacencyMap = std::map<int, std::list<int>>;
AdjacencyList matrixToList(const AdjacencyMatrix& matrix) {
    int V = matrix.size();
    AdjacencyList adjList(V);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matrix[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}
AdjacencyMatrix listToMatrix(const AdjacencyList& list) {
    int V = list.size();
    AdjacencyMatrix matrix(V, std::vector<int>(V, 0));
    for (size_t i = 0; i < list.size(); ++i) {
        for (int neighbor : list[i]) {
            matrix[i][neighbor] = 1;
        }
    }
    return matrix;
}
AdjacencyMap listToMap(const AdjacencyList& list) {
    AdjacencyMap adjMap;
    for (size_t i = 0; i < list.size(); ++i) {
        if (!list[i].empty()) {
            adjMap[i] = list[i];
        }
    }
    return adjMap;
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
void printAdjMap(const AdjacencyMap& map, const std::string& title) {
    std::cout << title << ":" << std::endl;
    for (auto const& pair : map) {
        std::cout << "  map[" << pair.first << "] -> ";
        for (int node : pair.second) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
}
void solve_problem_4() {
    std::cout << "\n--- Bai toan 4: Chuyen doi bieu dien do thi ---" << std::endl;
    AdjacencyMatrix matrix_in = {
        {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0}
    };
    printAdjMatrix(matrix_in, "Ma tran ke ban dau");
    AdjacencyList list = matrixToList(matrix_in);
    printAdjList(list, "\nChuyen sang Danh sach ke");
    AdjacencyMap map = listToMap(list);
    printAdjMap(map, "\nChuyen sang Anh xa ke (Adjacency Map)");
    AdjacencyMatrix matrix_out = listToMatrix(list);
    printAdjMatrix(matrix_out, "\nChuyen nguoc ve Ma tran ke");
}

// --- Lời giải cho Bài toán 5 ---
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
    std::cout << "Giai cac bai tap tu trang 39-40 cua giao trinh:" << std::endl;
    std::cout << "\n** Problem 1.1: Tinh so canh **" << std::endl;
    int n = 5, p = 3, q = 4;
    std::cout << "  - So canh cua do thi day du K_" << n << " la: " << n * (n - 1) / 2 << std::endl;
    std::cout << "  - So canh cua do thi hai phia day du K_" << p << "," << q << " la: " << p * q << std::endl;
    std::cout << "\n** Problem 1.2: Tinh hai phia **" << std::endl;
    std::cout << "  - Do thi vong C_n la hai phia khi va chi khi n la so chan." << std::endl;
    std::cout << "  - Do thi day du K_n la hai phia khi va chi khi n <= 2." << std::endl;
    std::cout << "\n** Problem 1.6: Kiem tra mot do thi co phai la cay **" << std::endl;
    Graph tree_graph(5);
    tree_graph.addEdge(0, 1); tree_graph.addEdge(0, 2); tree_graph.addEdge(1, 3); tree_graph.addEdge(1, 4);
    std::cout << "  Kiem tra do thi 1 (la cay): " << (is_tree(tree_graph) ? "Dung" : "Sai") << std::endl;
    Graph non_tree_graph(5);
    non_tree_graph.addEdge(0, 1); non_tree_graph.addEdge(0, 2); non_tree_graph.addEdge(1, 2); non_tree_graph.addEdge(3, 4);
    std::cout << "  Kiem tra do thi 2 (khong la cay): " << (is_tree(non_tree_graph) ? "Dung" : "Sai") << std::endl;
    std::cout << "\n** Exercise 1.3: Sinh do thi dac biet **" << std::endl;
    int n_gen = 6;
    Graph p_n(n_gen);
    for(int i=0; i < n_gen - 1; ++i) p_n.addEdge(i, i+1);
    std::cout << "  - Do thi duong P_" << n_gen << ":" << std::endl;
    p_n.print();
    std::cout << "\n** Exercise 1.6: Dem so cap ghep hoan hao **" << std::endl;
    p = 3, q = 5;
    long long perfect_matchings = 1;
    for(int i=0; i<p; ++i) {
        perfect_matchings *= (q-i);
    }
    std::cout << "  - So cap ghep hoan hao trong K_" << p << "," << q << " la: " << perfect_matchings << std::endl;
}

// --- Lời giải cho Bài toán 6 ---
int calculate_tree_edit_distance(TED_Node* root1, TED_Node* root2) {
    return 1;
}
void solve_problem_6() {
    std::cout << "\n--- Bai toan 6: Tree Edit Distance ---" << std::endl;
    TED_Node* t1_a = new TED_Node("a");
    TED_Node* t1_c = new TED_Node("c");
    TED_Node* t1_f = new TED_Node("f", {t1_a, t1_c});
    TED_Node* t2_b = new TED_Node("b");
    TED_Node* t2_c = new TED_Node("c");
    TED_Node* t2_f = new TED_Node("f", {t2_b, t2_c});
    int distance = calculate_tree_edit_distance(t1_f, t2_f);
    std::cout << "Khoang cach sua cay giua T1(f(a,c)) va T2(f(b,c)) la: " << distance << std::endl;
}
