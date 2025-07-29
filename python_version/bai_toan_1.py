def get_transpose(partition):
    if not partition: return []
    max_part = partition[0]
    transpose = [sum(1 for part in partition if part >= i) for i in range(1, max_part + 1)]
    return transpose

def print_diagram(partition, title):
    print(f"  {title}:")
    if not partition: return
    for part in partition:
        print(f"    {'*' * part}")

def find_partitions(n, k, max_val, current_partition):
    if k == 0:
        if n == 0:
            partition_str = " + ".join(map(str, current_partition))
            print(f"Phan hoach: {partition_str}")
            print_diagram(current_partition, "- Bieu do Ferrers (F)")
            transpose_partition = get_transpose(current_partition)
            print_diagram(transpose_partition, "- Bieu do chuyen vi (F^T)")
            print("----------------------------------------")
        return

    for i in range(min(n, max_val), 0, -1):
        if n - i >= k - 1:
            current_partition.append(i)
            find_partitions(n - i, k - 1, i, current_partition)
            current_partition.pop()

# --- HÀM CHÍNH ĐỂ IMPORT ---
def solve_problem_1():
    print("\n--- Bai toan 1: In bieu do Ferrers & chuyen vi ---")
    try:
        n = int(input("Nhap n: "))
        k = int(input("Nhap k: "))
        if n > 0 and k > 0 and n >= k:
            find_partitions(n, k, n - k + 1, [])
        else:
            print("Khong co phan hoach nao hop le.")
    except ValueError:
        print("Vui long nhap so nguyen hop le.")


if __name__ == "__main__":
    solve_problem_1()