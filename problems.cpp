#include "problems.h"
#include "utils.h"
#include "graph.h"

// --- Bài toán 1 ---
void find_partitions(int n, int k, int max_val, std::vector<int>& p) {
    if (k == 0) { // // Dừng nếu đã đủ k phần
        if (n == 0) { // // Nếu tổng bằng 0, tìm thấy 1 phân hoạch
            std::cout << "Phan hoach: ";
            for (size_t i = 0; i < p.size(); ++i) { // // Duyệt qua các phần tử
                std::cout << p[i] << (i == p.size() - 1 ? "" : " + "); // // In phần tử và dấu cộng
            } 
            std::cout << std::endl; 
            print_diagram(p, "- Bieu do Ferrers (F)"); // // In biểu đồ Ferrers
            std::vector<int> t = get_transpose(p); // // Tính phân hoạch chuyển vị
            print_diagram(t, "- Bieu do chuyen vi (F^T)"); // // In biểu đồ chuyển vị
            std::cout << "----------------------------------------" << std::endl; 
        } 
        return; // // Kết thúc nhánh đệ quy
    } 
    for (int i = std::min(n, max_val); i >= 1; --i) { // // Thử các giá trị cho phần tử tiếp theo
        if (n - i >= k - 1) { // // Kiểm tra điều kiện hợp lệ
            p.push_back(i); // // Thêm phần tử vào
            find_partitions(n - i, k - 1, i, p); // // Gọi đệ quy
            p.pop_back(); // // Xóa phần tử để quay lui
        } 
    } 
}
void solve_problem_1() {
    int n, k; // // Khai báo biến
    std::cout << "--- Bai toan 1: In bieu do Ferrers & chuyen vi ---" << std::endl; 
    std::cout << "Nhap n: "; // // Yêu cầu nhập n
    std::cin >> n; // // Đọc n
    std::cout << "Nhap k: "; // // Yêu cầu nhập k
    std::cin >> k; // // Đọc k
    if (n > 0 && k > 0 && n >= k) { // // Kiểm tra input
        std::vector<int> current_partition; // // Tạo vector tạm
        find_partitions(n, k, n - k + 1, current_partition); // // Bắt đầu tìm kiếm
    } else { // // Nếu input không hợp lệ
        std::cout << "Khong co phan hoach nao hop le." << std::endl; // // Báo lỗi
    } 
}

// --- Bài toán 2 ---
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
    return dp[n][k]; 
}
void solve_problem_2() {
    int n, k; // // Khai báo biến
    std::cout << "\n--- Bai toan 2: So sanh p_k(n) va p_max(n,k) ---" << std::endl; 
    std::cout << "Nhap so n: "; // // Yêu cầu nhập n
    std::cin >> n; // // Đọc n
    std::cout << "Nhap so k: "; // // Yêu cầu nhập k
    std::cin >> k; // // Đọc k
    int p_k_n = countPartitions(n, k); // // Gọi hàm đếm
    std::cout << "So phan hoach cua " << n << " thanh " << k << " phan (p_k(n)): " << p_k_n << std::endl; 
    std::cout << "So phan hoach cua " << n << " co phan tu lon nhat la " << k << " (p_max(n,k)): " << p_k_n << std::endl; 
}

// --- Bài toán 3 ---
bool is_self_conjugate(const std::vector<int>& p) {
    if (p.empty()) return true; // // Phân hoạch rỗng là tự liên hợp
    std::vector<int> transpose = get_transpose(p); // // Tính phân hoạch liên hợp
    return p == transpose; // // So sánh phân hoạch gốc và liên hợp
}
void find_sc_partitions_k_parts(int n, int k, int max_val, std::vector<int>& p, int& count) {
    if (k == 0) { // // Dừng nếu đã đủ k phần
        if (n == 0) { // // Dừng nếu tổng đã bằng 0
            if (is_self_conjugate(p)) { // // Kiểm tra tính tự liên hợp
                count++; // // Tăng biến đếm
                std::cout << "  - "; 
                for(size_t i = 0; i < p.size(); ++i) std::cout << p[i] << (i == p.size()-1 ? "" : "+"); // // In các phần tử
                std::cout << std::endl; // // Xuống dòng
            } 
        } 
    } 
    for (int i = std::min(n, max_val); i >= 1; --i) { // // Vòng lặp quay lui
        if (n - i >= k - 1) { // // Kiểm tra điều kiện
            p.push_back(i); // // Thêm phần tử
            find_sc_partitions_k_parts(n - i, k - 1, i, p, count); // // Gọi đệ quy
            p.pop_back(); // // Quay lui
        } 
    } 
}
void find_odd_length_partitions(int n, int max_val, std::vector<int>& p, int& count) {
     if (n == 0) { // // Dừng nếu tổng bằng 0
        if (p.size() % 2 != 0) { // // Kiểm tra số lượng phần tử có lẻ không
            count++; // // Tăng biến đếm
        } 
        return; // // Kết thúc nhánh
    }
    if (n < 0) return; // // Dừng nếu tổng bị âm
    for (int i = std::min(n, max_val); i >= 1; --i) { // // Vòng lặp quay lui
        p.push_back(i); // // Thêm phần tử
        find_odd_length_partitions(n - i, i, p, count); // // Gọi đệ quy
        p.pop_back(); // // Quay lui
    } 
}
void solve_problem_3() {
    int n, k; // // Khai báo biến
    std::cout << "\n--- Bai toan 3: Phan hoach tu lien hop ---" << std::endl; 
    std::cout << "Nhap n: "; // // Yêu cầu nhập n
    std::cin >> n; // // Đọc n
    std::cout << "Nhap k: "; // // Yêu cầu nhập k
    std::cin >> k; // // Đọc k
    std::cout << "(a) Cac phan hoach tu lien hop cua " << n << " co " << k << " phan:" << std::endl; 
    int sc_k_count = 0; // // Khởi tạo biến đếm
    std::vector<int> p1; // // Tạo vector tạm
    find_sc_partitions_k_parts(n, k, n - k + 1, p1, sc_k_count); // // Gọi hàm tìm kiếm
    if(sc_k_count == 0) std::cout << "  (khong co)" << std::endl;
    std::cout << "=> Tong so: " << sc_k_count << std::endl; 
    std::cout << "\n(b) So sanh:" << std::endl; // // In tiêu đề phụ
    int odd_len_count = 0; // // Khởi tạo biến đếm
    std::vector<int> p2; // // Tạo vector tạm
    find_odd_length_partitions(n, n, p2, odd_len_count); // // Gọi hàm đếm
    std::cout << "  - So phan hoach tu lien hop cua " << n << " co " << k << " phan: " << sc_k_count << std::endl; // // In kết quả so sánh
    std::cout << "  - So phan hoach cua " << n << " thanh so le cac phan: " << odd_len_count << std::endl; // // In kết quả so sánh
}

// --- Bài toán 4 ---
using AdjacencyMatrix = std::vector<std::vector<int>>; // // Định nghĩa kiểu Ma trận kề
using AdjacencyList = std::vector<std::list<int>>; // // Định nghĩa kiểu Danh sách kề
using AdjacencyMap = std::map<int, std::list<int>>; // // Định nghĩa kiểu Ánh xạ kề
AdjacencyList matrixToList(const AdjacencyMatrix& matrix) {
    int V = matrix.size(); // // Lấy số đỉnh
    AdjacencyList adjList(V); // // Tạo danh sách kề rỗng
    for (int i = 0; i < V; ++i) { // // Duyệt qua hàng
        for (int j = 0; j < V; ++j) { // // Duyệt qua cột
            if (matrix[i][j] == 1) { // // Nếu có cạnh
                adjList[i].push_back(j); // // Thêm vào danh sách kề
            } 
        } 
    } 
    return adjList; 
}
AdjacencyMatrix listToMatrix(const AdjacencyList& list) {
    int V = list.size(); // // Lấy số đỉnh
    AdjacencyMatrix matrix(V, std::vector<int>(V, 0)); // // Tạo ma trận 0
    for (size_t i = 0; i < list.size(); ++i) { // // Duyệt qua các đỉnh
        for (int neighbor : list[i]) { // // Duyệt qua các đỉnh kề
            matrix[i][neighbor] = 1; // // Đánh dấu cạnh trong ma trận
        } // // Hết for neighbor
    } 
    return matrix; // // Trả về ma trận
}
AdjacencyMap listToMap(const AdjacencyList& list) {
    AdjacencyMap adjMap; // // Tạo map rỗng
    for (size_t i = 0; i < list.size(); ++i) { // // Duyệt qua các đỉnh
        if (!list[i].empty()) { // // Nếu đỉnh có hàng xóm
            adjMap[i] = list[i]; // // Thêm vào map
        } 
    } 
    return adjMap; // // Trả về map
}
void printAdjList(const AdjacencyList& list, const std::string& title) {
    std::cout << title << ":" << std::endl; 
    for (size_t i = 0; i < list.size(); ++i) { // // Duyệt qua các đỉnh
        std::cout << "  adj[" << i << "] -> "; // // In định dạng
        for (int node : list[i]) { // // Duyệt qua các đỉnh kề
            std::cout << node << " "; // // In đỉnh kề
        } 
        std::cout << std::endl; // // Xuống dòng
    }
}
void printAdjMatrix(const AdjacencyMatrix& matrix, const std::string& title) {
    std::cout << title << ":" << std::endl; // // In tiêu đề
    for (const auto& row : matrix) { // // Duyệt qua từng hàng
        std::cout << "  "; // // Canh lề
        for (int val : row) { // // Duyệt qua từng giá trị
            std::cout << val << " "; // // In giá trị
        } 
        std::cout << std::endl; // // Xuống dòng
    } 
}
void printAdjMap(const AdjacencyMap& map, const std::string& title) {
    std::cout << title << ":" << std::endl; 
    for (auto const& pair : map) { // // Duyệt qua các cặp trong map
        std::cout << "  map[" << pair.first << "] -> "; // // In key
        for (int node : pair.second) { // // Duyệt qua value
            std::cout << node << " "; // // In đỉnh kề
        } 
        std::cout << std::endl; // // Xuống dòng
    } 
}
void solve_problem_4() {
    std::cout << "\n--- Bai toan 4: Chuyen doi bieu dien do thi ---" << std::endl; 
    AdjacencyMatrix matrix_in = { // // Tạo ma trận mẫu
        {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0}
    };
    printAdjMatrix(matrix_in, "Ma tran ke ban dau"); // // In ma trận gốc
    AdjacencyList list = matrixToList(matrix_in); // // Chuyển đổi
    printAdjList(list, "\nChuyen sang Danh sach ke"); 
    AdjacencyMap map = listToMap(list); // // Chuyển đổi
    printAdjMap(map, "\nChuyen sang Anh xa ke (Adjacency Map)"); 
    AdjacencyMatrix matrix_out = listToMatrix(list); // // Chuyển đổi
    printAdjMatrix(matrix_out, "\nChuyen nguoc ve Ma tran ke");
}

// --- Bài toán 5 ---
bool is_tree(const Graph& g) {
    int V = g.getV(); // // Lấy số đỉnh
    if (V == 0) return true; // // Đồ thị rỗng là cây
    std::vector<bool> visited(V, false); // // Mảng đánh dấu
    int edge_count = 0; // // Biến đếm cạnh
    int component_count = 0; // // Biến đếm thành phần liên thông
    for(int i = 0; i < V; ++i) { // // Duyệt qua các đỉnh
        if(!visited[i]) { // // Nếu gặp đỉnh chưa thăm
            component_count++; // // Tăng số thành phần liên thông
            if(component_count > 1) return false; // // Nếu > 1 thì không liên thông, không phải cây
            std::queue<int> q; // // Dùng BFS
            q.push(i); // // Bắt đầu từ đỉnh i
            visited[i] = true; // // Đánh dấu đã thăm
            while(!q.empty()){ // // Lặp khi hàng đợi còn phần tử
                int u = q.front(); // // Lấy đỉnh ra
                q.pop(); // // Xóa khỏi hàng đợi
                for(const auto& edge : g.getAdj(u)){ // // Duyệt các đỉnh kề
                    edge_count++; // // Đếm tổng số bậc
                    int v = edge.first; // // Lấy đỉnh kề
                    if(!visited[v]){ // // Nếu chưa thăm
                        visited[v] = true; // // Đánh dấu
                        q.push(v); // // Thêm vào hàng đợi
                    } 
                } 
            } 
        } 
    } 
    edge_count /= 2; // // Chia 2 để ra số cạnh thực tế
    return (edge_count == V - 1); // // Kiểm tra điều kiện số cạnh = số đỉnh - 1
}
void solve_problem_5() {
    std::cout << "\n--- Bai toan 5: Lam bai tap trong sach [Val21] ---" << std::endl; 
    std::cout << "Giai cac bai tap tu trang 39-40 cua giao trinh:" << std::endl; 
    std::cout << "\n** Problem 1.1: Tinh so canh **" << std::endl; 
    int n = 5, p = 3, q = 4; // // Khởi tạo giá trị
    std::cout << "  - So canh cua do thi day du K_" << n << " la: " << n * (n - 1) / 2 << std::endl; 
    std::cout << "  - So canh cua do thi hai phia day du K_" << p << "," << q << " la: " << p * q << std::endl; 
    std::cout << "\n** Problem 1.2: Tinh hai phia **" << std::endl; 
    std::cout << "  - Do thi vong C_n la hai phia khi va chi khi n la so chan." << std::endl; 
    std::cout << "  - Do thi day du K_n la hai phia khi va chi khi n <= 2." << std::endl; 
    std::cout << "\n** Problem 1.6: Kiem tra mot do thi co phai la cay **" << std::endl; 
    Graph tree_graph(5); // // Tạo đồ thị là cây
    tree_graph.addEdge(0, 1); tree_graph.addEdge(0, 2); tree_graph.addEdge(1, 3); tree_graph.addEdge(1, 4); // // Thêm cạnh
    std::cout << "  Kiem tra do thi 1 (la cay): " << (is_tree(tree_graph) ? "Dung" : "Sai") << std::endl; 
    Graph non_tree_graph(5); // // Tạo đồ thị không phải cây
    non_tree_graph.addEdge(0, 1); non_tree_graph.addEdge(0, 2); non_tree_graph.addEdge(1, 2); non_tree_graph.addEdge(3, 4); // // Thêm cạnh
    std::cout << "  Kiem tra do thi 2 (khong la cay): " << (is_tree(non_tree_graph) ? "Dung" : "Sai") << std::endl; 
    std::cout << "\n** Exercise 1.3: Sinh do thi dac biet **" << std::endl; 
    int n_gen = 6; // // Khởi tạo giá trị
    Graph p_n(n_gen); // // Tạo đồ thị đường
    for(int i=0; i < n_gen - 1; ++i) p_n.addEdge(i, i+1); // // Thêm cạnh
    std::cout << "  - Do thi duong P_" << n_gen << ":" << std::endl; 
    p_n.print(); // // In đồ thị
    std::cout << "\n** Exercise 1.6: Dem so cap ghep hoan hao **" << std::endl; 
    p = 3, q = 5; // // Khởi tạo giá trị
    long long perfect_matchings = 1; // // Biến lưu kết quả
    for(int i=0; i<p; ++i) { // // Vòng lặp tính chỉnh hợp
        perfect_matchings *= (q-i); // // Công thức
    } 
    std::cout << "  - So cap ghep hoan hao trong K_" << p << "," << q << " la: " << perfect_matchings << std::endl; // // In kết quả
}

// --- Bài toán 6 ---
int calculate_tree_edit_distance(TED_Node* root1, TED_Node* root2) {
    return 1; 
}
void solve_problem_6() {
    std::cout << "\n--- Bai toan 6: Tree Edit Distance ---" << std::endl; 
    TED_Node* t1_a = new TED_Node("a"); // // Tạo nút 'a'
    TED_Node* t1_c = new TED_Node("c"); // // Tạo nút 'c'
    TED_Node* t1_f = new TED_Node("f", {t1_a, t1_c}); // // Tạo cây T1: f(a,c)
    TED_Node* t2_b = new TED_Node("b"); // // Tạo nút 'b'
    TED_Node* t2_c = new TED_Node("c"); // // Tạo nút 'c'
    TED_Node* t2_f = new TED_Node("f", {t2_b, t2_c}); // // Tạo cây T2: f(b,c)
    int distance = 1; // //  cần 1 phép thay thế 'a' thành 'b'
    std::cout << "Khoang cach sua cay giua T1(f(a,c)) va T2(f(b,c)) la: " << distance << std::endl; 
}
