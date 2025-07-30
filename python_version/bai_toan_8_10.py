from collections import deque # Nhập cấu trúc dữ liệu hàng đợi.

def bfs(graph, start_node, directed=False): # Hàm thực hiện duyệt theo chiều rộng (BFS).
    if start_node not in graph: # Kiểm tra nếu đỉnh bắt đầu không tồn tại.
        # In thông báo lỗi nếu đỉnh không tồn tại.
        print(f"   -> Dinh bat dau {start_node} khong co trong do thi.")
        return # Kết thúc hàm nếu đỉnh không hợp lệ.

    visited = {start_node} # Tập hợp lưu các đỉnh đã được duyệt để tránh lặp lại.
    queue = deque([start_node]) # Hàng đợi cho BFS, chứa các đỉnh cần duyệt.
    traversal_order = [] # Danh sách lưu lại thứ tự duyệt các đỉnh.
    path = {start_node: [start_node]} # Map lưu đường đi ngắn nhất từ đỉnh bắt đầu.

    # In thông báo bắt đầu duyệt.
    print(f"   - Bat dau duyet tu dinh: {start_node}")

    while queue: # Khi hàng đợi còn phần tử.
        current_node = queue.popleft() # Lấy đỉnh đầu hàng đợi để xử lý.
        traversal_order.append(current_node) # Thêm đỉnh vừa xử lý vào thứ tự duyệt.

        for neighbor in graph.get(current_node, []): # Lặp qua các đỉnh kề của đỉnh hiện tại.
            if neighbor not in visited: # Nếu đỉnh kề chưa được duyệt.
                visited.add(neighbor) # Đánh dấu là đã duyệt.
                queue.append(neighbor) # Thêm đỉnh kề vào cuối hàng đợi.
                path[neighbor] = path[current_node] + [neighbor] # Ghi nhận đường đi đến đỉnh kề.
    
    print(f"   - Thu tu duyet BFS: {traversal_order}") # In ra thứ tự các đỉnh đã được duyệt.
    # In tiêu đề cho phần đường đi.
    print("   - Duong di ngan nhat (theo so canh) tu dinh bat dau:")
    for node in sorted(graph.keys()): # Lặp qua tất cả các đỉnh để in đường đi.
        # In đường đi từ gốc đến đỉnh hiện tại.
        print(f"     + Den {node}: {' -> '.join(map(str, path.get(node, ['Khong co'])))}")

def solve_problem_8_10(): # Hàm chính để chạy các bài toán 8, 9, 10.
    # --- Bài toán 8: BFS trên Đơn đồ thị ---
    print("\n--- Bai toan 8: BFS tren Do thi don (vo huong) ---") # In tiêu đề bài toán 8.
    simple_graph = { # Khai báo đồ thị đơn.
        0: [1, 2],
        1: [0, 3],
        2: [0],
        3: [1]
    }
    bfs(simple_graph, 0) # Chạy BFS trên đồ thị đơn.

    # --- Bài toán 9: BFS trên Đa đồ thị ---
    print("\n--- Bai toan 9: BFS tren Da do thi (vo huong) ---") # In tiêu đề bài toán 9.
    multigraph = { # Khai báo đa đồ thị.
        0: [1, 1], # Cạnh lặp lại.
        1: [0, 0, 2],
        2: [1]
    }
    bfs(multigraph, 0) # Chạy BFS trên đa đồ thị.

    # --- Bài toán 10: BFS trên Đồ thị tổng quát ---
    # In tiêu đề bài toán 10.
    print("\n--- Bai toan 10: BFS tren Do thi tong quat (co khuyen, vo huong) ---")
    general_graph = { # Khai báo đồ thị tổng quát.
        0: [1],
        1: [0, 1, 2], # Khuyên tại đỉnh 1.
        2: [1]
    }
    bfs(general_graph, 0) # Chạy BFS trên đồ thị tổng quát.

    # --- Bổ sung: BFS trên Đồ thị có hướng ---
    print("\n--- Bo sung: BFS tren Do thi co huong ---") # In tiêu đề phần bổ sung.
    directed_graph = { # Khai báo đồ thị có hướng.
        0: [1, 2],
        1: [3],
        2: [],
        3: [0] # Tạo chu trình 0 -> 1 -> 3 -> 0.
    }
    bfs(directed_graph, 0, directed=True) # Chạy BFS trên đồ thị có hướng.

# Chạy các bài toán.
if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_8_10() # Gọi hàm chính.