from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# (a) Preorder Traversal (Tiền thứ tự: Root-Left-Right)
def preorder_traversal(root):
    if root is None: return []
    return [root.val] + preorder_traversal(root.left) + preorder_traversal(root.right)

# (b) Postorder Traversal (Hậu thứ tự: Left-Right-Root)
def postorder_traversal(root):
    if root is None: return []
    return postorder_traversal(root.left) + postorder_traversal(root.right) + [root.val]

# Inorder Traversal (Trung thứ tự: Left-Root-Right )
def inorder_traversal(root):
    if root is None: return []
    return inorder_traversal(root.left) + [root.val] + inorder_traversal(root.right)

# (c) Top-down Traversal (Duyệt theo mức, từ trên xuống - BFS)
def top_down_traversal(root):
    if not root: return []
    result, q = [], deque([root])
    while q:
        node = q.popleft()
        result.append(node.val)
        if node.left: q.append(node.left)
        if node.right: q.append(node.right)
    return result

# (d) Bottom-up Traversal (Duyệt từ lá lên gốc)
def bottom_up_traversal(root):
    if not root: return []
    
    parent_map = {root: None}
    q = deque([root])
    all_nodes = [root]
    while q:
        node = q.popleft()
        if node.left: 
            parent_map[node.left] = node
            all_nodes.append(node.left)
            q.append(node.left)
        if node.right:
            parent_map[node.right] = node
            all_nodes.append(node.right)
            q.append(node.right)
            
    result = []
    visited = set()
    
    leaves = [n for n in all_nodes if not n.left and not n.right]
    q_bottom_up = deque(leaves)
    
    while q_bottom_up:
        node = q_bottom_up.popleft()
        if node in visited: continue
        
        visited.add(node)
        result.append(node.val)
        
        parent = parent_map[node]
        if parent:
            q_bottom_up.append(parent)
            
    return result


def solve_problem_7():
    print("\n--- Bai toan 7: Duyet Cay ---")
    
    root = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3))
    
    print("Cay nhi phan mau: (Goc 1, con trai (2 -> 4,5), con phai 3)")
    print("\n(a) Pre-order (Tien thu tu):")
    print(f"    -> {' '.join(map(str, preorder_traversal(root)))}")
    
    print("\n(b) Post-order (Hau thu tu):")
    print(f"    -> {' '.join(map(str, postorder_traversal(root)))}")

    print("\n(c) Top-down (Tu tren xuong - BFS):")
    print(f"    -> {' '.join(map(str, top_down_traversal(root)))}")
    
    print("\n(d) Bottom-up (Tu duoi len):")
    print(f"    -> {' '.join(map(str, bottom_up_traversal(root)))}")
    
    print("\n   In-order (Trung thu tu):")
    print(f"    -> {' '.join(map(str, inorder_traversal(root)))}")

if __name__ == "__main__":
    solve_problem_7()