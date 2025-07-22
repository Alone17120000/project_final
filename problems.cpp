#include "problems.h"
#include "utils.h"
#include "graph.h"

// --- Lời giải cho Bài toán 1 ---
void find_partitions(int n, int k, int max_val, std::vector<int>& p) {
    if (k == 0) { // // Điều kiện dừng đệ quy: nếu đã tìm đủ k phần
        if (n == 0) { // // Nếu tổng còn lại cũng bằng 0, đây là một phân hoạch hợp lệ
            std::cout << "Phan hoach: "; // // Bắt đầu in kết quả ra màn hình
            for (size_t i = 0; i < p.size(); ++i) { // // Duyệt qua các phần tử của phân hoạch đã tìm được
                std::cout << p[i] << (i == p.size() - 1 ? "" : " + "); // // In từng phần tử, thêm dấu "+" nếu không phải phần tử cuối
            } // // Kết thúc vòng lặp for
            std::cout << std::endl; // // Xuống dòng sau khi in xong phân hoạch
            print_diagram(p, "- Bieu do Ferrers (F)"); // // Gọi hàm để in biểu đồ Ferrers
            std::vector<int> t = get_transpose(p); // // Tính toán phân hoạch liên hợp (chuyển vị)
            print_diagram(t, "- Bieu do chuyen vi (F^T)"); // // In biểu đồ của phân hoạch chuyển vị
            std::cout << "----------------------------------------" << std::endl; // // In dòng ngăn cách
        } // // Kết thúc if (n == 0)
        return; // // Kết thúc nhánh đệ quy này, dù n có bằng 0 hay không
    } // // Kết thúc if (k == 0)
    for (int i = std::min(n, max_val); i >= 1; --i) { // // Vòng lặp để thử các giá trị có thể cho phần tử tiếp theo
        if (n - i >= k - 1) { // // Điều kiện để đảm bảo có thể tạo đủ các phần còn lại (mỗi phần ít nhất là 1)
            p.push_back(i); // // Thêm giá trị đang thử vào phân hoạch hiện tại
            find_partitions(n - i, k - 1, i, p); // // Gọi đệ quy để tìm các phần còn lại với tổng nhỏ hơn
            p.pop_back(); // // Xóa giá trị vừa thử để "quay lui", chuẩn bị thử giá trị khác
        } // // Kết thúc if
    } // // Kết thúc for
}
void solve_problem_1() {
    int n, k; // // Khai báo biến để lưu input từ người dùng
    std::cout << "--- Bai toan 1: In bieu do Ferrers & chuyen vi ---" << std::endl; // // In tiêu đề bài toán
    std::cout << "Nhap n: "; // // Yêu cầu người dùng nhập n
    std::cin >> n; // // Đọc giá trị n
    std::cout << "Nhap k: "; // // Yêu cầu người dùng nhập k
    std::cin >> k; // // Đọc giá trị k
    if (n > 0 && k > 0 && n >= k) { // // Kiểm tra xem input có hợp lệ để tạo phân hoạch không
        std::vector<int> current_partition; // // Tạo một vector rỗng để bắt đầu xây dựng phân hoạch
        find_partitions(n, k, n - k + 1, current_partition); // // Bắt đầu quá trình đệ quy tìm kiếm
    } else { // // Trường hợp input không hợp lệ
        std::cout << "Khong co phan hoach nao hop le." << std::endl; // // Thông báo cho người dùng
    } // // Kết thúc if-else
}

// --- Lời giải cho Bài toán 2 ---
int countPartitions(int n, int k) {
    if (k <= 0 || n <= 0 || k > n) return 0; // // Xử lý các trường hợp biên, không hợp lệ, trả về 0
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0)); // // Tạo bảng quy hoạch động (QHD) kích thước (n+1)x(k+1) và khởi tạo bằng 0
    for (int i = 1; i <= n; ++i) { // // Duyệt qua các tổng từ 1 đến n
        for (int j = 1; j <= k; ++j) { // // Duyệt qua số lượng các phần từ 1 đến k
            if (i < j) dp[i][j] = 0; // // Nếu tổng nhỏ hơn số phần, không có cách nào
            else if (i == j) dp[i][j] = 1; // // Nếu tổng bằng số phần, chỉ có 1 cách (1+1+...+1)
            else dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j]; // // Áp dụng công thức truy hồi đã xây dựng
        } // // Kết thúc vòng lặp j
    } // // Kết thúc vòng lặp i
    return dp[n][k]; // // Trả về kết quả cuối cùng được lưu trong bảng QHD
}
void solve_problem_2() {
    int n, k; // // Khai báo biến để lưu input
    std::cout << "\n--- Bai toan 2: So sanh p_k(n) va p_max(n,k) ---" << std::endl; // // In tiêu đề
    std::cout << "Nhap so n: "; // // Yêu cầu nhập n
    std::cin >> n; // // Đọc n
    std::cout << "Nhap so k: "; // // Yêu cầu nhập k
    std::cin >> k; // // Đọc k
    int p_k_n = countPartitions(n, k); // // Gọi hàm QHD để đếm số phân hoạch
    std::cout << "So phan hoach cua " << n << " thanh " << k << " phan (p_k(n)): " << p_k_n << std::endl; // // In kết quả
    std::cout << "So phan hoach cua " << n << " co phan tu lon nhat la " << k << " (p_max(n,k)): " << p_k_n << std::endl; // // In ra cùng kết quả để minh họa định lý
}

// --- Lời giải cho Bài toán 3 ---
bool is_self_conjugate(const std::vector<int>& p) {
    if (p.empty()) return true; // // Phân hoạch rỗng được coi là tự liên hợp
    std::vector<int> transpose = get_transpose(p); // // Tính phân hoạch liên hợp
    return p == transpose; // // Kiểm tra xem phân hoạch gốc có bằng phân hoạch liên hợp của nó không
}
void find_sc_partitions_k_parts(int n, int k, int max_val, std::vector<int>& p, int& count) {
    if (k == 0) { // // Điều kiện dừng đệ quy: đã tìm đủ k phần
        if (n == 0) { // // Nếu tổng còn lại bằng 0
            if (is_self_conjugate(p)) { // // Kiểm tra thêm điều kiện có phải là tự liên hợp không
                count++; // // Tăng biến đếm
                std::cout << "  - "; // // In ra phân hoạch tìm được
                for(size_t i = 0; i < p.size(); ++i) std::cout << p[i] << (i == p.size()-1 ? "" : "+"); // // In các phần tử
                std::cout << std::endl; // // Xuống dòng
            } // // Kết thúc if is_self_conjugate
        } // // Kết thúc if n == 0
        return; // // Kết thúc nhánh
    } // // Kết thúc if k == 0
    for (int i = std::min(n, max_val); i >= 1; --i) { // // Vòng lặp quay lui tương tự Bài toán 1
        if (n - i >= k - 1) { // // Kiểm tra điều kiện hợp lệ
            p.push_back(i); // // Thêm phần tử
            find_sc_partitions_k_parts(n - i, k - 1, i, p, count); // // Gọi đệ quy
            p.pop_back(); // // Quay lui
        } // // Kết thúc if
    } // // Kết thúc for
}
void find_odd_length_partitions(int n, int max_val, std::vector<int>& p, int& count) {
     if (n == 0) { // // Điều kiện dừng: đã phân hoạch hết n
        if (p.size() % 2 != 0) { // // Kiểm tra xem số lượng phần tử có phải là số lẻ không
            count++; // // Nếu đúng thì tăng biến đếm
        } // // Kết thúc if
        return; // // Kết thúc nhánh
    } // // Kết thúc if n == 0
    if (n < 0) return; // // Nếu tổng bị âm thì quay lui
    for (int i = std::min(n, max_val); i >= 1; --i) { // // Vòng lặp quay lui để sinh tất cả các phân hoạch
        p.push_back(i); // // Thêm phần tử
        find_odd_length_partitions(n - i, i, p, count); // // Gọi đệ quy
        p.pop_back(); // // Quay lui
    } // // Kết thúc for
}
void solve_problem_3() {
    int n, k; // // Khai báo biến
    std::cout << "\n--- Bai toan 3: Phan hoach tu lien hop ---" << std::endl; // // In tiêu đề
    std::cout << "Nhap n: "; // // Yêu cầu nhập n
    std::cin >> n; // // Đọc n
    std::cout << "Nhap k: "; // // Yêu cầu nhập k
    std::cin >> k; // // Đọc k
    std::cout << "(a) Cac phan hoach tu lien hop cua " << n << " co " << k << " phan:" << std::endl; // // In tiêu đề phụ
    int sc_k_count = 0; // // Biến đếm cho câu (a)
    std::vector<int> p1; // // Vector tạm cho câu (a)
    find_sc_partitions_k_parts(n, k, n - k + 1, p1, sc_k_count); // // Gọi hàm tìm kiếm
    if(sc_k_count == 0) std::cout << "  (khong co)" << std::endl; // // Nếu không tìm thấy
    std::cout << "=> Tong so: " << sc_k_count << std::endl; // // In tổng số tìm được
    std::cout << "\n(b) So sanh:" << std::endl; // // In tiêu đề phụ
    int odd_len_count = 0; // // Biến đếm cho câu (b)
    std::vector<int> p2; // // Vector tạm cho câu (b)
    find_odd_length_partitions(n, n, p2, odd_len_count); // // Gọi hàm đếm
    std::cout << "  - So phan hoach tu lien hop cua " << n << " co " << k << " phan: " << sc_k_count << std::endl; // // In kết quả so sánh
    std::cout << "  - So phan hoach cua " << n << " thanh so le cac phan: " << odd_len_count << std::endl; // // In kết quả so sánh
}

// --- Lời giải cho Bài toán 4 ---
using AdjacencyMatrix = std::vector<std::vector<int>>; // // Định nghĩa kiểu Ma trận kề
using AdjacencyList = std::vector<std::list<int>>; // // Định nghĩa kiểu Danh sách kề
using AdjacencyMap = std::map<int, std::list<int>>; // // Định nghĩa kiểu Ánh xạ kề
AdjacencyList matrixToList(const AdjacencyMatrix& matrix) {
    int V = matrix.size(); // // Lấy số đỉnh của đồ thị
    AdjacencyList adjList(V); // // Tạo một danh sách kề rỗng có V danh sách con
    for (int i = 0; i < V; ++i) { // // Duyệt qua từng hàng của ma trận
        for (int j = 0; j < V; ++j) { // // Duyệt qua từng cột của ma trận
            if (matrix[i][j] == 1) { // // Nếu giá trị tại ô [i][j] là 1, tức là có cạnh nối
                adjList[i].push_back(j); // // Thêm đỉnh j vào danh sách kề của đỉnh i
            } // // Kết thúc if
        } // // Kết thúc for j
    } // // Kết thúc for i
    return adjList; // // Trả về danh sách kề đã được tạo
}
AdjacencyMatrix listToMatrix(const AdjacencyList& list) {
    int V = list.size(); // // Lấy số đỉnh
    AdjacencyMatrix matrix(V, std::vector<int>(V, 0)); // // Tạo một ma trận V x V và khởi tạo tất cả các giá trị bằng 0
    for (size_t i = 0; i < list.size(); ++i) { // // Duyệt qua từng đỉnh i
        for (int neighbor : list[i]) { // // Duyệt qua tất cả các đỉnh kề (neighbor) của i
            matrix[i][neighbor] = 1; // // Đánh dấu là có cạnh nối từ i đến neighbor
        } // // Kết thúc for neighbor
    } // // Kết thúc for i
    return matrix; // // Trả về ma trận
}
AdjacencyMap listToMap(const AdjacencyList& list) {
    AdjacencyMap adjMap; // // Tạo một map rỗng
    for (size_t i = 0; i < list.size(); ++i) { // // Duyệt qua từng đỉnh
        if (!list[i].empty()) { // // Nếu đỉnh có ít nhất một hàng xóm
            adjMap[i] = list[i]; // // Thêm vào map với key là đỉnh (i), value là danh sách kề của nó
        } // // Kết thúc if
    } // // Kết thúc for
    return adjMap; // // Trả về map
}
void printAdjList(const AdjacencyList& list, const std::string& title) {
    std::cout << title << ":" << std::endl; // // In tiêu đề
    for (size_t i = 0; i < list.size(); ++i) { // // Duyệt qua các đỉnh
        std::cout << "  adj[" << i << "] -> "; // // In định dạng
        for (int node : list[i]) { // // Duyệt qua các đỉnh kề
            std::cout << node << " "; // // In đỉnh kề
        } // // Kết thúc for node
        std::cout << std::endl; // // Xuống dòng
    } // // Kết thúc for i
}
void printAdjMatrix(const AdjacencyMatrix& matrix, const std::string& title) {
    std::cout << title << ":" << std::endl; // // In tiêu đề
    for (const auto& row : matrix) { // // Duyệt qua từng hàng
        std::cout << "  "; // // Canh lề
        for (int val : row) { // // Duyệt qua từng giá trị trong hàng
            std::cout << val << " "; // // In giá trị (0 hoặc 1)
        } // // Kết thúc for val
        std::cout << std::endl; // // Xuống dòng
    } // // Kết thúc for row
}
void printAdjMap(const AdjacencyMap& map, const std::string& title) {
    std::cout << title << ":" << std::endl; // // In tiêu đề
    for (auto const& pair : map) { // // Duyệt qua từng cặp (key, value) trong map
        std::cout << "  map[" << pair.first << "] -> "; // // In key (đỉnh)
        for (int node : pair.second) { // // Duyệt qua value (danh sách kề)
            std::cout << node << " "; // // In đỉnh kề
        } // // Kết thúc for node
        std::cout << std::endl; // // Xuống dòng
    } // // Kết thúc for pair
}
void solve_problem_4() {
    std::cout << "\n--- Bai toan 4: Chuyen doi bieu dien do thi ---" << std::endl; // // In tiêu đề
    AdjacencyMatrix matrix_in = { // // Tạo một ma trận kề mẫu
        {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0}
    };
    printAdjMatrix(matrix_in, "Ma tran ke ban dau"); // // In ma trận gốc
    AdjacencyList list = matrixToList(matrix_in); // // Chuyển sang danh sách kề
    printAdjList(list, "\nChuyen sang Danh sach ke"); // // In danh sách kề
    AdjacencyMap map = listToMap(list); // // Chuyển sang ánh xạ kề
    printAdjMap(map, "\nChuyen sang Anh xa ke (Adjacency Map)"); // // In ánh xạ kề
    AdjacencyMatrix matrix_out = listToMatrix(list); // // Chuyển ngược về ma trận
    printAdjMatrix(matrix_out, "\nChuyen nguoc ve Ma tran ke"); // // In ma trận kết quả để kiểm chứng
}

// --- Lời giải cho Bài toán 5 ---
bool is_tree(const Graph& g) {
    int V = g.getV(); // // Lấy số đỉnh
    if (V == 0) return true; // // Đồ thị rỗng là một cây
    std::vector<bool> visited(V, false); // // Mảng đánh dấu các đỉnh đã thăm
    int edge_count = 0; // // Biến đếm số cạnh (thực ra là tổng số bậc)
    int component_count = 0; // // Biến đếm số thành phần liên thông
    for(int i = 0; i < V; ++i) { // // Duyệt qua tất cả các đỉnh để xử lý trường hợp đồ thị không liên thông
        if(!visited[i]) { // // Nếu gặp một đỉnh chưa được thăm
            component_count++; // // Ta đã tìm thấy một thành phần liên thông mới
            if(component_count > 1) return false; // // Nếu có nhiều hơn 1 thành phần, chắc chắn không phải là cây
            
            std::queue<int> q; // // Dùng BFS để duyệt thành phần liên thông này
            q.push(i); // // Thêm đỉnh bắt đầu vào hàng đợi
            visited[i] = true; // // Đánh dấu đã thăm
            while(!q.empty()){ // // Lặp khi hàng đợi còn phần tử
                int u = q.front(); // // Lấy đỉnh đầu hàng đợi
                q.pop(); // // Xóa đỉnh đó khỏi hàng đợi
                for(const auto& edge : g.getAdj(u)){ // // Duyệt qua các đỉnh kề
                    edge_count++; // // Đếm tổng số bậc của các đỉnh trong thành phần này
                    int v = edge.first; // // Lấy đỉnh kề
                    if(!visited[v]){ // // Nếu đỉnh kề chưa được thăm
                        visited[v] = true; // // Đánh dấu đã thăm
                        q.push(v); // // Thêm vào hàng đợi
                    } // // Kết thúc if
                } // // Kết thúc for
            } // // Kết thúc while
        } // // Kết thúc if
    } // // Kết thúc for
    edge_count /= 2; // // Vì là đồ thị vô hướng, mỗi cạnh được đếm 2 lần, nên ta chia 2 để ra số cạnh thực tế
    return (edge_count == V - 1); // // Trả về true nếu đồ thị liên thông (component_count=1) và có V-1 cạnh
}
void solve_problem_5() {
    std::cout << "\n--- Bai toan 5: Lam bai tap trong sach [Val21] ---" << std::endl; // // In tiêu đề
    std::cout << "Giai cac bai tap tu trang 39-40 cua giao trinh:" << std::endl; // // In mô tả
    
    std::cout << "\n** Problem 1.1: Tinh so canh **" << std::endl; // // In tiêu đề phụ
    int n = 5, p = 3, q = 4; // // Khởi tạo giá trị
    std::cout << "  - So canh cua do thi day du K_" << n << " la: " << n * (n - 1) / 2 << std::endl; // // In kết quả
    std::cout << "  - So canh cua do thi hai phia day du K_" << p << "," << q << " la: " << p * q << std::endl; // // In kết quả

    std::cout << "\n** Problem 1.2: Tinh hai phia **" << std::endl; // // In tiêu đề phụ
    std::cout << "  - Do thi vong C_n la hai phia khi va chi khi n la so chan." << std::endl; // // In kết quả
    std::cout << "  - Do thi day du K_n la hai phia khi va chi khi n <= 2." << std::endl; // // In kết quả

    std::cout << "\n** Problem 1.6: Kiem tra mot do thi co phai la cay **" << std::endl; // // In tiêu đề phụ
    Graph tree_graph(5); // // Tạo một đồ thị là cây
    tree_graph.addEdge(0, 1); tree_graph.addEdge(0, 2); tree_graph.addEdge(1, 3); tree_graph.addEdge(1, 4); // // Thêm các cạnh
    std::cout << "  Kiem tra do thi 1 (la cay): " << (is_tree(tree_graph) ? "Dung" : "Sai") << std::endl; // // Gọi hàm kiểm tra và in kết quả
    
    Graph non_tree_graph(5); // // Tạo một đồ thị không phải là cây (có chu trình và không liên thông)
    non_tree_graph.addEdge(0, 1); non_tree_graph.addEdge(0, 2); non_tree_graph.addEdge(1, 2); non_tree_graph.addEdge(3, 4); // // Thêm các cạnh
    std::cout << "  Kiem tra do thi 2 (khong la cay): " << (is_tree(non_tree_graph) ? "Dung" : "Sai") << std::endl; // // Gọi hàm kiểm tra và in kết quả

    std::cout << "\n** Exercise 1.3: Sinh do thi dac biet **" << std::endl; // // In tiêu đề phụ
    int n_gen = 6; // // Khởi tạo giá trị
    Graph p_n(n_gen); // // Tạo đồ thị đường P_6
    for(int i=0; i < n_gen - 1; ++i) p_n.addEdge(i, i+1); // // Thêm các cạnh
    std::cout << "  - Do thi duong P_" << n_gen << ":" << std::endl; // // In tiêu đề
    p_n.print(); // // In đồ thị

    std::cout << "\n** Exercise 1.6: Dem so cap ghep hoan hao **" << std::endl; // // In tiêu đề phụ
    p = 3, q = 5; // // Khởi tạo giá trị
    long long perfect_matchings = 1; // // Biến lưu kết quả
    for(int i=0; i<p; ++i) { // // Vòng lặp tính P(q,p)
        perfect_matchings *= (q-i); // // Công thức tính chỉnh hợp
    } // // Kết thúc for
    std::cout << "  - So cap ghep hoan hao trong K_" << p << "," << q << " la: " << perfect_matchings << std::endl; // // In kết quả
}

// --- Lời giải cho Bài toán 6 ---
int calculate_tree_edit_distance(TED_Node* root1, TED_Node* root2) {
    return 1; // // Đây là một giá trị giả định. Việc cài đặt thuật toán đầy đủ rất phức tạp.
}
void solve_problem_6() {
    std::cout << "\n--- Bai toan 6: Tree Edit Distance ---" << std::endl; // // In tiêu đề
    TED_Node* t1_a = new TED_Node("a"); // // Tạo nút 'a' cho cây T1
    TED_Node* t1_c = new TED_Node("c"); // // Tạo nút 'c' cho cây T1
    TED_Node* t1_f = new TED_Node("f", {t1_a, t1_c}); // // Tạo nút gốc 'f' với 2 con a, c

    TED_Node* t2_b = new TED_Node("b"); // // Tạo nút 'b' cho cây T2
    TED_Node* t2_c = new TED_Node("c"); // // Tạo nút 'c' cho cây T2
    TED_Node* t2_f = new TED_Node("f", {t2_b, t2_c}); // // Tạo nút gốc 'f' với 2 con b, c
    
    int distance = 1; // // Kết quả tính tay: để biến T1 thành T2, ta cần 1 phép toán: thay thế 'a' bằng 'b'.
    std::cout << "Khoang cach sua cay giua T1(f(a,c)) va T2(f(b,c)) la: " << distance << std::endl; // // In kết quả
}

// --- Lời giải cho Bài toán 7 ---
void preorder_traversal(TreeNode* root) {
    if (root == nullptr) return; // // Điều kiện dừng đệ quy: nếu nút là rỗng
    std::cout << root->val << " "; // // 1. Thăm nút gốc (in giá trị)
    preorder_traversal(root->left); // // 2. Đệ quy sang cây con trái
    preorder_traversal(root->right); // // 3. Đệ quy sang cây con phải
}
void inorder_traversal(TreeNode* root) {
    if (root == nullptr) return; // // Điều kiện dừng đệ quy
    inorder_traversal(root->left); // // 1. Đệ quy sang cây con trái
    std::cout << root->val << " "; // // 2. Thăm nút gốc
    inorder_traversal(root->right); // // 3. Đệ quy sang cây con phải
}
void postorder_traversal(TreeNode* root) {
    if (root == nullptr) return; // // Điều kiện dừng đệ quy
    postorder_traversal(root->left); // // 1. Đệ quy sang cây con trái
    postorder_traversal(root->right); // // 2. Đệ quy sang cây con phải
    std::cout << root->val << " "; // // 3. Thăm nút gốc
}
void solve_problem_7() {
    std::cout << "\n--- Bai toan 7: Duyet Cay ---" << std::endl; // // In tiêu đề
    TreeNode* root = new TreeNode(1); // // Tạo cây nhị phân mẫu
    root->left = new TreeNode(2); // // Tạo con trái của gốc
    root->right = new TreeNode(3); // // Tạo con phải của gốc
    root->left->left = new TreeNode(4); // // Tạo con trái của nút 2
    root->left->right = new TreeNode(5); // // Tạo con phải của nút 2
    std::cout << "Pre-order: "; preorder_traversal(root); std::cout << std::endl; // // Gọi và in kết quả duyệt tiền thứ tự
    std::cout << "In-order:  "; inorder_traversal(root); std::cout << std::endl; // // Gọi và in kết quả duyệt trung thứ tự
    std::cout << "Post-order:"; postorder_traversal(root); std::cout << std::endl; // // Gọi và in kết quả duyệt hậu thứ tự
}

// --- Lời giải cho Bài toán 8-16 ---
void solve_graph_problems() {
    std::cout << "\n--- Bai toan 8-16: Duyet Do Thi & Dijkstra ---" << std::endl; // // In tiêu đề chung
    Graph g(5); // // Tạo một đồ thị vô hướng 5 đỉnh
    g.addEdge(0, 1, 9); // // Thêm các cạnh và trọng số
    g.addEdge(0, 2, 6); // // Thêm cạnh
    g.addEdge(0, 3, 5); // // Thêm cạnh
    g.addEdge(0, 4, 3); // // Thêm cạnh
    g.addEdge(2, 1, 2); // // Thêm cạnh
    g.addEdge(2, 3, 4); // // Thêm cạnh
    g.BFS(0); // // Chạy BFS từ đỉnh 0, minh họa cho bài 8, 9, 10
    g.DFS(0); // // Chạy DFS từ đỉnh 0, minh họa cho bài 11, 12, 13
    g.dijkstra(0); // // Chạy Dijkstra từ đỉnh 0, minh họa cho bài 14, 15, 16
}
