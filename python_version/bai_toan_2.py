def count_partitions_pk(n, k):

    if k <= 0 or n <= 0 or k > n:
        return 0
    
    # dp[i][j] sẽ lưu số cách phân hoạch số i thành j phần
    dp = [[0] * (k + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(1, k + 1):
            if i < j:
                dp[i][j] = 0
            elif i == j:
                dp[i][j] = 1
            else:
                # Công thức truy hồi: pₖ(n) = pₖ₋₁(n-1) + pₖ(n-k)
                # Chuyển đổi một chút: dp[i][j] = dp[i-1][j-1] + dp[i-j][j]
                dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j]
                
    return dp[n][k]

def count_partitions_pmax(n, k):
    """
    Tính pₘₐₓ(n, k): Số phân hoạch của n có phần tử lớn nhất là k.
    Đây chính là số cách phân hoạch (n - k) thành các phần tử có giá trị <= k.
    """
    if k <= 0 or n <= 0 or k > n:
        return 0
    
    target_sum = n - k
    
    # dp[i][j] sẽ lưu số cách phân hoạch số i thành các phần tử <= j
    dp = [[0] * (k + 1) for _ in range(target_sum + 1)]

    # Có 1 cách để phân hoạch số 0 (là không có phần tử nào)
    for j in range(k + 1):
        dp[0][j] = 1

    for i in range(1, target_sum + 1):
        for j in range(1, k + 1):
            # Cách 1: Không dùng phần tử j -> số cách = dp[i][j-1]
            # Cách 2: Dùng ít nhất một phần tử j -> số cách = dp[i-j][j]
            dp[i][j] = dp[i][j - 1]
            if i >= j:
                dp[i][j] += dp[i - j][j]
                
    return dp[target_sum][k]

def solve_problem_2():

    print("\n--- Bai toan 2: So sanh p_k(n) va p_max(n,k) ---")
    try:
        n = int(input("Nhap so n: "))
        k = int(input("Nhap so k: "))

        pk_n = count_partitions_pk(n, k)
        pmax_n_k = count_partitions_pmax(n, k)

        print(f"So phan hoach cua {n} thanh {k} phan (p_k(n)): {pk_n}")
        print(f"So phan hoach cua {n} co phan tu lon nhat la {k} (p_max(n,k)): {pmax_n_k}")

        if pk_n == pmax_n_k:
            print("=> Ket qua: p_k(n) = p_max(n,k). Dinh ly duoc chung minh.")
        else:
            print("=> Ket qua: p_k(n) != p_max(n,k). Co loi trong tinh toan.")

    except ValueError:
        print("Vui long nhap so nguyen hop le.")

# Chạy bài toán 2
if __name__ == "__main__":
    solve_problem_2()