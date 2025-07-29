# -*- coding: utf-8 -*-
import sys


class TED_Node:
    def __init__(self, label, children=None):
        self.label = label
        self.children = children if children is not None else []
        self.id = -1
        self.leftmost_leaf_id = -1

def _prepare_tree(root):
    nodes_postorder = []
    
    def _postorder_traverse(node):
        if not node: return
        for child in node.children:
            _postorder_traverse(child)
        node.id = len(nodes_postorder)
        nodes_postorder.append(node)

    _postorder_traverse(root)
    
    for node in nodes_postorder:
        if not node.children:
            node.leftmost_leaf_id = node.id
        else:
           
            node.leftmost_leaf_id = node.children[0].leftmost_leaf_id
            
    return nodes_postorder

# --- (a) Backtracking ---
def solve_backtracking(root1, root2):
    print("\n(a) Giai bang Backtracking (Brute-force):")
    
    postorder1, postorder2 = _prepare_tree(root1), _prepare_tree(root2)
    n1, n2 = len(postorder1), len(postorder2)
    min_cost = [float('inf')]

    def backtrack(mapping, cost):
        if len(mapping) == n1:
            final_cost = cost + (n2 - len(set(mapping.values())))
            min_cost[0] = min(min_cost[0], final_cost)
            return

        u = postorder1[len(mapping)]
        
        # Lựa chọn 1: Xóa u
        new_map_del = mapping.copy()
        backtrack(new_map_del, cost + 1)
        
        # Lựa chọn 2: Thay thế u bằng một v chưa được map
        mapped_v = set(mapping.values())
        for v in postorder2:
            if v not in mapped_v:
                cost_sub = 0 if u.label == v.label else 1
                new_map_sub = mapping.copy()
                new_map_sub[u] = v
                backtrack(new_map_sub, cost + cost_sub)

    # Cần một ánh xạ ban đầu để xử lý các nút được chèn
    initial_map = {}
    backtrack(initial_map, 0)
    
    result = min_cost[0] if min_cost[0] != float('inf') else n1 + n2
    print(f"    => Khoang cach sua cay la: {result}")
    return result

# --- (b) Branch-&-Bound ---
def solve_branch_and_bound(root1, root2):
    print("\n(b) Giai bang Branch-&-Bound:")
    
    postorder1, postorder2 = _prepare_tree(root1), _prepare_tree(root2)
    n1, n2 = len(postorder1), len(postorder2)
    min_cost = [float('inf')]
    
    def backtrack_bb(mapping, cost):
        if cost >= min_cost[0]:
            return

        if len(mapping) == n1:
            final_cost = cost + (n2 - len(set(mapping.values())))
            min_cost[0] = min(min_cost[0], final_cost)
            return

        u = postorder1[len(mapping)]
        
        backtrack_bb(mapping.copy(), cost + 1)
        
        mapped_v = set(mapping.values())
        for v in postorder2:
            if v not in mapped_v:
                cost_sub = 0 if u.label == v.label else 1
                new_map_sub = mapping.copy()
                new_map_sub[u] = v
                backtrack_bb(new_map_sub, cost + cost_sub)
                
    backtrack_bb({}, 0)
    result = min_cost[0] if min_cost[0] != float('inf') else n1 + n2
    print(f"    => Khoang cach sua cay la: {result}")
    return result

# --- (c) Divide-&-Conquer (Recursive, no memoization) ---
def solve_divide_and_conquer(root1, root2):
    print("\n(c) Giai bang Divide-&-Conquer (De quy):")
    
    postorder1, postorder2 = _prepare_tree(root1), _prepare_tree(root2)
    
    def d(i, j):
        if i < 0 and j < 0: return 0
        if i < 0: return j + 1
        if j < 0: return i + 1
            
        u, v = postorder1[i], postorder2[j]
        cost_sub = 0 if u.label == v.label else 1
        
        cost_del = d(i - 1, j) + 1
        cost_ins = d(i, j - 1) + 1
        cost_rep = d(i - 1, j - 1) + cost_sub
        
        return min(cost_del, cost_ins, cost_rep)

    result = d(len(postorder1) - 1, len(postorder2) - 1)
    print(f"    => Khoang cach sua cay la: {result}")
    return result

# --- (d) Dynamic Programming (Zhang-Shasha Algorithm) ---
def solve_dynamic_programming(root1, root2):
    print("\n(d) Giai bang Dynamic Programming:")
    
    postorder1, postorder2 = _prepare_tree(root1), _prepare_tree(root2)
    n1, n2 = len(postorder1), len(postorder2)
    
    fd = [[0] * (n2 + 1) for _ in range(n1 + 1)]
    for i in range(1, n1 + 1): fd[i][0] = i
    for j in range(1, n2 + 1): fd[0][j] = j
        
    for i in range(1, n1 + 1):
        for j in range(1, n2 + 1):
            cost_sub = 0 if postorder1[i-1].label == postorder2[j-1].label else 1
            
            i_lm = postorder1[i-1].leftmost_leaf_id
            j_lm = postorder2[j-1].leftmost_leaf_id
            
            fd[i][j] = min(fd[i-1][j] + 1,
                           fd[i][j-1] + 1,
                           fd[i_lm-1][j_lm-1] + (fd[i][j-1] - fd[i_lm-1][j-1]) + \
                           (fd[i-1][j] - fd[i-1][j_lm-1]) + cost_sub)

    print("    Bang quy hoach dong (forest_dist) :")
    for row in fd:
        print(f"      {row}")
        
    final_dist = fd[n1][n2]
    print(f"    => Khoang cach sua cay la: {final_dist}")
    return final_dist

def solve_problem_6():
    print("\n--- Bai toan 6: Tree Edit Distance ---")
    
    t1 = TED_Node("f", children=[TED_Node("a"), TED_Node("c")])
    t2 = TED_Node("f", children=[TED_Node("b"), TED_Node("c")])
    

    t1_small = TED_Node("a")
    t2_small = TED_Node("b")

    
    solve_divide_and_conquer(t1, t2)
    solve_dynamic_programming(t1, t2)
    print("\n    Luu y: Backtracking va Branch-&-Bound hiện tại em chưa code cho run được voi cay co >2 nut.")

if __name__ == "__main__":
    solve_problem_6()