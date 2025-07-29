# Các hàm tiện ích kế thừa từ bài toán 1
def get_transpose(partition):
    if not partition:
        return []
    max_part = partition[0]
    transpose = []
    for i in range(1, max_part + 1):
        count = sum(1 for part in partition if part >= i)
        transpose.append(count)
    return transpose

def is_self_conjugate(partition):
    """
    Kiểm tra xem một phân hoạch có phải là tự liên hợp hay không.
    Một phân hoạch là tự liên hợp nếu nó bằng với chuyển vị của nó.
    """
    if not partition:
        return True
    return partition == get_transpose(partition)

# --- Phần (a): Tìm các phân hoạch tự liên hợp của n có k phần ---
# Cách tiếp cận đúng là: Tìm tất cả phân hoạch của n thành k phần, sau đó kiểm tra tính tự liên hợp.
def find_k_partitions(n, k, max_val, current_partition, result_list):
    if k == 0:
        if n == 0:
            result_list.append(list(current_partition))
        return

    for i in range(min(n, max_val), 0, -1):
        # Điều kiện cắt tỉa này vẫn đúng để tìm phân hoạch n thành k phần
        if n - i >= k - 1:
            current_partition.append(i)
            find_k_partitions(n - i, k - 1, i, current_partition, result_list)
            current_partition.pop()

def solve_part_a(n, k):
    print(f"(a) Cac phan hoach tu lien hop cua {n} co {k} phan:")
    
    all_k_partitions = []
    find_k_partitions(n, k, n, [], all_k_partitions)
    
    self_conjugate_partitions = []
    for p in all_k_partitions:
        if is_self_conjugate(p):
            self_conjugate_partitions.append(p)

    if not self_conjugate_partitions:
        print("  (khong co)")
    else:
        for p in self_conjugate_partitions:
            print(f"  - {' + '.join(map(str, p))}")
            
    print(f"=> Tong so: {len(self_conjugate_partitions)}")
    return len(self_conjugate_partitions)

# --- Phần (c): Tìm số phân hoạch tự liên hợp theo định lý ---
# Đây là phần chính, chứng minh bằng cách liệt kê các phân hoạch thành các phần tử lẻ và phân biệt.
def find_odd_distinct_partitions(n, max_odd, current_partition, result_list):
    if n == 0:
        result_list.append(list(current_partition))
        return
    if n < 0 or max_odd <= 0:
        return

    # Lựa chọn 1: KHÔNG lấy phần tử max_odd
    find_odd_distinct_partitions(n, max_odd - 2, current_partition, result_list)
    
    # Lựa chọn 2: LẤY phần tử max_odd
    current_partition.append(max_odd)
    find_odd_distinct_partitions(n - max_odd, max_odd - 2, current_partition, result_list)
    current_partition.pop() # Quay lui

def solve_part_c(n):
    print("\n(c) So phan hoach tu lien hop (theo dinh ly):")
    
    odd_distinct_partitions = []
    # Bắt đầu với số lẻ lớn nhất không vượt quá n
    start_odd = n if n % 2 != 0 else n - 1
    
    find_odd_distinct_partitions(n, start_odd, [], odd_distinct_partitions)
    
    print(f"  Cac phan hoach cua {n} thanh cac phan tu le va phan biet la:")
    if not odd_distinct_partitions:
        print("  (khong co)")
    else:
        for p in sorted(odd_distinct_partitions):
             print(f"  - {' + '.join(map(str, p))}")

    print(f"=> Tong so: {len(odd_distinct_partitions)}")

def solve_problem_3():
    """
    Hàm chính để chạy giải pháp cho Bài toán 3.
    """
    print("\n--- Bai toan 3: Phan hoach tu lien hop ---")
    try:
        n = int(input("Nhap n: "))
        k = int(input("Nhap k: "))

        solve_part_a(n, k)
        # Phần (b) có vẻ ít quan trọng hơn và logic trong C++ có thể gây nhầm lẫn,
        # nên chúng ta tập trung vào phần (a) và (c) theo feedback của thầy.
        solve_part_c(n)

    except ValueError:
        print("Vui long nhap so nguyen hop le.")

# Chạy bài toán 3
if __name__ == "__main__":
    solve_problem_3()