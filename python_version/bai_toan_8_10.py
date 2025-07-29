# -*- coding: utf-8 -*-
from collections import deque

def bfs(graph, start_node, directed=False):

    if start_node not in graph:
        print(f"  -> Dinh bat dau {start_node} khong co trong do thi.")
        return

    # Theo dõi các đỉnh đã duyệt
    visited = {start_node}
    # Hàng đợi cho BFS, chứa các đỉnh cần duyệt
    queue = deque([start_node])
    # Lưu lại thứ tự duyệt
    traversal_order = []
    # Lưu đường đi từ đỉnh bắt đầu
    path = {start_node: [start_node]}

    print(f"  - Bat dau duyet tu dinh: {start_node}")

    while queue:
        current_node = queue.popleft()
        traversal_order.append(current_node)

        for neighbor in graph.get(current_node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
                # Ghi nhận đường đi
                path[neighbor] = path[current_node] + [neighbor]
    
    print(f"  - Thu tu duyet BFS: {traversal_order}")
    print("  - Duong di ngan nhat (theo so canh) tu dinh bat dau:")
    for node in sorted(graph.keys()):
        print(f"    + Den {node}: {' -> '.join(map(str, path.get(node, ['Khong co'])))}")


def solve_problem_8_10():

    # --- Bài toán 8: BFS trên Đơn đồ thị  ---
    print("\n--- Bai toan 8: BFS tren Do thi don (vo huong) ---")
    simple_graph = {
        0: [1, 2],
        1: [0, 3],
        2: [0],
        3: [1]
    }
    bfs(simple_graph, 0)

    # --- Bài toán 9: BFS trên Đa đồ thị  ---
    print("\n--- Bai toan 9: BFS tren Da do thi (vo huong) ---")
    multigraph = {
        0: [1, 1], # Cạnh lặp lại
        1: [0, 0, 2],
        2: [1]
    }
    bfs(multigraph, 0)

    # --- Bài toán 10: BFS trên Đồ thị tổng quát  ---
    print("\n--- Bai toan 10: BFS tren Do thi tong quat (co khuyen, vo huong) ---")
    general_graph = {
        0: [1],
        1: [0, 1, 2], # Khuyên tại đỉnh 1
        2: [1]
    }
    bfs(general_graph, 0)

    # --- Bổ sung: BFS trên Đồ thị có hướng  ---
    print("\n--- Bo sung: BFS tren Do thi co huong ---")
    directed_graph = {
        0: [1, 2],
        1: [3],
        2: [],
        3: [0] # Tạo chu trình 0 -> 1 -> 3 -> 0
    }
 

    bfs(directed_graph, 0, directed=True)

# Chạy các bài toán
if __name__ == "__main__":
    solve_problem_8_10()