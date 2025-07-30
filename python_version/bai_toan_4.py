from collections import deque 


class Edge: # Lớp biểu diễn một cạnh của đồ thị.
    def __init__(self, u, v): # Hàm khởi tạo một cạnh.
        self.u, self.v = u, v # Gán đỉnh đầu (u) và đỉnh cuối (v).
    def __repr__(self): # Hàm biểu diễn đối tượng dạng chuỗi.
        return f"({self.u}->{self.v})" # Trả về chuỗi "(u->v)".

def am_to_al(matrix): # Chuyển ma trận kề (AM) sang danh sách kề (AL).
    adj_list = {i: [] for i in range(len(matrix))} # Khởi tạo danh sách kề rỗng.
    for i, row in enumerate(matrix): # Lặp qua từng hàng của ma trận.
        for j, count in enumerate(row): # Lặp qua từng phần tử trong hàng.
            adj_list[i].extend([j] * count) # Thêm đỉnh kề j vào count lần.
    return adj_list # Trả về danh sách kề.

def am_to_eal(matrix): # Chuyển AM sang danh sách kề mở rộng (EAL).
    num_v = len(matrix) # Lấy số đỉnh.
    ext_adj_list = {i: {'in': [], 'out': []} for i in range(num_v)} # Khởi tạo EAL rỗng.
    for i in range(num_v): # Lặp qua đỉnh nguồn i.
        for j in range(num_v): # Lặp qua đỉnh đích j.
            for _ in range(matrix[i][j]): # Lặp theo số cạnh từ i đến j.
                edge = Edge(i, j) # Tạo đối tượng cạnh.
                ext_adj_list[i]['out'].append(edge) # Thêm vào danh sách cạnh ra của i.
                ext_adj_list[j]['in'].append(edge) # Thêm vào danh sách cạnh vào của j.
    return ext_adj_list # Trả về EAL.

def am_to_amap(matrix): # Chuyển AM sang map kề (AMap).
    num_v = len(matrix) # Lấy số đỉnh.
    adj_map = {i: {'in': {}, 'out': {}} for i in range(num_v)} # Khởi tạo AMap rỗng.
    for i in range(num_v): # Lặp qua đỉnh nguồn i.
        for j in range(num_v): # Lặp qua đỉnh đích j.
            if matrix[i][j] > 0: # Nếu có ít nhất một cạnh.
                edge = Edge(i, j) # Tạo đối tượng cạnh.
                adj_map[i]['out'][j] = edge # Gán cạnh ra từ i đến j.
                adj_map[j]['in'][i] = edge # Gán cạnh vào j từ i.
    return adj_map # Trả về AMap.

def al_to_am(adj_list): # Chuyển danh sách kề (AL) sang ma trận kề (AM).
    num_v = len(adj_list) # Lấy số đỉnh.
    matrix = [[0] * num_v for _ in range(num_v)] # Khởi tạo ma trận rỗng.
    for u, neighbors in adj_list.items(): # Lặp qua các đỉnh và danh sách kề của nó.
        for v in neighbors: # Lặp qua các đỉnh kề.
            matrix[u][v] += 1 # Tăng số cạnh từ u đến v.
    return matrix # Trả về ma trận.

def al_to_eal(adj_list): # Chuyển AL sang EAL.
    return am_to_eal(al_to_am(adj_list)) # Chuyển AL -> AM -> EAL.

def al_to_amap(adj_list): # Chuyển AL sang AMap.
    return am_to_amap(al_to_am(adj_list)) # Chuyển AL -> AM -> AMap.

def eal_to_am(ext_list): # Chuyển EAL sang AM.
    num_v = len(ext_list) # Lấy số đỉnh.
    matrix = [[0] * num_v for _ in range(num_v)] # Khởi tạo ma trận.
    for u, data in ext_list.items(): # Lặp qua các đỉnh trong EAL.
        for edge in data['out']: # Lặp qua các cạnh đi ra.
            matrix[edge.u][edge.v] += 1 # Tăng số cạnh tương ứng.
    return matrix # Trả về ma trận.

def eal_to_al(ext_list): # Chuyển EAL sang AL.
    return am_to_al(eal_to_am(ext_list)) # Chuyển EAL -> AM -> AL.

def eal_to_amap(ext_list): # Chuyển EAL sang AMap.
    return am_to_amap(eal_to_am(ext_list)) # Chuyển EAL -> AM -> AMap.

def amap_to_am(adj_map): # Chuyển AMap sang AM.
    num_v = len(adj_map) # Lấy số đỉnh.
    matrix = [[0] * num_v for _ in range(num_v)] # Khởi tạo ma trận.
    for u, data in adj_map.items(): # Lặp qua các đỉnh trong AMap.
        for v in data['out']: # Lặp qua các đỉnh kề đi ra.
            matrix[u][v] += 1 # Tăng số cạnh.
    return matrix # Trả về ma trận.

def amap_to_al(adj_map): # Chuyển AMap sang AL.
    return am_to_al(amap_to_am(adj_map)) # Chuyển AMap -> AM -> AL.

def amap_to_eal(adj_map): # Chuyển AMap sang EAL.
    return am_to_eal(amap_to_am(adj_map)) # Chuyển AMap -> AM -> EAL.

def ap_to_al_tree(parents): # Chuyển mảng cha (AP) sang danh sách kề (AL) cho cây.
    num_nodes = len(parents) # Lấy số đỉnh.
    adj_list = {i: [] for i in range(num_nodes)} # Khởi tạo danh sách kề.
    for i, p in enumerate(parents): # Lặp qua mảng cha.
        if p is not None: # Nếu đỉnh i có cha.
            adj_list[p].append(i) # Thêm cạnh (cha, con).
            adj_list[i].append(p) # Thêm cạnh (con, cha) (vô hướng).
    return adj_list # Trả về danh sách kề.

def ap_to_fcns(parents): # Chuyển mảng cha (AP) sang con cả - em kế (FCNS).
    adj_list = ap_to_al_tree(parents) # Chuyển sang danh sách kề trước.
    try: # Khối xử lý lỗi.
        root = parents.index(None) # Tìm gốc của cây (đỉnh không có cha).
    except ValueError: # Bắt lỗi nếu không tìm thấy gốc.
        return [], [] # Trả về rỗng.
    return al_tree_to_fcns(adj_list, root) # Chuyển từ danh sách kề và gốc sang FCNS.

def fcns_to_al_tree(fc, ns): # Chuyển FCNS sang danh sách kề cây.
    num_nodes = len(fc) # Lấy số đỉnh.
    adj_list = {i: [] for i in range(num_nodes)} # Khởi tạo danh sách kề.
    for i in range(num_nodes): # Lặp qua các đỉnh.
        child = fc[i] # Lấy con cả của đỉnh i.
        while child is not None: # Lặp qua các con của i.
            adj_list[i].append(child) # Thêm cạnh (cha, con).
            adj_list[child].append(i) # Thêm cạnh (con, cha).
            child = ns[child] # Chuyển sang em kế.
    return adj_list # Trả về danh sách kề.

def fcns_to_ap(fc, ns): # Chuyển FCNS sang mảng cha (AP).
    adj_list = fcns_to_al_tree(fc, ns) # Chuyển sang danh sách kề trước.
    if not adj_list: return [] # Nếu rỗng thì trả về rỗng.
    is_child = [False] * len(fc) # Mảng đánh dấu các đỉnh là con.
    for i in range(len(fc)): # Lặp qua các đỉnh.
        child = fc[i] # Lấy con cả.
        while child is not None: # Lặp qua chuỗi con.
            is_child[child] = True # Đánh dấu là con.
            child = ns[child] # Chuyển sang em kế.
    try: # Khối xử lý lỗi.
        root = is_child.index(False) # Gốc là đỉnh duy nhất không phải là con.
    except ValueError: # Bắt lỗi nếu không tìm thấy gốc.
        return [] # Trả về rỗng.
    return al_tree_to_ap(adj_list, root) # Chuyển từ AL và gốc sang AP.

def al_tree_to_ap(adj_list, root_node=0): # Chuyển AL cây sang mảng cha (AP) bằng BFS.
    num_nodes = len(adj_list) # Lấy số đỉnh.
    parents = [None] * num_nodes # Khởi tạo mảng cha.
    q = deque([root_node]) # Hàng đợi cho BFS, bắt đầu từ gốc.
    visited = {root_node} # Tập hợp các đỉnh đã thăm.
    while q: # Khi hàng đợi còn phần tử.
        u = q.popleft() # Lấy một đỉnh ra.
        for v in adj_list[u]: # Lặp qua các đỉnh kề.
            if v not in visited: # Nếu đỉnh kề chưa được thăm.
                visited.add(v) # Đánh dấu đã thăm.
                parents[v] = u # Gán cha cho đỉnh v.
                q.append(v) # Thêm v vào hàng đợi.
    return parents # Trả về mảng cha.

def al_tree_to_fcns(adj_list, root_node=0): # Chuyển AL cây sang FCNS.
    num_nodes = len(adj_list) # Lấy số đỉnh.
    fc, ns = [None] * num_nodes, [None] * num_nodes # Khởi tạo mảng FC và NS.
    parent_child_map = {i: [] for i in range(num_nodes)} # Tạo map từ cha đến danh sách con.
    q = deque([root_node]) # Hàng đợi cho BFS.
    visited = {root_node} # Tập hợp đỉnh đã thăm.
    while q: # Khi hàng đợi còn phần tử.
        u = q.popleft() # Lấy một đỉnh ra.
        for v in adj_list[u]: # Lặp qua các đỉnh kề.
            if v not in visited: # Nếu chưa thăm.
                visited.add(v) # Đánh dấu đã thăm.
                parent_child_map[u].append(v) # Thêm v làm con của u.
                q.append(v) # Thêm v vào hàng đợi.
    for i in range(num_nodes): # Lặp qua các đỉnh để xây dựng FCNS.
        children = parent_child_map[i] # Lấy danh sách con của đỉnh i.
        if children: # Nếu đỉnh i có con.
            fc[i] = children[0] # Gán con cả.
            for j in range(len(children) - 1): # Lặp qua các con để nối em kế.
                ns[children[j]] = children[j+1] # Gán em kế.
    return fc, ns # Trả về mảng FC và NS.
    



def print_am_table(matrix, title="Ma trận kề (AM)"): # Hàm in ma trận kề dạng bảng.
    print(f"### {title}") # In tiêu đề bảng.
    num_v = len(matrix) # Lấy số đỉnh.
    header = "| |" + "".join([f" {i} |" for i in range(num_v)]) # Tạo dòng tiêu đề cột.
    separator = "|:---|" + "".join([":---:|" for _ in range(num_v)]) # Tạo dòng phân cách bảng.
    print(header) # In dòng tiêu đề.
    print(separator) # In dòng phân cách.
    for i, row in enumerate(matrix): # Lặp qua các hàng.
        row_str = f"| **{i}** |" + "".join([f" {cell} |" for cell in row]) # Tạo chuỗi cho một hàng.
        print(row_str) # In hàng của bảng.

def print_al_table(adj_list, title="Danh sách kề (AL)"): # Hàm in danh sách kề dạng bảng.
    print(f"### {title}") # In tiêu đề bảng.
    print("| Đỉnh | Danh sách kề |") # In tiêu đề cột.
    print("|:---:|:---|") # In dòng phân cách.
    for u, neighbors in adj_list.items(): # Lặp qua các đỉnh.
        print(f"| **{u}** | `{repr(neighbors)}` |") # In một hàng của bảng.

def print_eal_table(ext_adj_list): # Hàm in danh sách kề mở rộng dạng bảng.
    print("### Danh sách kề mở rộng (EAL)") # In tiêu đề bảng.
    print("| Đỉnh | Cạnh vào (in) | Cạnh ra (out) |") # In tiêu đề cột.
    print("|:---:|:---|:---|") # In dòng phân cách.
    for u, data in ext_adj_list.items(): # Lặp qua các đỉnh.
        print(f"| **{u}** | `{repr(data['in'])}` | `{repr(data['out'])}` |") # In một hàng của bảng.

def print_amap_table(adj_map): # Hàm in map kề dạng bảng.
    print("### Map kề (AMap)") # In tiêu đề bảng.
    print("| Đỉnh | Map cạnh vào (in) | Map cạnh ra (out) |") # In tiêu đề cột.
    print("|:---:|:---|:---|") # In dòng phân cách.
    for u, data in adj_map.items(): # Lặp qua các đỉnh.
        print(f"| **{u}** | `{repr(data['in'])}` | `{repr(data['out'])}` |") # In một hàng của bảng.
        
def print_ap_table(parents, title="Mảng cha (AP)"): # Hàm in mảng cha dạng bảng.
    print(f"### {title}") # In tiêu đề bảng.
    print("| Đỉnh (Con) | Cha |") # In tiêu đề cột.
    print("|:---:|:---:|") # In dòng phân cách.
    for i, p in enumerate(parents): # Lặp qua các đỉnh.
        print(f"| **{i}** | `{p}` |") # In một hàng của bảng.

def print_fcns_table(fc, ns): # Hàm in FCNS dạng bảng.
    print("### Con cả - Em kế (FCNS)") # In tiêu đề bảng.
    print("| Đỉnh | Con Cả (FC) | Em Kế (NS) |") # In tiêu đề cột.
    print("|:---:|:---:|:---:|") # In dòng phân cách.
    for i in range(len(fc)): # Lặp qua các đỉnh.
        print(f"| **{i}** | `{fc[i]}` | `{ns[i]}` |") # In một hàng của bảng.




def solve_problem_4(): # Hàm chính cho bài toán 4 (phiên bản in bảng).
    print("## --- Bai toan 4: Chuyen doi bieu dien do thi va cay ---") # In tiêu đề chính.
    
    simple_graph_matrix = [[0,1,1,0], [1,0,0,1], [1,0,0,1], [0,1,1,0]] # Khai báo ma trận kề mẫu.

    print("\n## I. DO THI") # In tiêu đề phần đồ thị.
    print("\n### --- Trường hợp: Đơn đồ thị ---") # In tiêu đề trường hợp.
    print_am_table(simple_graph_matrix, title="Đầu vào: Ma trận kề (AM)") # In bảng ma trận đầu vào.
    
    print("\n---") # In dòng ngăn cách.
    
    print("\n### * Chuyển đổi từ Ma trận kề (AM):") # In tiêu đề khối chuyển đổi.
    print_al_table(am_to_al(simple_graph_matrix), title="AM to AL") # In bảng AM sang AL.
    print_eal_table(am_to_eal(simple_graph_matrix)) # In bảng AM sang EAL.
    print_amap_table(am_to_amap(simple_graph_matrix)) # In bảng AM sang AMap.
    
    print("\n" + "="*40 + "\n") # In dòng ngăn cách lớn.
    
    print("## II. CAY") # In tiêu đề phần cây.
    parents = [None, 0, 0, 1, 1] # Khai báo mảng cha mẫu.
    print_ap_table(parents, title="Đầu vào: Mảng cha (AP)") # In bảng mảng cha đầu vào.
    
    print("\n---") # In dòng ngăn cách.
    
    print("\n### * Chuyển đổi từ Array of Parents (AP):") # In tiêu đề khối chuyển đổi.
    print_al_table(ap_to_al_tree(parents), title="AP to AL_Tree") # In bảng AP sang AL Cây.
    fc, ns = ap_to_fcns(parents) # Chuyển AP sang FCNS.
    print_fcns_table(fc, ns) # In bảng FCNS.
    
    print("\n### * Chuyển đổi từ First-Child, Next-Sibling (FCNS):") # In tiêu đề khối chuyển đổi.
    print_ap_table(fcns_to_ap(fc, ns), title="FCNS to AP") # In bảng FCNS sang AP.
    print_al_table(fcns_to_al_tree(fc, ns), title="FCNS to AL_Tree") # In bảng FCNS sang AL Cây.

    print("\n### * Chuyển đổi từ Adjacency List (AL_Tree):") # In tiêu đề khối chuyển đổi.
    al_tree = ap_to_al_tree(parents) # Lấy danh sách kề của cây.
    root = parents.index(None) # Tìm gốc cây.
    print_ap_table(al_tree_to_ap(al_tree, root), title="AL_Tree to AP") # In bảng AL Cây sang AP.
    fc_new, ns_new = al_tree_to_fcns(al_tree, root) # Chuyển AL Cây sang FCNS.
    print_fcns_table(fc_new, ns_new) # In bảng FCNS.


if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_4() # Gọi hàm chính.