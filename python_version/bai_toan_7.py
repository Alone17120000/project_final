from collections import deque # Nhập cấu trúc dữ liệu hàng đợi.

class TreeNode: # Lớp định nghĩa một nút của cây nhị phân.
    def __init__(self, val=0, left=None, right=None): # Hàm khởi tạo nút.
        self.val = val # Giá trị của nút.
        self.left = left # Nút con trái.
        self.right = right # Nút con phải.

# (a) Preorder Traversal (Tiền thứ tự: Root-Left-Right)
def preorder_traversal(root): # Hàm duyệt tiền thứ tự (đệ quy).
    if root is None: return [] # Nếu cây rỗng, trả về danh sách rỗng.
    return [root.val] + preorder_traversal(root.left) + preorder_traversal(root.right) # Trả về [nút] + [duyệt cây con trái] + [duyệt cây con phải].

# (b) Postorder Traversal (Hậu thứ tự: Left-Right-Root)
def postorder_traversal(root): # Hàm duyệt hậu thứ tự (đệ quy).
    if root is None: return [] # Nếu cây rỗng, trả về danh sách rỗng.
    return postorder_traversal(root.left) + postorder_traversal(root.right) + [root.val] # Trả về [duyệt cây con trái] + [duyệt cây con phải] + [nút].

# Inorder Traversal (Trung thứ tự: Left-Root-Right )
def inorder_traversal(root): # Hàm duyệt trung thứ tự (đệ quy).
    if root is None: return [] # Nếu cây rỗng, trả về danh sách rỗng.
    return inorder_traversal(root.left) + [root.val] + inorder_traversal(root.right) # Trả về [duyệt cây con trái] + [nút] + [duyệt cây con phải].

# (c) Top-down Traversal (Duyệt theo mức, từ trên xuống - BFS)
def top_down_traversal(root): # Hàm duyệt theo mức (BFS).
    if not root: return [] # Nếu cây rỗng, trả về danh sách rỗng.
    result, q = [], deque([root]) # Khởi tạo danh sách kết quả và hàng đợi.
    while q: # Khi hàng đợi còn phần tử.
        node = q.popleft() # Lấy nút đầu hàng đợi.
        result.append(node.val) # Thêm giá trị nút vào kết quả.
        if node.left: q.append(node.left) # Thêm con trái vào cuối hàng đợi.
        if node.right: q.append(node.right) # Thêm con phải vào cuối hàng đợi.
    return result # Trả về kết quả.

# (d) Bottom-up Traversal (Duyệt từ lá lên gốc)
def bottom_up_traversal(root): # Hàm duyệt từ dưới lên.
    if not root: return [] # Nếu cây rỗng, trả về rỗng.
    
    # Bước 1: Duyệt cây để xây dựng map từ con -> cha và lấy danh sách tất cả các nút.
    parent_map = {root: None} # Map để lưu cha của mỗi nút.
    q = deque([root]) # Hàng đợi để duyệt cây (BFS).
    all_nodes = [root] # Danh sách chứa tất cả các nút trong cây.
    while q: # Bắt đầu duyệt BFS.
        node = q.popleft() # Lấy nút ra khỏi hàng đợi.
        if node.left: # Nếu có con trái.
            parent_map[node.left] = node # Gán cha cho nút con trái.
            all_nodes.append(node.left) # Thêm con trái vào danh sách các nút.
            q.append(node.left) # Thêm con trái vào hàng đợi.
        if node.right: # Nếu có con phải.
            parent_map[node.right] = node # Gán cha cho nút con phải.
            all_nodes.append(node.right) # Thêm con phải vào danh sách.
            q.append(node.right) # Thêm con phải vào hàng đợi.
            
    # Bước 2: Duyệt từ lá lên, sử dụng parent_map.
    result = [] # Khởi tạo danh sách kết quả.
    visited = set() # Tập hợp các nút đã duyệt (để tránh xử lý lại cha nhiều lần).
    
    leaves = [n for n in all_nodes if not n.left and not n.right] # Tìm tất cả các nút lá.
    q_bottom_up = deque(leaves) # Khởi tạo hàng đợi duyệt từ dưới lên bằng các nút lá.
    
    while q_bottom_up: # Khi hàng đợi còn phần tử.
        node = q_bottom_up.popleft() # Lấy một nút ra (bắt đầu từ lá).
        if node in visited: continue # Nếu nút đã được thêm vào kết quả, bỏ qua.
        
        visited.add(node) # Đánh dấu nút đã xử lý.
        result.append(node.val) # Thêm giá trị nút vào kết quả.
        
        parent = parent_map[node] # Lấy cha của nút hiện tại.
        if parent: # Nếu nút có cha.
            q_bottom_up.append(parent) # Thêm cha vào hàng đợi để xử lý ở các vòng lặp sau.
            
    return result # Trả về kết quả.

def solve_problem_7(): # Hàm chính để chạy bài toán 7.
    print("\n--- Bai toan 7: Duyet Cay ---") # In tiêu đề bài toán.
    
    root = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3)) # Tạo cây nhị phân mẫu.
    
    print("Cay nhi phan mau: (Goc 1, con trai (2 -> 4,5), con phai 3)") # In mô tả cây.
    print("\n(a) Pre-order (Tien thu tu):") # In tiêu đề phần a.
    print(f"     -> {' '.join(map(str, preorder_traversal(root)))}") # In kết quả duyệt tiền thứ tự.
    
    print("\n(b) Post-order (Hau thu tu):") # In tiêu đề phần b.
    print(f"     -> {' '.join(map(str, postorder_traversal(root)))}") # In kết quả duyệt hậu thứ tự.

    print("\n(c) Top-down (Tu tren xuong - BFS):") # In tiêu đề phần c.
    print(f"     -> {' '.join(map(str, top_down_traversal(root)))}") # In kết quả duyệt theo mức.
    
    print("\n(d) Bottom-up (Tu duoi len):") # In tiêu đề phần d.
    print(f"     -> {' '.join(map(str, bottom_up_traversal(root)))}") # In kết quả duyệt từ dưới lên.
    
    print("\n   In-order (Trung thu tu):") # In tiêu đề phần duyệt trung thứ tự.
    print(f"     -> {' '.join(map(str, inorder_traversal(root)))}") # In kết quả duyệt trung thứ tự.

if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_7() # Gọi hàm chính.