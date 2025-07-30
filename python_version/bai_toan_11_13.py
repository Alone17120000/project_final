def dfs(graph, start_node, directed=False): # Hàm thực hiện duyệt theo chiều sâu (DFS).
    if start_node not in graph: # Kiểm tra nếu đỉnh bắt đầu không tồn tại.
        print(f"   -> Dinh bat dau {start_node} khong co trong do thi.") # In thông báo lỗi.
        return # Kết thúc hàm nếu đỉnh không hợp lệ.

    visited = set() # Tập hợp lưu các đỉnh đã được duyệt.
    stack = [start_node] # Ngăn xếp cho DFS, bắt đầu với đỉnh xuất phát.
    traversal_order = [] # Danh sách lưu lại thứ tự duyệt.
    path = {node: [] for node in graph} # Map lưu đường đi từ đỉnh bắt đầu.
    prev = {start_node: None} # Map theo dõi đỉnh cha trong cây DFS.

    print(f"   - Bat dau duyet tu dinh: {start_node}") # In thông báo bắt đầu duyệt.
    
    while stack: # Khi ngăn xếp còn phần tử.
        current_node = stack.pop() # Lấy đỉnh trên cùng của ngăn xếp để xử lý.
        
        if current_node not in visited: # Nếu đỉnh này chưa được duyệt.
            visited.add(current_node) # Đánh dấu là đã duyệt.
            traversal_order.append(current_node) # Thêm vào thứ tự duyệt.
            
            # Xây dựng đường đi từ đỉnh cha.
            if prev[current_node] is None: # Nếu là đỉnh bắt đầu.
                path[current_node] = [current_node] # Đường đi là chính nó.
            else: # Nếu không phải đỉnh bắt đầu.
                path[current_node] = path[prev[current_node]] + [current_node] # Xây dựng đường đi từ đường đi của đỉnh cha.

            # Lấy danh sách đỉnh kề, sắp xếp ngược để duyệt từ trái sang phải.
            neighbors = sorted(list(set(graph.get(current_node, []))), reverse=True)
            for neighbor in neighbors: # Lặp qua các đỉnh kề.
                if neighbor not in visited: # Nếu đỉnh kề chưa được duyệt.
                    stack.append(neighbor) # Thêm đỉnh kề vào ngăn xếp.
                    prev[neighbor] = current_node # Ghi nhận đỉnh cha.

    print(f"   - Thu tu duyet DFS: {traversal_order}") # In ra thứ tự các đỉnh đã được duyệt.
    print("   - Duong di tim thay tu dinh bat dau:") # In tiêu đề cho phần đường đi.
    for node in sorted(graph.keys()): # Lặp qua tất cả các đỉnh để in đường đi.
        print(f"     + Den {node}: {' -> '.join(map(str, path.get(node, ['Khong co'])))}") # In đường đi từ gốc đến đỉnh hiện tại.

def solve_problem_11_13(): # Hàm chính để chạy các bài toán 11, 12, 13.
    # --- Bài toán 11: DFS trên Đơn đồ thị (vô hướng) ---
    print("\n--- Bai toan 11: DFS tren Do thi don (vo huong) ---") # In tiêu đề bài toán 11.
    simple_graph = { # Khai báo đồ thị đơn.
        0: [1, 2],
        1: [0, 3],
        2: [0],
        3: [1]
    }
    dfs(simple_graph, 0) # Chạy DFS trên đồ thị đơn.

    # --- Bài toán 12: DFS trên Đa đồ thị (vô hướng) ---
    print("\n--- Bai toan 12: DFS tren Da do thi (vo huong) ---") # In tiêu đề bài toán 12.
    multigraph = { # Khai báo đa đồ thị.
        0: [1, 1],
        1: [0, 0, 2],
        2: [1]
    }
    dfs(multigraph, 0) # Chạy DFS trên đa đồ thị.

    # --- Bài toán 13: DFS trên Đồ thị tổng quát (có khuyên, vô hướng) ---
    print("\n--- Bai toan 13: DFS tren Do thi tong quat (co khuyen, vo huong) ---") # In tiêu đề bài toán 13.
    general_graph = { # Khai báo đồ thị tổng quát.
        0: [1],
        1: [0, 1, 2], # Khuyên tại đỉnh 1.
        2: [1]
    }
    dfs(general_graph, 0) # Chạy DFS trên đồ thị tổng quát.

    # --- Bổ sung: DFS trên Đồ thị có hướng ---
    print("\n--- Bo sung: DFS tren Do thi co huong ---") # In tiêu đề phần bổ sung.
    directed_graph = { # Khai báo đồ thị có hướng.
        0: [1, 2],
        1: [2],
        2: [0, 3],
        3: [3] # Khuyên tại đỉnh 3.
    }
    dfs(directed_graph, 2, directed=True) # Chạy DFS trên đồ thị có hướng.

# Chạy các bài toán
if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_11_13() # Gọi hàm chính.