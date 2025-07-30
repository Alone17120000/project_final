import heapq 
import sys 

def dijkstra(graph, start_node): # Hàm thực hiện thuật toán Dijkstra.
    if start_node not in graph: # Kiểm tra nếu đỉnh bắt đầu không tồn tại.
        print(f"   -> Dinh bat dau {start_node} khong co trong do thi.") # In thông báo lỗi.
        return # Kết thúc hàm nếu đỉnh không hợp lệ.

    distances = {node: float('inf') for node in graph} # Khởi tạo khoảng cách tới các đỉnh là vô cực.
    distances[start_node] = 0 # Khoảng cách tới đỉnh bắt đầu là 0.
    
    priority_queue = [(0, start_node)] # Hàng đợi ưu tiên chứa (khoảng cách, đỉnh).
    
    previous_nodes = {node: None for node in graph} # Map lưu lại đỉnh trước đó trên đường đi ngắn nhất.

    print(f"--- Thuat toan Dijkstra (bat dau tu {start_node}) ---") # In tiêu đề thuật toán.
    
    while priority_queue: # Khi hàng đợi ưu tiên còn phần tử.
        current_distance, current_node = heapq.heappop(priority_queue) # Lấy đỉnh có khoảng cách nhỏ nhất ra khỏi hàng đợi.
        
        if current_distance > distances[current_node]: # Nếu đã có đường đi ngắn hơn được tìm thấy trước đó.
            continue # Bỏ qua và xử lý đỉnh tiếp theo.
            
        for neighbor, weight in graph.get(current_node, []): # Lặp qua các đỉnh kề của đỉnh hiện tại.
            distance = current_distance + weight # Tính khoảng cách mới qua đỉnh hiện tại.
            
            if distance < distances[neighbor]: # Nếu tìm thấy đường đi mới ngắn hơn.
                distances[neighbor] = distance # Cập nhật khoảng cách ngắn nhất.
                previous_nodes[neighbor] = current_node # Ghi nhận đỉnh cha.
                heapq.heappush(priority_queue, (distance, neighbor)) # Thêm đỉnh kề vào hàng đợi với khoảng cách mới.

    print("   - KET QUA CUOI CUNG:") # In tiêu đề kết quả.
    for node in sorted(distances.keys()): # Lặp qua các đỉnh để in kết quả.
        path = [] # Khởi tạo danh sách để lưu đường đi.
        curr = node # Bắt đầu từ đỉnh đích.
        while curr is not None: # Lần ngược về đỉnh bắt đầu.
            path.append(str(curr)) # Thêm đỉnh vào đường đi.
            curr = previous_nodes[curr] # Di chuyển đến đỉnh cha.
        path.reverse() # Đảo ngược danh sách để có đường đi đúng thứ tự.
        
        dist_str = distances[node] if distances[node] != float('inf') else "INF" # Định dạng chuỗi khoảng cách.
        path_str = " -> ".join(path) if distances[node] != float('inf') else "Khong co duong di" # Định dạng chuỗi đường đi.
        
        print(f"     + Duong di ngan nhat toi {node}: {path_str} (Do dai: {dist_str})") # In ra đường đi và độ dài.

def solve_problem_14_16(): # Hàm chính để chạy các bài toán 14, 15, 16.
    # --- Bài toán 14: Dijkstra trên Đơn đồ thị có trọng số ---
    print("\n--- Bai toan 14: Dijkstra tren Do thi don ---") # In tiêu đề bài toán 14.
    simple_weighted_graph = { # Khai báo đồ thị đơn có trọng số.
        0: [(1, 4), (7, 8)],
        1: [(0, 4), (2, 8), (7, 11)],
        2: [(1, 8), (3, 7), (5, 4), (8, 2)],
        3: [(2, 7), (4, 9), (5, 14)],
        4: [(3, 9), (5, 10)],
        5: [(2, 4), (3, 14), (4, 10), (6, 2)],
        6: [(5, 2), (7, 1), (8, 6)],
        7: [(0, 8), (1, 11), (6, 1), (8, 7)],
        8: [(2, 2), (6, 6), (7, 7)]
    }
    dijkstra(simple_weighted_graph, 0) # Chạy Dijkstra trên đồ thị đơn.
    
    # --- Bài toán 15: Dijkstra trên Đa đồ thị ---
    print("\n--- Bai toan 15: Dijkstra tren Da do thi ---") # In tiêu đề bài toán 15.
    multi_weighted_graph = { # Khai báo đa đồ thị có trọng số.
        0: [(1, 5), (1, 10)], # Hai cạnh từ 0 đến 1.
        1: [(0, 5), (0, 10), (2, 2)],
        2: [(1, 2)]
    }
    dijkstra(multi_weighted_graph, 0) # Chạy Dijkstra trên đa đồ thị.

    # --- Bài toán 16: Dijkstra trên Đồ thị tổng quát (có khuyên) ---
    print("\n--- Bai toan 16: Dijkstra tren Do thi tong quat ---") # In tiêu đề bài toán 16.
    general_weighted_graph = { # Khai báo đồ thị tổng quát có trọng số.
        0: [(1, 5)],
        1: [(0, 5), (1, 10), (2, 2)], # Khuyên tại đỉnh 1.
        2: [(1, 2)]
    }
    dijkstra(general_weighted_graph, 0) # Chạy Dijkstra trên đồ thị tổng quát.

# Chạy các bài toán
if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_14_16() # Gọi hàm chính.