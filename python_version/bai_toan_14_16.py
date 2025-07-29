import heapq # Thư viện để hiện thực hàng đợi ưu tiên (priority queue)
import sys

def dijkstra(graph, start_node):

    if start_node not in graph:
        print(f"  -> Dinh bat dau {start_node} khong co trong do thi.")
        return

    # Khởi tạo khoảng cách: vô cực cho tất cả các đỉnh, 0 cho đỉnh bắt đầu
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    
    # Hàng đợi ưu tiên chứa (khoảng cách, đỉnh)
    priority_queue = [(0, start_node)]
    
    # Dictionary để lưu lại đường đi
    previous_nodes = {node: None for node in graph}

    print(f"--- Thuat toan Dijkstra (bat dau tu {start_node}) ---")
    
    while priority_queue:
        # Lấy đỉnh có khoảng cách nhỏ nhất
        current_distance, current_node = heapq.heappop(priority_queue)
        
        # Bỏ qua nếu đã tìm được đường đi ngắn hơn
        if current_distance > distances[current_node]:
            continue
            
        # Duyệt qua các đỉnh kề
        for neighbor, weight in graph.get(current_node, []):
            distance = current_distance + weight
            
            # Nếu tìm thấy đường đi mới ngắn hơn, cập nhật lại
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous_nodes[neighbor] = current_node
                heapq.heappush(priority_queue, (distance, neighbor))

    # In kết quả cuối cùng
    print("  - KET QUA CUOI CUNG:")
    for node in sorted(distances.keys()):
        # Xây dựng lại đường đi từ cuối về đầu
        path = []
        curr = node
        while curr is not None:
            path.append(str(curr))
            curr = previous_nodes[curr]
        path.reverse()
        
        dist_str = distances[node] if distances[node] != float('inf') else "INF"
        path_str = " -> ".join(path) if distances[node] != float('inf') else "Khong co duong di"
        
        print(f"    + Duong di ngan nhat toi {node}: {path_str} (Do dai: {dist_str})")


def solve_problem_14_16():

    # --- Bài toán 14: Dijkstra trên Đơn đồ thị có trọng số ---
    print("\n--- Bai toan 14: Dijkstra tren Do thi don ---")
    simple_weighted_graph = {
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
    dijkstra(simple_weighted_graph, 0)
    
    # --- Bài toán 15: Dijkstra trên Đa đồ thị ---
    # Thuật toán Dijkstra tự động chọn cạnh có trọng số nhỏ hơn.
    print("\n--- Bai toan 15: Dijkstra tren Da do thi ---")
    multi_weighted_graph = {
        0: [(1, 5), (1, 10)], # Hai cạnh từ 0 đến 1
        1: [(0, 5), (0, 10), (2, 2)],
        2: [(1, 2)]
    }
    dijkstra(multi_weighted_graph, 0)

    # --- Bài toán 16: Dijkstra trên Đồ thị tổng quát (có khuyên) ---
    # Khuyên thường không ảnh hưởng đến đường đi ngắn nhất trừ khi trọng số âm.
    print("\n--- Bai toan 16: Dijkstra tren Do thi tong quat ---")
    general_weighted_graph = {
        0: [(1, 5)],
        1: [(0, 5), (1, 10), (2, 2)], # Khuyên tại đỉnh 1
        2: [(1, 2)]
    }
    dijkstra(general_weighted_graph, 0)

# Chạy các bài toán
if __name__ == "__main__":
    solve_problem_14_16()