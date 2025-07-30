from collections import deque # Nhập cấu trúc dữ liệu hàng đợi.
import itertools # Nhập thư viện để dùng các tổ hợp.

# Problem 1.1: Tính kích thước (số cạnh) của đồ thị
def problem_1_1(): # Hàm giải bài 1.1.
    print("\n--- Problem 1.1: Tinh so canh cua do thi ---") # In tiêu đề.
    
    def size_of_Kn(n): # Hàm tính số cạnh đồ thị hoàn chỉnh K_n.
        """Tính số cạnh của đồ thị hoàn chỉnh K_n."""
        if n < 2: return 0 # Nếu n < 2 thì không có cạnh.
        return n * (n - 1) // 2 # Áp dụng công thức tổ hợp.

    def size_of_Kpq(p, q): # Hàm tính số cạnh đồ thị hai phía K_p,q.
        """Tính số cạnh của đồ thị hai phía hoàn chỉnh K_p,q."""
        return p * q # Mỗi đỉnh bên p nối với mọi đỉnh bên q.

    n = 5 # Gán giá trị n.
    p, q = 3, 4 # Gán giá trị p, q.
    print(f"   - So canh cua K_{n}: {size_of_Kn(n)}") # In kết quả cho K_n.
    print(f"   - So canh cua K_{p},{q}: {size_of_Kpq(p, q)}") # In kết quả cho K_p,q.

# Problem 1.2: Xác định đồ thị hai phía
def problem_1_2(): # Hàm giải bài 1.2.
    print("\n--- Problem 1.2: Xac dinh do thi hai phia ---") # In tiêu đề.
    
    def is_Cn_bipartite(n): # Hàm kiểm tra C_n có hai phía không.
        """Đồ thị vòng C_n là hai phía khi và chỉ khi n chẵn."""
        return n > 0 and n % 2 == 0 # C_n hai phía khi và chỉ khi n chẵn.
        
    def is_Kn_bipartite(n): # Hàm kiểm tra K_n có hai phía không.
        """Đồ thị hoàn chỉnh K_n là hai phía khi và chỉ khi n <= 2."""
        return n > 0 and n <= 2 # K_n hai phía khi và chỉ khi n <= 2.
        
    print(f"   - C_4 la do thi hai phia: {is_Cn_bipartite(4)}") # In kết quả kiểm tra C_4.
    print(f"   - C_5 la do thi hai phia: {is_Cn_bipartite(5)}") # In kết quả kiểm tra C_5.
    print(f"   - K_2 la do thi hai phia: {is_Kn_bipartite(2)}") # In kết quả kiểm tra K_2.
    print(f"   - K_3 la do thi hai phia: {is_Kn_bipartite(3)}") # In kết quả kiểm tra K_3.

# Problem 1.3: Liệt kê cây khung
def problem_1_3(): # Hàm giải bài 1.3.
    print("\n--- Problem 1.3: Liet ke cay khung ---") # In tiêu đề.
    # Đồ thị trong Hình 1.30
    num_vertices = 7 # Gán số đỉnh.
    edges = [(0,1), (0,2), (1,3), (1,4), (2,3), (2,5), (3,4), (3,5), (4,6), (5,6)] # Khai báo danh sách cạnh của đồ thị.
    
    def find_all_spanning_trees(num_vertices, edges): # Hàm tìm tất cả cây khung.
        spanning_trees = [] # Khởi tạo danh sách chứa các cây khung.
        num_edges_in_tree = num_vertices - 1 # Cây khung có n-1 cạnh.
        
        for edge_combo in itertools.combinations(edges, num_edges_in_tree): # Thử mọi tổ hợp cạnh có thể.
            adj = {i: [] for i in range(num_vertices)} # Tạo danh sách kề cho đồ thị con.
            for u, v in edge_combo: # Lặp qua các cạnh trong tổ hợp.
                adj[u].append(v) # Thêm cạnh vào danh sách kề.
                adj[v].append(u) # Thêm cạnh vào danh sách kề (vô hướng).
            
            q = deque([0]) # Hàng đợi cho BFS.
            visited = {0} # Tập đỉnh đã thăm cho BFS.
            while q: # Bắt đầu duyệt BFS.
                u = q.popleft() # Lấy đỉnh ra khỏi hàng đợi.
                for v_neighbor in adj[u]: # Lặp qua các đỉnh kề.
                    if v_neighbor not in visited: # Nếu đỉnh kề chưa được thăm.
                        visited.add(v_neighbor) # Đánh dấu đã thăm.
                        q.append(v_neighbor) # Thêm vào hàng đợi.
            
            if len(visited) == num_vertices: # Nếu duyệt được hết các đỉnh (liên thông).
                spanning_trees.append(list(edge_combo)) # Đây là một cây khung.
        return spanning_trees # Trả về danh sách các cây khung.

    trees = find_all_spanning_trees(num_vertices, edges) # Gọi hàm tìm cây khung.
    print(f"   - Tim thay {len(trees)} cay khung cho do thi trong Hinh 1.30.") # In ra số lượng cây khung tìm thấy.
    for i, tree in enumerate(trees[:3]): # Lặp qua 3 cây đầu tiên.
        print(f"     + Cay khung {i+1}: {tree}") # In ra cây khung ví dụ.

# Problem 1.6: Kiểm tra một đồ thị có phải là cây hay không
def is_tree(graph): # Hàm kiểm tra đồ thị có phải là cây không.
    num_vertices = len(graph) # Lấy số đỉnh.
    if num_vertices == 0: # Nếu đồ thị rỗng.
        return True # Coi là một cây.
        
    visited = set() # Khởi tạo tập đỉnh đã thăm.
    queue = deque([next(iter(graph))]) # Khởi tạo hàng đợi BFS với một đỉnh bất kỳ.
    visited.add(next(iter(graph))) # Thêm đỉnh bắt đầu vào tập đã thăm.
    
    while queue: # Bắt đầu duyệt BFS để kiểm tra liên thông.
        node = queue.popleft() # Lấy đỉnh ra khỏi hàng đợi.
        for neighbor in graph[node]: # Lặp qua các đỉnh kề.
            if neighbor not in visited: # Nếu chưa thăm.
                visited.add(neighbor) # Đánh dấu đã thăm.
                queue.append(neighbor) # Thêm vào hàng đợi.
                
    if len(visited) != num_vertices: # Nếu số đỉnh thăm được khác tổng số đỉnh.
        return False # Đồ thị không liên thông.
        
    edge_count = 0 # Khởi tạo biến đếm cạnh.
    for u in graph: # Lặp qua các đỉnh.
        edge_count += len(graph[u]) # Cộng bậc của đỉnh vào tổng.
    
    if edge_count // 2 != num_vertices - 1: # Tổng bậc / 2 (số cạnh) phải bằng n-1.
        return False # Sai số cạnh, không phải là cây.
        
    return True # Thỏa mãn các điều kiện, là một cây.

def problem_1_6(): # Hàm giải bài 1.6.
    print("\n--- Problem 1.6: Kiem tra mot do thi co phai la cay ---") # In tiêu đề.
    tree_graph = {0: [1, 2], 1: [0, 3, 4], 2: [0], 3: [1], 4: [1]} # Khai báo đồ thị là cây.
    non_tree_graph = {0: [1, 2], 1: [0, 2], 2: [0, 1]} # Khai báo đồ thị không phải cây (có chu trình).
    
    print(f"   - Do thi 1 co phai la cay? -> {is_tree(tree_graph)}") # In kết quả kiểm tra đồ thị 1.
    print(f"   - Do thi 2 co phai la cay? -> {is_tree(non_tree_graph)}") # In kết quả kiểm tra đồ thị 2.
    
# Exercise 1.7: Sinh cây nhị phân hoàn chỉnh
def exercise_1_7(): # Hàm giải bài tập 1.7.
    print("\n--- Exercise 1.7: Sinh cay nhi phan hoan chinh ---") # In tiêu đề.
    
    def generate_complete_binary_tree(n_nodes): # Hàm sinh cây nhị phân hoàn chỉnh.
        if n_nodes <= 0: # Nếu số đỉnh không hợp lệ.
            return {} # Trả về đồ thị rỗng.
        adj_list = {i: [] for i in range(n_nodes)} # Khởi tạo danh sách kề.
        for i in range(n_nodes): # Lặp qua các đỉnh (để làm đỉnh cha).
            left = 2 * i + 1 # Tính chỉ số con trái.
            right = 2 * i + 2 # Tính chỉ số con phải.
            if left < n_nodes: # Nếu con trái tồn tại.
                adj_list[i].append(left) # Thêm cạnh (cha, con trái).
                adj_list[left].append(i) # Thêm cạnh ngược lại.
            if right < n_nodes: # Nếu con phải tồn tại.
                adj_list[i].append(right) # Thêm cạnh (cha, con phải).
                adj_list[right].append(i) # Thêm cạnh ngược lại.
        return adj_list # Trả về cây.

    n_nodes = 7 # Gán số đỉnh.
    tree = generate_complete_binary_tree(n_nodes) # Gọi hàm sinh cây.
    print(f"   - Cay nhi phan hoan chinh voi {n_nodes} dinh:") # In tiêu đề kết quả.
    for node, neighbors in sorted(tree.items()): # Lặp qua các đỉnh và in.
        print(f"     {node}: {neighbors}") # In đỉnh và các đỉnh kề của nó.

def solve_problem_5(): 
    """Hàm tổng hợp để chạy các lời giải cho Bài toán 5."""
    print("=====================================================") 
    print("                 BAI TOAN 5") 
    print("=====================================================") 
    
    problem_1_1() 
    problem_1_2() 
    problem_1_3()
    problem_1_6() 
    exercise_1_7() 

if __name__ == "__main__": 
    solve_problem_5()