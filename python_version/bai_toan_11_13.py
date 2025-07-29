

def dfs(graph, start_node, directed=False):

    if start_node not in graph:
        print(f"  -> Dinh bat dau {start_node} khong co trong do thi.")
        return

    visited = set()
    # Dùng stack cho DFS, bắt đầu với đỉnh xuất phát
    stack = [start_node]
    # Lưu lại thứ tự duyệt
    traversal_order = []
    # Lưu đường đi từ đỉnh bắt đầu
    path = {node: [] for node in graph}
    # Dùng dictionary để theo dõi đỉnh cha trong cây DFS
    prev = {start_node: None}

    print(f"  - Bat dau duyet tu dinh: {start_node}")
    
    while stack:
        current_node = stack.pop()
        
        if current_node not in visited:
            visited.add(current_node)
            traversal_order.append(current_node)
            
            # Xây dựng đường đi
            if prev[current_node] is None:
                path[current_node] = [current_node]
            else:
                path[current_node] = path[prev[current_node]] + [current_node]

            # Thêm các đỉnh kề vào stack (theo thứ tự ngược lại để duyệt từ trái sang phải)
            # Dùng set để loại bỏ các cạnh song song trong đa đồ thị
            neighbors = sorted(list(set(graph.get(current_node, []))), reverse=True)
            for neighbor in neighbors:
                if neighbor not in visited:
                    stack.append(neighbor)
                    prev[neighbor] = current_node

    print(f"  - Thu tu duyet DFS: {traversal_order}")
    print("  - Duong di tim thay tu dinh bat dau:")
    for node in sorted(graph.keys()):
        print(f"    + Den {node}: {' -> '.join(map(str, path.get(node, ['Khong co'])))}")


def solve_problem_11_13():

    # --- Bài toán 11: DFS trên Đơn đồ thị (vô hướng) ---
    print("\n--- Bai toan 11: DFS tren Do thi don (vo huong) ---")
    simple_graph = {
        0: [1, 2],
        1: [0, 3],
        2: [0],
        3: [1]
    }
    dfs(simple_graph, 0)

    # --- Bài toán 12: DFS trên Đa đồ thị (vô hướng) ---
    print("\n--- Bai toan 12: DFS tren Da do thi (vo huong) ---")
    multigraph = {
        0: [1, 1],
        1: [0, 0, 2],
        2: [1]
    }
    dfs(multigraph, 0)

    # --- Bài toán 13: DFS trên Đồ thị tổng quát (có khuyên, vô hướng) ---
    print("\n--- Bai toan 13: DFS tren Do thi tong quat (co khuyen, vo huong) ---")
    general_graph = {
        0: [1],
        1: [0, 1, 2],
        2: [1]
    }
    dfs(general_graph, 0)

    # --- Bổ sung: DFS trên Đồ thị có hướng ---
    print("\n--- Bo sung: DFS tren Do thi co huong ---")
    directed_graph = {
        0: [1, 2],
        1: [2],
        2: [0, 3],
        3: [3]
    }
    dfs(directed_graph, 2, directed=True)

# Chạy các bài toán
if __name__ == "__main__":
    solve_problem_11_13()