import sys # Dùng để truy cập các biến hệ thống (ít dùng trong code này).

class TED_Node: # Lớp định nghĩa cấu trúc một nút trong cây.
    def __init__(self, label, children=None): # Hàm khởi tạo một nút cây.
        self.label = label # Nhãn của nút (ví dụ: 'f', 'a').
        self.children = children if children is not None else [] # Danh sách các nút con.
        self.id = -1 # ID của nút sau khi duyệt hậu thứ tự, mặc định là -1.
        self.leftmost_leaf_id = -1 # ID của lá trái nhất trong cây con gốc tại nút này.

def _prepare_tree(root): # Hàm tiền xử lý cây: duyệt hậu thứ tự và gán ID.
    nodes_postorder = [] # Danh sách lưu các nút theo thứ tự hậu duyệt.
    
    def _postorder_traverse(node): # Hàm đệ quy duyệt hậu thứ tự (post-order).
        if not node: return # Dừng nếu nút không tồn tại.
        for child in node.children: # Duyệt các cây con trước (trái sang phải).
            _postorder_traverse(child) # Gọi đệ quy cho từng con.
        node.id = len(nodes_postorder) # Gán ID thứ tự cho nút.
        nodes_postorder.append(node) # Thêm nút vào danh sách hậu duyệt.

    _postorder_traverse(root) # Bắt đầu duyệt từ gốc.
    
    for node in nodes_postorder: # Lặp qua các nút đã duyệt để gán leftmost_leaf_id.
        if not node.children: # Nếu là nút lá.
            node.leftmost_leaf_id = node.id # Lá trái nhất là chính nó.
        else: # Nếu không phải nút lá.
            node.leftmost_leaf_id = node.children[0].leftmost_leaf_id # Lá trái nhất là của con đầu tiên.
            
    return nodes_postorder # Trả về danh sách các nút đã được xử lý.

# --- (a) Backtracking ---
def solve_backtracking(root1, root2): # Giải bằng phương pháp quay lui (vét cạn).
    postorder1, postorder2 = _prepare_tree(root1), _prepare_tree(root2) # Chuẩn bị cây và lấy danh sách hậu duyệt.
    n1, n2 = len(postorder1), len(postorder2) # Lấy số lượng nút của mỗi cây.
    min_cost = [float('inf')] # Biến lưu chi phí nhỏ nhất (dùng list để có thể thay đổi trong hàm đệ quy).

    def backtrack(mapping, cost): # Hàm đệ quy quay lui.
        if len(mapping) == n1: # Nếu đã ánh xạ tất cả các nút của cây 1.
            final_cost = cost + (n2 - len(set(mapping.values()))) # Chi phí cuối cùng = chi phí hiện tại + số nút của cây 2 chưa được ánh xạ (chèn).
            min_cost[0] = min(min_cost[0], final_cost) # Cập nhật chi phí nhỏ nhất.
            return # Dừng nhánh.

        u = postorder1[len(mapping)] # Lấy nút tiếp theo từ cây 1 để xử lý.
        
        # Lựa chọn 1: Xóa nút u.
        new_map_del = mapping.copy() # Tạo bản sao mapping cho trường hợp xóa.
        backtrack(new_map_del, cost + 1) # Đệ quy với chi phí xóa là 1.
        
        # Lựa chọn 2: Thay thế u bằng một nút v chưa được ánh xạ.
        mapped_v = set(mapping.values()) # Lấy tập các nút của cây 2 đã được ánh xạ.
        for v in postorder2: # Lặp qua tất cả các nút của cây 2.
            if v not in mapped_v: # Nếu nút v chưa được ánh xạ.
                cost_sub = 0 if u.label == v.label else 1 # Tính chi phí thay thế (0 nếu nhãn giống nhau, 1 nếu khác).
                new_map_sub = mapping.copy() # Tạo bản sao mapping cho trường hợp thay thế.
                new_map_sub[u] = v # Thực hiện ánh xạ u -> v.
                backtrack(new_map_sub, cost + cost_sub) # Đệ quy với chi phí thay thế.

    initial_map = {} # Ánh xạ ban đầu rỗng.
    backtrack(initial_map, 0) # Bắt đầu quay lui.
    
    result = min_cost[0] if min_cost[0] != float('inf') else n1 + n2 # Lấy kết quả cuối cùng.
    return result # Trả về kết quả.

# --- (b) Branch-&-Bound ---
def solve_branch_and_bound(root1, root2): # Giải bằng phương pháp Nhánh và Cận.
    postorder1, postorder2 = _prepare_tree(root1), _prepare_tree(root2) # Chuẩn bị cây.
    n1, n2 = len(postorder1), len(postorder2) # Lấy số lượng nút.
    min_cost = [float('inf')] # Biến lưu chi phí nhỏ nhất.
    
    def backtrack_bb(mapping, cost): # Hàm đệ quy quay lui có nhánh cận.
        if cost >= min_cost[0]: # Nhánh cận: nếu chi phí hiện tại đã lớn hơn hoặc bằng chi phí tối ưu đã biết.
            return # Cắt tỉa nhánh này, không cần duyệt tiếp.

        if len(mapping) == n1: # Điều kiện dừng: đã xử lý hết cây 1.
            final_cost = cost + (n2 - len(set(mapping.values()))) # Tính chi phí cuối cùng (cộng thêm các phép chèn).
            min_cost[0] = min(min_cost[0], final_cost) # Cập nhật chi phí nhỏ nhất.
            return

        u = postorder1[len(mapping)] # Lấy nút tiếp theo từ cây 1.
        
        backtrack_bb(mapping.copy(), cost + 1) # Lựa chọn 1: Xóa nút u.
        
        mapped_v = set(mapping.values()) # Lấy tập các nút đã ánh xạ ở cây 2.
        for v in postorder2: # Lựa chọn 2: Thay thế u bằng v.
            if v not in mapped_v: # Nếu v chưa được ánh xạ.
                cost_sub = 0 if u.label == v.label else 1 # Tính chi phí thay thế.
                new_map_sub = mapping.copy() # Tạo bản sao mapping.
                new_map_sub[u] = v # Thực hiện ánh xạ.
                backtrack_bb(new_map_sub, cost + cost_sub) # Đệ quy.
                
    backtrack_bb({}, 0) # Bắt đầu từ ánh xạ rỗng, chi phí 0.
    result = min_cost[0] if min_cost[0] != float('inf') else n1 + n2 # Lấy kết quả.
    return result # Trả về kết quả.

# --- (c) Divide-&-Conquer (Recursive, no memoization) ---
def solve_divide_and_conquer(root1, root2): # Giải bằng Chia để trị (đệ quy đơn thuần).
    postorder1, postorder2 = _prepare_tree(root1), _prepare_tree(root2) # Chuẩn bị cây.
    
    def d(i, j): # Hàm đệ quy tính khoảng cách giữa hai cây con (forest).
        if i < 0 and j < 0: return 0 # Cả hai cây con đều rỗng.
        if i < 0: return j + 1 # Cây 1 rỗng, cần j+1 phép chèn.
        if j < 0: return i + 1 # Cây 2 rỗng, cần i+1 phép xóa.
            
        u, v = postorder1[i], postorder2[j] # Lấy nút gốc của hai cây con đang xét.
        cost_sub = 0 if u.label == v.label else 1 # Chi phí thay thế nhãn.
        
        cost_del = d(i - 1, j) + 1 # Chi phí xóa nút u.
        cost_ins = d(i, j - 1) + 1 # Chi phí chèn nút v.
        cost_rep = d(i - 1, j - 1) + cost_sub # Chi phí thay thế u bằng v.
        
        return min(cost_del, cost_ins, cost_rep) # Trả về chi phí nhỏ nhất trong 3 lựa chọn.

    result = d(len(postorder1) - 1, len(postorder2) - 1) # Bắt đầu tính từ gốc của hai cây.
    return result # Trả về kết quả.

# --- (d) Dynamic Programming (Zhang-Shasha Algorithm) ---
def solve_dynamic_programming(root1, root2): # Giải bằng Quy hoạch động.
    postorder1, postorder2 = _prepare_tree(root1), _prepare_tree(root2) # Chuẩn bị cây.
    n1, n2 = len(postorder1), len(postorder2) # Lấy số lượng nút.
    
    fd = [[0] * (n2 + 1) for _ in range(n1 + 1)] # Bảng quy hoạch động (forest distance).
    for i in range(1, n1 + 1): fd[i][0] = i # Khởi tạo chi phí xóa (hàng đầu tiên).
    for j in range(1, n2 + 1): fd[0][j] = j # Khởi tạo chi phí chèn (cột đầu tiên).
        
    for i in range(1, n1 + 1): # Lặp qua các nút cây 1.
        for j in range(1, n2 + 1): # Lặp qua các nút cây 2.
            cost_sub = 0 if postorder1[i-1].label == postorder2[j-1].label else 1 # Chi phí thay thế nhãn.
            
            i_lm = postorder1[i-1].leftmost_leaf_id # Lấy ID lá trái nhất của cây con 1.
            j_lm = postorder2[j-1].leftmost_leaf_id # Lấy ID lá trái nhất của cây con 2.
            
            # Áp dụng công thức truy hồi của thuật toán Zhang-Shasha.
            fd[i][j] = min(fd[i-1][j] + 1, # Chi phí xóa postorder1[i-1].
                           fd[i][j-1] + 1, # Chi phí chèn postorder2[j-1].
                           fd[i_lm-1][j_lm-1] + (fd[i][j-1] - fd[i_lm-1][j-1]) + \
                           (fd[i-1][j] - fd[i-1][j_lm-1]) + cost_sub)

    final_dist = fd[n1][n2] # Kết quả là giá trị ở góc dưới phải của bảng.
    return final_dist # Trả về kết quả.

def solve_problem_6(): # Hàm chính để chạy bài toán 6.
    t1 = TED_Node("f", children=[TED_Node("a"), TED_Node("c")]) # Tạo cây T1.
    t2 = TED_Node("f", children=[TED_Node("b"), TED_Node("c")]) # Tạo cây T2.
    
    t1_small = TED_Node("a") # Tạo cây T1 nhỏ.
    t2_small = TED_Node("b") # Tạo cây T2 nhỏ.

    solve_divide_and_conquer(t1, t2) # Gọi hàm giải bằng chia để trị.
    solve_dynamic_programming(t1, t2) # Gọi hàm giải bằng quy hoạch động.

if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_6() # Gọi hàm chính để chạy bài toán.