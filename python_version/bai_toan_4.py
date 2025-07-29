from collections import deque

class Edge:
    def __init__(self, u, v):
        self.u, self.v = u, v
    def __repr__(self):
        return f"({self.u}->{self.v})"

def am_to_al(matrix):
    adj_list = {i: [] for i in range(len(matrix))}
    for i, row in enumerate(matrix):
        for j, count in enumerate(row):
            adj_list[i].extend([j] * count)
    return adj_list

def am_to_eal(matrix):
    num_v = len(matrix)
    ext_adj_list = {i: {'in': [], 'out': []} for i in range(num_v)}
    for i in range(num_v):
        for j in range(num_v):
            for _ in range(matrix[i][j]):
                edge = Edge(i, j)
                ext_adj_list[i]['out'].append(edge)
                ext_adj_list[j]['in'].append(edge)
    return ext_adj_list

def am_to_amap(matrix):
    num_v = len(matrix)
    adj_map = {i: {'in': {}, 'out': {}} for i in range(num_v)}
    for i in range(num_v):
        for j in range(num_v):
            if matrix[i][j] > 0:
                edge = Edge(i, j)
                adj_map[i]['out'][j] = edge
                adj_map[j]['in'][i] = edge
    return adj_map

def al_to_am(adj_list):
    num_v = len(adj_list)
    matrix = [[0] * num_v for _ in range(num_v)]
    for u, neighbors in adj_list.items():
        for v in neighbors:
            matrix[u][v] += 1
    return matrix

def al_to_eal(adj_list):
    return am_to_eal(al_to_am(adj_list))

def al_to_amap(adj_list):
    return am_to_amap(al_to_am(adj_list))

def eal_to_am(ext_list):
    num_v = len(ext_list)
    matrix = [[0] * num_v for _ in range(num_v)]
    for u, data in ext_list.items():
        for edge in data['out']:
            matrix[edge.u][edge.v] += 1
    return matrix

def eal_to_al(ext_list):
    return am_to_al(eal_to_am(ext_list))

def eal_to_amap(ext_list):
    return am_to_amap(eal_to_am(ext_list))

def amap_to_am(adj_map):
    num_v = len(adj_map)
    matrix = [[0] * num_v for _ in range(num_v)]
    for u, data in adj_map.items():
        for v in data['out']:
            matrix[u][v] += 1
    return matrix

def amap_to_al(adj_map):
    return am_to_al(amap_to_am(adj_map))

def amap_to_eal(adj_map):
    return am_to_eal(amap_to_am(adj_map))

def ap_to_al_tree(parents):
    num_nodes = len(parents)
    adj_list = {i: [] for i in range(num_nodes)}
    for i, p in enumerate(parents):
        if p is not None:
            adj_list[p].append(i)
            adj_list[i].append(p)
    return adj_list

def ap_to_fcns(parents):
    adj_list = ap_to_al_tree(parents)
    try:
        root = parents.index(None)
    except ValueError:
        return [], []
    return al_tree_to_fcns(adj_list, root)

def fcns_to_al_tree(fc, ns):
    num_nodes = len(fc)
    adj_list = {i: [] for i in range(num_nodes)}
    for i in range(num_nodes):
        child = fc[i]
        while child is not None:
            adj_list[i].append(child)
            adj_list[child].append(i)
            child = ns[child]
    return adj_list

def fcns_to_ap(fc, ns):
    adj_list = fcns_to_al_tree(fc, ns)
    if not adj_list: return []
    is_child = [False] * len(fc)
    for i in range(len(fc)):
        child = fc[i]
        while child is not None:
            is_child[child] = True
            child = ns[child]
    try:
        root = is_child.index(False)
    except ValueError:
        return []
    return al_tree_to_ap(adj_list, root)

def al_tree_to_ap(adj_list, root_node=0):
    num_nodes = len(adj_list)
    parents = [None] * num_nodes
    q = deque([root_node])
    visited = {root_node}
    while q:
        u = q.popleft()
        for v in adj_list[u]:
            if v not in visited:
                visited.add(v)
                parents[v] = u
                q.append(v)
    return parents

def al_tree_to_fcns(adj_list, root_node=0):
    num_nodes = len(adj_list)
    fc, ns = [None] * num_nodes, [None] * num_nodes
    parent_child_map = {i: [] for i in range(num_nodes)}
    q = deque([root_node])
    visited = {root_node}
    while q:
        u = q.popleft()
        for v in adj_list[u]:
            if v not in visited:
                visited.add(v)
                parent_child_map[u].append(v)
                q.append(v)
    for i in range(num_nodes):
        children = parent_child_map[i]
        if children:
            fc[i] = children[0]
            for j in range(len(children) - 1):
                ns[children[j]] = children[j+1]
    return fc, ns

def solve_problem_4():
    print("--- Bai toan 4: Chuyen doi bieu dien do thi va cay ---")
    
    simple_graph_matrix = [[0,1,1,0], [1,0,0,1], [1,0,0,1], [0,1,1,0]]
    graphs = {"Don do thi": simple_graph_matrix}

    print("\n--- I. DO THI ---")
    for name, matrix in graphs.items():
        print(f"\n--- Truong hop: {name} ---")
        print(f"  - Dau vao (Ma tran ke):\n    {matrix}")
        
        al = am_to_al(matrix)
        eal = am_to_eal(matrix)
        amap = am_to_amap(matrix)

        print("\n  * Chuyen doi tu Ma tran ke (AM):")
        print(f"    -> AM to AL: {al}")
        print(f"    -> AM to EAL: {eal}")
        print(f"    -> AM to AMap: {amap}")
        
        print("\n  * Chuyen doi tu Danh sach ke (AL):")
        print(f"    -> AL to AM: {al_to_am(al)}")
        print(f"    -> AL to EAL: {al_to_eal(al)}")
        print(f"    -> AL to AMap: {al_to_amap(al)}")

        print("\n  * Chuyen doi tu DS ke mo rong (EAL):")
        print(f"    -> EAL to AM: {eal_to_am(eal)}")
        print(f"    -> EAL to AL: {eal_to_al(eal)}")
        print(f"    -> EAL to AMap: {eal_to_amap(eal)}")

        print("\n  * Chuyen doi tu Map ke (AMap):")
        print(f"    -> AMap to AM: {amap_to_am(amap)}")
        print(f"    -> AMap to AL: {amap_to_al(amap)}")
        print(f"    -> AMap to EAL: {amap_to_eal(amap)}")
        
    print("\n\n--- II. CAY ---")
    parents = [None, 0, 0, 1, 1]
    print(f"  - Dau vao (Array of Parents): {parents}")
    
    al_tree = ap_to_al_tree(parents)
    fc, ns = ap_to_fcns(parents)
    
    print("\n  * Chuyen doi tu Array of Parents (AP):")
    print(f"    -> AP to AL_Tree: {al_tree}")
    print(f"    -> AP to FCNS: (FC={fc}, NS={ns})")
    
    print("\n  * Chuyen doi tu First-Child, Next-Sibling (FCNS):")
    print(f"    -> FCNS to AP: {fcns_to_ap(fc, ns)}")
    print(f"    -> FCNS to AL_Tree: {fcns_to_al_tree(fc, ns)}")
    
    print("\n  * Chuyen doi tu Adjacency List (AL_Tree):")
    print(f"    -> AL_Tree to AP: {al_tree_to_ap(al_tree, 0)}")
    print(f"    -> AL_Tree to FCNS: {al_tree_to_fcns(al_tree, 0)}")

if __name__ == "__main__":
    solve_problem_4()