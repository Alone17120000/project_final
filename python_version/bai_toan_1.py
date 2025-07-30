def get_transpose(partition): # Hàm tính phân hoạch chuyển vị.
    if not partition: return [] # Trả về rỗng nếu phân hoạch rỗng.
    max_part = partition[0] # Lấy phần tử lớn nhất.
    transpose = [sum(1 for part in partition if part >= i) for i in range(1, max_part + 1)] # Tạo chuyển vị: đếm số phần tử >= i.
    return transpose # Trả về phân hoạch chuyển vị.

def print_diagram(partition, title): # Hàm in biểu đồ.
    print(f"   {title}:") # In tiêu đề của biểu đồ.
    if not partition: return # Bỏ qua nếu phân hoạch rỗng.
    for part in partition: # Lặp qua từng phần tử.
        print(f"     {'*' * part}") # In ra các dấu sao tương ứng.

def find_partitions(n, k, max_val, current_partition): # Hàm đệ quy tìm phân hoạch.
    if k == 0: # Nếu đã tìm đủ k phần tử.
        if n == 0: # Nếu tổng các phần tử đúng bằng n.
            partition_str = " + ".join(map(str, current_partition)) # Tạo chuỗi biểu diễn phân hoạch.
            print(f"Phan hoach: {partition_str}") # In phân hoạch.
            print_diagram(current_partition, "- Bieu do Ferrers (F)") # In biểu đồ Ferrers.
            transpose_partition = get_transpose(current_partition) # Tính phân hoạch chuyển vị.
            print_diagram(transpose_partition, "- Bieu do chuyen vi (F^T)") # In biểu đồ chuyển vị.
            print("----------------------------------------") # In dòng ngăn cách.
        return # Dừng nhánh đệ quy.

    for i in range(min(n, max_val), 0, -1): # Lặp để thử các giá trị.
        if n - i >= k - 1: # Điều kiện cắt tỉa.
            current_partition.append(i) # Thêm i vào phân hoạch.
            find_partitions(n - i, k - 1, i, current_partition) # Gọi đệ quy.
            current_partition.pop() # Quay lui, xóa i.

def solve_problem_1(): # Hàm chính cho bài toán 1.
    print("\n--- Bai toan 1: In bieu do Ferrers & chuyen vi ---") # In tiêu đề bài toán.
    try: # Khối xử lý lỗi.
        n = int(input("Nhap n: ")) # Nhận n.
        k = int(input("Nhap k: ")) # Nhận k.
        if n > 0 and k > 0 and n >= k: # Kiểm tra điều kiện.
            find_partitions(n, k, n - k + 1, []) # Gọi hàm tìm phân hoạch.
        else: # Nếu điều kiện sai.
            print("Khong co phan hoach nao hop le.") # Thông báo không hợp lệ.
    except ValueError: # Bắt lỗi nhập sai kiểu.
        print("Vui long nhap so nguyen hop le.") # Thông báo lỗi.

if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_1() # Gọi hàm chính.