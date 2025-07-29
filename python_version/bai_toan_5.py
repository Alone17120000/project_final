
from collections import deque
import itertools # Dùng cho việc liệt kê các cặp cạnh





# Problem 1.1: Tính kích thước (số cạnh) của đồ thị
def problem_1_1():
    print("\n--- Problem 1.1: Tinh so canh cua do thi ---")
    
    def size_of_Kn(n):
        """Tính số cạnh của đồ thị hoàn chỉnh K_n."""
        if n < 2: return 0
        return n * (n - 1) // 2

    def size_of_Kpq(p, q):
        """Tính số cạnh của đồ thị hai phía hoàn chỉnh K_p,q."""
        return p * q

    n = 5
    p, q = 3, 4
    print(f"  - So canh cua K_{n}: {size_of_Kn(n)}")
    print(f"  - So canh cua K_{p},{q}: {size_of_Kpq(p, q)}")

# Problem 1.2: Xác định đồ thị hai phía
def problem_1_2():
    print("\n--- Problem 1.2: Xac dinh do thi hai phia ---")
    
    def is_Cn_bipartite(n):
        """Đồ thị vòng C_n là hai phía khi và chỉ khi n chẵn."""
        return n > 0 and n % 2 == 0
        
    def is_Kn_bipartite(n):
        """Đồ thị hoàn chỉnh K_n là hai phía khi và chỉ khi n <= 2."""
        return n > 0 and n <= 2
        
    print(f"  - C_4 la do thi hai phia: {is_Cn_bipartite(4)}")
    print(f"  - C_5 la do thi hai phia: {is_Cn_bipartite(5)}")
    print(f"  - K_2 la do thi hai phia: {is_Kn_bipartite(2)}")
    print(f"  - K_3 la do thi hai phia: {is_Kn_bipartite(3)}")

# Problem 1.3: Liệt kê cây khung
def problem_1_3():
    print("\n--- Problem 1.3: Liet ke cay khung ---")
    # Đồ thị trong Hình 1.30
    num_vertices = 7
    edges = [(0,1), (0,2), (1,3), (1,4), (2,3), (2,5), (3,4), (3,5), (4,6), (5,6)]
    
    def find_all_spanning_trees(num_vertices, edges):
        spanning_trees = []
        # Một cây khung có (số đỉnh - 1) cạnh
        num_edges_in_tree = num_vertices - 1
        
        # Thử tất cả các tổ hợp cạnh có thể có
        for edge_combo in itertools.combinations(edges, num_edges_in_tree):
            # Kiểm tra tính liên thông của đồ thị con tạo bởi tổ hợp cạnh
            adj = {i: [] for i in range(num_vertices)}
            for u, v in edge_combo:
                adj[u].append(v)
                adj[v].append(u)
            
            # Dùng BFS/DFS để kiểm tra
            q = deque([0])
            visited = {0}
            while q:
                u = q.popleft()
                for v_neighbor in adj[u]:
                    if v_neighbor not in visited:
                        visited.add(v_neighbor)
                        q.append(v_neighbor)
            
            # Nếu duyệt được hết các đỉnh, đây là một cây khung
            if len(visited) == num_vertices:
                spanning_trees.append(list(edge_combo))
        return spanning_trees

    trees = find_all_spanning_trees(num_vertices, edges)
    print(f"  - Tim thay {len(trees)} cay khung cho do thi trong Hinh 1.30.")
    # In ra 3 cây khung đầu tiên làm ví dụ
    for i, tree in enumerate(trees[:3]):
        print(f"    + Cay khung {i+1}: {tree}")

# Problem 1.6: Kiểm tra một đồ thị có phải là cây hay không
def is_tree(graph):
    """
    Kiểm tra một đồ thị có phải là cây hay không.
    Logic tương tự code C++ của bạn, đã được chuyển ngữ.
    """
    num_vertices = len(graph)
    if num_vertices == 0:
        return True
        
    # 1. Kiểm tra liên thông
    visited = set()
    queue = deque([next(iter(graph))])
    visited.add(next(iter(graph)))
    
    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
                
    if len(visited) != num_vertices:
        return False # Không liên thông
        
    # 2. Kiểm tra số cạnh = số đỉnh - 1
    edge_count = 0
    for u in graph:
        edge_count += len(graph[u])
    
    # Chia 2 vì mỗi cạnh được đếm 2 lần trong đồ thị vô hướng
    if edge_count // 2 != num_vertices - 1:
        return False
        
    return True

def problem_1_6():
    print("\n--- Problem 1.6: Kiem tra mot do thi co phai la cay ---")
    tree_graph = {0: [1, 2], 1: [0, 3, 4], 2: [0], 3: [1], 4: [1]}
    non_tree_graph = {0: [1, 2], 1: [0, 2], 2: [0, 1]} # Có chu trình
    
    print(f"  - Do thi 1 co phai la cay? -> {is_tree(tree_graph)}")
    print(f"  - Do thi 2 co phai la cay? -> {is_tree(non_tree_graph)}")
    
# --- EXERCISES (1.7) ---

# Exercise 1.7: Sinh cây nhị phân hoàn chỉnh
def exercise_1_7():
    print("\n--- Exercise 1.7: Sinh cay nhi phan hoan chinh ---")
    
    def generate_complete_binary_tree(n_nodes):
        if n_nodes <= 0:
            return {}
        adj_list = {i: [] for i in range(n_nodes)}
        for i in range(n_nodes):
            left = 2 * i + 1
            right = 2 * i + 2
            if left < n_nodes:
                adj_list[i].append(left)
                adj_list[left].append(i)
            if right < n_nodes:
                adj_list[i].append(right)
                adj_list[right].append(i)
        return adj_list

    n_nodes = 7
    tree = generate_complete_binary_tree(n_nodes)
    print(f"  - Cay nhi phan hoan chinh voi {n_nodes} dinh:")
    for node, neighbors in sorted(tree.items()):
        print(f"    {node}: {neighbors}")



def solve_problem_5():
    """Hàm tổng hợp để chạy các lời giải cho Bài toán 5."""
    print("=====================================================")
    print("            BAI TOAN 5")
    print("=====================================================")
    
   
    problem_1_1()
    problem_1_2()
    problem_1_3()

    problem_1_6()
    
  
    exercise_1_7()


if __name__ == "__main__":
    solve_problem_5()