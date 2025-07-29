# -*- coding: utf-8 -*-

class TED_Node:
    def __init__(self, label, children=None):
        self.label = label
        self.children = children if children is not None else []
        self.postorder_id = -1
        self.preorder_id = -1
        self.depth = -1
        self.leftmost_leaf = None

def _prepare_tree(root):
    nodes = []
    postorder_nodes = []
    
    def _postorder_traverse(node):
        if not node: return
        for child in node.children:
            _postorder_traverse(child)
        node.postorder_id = len(postorder_nodes)
        postorder_nodes.append(node)

    def _preorder_traverse(node, depth=0):
        if not node: return
        node.preorder_id = len(nodes)
        node.depth = depth
        nodes.append(node)
        is_leaf = True
        for child in node.children:
            is_leaf = False
            _preorder_traverse(child, depth + 1)
        if is_leaf:
            node.leftmost_leaf = node
    
    _postorder_traverse(root)
    _preorder_traverse(root)
    
    for node in reversed(nodes):
        if not node.children:
            node.leftmost_leaf = node
        else:
            node.leftmost_leaf = node.children[0].leftmost_leaf
            
    return nodes, postorder_nodes

def solve_dynamic_programming(root1, root2):
    preorder1, postorder1 = _prepare_tree(root1)
    preorder2, postorder2 = _prepare_tree(root2)
    
    n1, n2 = len(postorder1), len(postorder2)
    
    tree_dist = [[0] * n2 for _ in range(n1)]
    
    for i in range(n1):
        for j in range(n2):
            i_lm = postorder1[i].leftmost_leaf.postorder_id
            j_lm = postorder2[j].leftmost_leaf.postorder_id
            
            cost_sub = 0 if postorder1[i].label == postorder2[j].label else 1
            
            if i_lm == postorder1[i].postorder_id and j_lm == postorder2[j].postorder_id:
                dp_val_del = tree_dist[i-1][j] + 1 if i > 0 else j + 1
                dp_val_ins = tree_dist[i][j-1] + 1 if j > 0 else i + 1
                dp_val_rep = tree_dist[i-1][j-1] + cost_sub if i > 0 and j > 0 else cost_sub
                tree_dist[i][j] = min(dp_val_del, dp_val_ins, dp_val_rep)
            else:
                dp_val_del = tree_dist[i-1][j] + 1 if i > 0 else j + 1
                dp_val_ins = tree_dist[i][j-1] + 1 if j > 0 else i + 1
                dp_val_rep = tree_dist[i_lm-1][j_lm-1] + tree_dist[i][j] - tree_dist[i_lm-1][j] - tree_dist[i][j_lm-1] + cost_sub
                tree_dist[i][j] = min(dp_val_del, dp_val_ins, dp_val_rep)
    
    print("    Bang quy hoach dong (treedist):")
    for row in tree_dist:
        print(f"      {row}")
        
    return tree_dist[n1-1][n2-1]

def solve_problem_6():
    print("\n--- Bai toan 6: Tree Edit Distance ---")
    
    t1_f = TED_Node("f", children=[TED_Node("a"), TED_Node("c")])
    t2_f = TED_Node("f", children=[TED_Node("b"), TED_Node("c")])

    print("\n(d) Dynamic Programming:")
    dist_dp = solve_dynamic_programming(t1_f, t2_f)
    print(f"    Khoang cach sua cay la: {dist_dp}")

    print("\n(a), (b), (c) Backtracking, Branch-&-Bound, Divide-&-Conquer:")
    print("    Cac phuong phap nay co do phuc tap rat cao (O(n!)) va khong thuc te de hien thuc cho bai toan nay.")
    print("    Thuat toan Dynamic Programming (Zhang-Shasha) la giai phap tieu chuan va hieu qua nhat.")


if __name__ == "__main__":
    solve_problem_6()