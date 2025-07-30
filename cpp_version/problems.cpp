#include "problems.h"
#include "utils.h"
#include "graph.h"
#include <iterator> 
#include <map>
#include <set>
#include <memory>
#include <algorithm> 
#include <iomanip> 
// --- Bài toán 1: Phân hoạch số và Biểu đồ Ferrers ---

// Hàm đệ quy để tìm và in tất cả các phân hoạch của n thành k phần.
void find_partitions(int n, int k, int max_val, std::vector<int>& p) {
    if (k == 0) { // Điều kiện dừng: đã tìm đủ k phần.
        if (n == 0) { // Nếu tổng các phần đã chọn bằng đúng n.
            std::cout << "Phan hoach: "; // In ra tiêu đề.
            // Vòng lặp để in ra các phần tử của phân hoạch hiện tại.
            for (size_t i = 0; i < p.size(); ++i) {
                std::cout << p[i] << (i == p.size() - 1 ? "" : " + "); // In phần tử và dấu cộng.
            }
            std::cout << std::endl; // Xuống dòng.
            print_diagram(p, "- Bieu do Ferrers (F)"); // Gọi hàm in biểu đồ Ferrers.
            std::vector<int> t = get_transpose(p); // Lấy phân hoạch chuyển vị.
            print_diagram(t, "- Bieu do chuyen vi (F^T)"); // In biểu đồ của phân hoạch chuyển vị.
            std::cout << "----------------------------------------" << std::endl; // In dòng phân cách.
        }
        return; // Kết thúc nhánh đệ quy.
    }
    // Vòng lặp để chọn phần tử tiếp theo cho phân hoạch (theo thứ tự giảm dần để tránh trùng lặp).
    for (int i = std::min(n, max_val); i >= 1; --i) {
        if (n - i >= k - 1) { // Điều kiện để đảm bảo tổng còn lại có thể tạo thành k-1 phần.
            p.push_back(i); // Thêm phần tử i vào phân hoạch hiện tại.
            find_partitions(n - i, k - 1, i, p); // Gọi đệ quy để tìm các phần còn lại.
            p.pop_back(); // Quay lui: xóa phần tử i để thử các khả năng khác.
        }
    }
}

// Hàm chính để giải bài toán 1.
void solve_problem_1() {
    int n, k; // Khai báo biến n (tổng) và k (số phần tử).
    std::cout << "\n--- Bai toan 1: In bieu do Ferrers & chuyen vi ---" << std::endl; // In tiêu đề bài toán.
    std::cout << "Nhap n: "; // Yêu cầu người dùng nhập n.
    std::cin >> n; // Đọc giá trị n.
    std::cout << "Nhap k: "; // Yêu cầu người dùng nhập k.
    std::cin >> k; // Đọc giá trị k.
    if (n > 0 && k > 0 && n >= k) { // Kiểm tra điều kiện hợp lệ của n và k.
        std::vector<int> current_partition; // Tạo vector để lưu một phân hoạch đang xét.
        find_partitions(n, k, n - k + 1, current_partition); // Bắt đầu quá trình tìm kiếm phân hoạch.
    } else { // Nếu điều kiện không hợp lệ.
        std::cout << "Khong co phan hoach nao hop le." << std::endl; // Thông báo không có phân hoạch.
    }
}

// --- Bài toán 2: Chứng minh Định lý p_k(n) = p_max(n,k) ---

// Hàm đếm số phân hoạch của n thành k phần (p_k(n)) sử dụng quy hoạch động.
int countPartitions(int n, int k) {
    if (k <= 0 || n <= 0 || k > n) return 0; // Trả về 0 nếu điều kiện không hợp lệ.
    // Khởi tạo bảng quy hoạch động dp[i][j] sẽ lưu số cách phân hoạch số i thành j phần.
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
    // Lặp qua các tổng từ 1 đến n.
    for (int i = 1; i <= n; ++i) {
        // Lặp qua số phần tử từ 1 đến k.
        for (int j = 1; j <= k; ++j) {
            if (i < j) dp[i][j] = 0; // Không thể phân hoạch số nhỏ thành số phần tử lớn hơn.
            else if (i == j) dp[i][j] = 1; // Chỉ có 1 cách: 1 + 1 + ... + 1.
            // Áp dụng công thức truy hồi: p_k(n) = p_{k-1}(n-1) + p_k(n-k).
            // Trong mảng dp là: dp[i][j] = dp[i-1][j-1] + dp[i-j][j].
            else dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j];
        }
    }
    return dp[n][k]; // Trả về kết quả tại dp[n][k].
}

// Hàm đếm số phân hoạch của n có phần tử lớn nhất là k (p_max(n,k)).
int countPartitionsMax(int n, int k) {
    if (k <= 0 || n <= 0 || k > n) return 0; // Trả về 0 nếu điều kiện không hợp lệ.
    // Vấn đề tương đương với phân hoạch số (n-k) thành các phần không lớn hơn k.
    int target_sum = n - k;
    // Bảng dp[i][j] lưu số cách phân hoạch số i thành các phần không lớn hơn j.
    std::vector<std::vector<int>> dp(target_sum + 1, std::vector<int>(k + 1, 0));
    // Trường hợp cơ sở: có 1 cách phân hoạch tổng 0 (là phân hoạch rỗng).
    for (int j = 0; j <= k; ++j) {
        dp[0][j] = 1;
    }
    // Lặp qua các tổng từ 1 đến target_sum.
    for (int i = 1; i <= target_sum; ++i) {
        // Lặp qua các giá trị giới hạn của phần tử từ 1 đến k.
        for (int j = 1; j <= k; ++j) {
            // Số cách = (số cách không dùng j) + (số cách có dùng j).
            dp[i][j] = dp[i][j - 1]; // Số cách phân hoạch i với các phần tử <= j-1.
            if (i >= j) {
                dp[i][j] += dp[i - j][j]; // Thêm số cách phân hoạch (i-j) với các phần tử <= j.
            }
        }
    }
    return dp[target_sum][k]; // Trả về kết quả.
}

// Hàm chính để giải bài toán 2.
void solve_problem_2() {
    int n, k; // Khai báo biến.
    std::cout << "\n--- Bai toan 2: So sanh p_k(n) va p_max(n,k) ---" << std::endl; // In tiêu đề.
    std::cout << "Nhap so n: "; // Yêu cầu nhập n.
    std::cin >> n; // Đọc n.
    std::cout << "Nhap so k: "; // Yêu cầu nhập k.
    std::cin >> k; // Đọc k.
    int p_k_n = countPartitions(n, k); // Tính số phân hoạch của n thành k phần.
    int p_max_n_k = countPartitionsMax(n, k); // Tính số phân hoạch của n có phần tử lớn nhất là k.
    std::cout << "So phan hoach cua " << n << " thanh " << k << " phan (p_k(n)): " << p_k_n << std::endl; // In kết quả p_k(n).
    std::cout << "So phan hoach cua " << n << " co phan tu lon nhat la " << k << " (p_max(n,k)): " << p_max_n_k << std::endl; // In kết quả p_max(n,k).
    if (p_k_n == p_max_n_k) { // So sánh hai kết quả.
        std::cout << "=> Ket qua: p_k(n) = p_max(n,k). Dinh ly duoc chung minh." << std::endl; // Nếu bằng nhau, định lý đúng.
    } else { // Nếu khác nhau.
        std::cout << "=> Ket qua: p_k(n) != p_max(n,k). Co loi trong tinh toan." << std::endl; // Báo lỗi.
    }
}


// --- Bài toán 3: Phân hoạch tự liên hợp và Định lý Glaisher ---

// Hàm kiểm tra một phân hoạch có phải là tự liên hợp hay không.
bool is_self_conjugate(const std::vector<int>& p) {
    if (p.empty()) return true; // Phân hoạch rỗng là tự liên hợp.
    return p == get_transpose(p); // So sánh phân hoạch với chuyển vị của nó.
}

// Hàm tìm các phân hoạch tự liên hợp của n có k phần.
void find_sc_partitions_k_parts(int n, int k, int max_val, std::vector<int>& p, std::vector<std::vector<int>>& results) {
    if (k == 0) { // Điều kiện dừng: đã tìm đủ k phần.
        if (n == 0 && is_self_conjugate(p)) { // Nếu tổng đúng bằng n VÀ phân hoạch là tự liên hợp.
            results.push_back(p); // Thêm phân hoạch này vào danh sách kết quả.
        }
        return; // Kết thúc nhánh đệ quy.
    }
    // Vòng lặp tìm kiếm đệ quy tương tự bài 1.
    for (int i = std::min(n, max_val); i >= 1; --i) {
        if (n - i >= k - 1) {
            p.push_back(i); // Thêm phần tử.
            find_sc_partitions_k_parts(n - i, k - 1, i, p, results); // Gọi đệ quy.
            p.pop_back(); // Quay lui.
        }
    }
}

// Hàm đếm số phân hoạch của n thành các phần tử lẻ và phân biệt.
void find_odd_distinct_partitions(int n, int max_odd, std::vector<int>& p, int& count) {
    if (n == 0) { // Nếu tìm được một phân hoạch có tổng bằng n.
        count++; // Tăng bộ đếm.
        return; // Kết thúc.
    }
    if (n < 0 || max_odd < 1) return; // Nếu tổng < 0 hoặc không còn phần tử lẻ nào để thử.
    // Trường hợp 1: không chọn max_odd vào phân hoạch.
    find_odd_distinct_partitions(n, max_odd - 2, p, count);
    // Trường hợp 2: chọn max_odd vào phân hoạch.
    p.push_back(max_odd); // Thêm max_odd vào.
    find_odd_distinct_partitions(n - max_odd, max_odd - 2, p, count); // Gọi đệ quy với tổng còn lại.
    p.pop_back(); // Quay lui.
}

// Hàm chính để giải bài toán 3.
void solve_problem_3() {
    int n, k; // Khai báo biến.
    std::cout << "\n--- Bai toan 3: Phan hoach tu lien hop ---" << std::endl; // In tiêu đề.
    std::cout << "Nhap n: "; // Yêu cầu nhập n.
    std::cin >> n; // Đọc n.
    std::cout << "Nhap k: "; // Yêu cầu nhập k.
    std::cin >> k; // Đọc k.
    std::cout << "(a) Cac phan hoach tu lien hop cua " << n << " co " << k << " phan:" << std::endl; // In tiêu đề phần a.
    std::vector<std::vector<int>> sc_partitions; // Vector lưu các phân hoạch tự liên hợp tìm được.
    std::vector<int> p1; // Vector tạm để xây dựng phân hoạch.
    find_sc_partitions_k_parts(n, k, n - k + 1, p1, sc_partitions); // Bắt đầu tìm kiếm.
    if(sc_partitions.empty()) { // Nếu không tìm thấy phân hoạch nào.
        std::cout << "  (khong co)" << std::endl; // In thông báo.
    } else { // Nếu có.
        // Lặp qua và in tất cả các phân hoạch tìm được.
        for (size_t i = 0; i < sc_partitions.size(); ++i) {
            const std::vector<int>& part = sc_partitions[i];
            std::cout << "  - ";
            for(size_t j = 0; j < part.size(); ++j) std::cout << part[j] << (j == part.size()-1 ? "" : " + ");
            std::cout << std::endl;
        }
    }
    std::cout << "=> Tong so: " << sc_partitions.size() << std::endl; // In tổng số phân hoạch tìm được.
    std::cout << "\n(c) So phan hoach tu lien hop (theo dinh ly):" << std::endl; // In tiêu đề phần c.
    int odd_distinct_count = 0; // Biến đếm số phân hoạch thành các phần tử lẻ và phân biệt.
    std::vector<int> p3; // Vector tạm.
    // Xác định số lẻ lớn nhất không vượt quá n để bắt đầu tìm kiếm.
    int start_odd = (n > 0 && n % 2 == 0) ? n - 1 : n;
    // Bắt đầu đếm số phân hoạch thành các phần tử lẻ và phân biệt.
    find_odd_distinct_partitions(n, start_odd, p3, odd_distinct_count);
    std::cout << "  So phan hoach cua " << n << " thanh cac phan tu le va phan biet la: " << odd_distinct_count << std::endl;
    std::cout << "=> So luong phan hoach tu lien hop cua " << n << " la: " << odd_distinct_count << std::endl;
}


// --- Bài toán 4: Chuyển đổi các biểu diễn đồ thị và cây ---
void solve_problem_4() {
    std::cout << "\n--- Bai toan 4: Chuyen doi bieu dien do thi va cay ---" << std::endl;
    std::cout << "\n--- I. DO THI (12 converters) ---" << std::endl;
    // Khởi tạo các ma trận kề cho các loại đồ thị khác nhau.
    AdjacencyMatrix am_simple = { {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0} }; // Đơn đồ thị
    AdjacencyMatrix am_multi = { {0, 2, 0}, {2, 0, 1}, {0, 1, 0} }; // Đa đồ thị
    AdjacencyMatrix am_general = { {0, 1, 0}, {1, 1, 1}, {0, 1, 0} }; // Đồ thị tổng quát (có khuyên)

    std::cout << "\n** Truong hop 1: Don do thi **" << std::endl;
    print_am(am_simple, "Dau vao (Ma tran ke):"); // In ma trận đầu vào.
    AdjacencyList al_s = am_to_al(am_simple); // Chuyển từ Ma trận kề (AM) sang Danh sách kề (AL).
    print_al(al_s, "\n-> AM sang AL:"); // In kết quả.
    ExtendedAdjacencyList eal_s = am_to_eal(am_simple); // Chuyển từ AM sang Danh sách kề mở rộng (EAL).
    print_eal(eal_s, "\n-> AM sang EAL:");
    AdjacencyMap amap_s = am_to_amap(am_simple); // Chuyển từ AM sang Ánh xạ kề (AMap).
    print_amap(amap_s, "\n-> AM sang AMap:");
    print_am(al_to_am(al_s), "\n-> (Kiem tra) AL sang AM:"); // Chuyển ngược lại để kiểm tra.

    std::cout << "\n\n** Truong hop 2: Da do thi **" << std::endl;
    print_am(am_multi, "Dau vao (Ma tran ke):");
    ExtendedAdjacencyList eal_m = am_to_eal(am_multi); // AM -> EAL.
    print_eal(eal_m, "\n-> AM sang EAL:");
    print_al(eal_to_al(eal_m), "\n-> (Kiem tra) EAL sang AL:"); // EAL -> AL (kiểm tra).

    std::cout << "\n\n** Truong hop 3: Do thi tong quat **" << std::endl;
    print_am(am_general, "Dau vao (Ma tran ke):");
    AdjacencyMap amap_g = am_to_amap(am_general); // AM -> AMap.
    print_amap(amap_g, "\n-> AM sang AMap:");
    print_am(amap_to_am(amap_g), "\n-> (Kiem tra) AMap sang AM:"); // AMap -> AM (kiểm tra).

    std::cout << "\n\n--- II. CAY (6 converters) ---" << std::endl;
    // Khởi tạo cây bằng Mảng cha (Parent Array).
    ParentArray ap_in(6);
    ap_in[0] = -1; ap_in[1] = 0; ap_in[2] = 0; ap_in[3] = 1; ap_in[4] = 1; ap_in[5] = 2;
    // Chuyển đổi mảng cha sang các biểu diễn khác.
    AdjacencyListTree al_in = ap_to_al_tree(ap_in); // Mảng cha -> Danh sách kề cây.
    FCNS fcns_in = ap_to_fcns(ap_in); // Mảng cha -> Con cả - Em kế.
    std::cout << "\n** Dau vao **" << std::endl;
    print_ap(ap_in, "Mang cha (AP):"); // In các biểu diễn ban đầu.
    print_al_tree(al_in, "Danh sach ke (AL_Tree):");
    print_fcns(fcns_in, "Con ca - Em ke (FCNS):");

    std::cout << "\n** Kiem tra chuyen doi **" << std::endl;
    // Thực hiện chuỗi chuyển đổi vòng tròn để kiểm tra tính đúng đắn.
    print_ap(fcns_to_ap(al_tree_to_fcns(ap_to_al_tree(ap_in), 0)), "-> Kiem tra (AP -> AL -> FCNS -> AP):");
    print_fcns(al_tree_to_fcns(fcns_to_al_tree(ap_to_fcns(ap_in)), 0), "-> Kiem tra (AP -> FCNS -> AL -> FCNS):");
    print_al_tree(ap_to_al_tree(al_tree_to_ap(fcns_to_al_tree(fcns_in), 0)), "-> Kiem tra (FCNS -> AL -> AP -> AL):");
}

// --- Bài toán 5: Các bài tập cơ bản về đồ thị ---
void problem_1_1() {
    std::cout << "\n--- Problem 1.1: Tinh so canh cua do thi ---" << std::endl; // Tiêu đề.
    // Hàm lambda tính số cạnh của đồ thị đầy đủ K_n. Công thức: n*(n-1)/2.
    auto size_of_Kn = [](int n) { return n < 2 ? 0 : n * (n - 1) / 2; };
    // Hàm lambda tính số cạnh của đồ thị hai phía đầy đủ K_{p,q}. Công thức: p*q.
    auto size_of_Kpq = [](int p, int q) { return p * q; };
    int n = 5, p = 3, q = 4; // Khởi tạo giá trị mẫu.
    std::cout << "  - So canh cua K_" << n << ": " << size_of_Kn(n) << std::endl; // Tính và in kết quả.
    std::cout << "  - So canh cua K_" << p << "," << q << ": " << size_of_Kpq(p, q) << std::endl;
}
void problem_1_2() {
    std::cout << "\n--- Problem 1.2: Xac dinh do thi hai phia ---" << std::endl; // Tiêu đề.
    // Đồ thị vòng C_n là hai phía khi và chỉ khi n là số chẵn.
    auto is_Cn_bipartite = [](int n) { return n > 0 && n % 2 == 0; };
    // Đồ thị đầy đủ K_n là hai phía khi và chỉ khi n <= 2.
    auto is_Kn_bipartite = [](int n) { return n > 0 && n <= 2; };
    std::cout << "  - C_4 la do thi hai phia: " << (is_Cn_bipartite(4) ? "Dung" : "Sai") << std::endl; // In kết quả kiểm tra.
    std::cout << "  - C_5 la do thi hai phia: " << (is_Cn_bipartite(5) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - K_2 la do thi hai phia: " << (is_Kn_bipartite(2) ? "Dung" : "Sai") << std::endl;
    std::cout << "  - K_3 la do thi hai phia: " << (is_Kn_bipartite(3) ? "Dung" : "Sai") << std::endl;
}
void problem_1_3() {
    std::cout << "\n--- Problem 1.3: Liet ke cay khung ---" << std::endl; // Tiêu đề.
    int num_vertices = 7; // Số đỉnh của đồ thị.
    std::vector<std::pair<int, int> > edges; // Danh sách các cạnh của đồ thị.
    // Thêm các cạnh vào đồ thị.
    edges.push_back(std::make_pair(0,1)); edges.push_back(std::make_pair(0,2)); edges.push_back(std::make_pair(1,3));
    edges.push_back(std::make_pair(1,4)); edges.push_back(std::make_pair(2,3)); edges.push_back(std::make_pair(2,5));
    edges.push_back(std::make_pair(3,4)); edges.push_back(std::make_pair(3,5)); edges.push_back(std::make_pair(4,6));
    edges.push_back(std::make_pair(5,6));
    int num_edges_in_tree = num_vertices - 1; // Số cạnh trong một cây khung = số đỉnh - 1.
    // Sử dụng hoán vị để sinh tất cả các tổ hợp chập (V-1) của các cạnh.
    std::vector<bool> v(edges.size());
    std::fill(v.begin() + num_edges_in_tree, v.end(), true);
    int count = 0; // Biến đếm số cây khung.
    // Lặp qua tất cả các hoán vị (tương đương tất cả các tổ hợp).
    do {
        std::vector<std::pair<int, int>> current_combo; // Lưu tổ hợp cạnh hiện tại.
        for (int i = 0; i < edges.size(); ++i) if (!v[i]) current_combo.push_back(edges[i]);
        Graph g(num_vertices); // Tạo một đồ thị con từ tổ hợp cạnh.
        for(size_t i = 0; i < current_combo.size(); ++i) g.addEdge(current_combo[i].first, current_combo[i].second);
        if (g.isConnected()) { // Nếu đồ thị con liên thông (và có V-1 cạnh) thì nó là một cây khung.
            count++; // Tăng bộ đếm.
        }
    } while (std::next_permutation(v.begin(), v.end())); // Sinh hoán vị tiếp theo.
    std::cout << "  - Tong so cay khung tim thay: " << count << std::endl; // In kết quả.
}

// Hàm kiểm tra một đồ thị có phải là cây hay không.
bool is_tree(Graph& g) {
    int v = g.getV(); // Lấy số đỉnh.
    if (v == 0) return true; // Đồ thị rỗng được xem là cây.
    if (!g.isConnected()) return false; // Cây phải liên thông.
    int edge_count = 0; // Biến đếm số cạnh.
    for (int i = 0; i < v; ++i) edge_count += g.getAdj(i).size(); // Tổng bậc các đỉnh.
    // Cây phải có số cạnh = số đỉnh - 1. (Tổng bậc = 2 * số cạnh).
    return (edge_count / 2 == v - 1);
}
void problem_1_6() {
    std::cout << "\n--- Problem 1.6: Kiem tra mot do thi co phai la cay ---" << std::endl; // Tiêu đề.
    // Tạo một đồ thị là cây.
    Graph tree_graph(5);
    tree_graph.addEdge(0, 1); tree_graph.addEdge(0, 2); tree_graph.addEdge(1, 3); tree_graph.addEdge(1, 4);
    // Tạo một đồ thị không phải là cây (có chu trình).
    Graph non_tree_graph(3);
    non_tree_graph.addEdge(0, 1); non_tree_graph.addEdge(1, 2); non_tree_graph.addEdge(2, 0);
    std::cout << "  - Do thi 1 co phai la cay? -> " << (is_tree(tree_graph) ? "Dung" : "Sai") << std::endl; // Kiểm tra và in kết quả.
    std::cout << "  - Do thi 2 co phai la cay? -> " << (is_tree(non_tree_graph) ? "Dung" : "Sai") << std::endl;
}
void exercise_1_7() {
    std::cout << "\n--- Exercise 1.7: Sinh cay nhi phan hoan chinh ---" << std::endl; // Tiêu đề.
    int n_nodes = 7; // Số đỉnh của cây.
    Graph g(n_nodes); // Tạo đồ thị.
    // Lặp qua các đỉnh để thêm cạnh theo quy tắc cây nhị phân hoàn chỉnh.
    for(int i = 0; i < n_nodes; ++i) {
        if (2*i + 1 < n_nodes) g.addEdge(i, 2*i + 1); // Thêm cạnh tới con trái.
        if (2*i + 2 < n_nodes) g.addEdge(i, 2*i + 2); // Thêm cạnh tới con phải.
    }
    std::cout << "  - Cay nhi phan hoan chinh voi " << n_nodes << " dinh:" << std::endl; // In thông báo.
    g.print(); // In danh sách kề của cây.
}
// Hàm chính để giải bài toán 5.
void solve_problem_5() {
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "                      BAI TOAN 5" << std::endl;
    std::cout << "=====================================================" << std::endl;
    problem_1_1(); // Gọi hàm giải bài tập 1.1.
    problem_1_2(); // Gọi hàm giải bài tập 1.2.
    problem_1_3(); // Gọi hàm giải bài tập 1.3.
    problem_1_6(); // Gọi hàm giải bài tập 1.6.
    exercise_1_7(); // Gọi hàm giải bài tập 1.7.
}

// --- Bài toán 6: Khoảng cách sửa cây (Tree Edit Distance) ---

namespace Problem6 { // Namespace để gom các biến và cấu trúc liên quan đến Bài 6.
    // Biến toàn cục cho các phương pháp, được reset mỗi lần gọi.
    std::vector<TED_Node*> postorder1, postorder2; // Lưu danh sách các nút theo thứ tự post-order.
    int min_cost_global; // Lưu chi phí nhỏ nhất tìm được (dùng cho Backtracking và Branch-&-Bound).

    // Cấu trúc để làm key cho map trong các thuật toán quy hoạch động (chưa dùng trong code này).
    struct NodeRange {
        int i1, j1, i2, j2;
        bool operator<(const NodeRange& other) const {
            if (i1 != other.i1) return i1 < other.i1;
            if (j1 != other.j1) return j1 < other.j1;
            if (i2 != other.i2) return i2 < other.i2;
            return j2 < other.j2;
        }
    };
    std::map<NodeRange, int> memo; // Bộ nhớ cho các thuật toán tối ưu (chưa dùng trong code này).
}

// --- Các hàm tiền xử lý cho Bài toán 6 ---
// Hàm duyệt cây theo thứ tự post-order và gán ID cho mỗi nút.
void postorder_traverse_and_id(TED_Node* node, std::vector<TED_Node*>& nodes) {
    if (!node) return; // Nếu nút rỗng thì dừng.
    // Duyệt đệ quy qua các con của nút hiện tại.
    for (size_t i = 0; i < node->children.size(); ++i) {
        postorder_traverse_and_id(node->children[i].get(), nodes);
    }
    node->postorder_id = nodes.size(); // Gán ID post-order cho nút hiện tại.
    nodes.push_back(node); // Thêm nút vào danh sách.
}

// Hàm tính ID của nút lá trái nhất (leftmost leaf) cho mỗi nút trong cây.
void calculate_leftmost_leaf_ids(const std::vector<TED_Node*>& nodes) {
    // Lặp qua tất cả các nút đã được duyệt post-order.
    for (size_t i = 0; i < nodes.size(); ++i) {
        TED_Node* node = nodes[i];
        if (node->children.empty()) { // Nếu là nút lá.
            node->leftmost_leaf_id = node->postorder_id; // Nút lá trái nhất của nó là chính nó.
        } else { // Nếu là nút trong.
            // Nút lá trái nhất của nó là nút lá trái nhất của con đầu tiên.
            node->leftmost_leaf_id = nodes[node->children[0]->postorder_id]->leftmost_leaf_id;
        }
    }
}

// --- (a) Giải bằng Quay lui (Backtracking) ---
// Hàm đệ quy cho thuật toán quay lui.
void backtrack_recursive(int k, int current_cost, std::map<TED_Node*, TED_Node*>& mapping, std::set<TED_Node*>& used_nodes) {
    using namespace Problem6; // Sử dụng các biến trong namespace Problem6.
    if (k == postorder1.size()) { // Nếu đã xét hết các nút của cây 1.
        // Chi phí cuối cùng = chi phí hiện tại + số nút của cây 2 chưa được ánh xạ (phép chèn).
        int final_cost = current_cost + (postorder2.size() - used_nodes.size());
        if (final_cost < min_cost_global) { // Nếu tìm thấy chi phí tốt hơn.
            min_cost_global = final_cost; // Cập nhật chi phí nhỏ nhất toàn cục.
        }
        return; // Dừng nhánh đệ quy.
    }

    TED_Node* u = postorder1[k]; // Lấy nút thứ k của cây 1.

    // Lựa chọn 1: Xóa nút u (chi phí +1).
    backtrack_recursive(k + 1, current_cost + 1, mapping, used_nodes);

    // Lựa chọn 2: Ánh xạ u sang một nút v trong cây 2.
    for (size_t i = 0; i < postorder2.size(); ++i) {
        TED_Node* v = postorder2[i]; // Lấy một nút v từ cây 2.
        if (used_nodes.find(v) == used_nodes.end()) { // Nếu v chưa được sử dụng.
            int sub_cost = (u->label == v->label) ? 0 : 1; // Chi phí thay thế: 0 nếu nhãn giống nhau, 1 nếu khác.
            mapping[u] = v; // Thực hiện ánh xạ u -> v.
            used_nodes.insert(v); // Đánh dấu v đã được sử dụng.
            backtrack_recursive(k + 1, current_cost + sub_cost, mapping, used_nodes); // Gọi đệ quy cho nút tiếp theo.
            used_nodes.erase(v); // Quay lui: bỏ đánh dấu v.
            mapping.erase(u); // Quay lui: xóa ánh xạ u -> v.
        }
    }
}
// Hàm chính để bắt đầu giải bằng quay lui.
int solve_backtracking() {
    using namespace Problem6;
    min_cost_global = postorder1.size() + postorder2.size(); // Khởi tạo chi phí min bằng giá trị lớn nhất có thể.
    std::map<TED_Node*, TED_Node*> mapping; // Map lưu các ánh xạ.
    std::set<TED_Node*> used_nodes; // Set lưu các nút của cây 2 đã được dùng.
    backtrack_recursive(0, 0, mapping, used_nodes); // Bắt đầu quá trình đệ quy.
    return min_cost_global; // Trả về chi phí nhỏ nhất tìm được.
}


// --- (b) Giải bằng Nhánh và Cận (Branch-&-Bound) ---
// Hàm đệ quy cho thuật toán Nhánh và Cận.
void branch_and_bound_recursive(int k, int current_cost, std::map<TED_Node*, TED_Node*>& mapping, std::set<TED_Node*>& used_nodes) {
    using namespace Problem6;
    if (current_cost >= min_cost_global) { // Cắt tỉa: nếu chi phí hiện tại đã tệ hơn kết quả tốt nhất đã biết.
        return; // Không cần xét tiếp nhánh này.
    }
    // Phần còn lại tương tự như Backtracking.
    if (k == postorder1.size()) {
        int final_cost = current_cost + (postorder2.size() - used_nodes.size());
        if (final_cost < min_cost_global) {
            min_cost_global = final_cost;
        }
        return;
    }

    TED_Node* u = postorder1[k];

    // Lựa chọn 1: Xóa u.
    branch_and_bound_recursive(k + 1, current_cost + 1, mapping, used_nodes);

    // Lựa chọn 2: Ánh xạ u sang v.
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
// Hàm chính để bắt đầu giải bằng Nhánh và Cận.
int solve_branch_and_bound() {
    using namespace Problem6;
    min_cost_global = postorder1.size() + postorder2.size(); // Khởi tạo chi phí min.
    std::map<TED_Node*, TED_Node*> mapping;
    std::set<TED_Node*> used_nodes;
    branch_and_bound_recursive(0, 0, mapping, used_nodes); // Bắt đầu đệ quy.
    return min_cost_global; // Trả về kết quả.
}


// --- (c) Giải bằng Chia để trị (Divide-&-Conquer) ---
// Hàm đệ quy cho thuật toán chia để trị (cơ bản, chưa tối ưu).
int solve_divide_and_conquer_recursive(int i, int j) {
    using namespace Problem6;
    if (i == -1 && j == -1) return 0; // Cả hai cây rỗng, chi phí là 0.
    if (i == -1) return j + 1; // Cây 1 rỗng, cần j+1 phép chèn.
    if (j == -1) return i + 1; // Cây 2 rỗng, cần i+1 phép xóa.

    TED_Node* u = postorder1[i]; // Lấy nút i của cây 1.
    TED_Node* v = postorder2[j]; // Lấy nút j của cây 2.
    int cost_sub = (u->label == v->label) ? 0 : 1; // Chi phí thay thế.

    // Tính chi phí cho 3 trường hợp: xóa, chèn, thay thế.
    int cost_del = solve_divide_and_conquer_recursive(i - 1, j) + 1; // Xóa u.
    int cost_ins = solve_divide_and_conquer_recursive(i, j - 1) + 1; // Chèn v.
    int cost_rep = solve_divide_and_conquer_recursive(i - 1, j - 1) + cost_sub; // Thay thế u bằng v.

    return std::min({cost_del, cost_ins, cost_rep}); // Trả về chi phí nhỏ nhất trong 3 trường hợp.
}
// Hàm chính để bắt đầu giải bằng Chia để trị.
int solve_divide_and_conquer() {
    using namespace Problem6;
    // Bắt đầu từ nút gốc của cả hai cây (nút cuối cùng trong danh sách post-order).
    return solve_divide_and_conquer_recursive(postorder1.size() - 1, postorder2.size() - 1);
}


// --- (d) Giải bằng Quy hoạch động (Dynamic Programming - Thuật toán Zhang-Shasha) ---
int solve_dynamic_programming() {
    using namespace Problem6;
    int n1 = postorder1.size(); // Số nút cây 1.
    int n2 = postorder2.size(); // Số nút cây 2.
    // Bảng fd[i][j] lưu chi phí biến đổi rừng con gồm các nút 1..i của cây 1 thành rừng con 1..j của cây 2.
    std::vector<std::vector<int>> fd(n1 + 1, std::vector<int>(n2 + 1, 0));

    // Khởi tạo hàng và cột 0: chi phí biến đổi một rừng thành rừng rỗng là số nút của nó.
    for (int i = 1; i <= n1; i++) fd[i][0] = i; // Xóa i nút.
    for (int j = 1; j <= n2; j++) fd[0][j] = j; // Chèn j nút.

    // Lặp qua tất cả các cặp rừng con (i, j).
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            TED_Node* u = postorder1[i - 1]; // Nút thứ i (chỉ số i-1).
            TED_Node* v = postorder2[j - 1]; // Nút thứ j (chỉ số j-1).
            int cost_sub = (u->label == v->label) ? 0 : 1; // Chi phí thay thế nhãn.

            // Nếu u và v là gốc của các cây (không phải rừng), dùng công thức đơn giản.
            // Điều kiện này kiểm tra xem các nút trước u/v có phải là con cháu của u/v không.
            // Chú ý: logic này có thể cần xem lại, công thức Zhang-Shasha gốc phức tạp hơn.
            // Dưới đây là triển khai theo Zhang-Shasha gốc.
            int i_lm = u->leftmost_leaf_id + 1; // ID bắt đầu từ 0, chỉ số mảng bắt đầu từ 1.
            int j_lm = v->leftmost_leaf_id + 1;
            
            int cost_del = fd[i - 1][j] + 1; // Chi phí xóa nút u.
            int cost_ins = fd[i][j - 1] + 1; // Chi phí chèn nút v.
            // Chi phí thay thế u bằng v, bao gồm chi phí sửa đổi các cây con.
            int cost_rep = fd[i_lm - 1][j_lm - 1] + (fd[i - 1][j - 1] - fd[i_lm - 1][j_lm - 1]) + cost_sub;
            
            fd[i][j] = std::min({cost_del, cost_ins, cost_rep}); // Chọn chi phí nhỏ nhất.
        }
    }
    
    // In bảng quy hoạch động ra màn hình.
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
    
    return fd[n1][n2]; // Kết quả cuối cùng nằm ở góc dưới bên phải của bảng.
}


// --- HÀM CHÍNH CHO BÀI 6 ---
void solve_problem_6() {
    std::cout << "\n--- Bai toan 6: Tree Edit Distance ---" << std::endl;
    std::cout << "So sanh T1 = f(a,c) va T2 = f(b,c)" << std::endl;
    
    // Tạo cây T1: f(a, c)
    std::unique_ptr<TED_Node> t1_f(new TED_Node("f"));
    t1_f->children.push_back(std::unique_ptr<TED_Node>(new TED_Node("a")));
    t1_f->children.push_back(std::unique_ptr<TED_Node>(new TED_Node("c")));

    // Tạo cây T2: f(b, c)
    std::unique_ptr<TED_Node> t2_f(new TED_Node("f"));
    t2_f->children.push_back(std::unique_ptr<TED_Node>(new TED_Node("b")));
    t2_f->children.push_back(std::unique_ptr<TED_Node>(new TED_Node("c")));

    // Tiền xử lý: Lấy thứ tự post-order và tính ID lá trái nhất cho cả hai cây.
    Problem6::postorder1.clear(); 
    Problem6::postorder2.clear();
    postorder_traverse_and_id(t1_f.get(), Problem6::postorder1);
    postorder_traverse_and_id(t2_f.get(), Problem6::postorder2);
    
    calculate_leftmost_leaf_ids(Problem6::postorder1);
    calculate_leftmost_leaf_ids(Problem6::postorder2);
    
    // Gọi và in kết quả cho từng phương pháp.
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


// --- Bài toán 7: Duyệt cây nhị phân ---
// Duyệt theo thứ tự Trước (Node -> Left -> Right).
void preorder_traversal(TreeNode* root) {
    if (root == NULL) return; // Nếu nút rỗng thì dừng.
    std::cout << root->val << " "; // Thăm nút gốc.
    preorder_traversal(root->left.get()); // Duyệt cây con trái.
    preorder_traversal(root->right.get()); // Duyệt cây con phải.
}
// Duyệt theo thứ tự Giữa (Left -> Node -> Right).
void inorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    inorder_traversal(root->left.get()); // Duyệt cây con trái.
    std::cout << root->val << " "; // Thăm nút gốc.
    inorder_traversal(root->right.get()); // Duyệt cây con phải.
}
// Duyệt theo thứ tự Sau (Left -> Right -> Node).
void postorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    postorder_traversal(root->left.get()); // Duyệt cây con trái.
    postorder_traversal(root->right.get()); // Duyệt cây con phải.
    std::cout << root->val << " "; // Thăm nút gốc.
}
// Duyệt theo chiều rộng (Top-down / BFS).
void top_down_traversal(TreeNode* root) {
    if (!root) return; // Nếu cây rỗng thì dừng.
    std::queue<TreeNode*> q; // Sử dụng hàng đợi để lưu các nút cần duyệt.
    q.push(root); // Bắt đầu từ nút gốc.
    while(!q.empty()){ // Khi hàng đợi còn phần tử.
        TreeNode* node = q.front(); // Lấy nút ở đầu hàng đợi.
        q.pop(); // Xóa nút khỏi hàng đợi.
        std::cout << node->val << " "; // Thăm nút.
        if(node->left) q.push(node->left.get()); // Thêm con trái vào hàng đợi (nếu có).
        if(node->right) q.push(node->right.get()); // Thêm con phải vào hàng đợi (nếu có).
    }
}
void solve_problem_7() {
    std::cout << "\n--- Bai toan 7: Duyet Cay ---" << std::endl; // Tiêu đề.
    // Xây dựng một cây nhị phân mẫu.
    std::unique_ptr<TreeNode> root(new TreeNode(1));
    root->left.reset(new TreeNode(2));
    root->right.reset(new TreeNode(3));
    root->left->left.reset(new TreeNode(4));
    root->left->right.reset(new TreeNode(5));
    
    std::cout << "Cay nhi phan mau: (Goc 1, con trai (2 -> 4,5), con phai 3)" << std::endl;
    // Gọi các hàm duyệt và in kết quả.
    std::cout << "Pre-order: "; preorder_traversal(root.get()); std::cout << std::endl;
    std::cout << "In-order:  "; inorder_traversal(root.get()); std::cout << std::endl;
    std::cout << "Post-order:"; postorder_traversal(root.get()); std::cout << std::endl;
    std::cout << "Top-down (BFS):"; top_down_traversal(root.get()); std::cout << std::endl;
}

// --- Bài toán 8-10: Duyệt đồ thị theo chiều rộng (BFS) ---
void solve_problem_8_10() {
    std::cout << "\n--- Bai toan 8: BFS tren Do thi don ---" << std::endl;
    Graph g8(4); g8.addEdge(0, 1); g8.addEdge(0, 2); g8.addEdge(1, 3); // Tạo đơn đồ thị.
    g8.analyzeGraph(); g8.BFS(0); // Phân tích và chạy BFS từ đỉnh 0.

    std::cout << "\n--- Bai toan 9: BFS tren Da do thi ---" << std::endl;
    Graph g9(3); g9.addEdge(0, 1); g9.addEdge(0, 1); g9.addEdge(1, 2); // Tạo đa đồ thị (cạnh (0,1) lặp lại).
    g9.analyzeGraph(); g9.BFS(0); // Chạy BFS.

    std::cout << "\n--- Bai toan 10: BFS tren Do thi tong quat ---" << std::endl;
    Graph g10(3); g10.addEdge(0, 1); g10.addEdge(1, 1); g10.addEdge(1, 2); // Tạo đồ thị có khuyên (cạnh (1,1)).
    g10.analyzeGraph(); g10.BFS(0); // Chạy BFS.

    std::cout << "\n--- Bo sung: BFS tren Do thi co huong ---" << std::endl;
    Graph g_dir(4, true); // Tạo đồ thị có hướng.
    g_dir.addEdge(0, 1); g_dir.addEdge(0, 2); g_dir.addEdge(1, 3); g_dir.addEdge(3, 0);
    g_dir.analyzeGraph(); g_dir.BFS(0); // Chạy BFS.
}
// --- Bài toán 11-13: Duyệt đồ thị theo chiều sâu (DFS) ---
void solve_problem_11_13() {
    std::cout << "\n--- Bai toan 11: DFS tren Do thi don ---" << std::endl;
    Graph g11(4); g11.addEdge(0, 1); g11.addEdge(0, 2); g11.addEdge(1, 3); // Tạo đơn đồ thị.
    g11.analyzeGraph(); g11.DFS(0); // Phân tích và chạy DFS từ đỉnh 0.

    std::cout << "\n--- Bai toan 12: DFS tren Da do thi ---" << std::endl;
    Graph g12(3); g12.addEdge(0, 1); g12.addEdge(0, 1); g12.addEdge(1, 2); // Tạo đa đồ thị.
    g12.analyzeGraph(); g12.DFS(0); // Chạy DFS.

    std::cout << "\n--- Bai toan 13: DFS tren Do thi tong quat ---" << std::endl;
    Graph g13(3); g13.addEdge(0, 1); g13.addEdge(1, 1); g13.addEdge(1, 2); // Tạo đồ thị có khuyên.
    g13.analyzeGraph(); g13.DFS(0); // Chạy DFS.

    std::cout << "\n--- Bo sung: DFS tren Do thi co huong ---" << std::endl;
    Graph g_dir(4, true); // Tạo đồ thị có hướng.
    g_dir.addEdge(0, 1); g_dir.addEdge(1, 2); g_dir.addEdge(2, 0); g_dir.addEdge(2, 3); g_dir.addEdge(3, 3);
    g_dir.analyzeGraph(); g_dir.DFS(2); // Chạy DFS từ đỉnh 2.
}
// --- Bài toán 14-16: Thuật toán Dijkstra ---
void solve_problem_14_16() {
    std::cout << "\n--- Bai toan 14: Dijkstra tren Do thi don ---" << std::endl;
    Graph g(9); // Tạo đồ thị có trọng số với 9 đỉnh.
    // Thêm các cạnh và trọng số tương ứng.
    g.addEdge(0, 1, 4); g.addEdge(0, 7, 8); g.addEdge(1, 2, 8); g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7); g.addEdge(2, 5, 4); g.addEdge(2, 8, 2); g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14); g.addEdge(4, 5, 10); g.addEdge(5, 6, 2); g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6); g.addEdge(7, 8, 7);
    g.analyzeGraph(); // Phân tích đồ thị.
    g.dijkstra(0); // Tìm đường đi ngắn nhất từ đỉnh 0.
    
    std::cout << "\n--- Bai toan 15: Dijkstra tren Da do thi ---" << std::endl;
    Graph g15(3); // Tạo đa đồ thị có trọng số.
    g15.addEdge(0, 1, 5); g15.addEdge(0, 1, 10); g15.addEdge(1, 2, 2);
    g15.analyzeGraph();
    g15.dijkstra(0); // Chạy Dijkstra (thường sẽ chọn cạnh có trọng số nhỏ hơn).

    std::cout << "\n--- Bai toan 16: Dijkstra tren Do thi tong quat ---" << std::endl;
    Graph g16(3); // Tạo đồ thị có khuyên và trọng số.
    g16.addEdge(0, 1, 5); g16.addEdge(1, 1, 10); g16.addEdge(1, 2, 2);
    g16.analyzeGraph();
    g16.dijkstra(0); // Chạy Dijkstra.
}