def get_transpose(partition): # Hàm tính phân hoạch chuyển vị.
    if not partition: # Nếu phân hoạch rỗng.
        return [] # Trả về rỗng.
    max_part = partition[0] # Lấy phần tử lớn nhất.
    transpose = [] # Khởi tạo danh sách chuyển vị.
    for i in range(1, max_part + 1): # Lặp qua từng cột có thể.
        count = sum(1 for part in partition if part >= i) # Đếm số hàng dài hơn hoặc bằng i.
        transpose.append(count) # Thêm kết quả đếm vào chuyển vị.
    return transpose # Trả về kết quả.

def is_self_conjugate(partition): # Hàm kiểm tra tính tự liên hợp.
    if not partition: # Nếu phân hoạch rỗng.
        return True # Coi là tự liên hợp.
    return partition == get_transpose(partition) # So sánh phân hoạch với chuyển vị của nó.

# --- Phần (a): Tìm các phân hoạch tự liên hợp của n có k phần ---
def find_k_partitions(n, k, max_val, current_partition, result_list): # Hàm tìm phân hoạch của n thành k phần.
    if k == 0: # Nếu đã tìm đủ k phần.
        if n == 0: # Nếu tổng vừa bằng n.
            result_list.append(list(current_partition)) # Thêm phân hoạch vào danh sách kết quả.
        return # Dừng nhánh đệ quy.

    for i in range(min(n, max_val), 0, -1): # Lặp thử các giá trị.
        if n - i >= k - 1: # Điều kiện cắt tỉa.
            current_partition.append(i) # Thêm i vào phân hoạch.
            find_k_partitions(n - i, k - 1, i, current_partition, result_list) # Gọi đệ quy.
            current_partition.pop() # Quay lui.

def solve_part_a(n, k): # Hàm giải câu (a).
    print(f"(a) Cac phan hoach tu lien hop cua {n} co {k} phan:") # In tiêu đề câu (a).
    all_k_partitions = [] # Danh sách chứa tất cả phân hoạch.
    find_k_partitions(n, k, n, [], all_k_partitions) # Tìm tất cả phân hoạch của n thành k phần.
    self_conjugate_partitions = [] # Danh sách chứa phân hoạch tự liên hợp.
    for p in all_k_partitions: # Lặp qua từng phân hoạch đã tìm.
        if is_self_conjugate(p): # Nếu phân hoạch là tự liên hợp.
            self_conjugate_partitions.append(p) # Thêm vào danh sách kết quả.

    if not self_conjugate_partitions: # Nếu không có kết quả.
        print("   (khong co)") # In thông báo không có.
    else: # Nếu có kết quả.
        for p in self_conjugate_partitions: # Lặp và in từng kết quả.
            print(f"   - {' + '.join(map(str, p))}") # In phân hoạch dạng chuỗi.
            
    print(f"=> Tong so: {len(self_conjugate_partitions)}") # In tổng số phân hoạch tìm được.
    return len(self_conjugate_partitions) # Trả về số lượng.

# --- Phần (c): Tìm số phân hoạch tự liên hợp theo định lý ---
def find_odd_distinct_partitions(n, max_odd, current_partition, result_list): # Hàm tìm phân hoạch thành các phần tử lẻ và phân biệt.
    if n == 0: # Nếu tổng bằng 0.
        result_list.append(list(current_partition)) # Thêm phân hoạch hợp lệ vào kết quả.
        return # Dừng nhánh.
    if n < 0 or max_odd <= 0: # Điều kiện dừng khi không hợp lệ.
        return # Dừng nhánh.

    find_odd_distinct_partitions(n, max_odd - 2, current_partition, result_list) # Lựa chọn 1: KHÔNG lấy phần tử max_odd.
    current_partition.append(max_odd) # Thêm max_odd vào phân hoạch.
    find_odd_distinct_partitions(n - max_odd, max_odd - 2, current_partition, result_list) # Lựa chọn 2: LẤY phần tử max_odd.
    current_partition.pop() # Quay lui.

def solve_part_c(n): # Hàm giải câu (c).
    print("\n(c) So phan hoach tu lien hop (theo dinh ly):") # In tiêu đề câu (c).
    odd_distinct_partitions = [] # Danh sách chứa kết quả.
    start_odd = n if n % 2 != 0 else n - 1 # Tìm số lẻ lớn nhất không vượt quá n.
    find_odd_distinct_partitions(n, start_odd, [], odd_distinct_partitions) # Bắt đầu tìm kiếm.
    print(f"   Cac phan hoach cua {n} thanh cac phan tu le va phan biet la:") # In tiêu đề kết quả.
    if not odd_distinct_partitions: # Nếu không có kết quả.
        print("   (khong co)") # In thông báo không có.
    else: # Nếu có kết quả.
        for p in sorted(odd_distinct_partitions): # Lặp qua và in từng kết quả.
            print(f"   - {' + '.join(map(str, p))}") # In phân hoạch dạng chuỗi.

    print(f"=> Tong so: {len(odd_distinct_partitions)}") # In tổng số.

def solve_problem_3(): # Hàm chính cho bài toán 3.
    print("\n--- Bai toan 3: Phan hoach tu lien hop ---") # In tiêu đề bài toán.
    try: # Khối xử lý lỗi.
        n = int(input("Nhap n: ")) # Nhận n.
        k = int(input("Nhap k: ")) # Nhận k.
        solve_part_a(n, k) # Gọi hàm giải câu (a).
        solve_part_c(n) # Gọi hàm giải câu (c).
    except ValueError: # Bắt lỗi nhập sai kiểu.
        print("Vui long nhap so nguyen hop le.") # Thông báo lỗi.

# Chạy bài toán 3.
if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_3() # Gọi hàm chính.