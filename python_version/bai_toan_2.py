def count_partitions_pk(n, k): # Hàm đếm số phân hoạch của n thành k phần (pₖ(n)).
    if k <= 0 or n <= 0 or k > n: # Kiểm tra điều kiện biên.
        return 0 # Trả về 0 nếu không hợp lệ.
    
    # dp[i][j] sẽ lưu số cách phân hoạch số i thành j phần.
    dp = [[0] * (k + 1) for _ in range(n + 1)] # Bảng quy hoạch động dp[i][j] = pⱼ(i).

    for i in range(1, n + 1): # Lặp qua các tổng từ 1 đến n.
        for j in range(1, k + 1): # Lặp qua số phần tử từ 1 đến k.
            if i < j: # Nếu tổng nhỏ hơn số phần tử.
                dp[i][j] = 0 # Không có cách phân hoạch nào.
            elif i == j: # Nếu tổng bằng số phần tử.
                dp[i][j] = 1 
            else: # Trường hợp tổng quát.
                # Áp dụng công thức truy hồi: pₖ(n) = pₖ₋₁(n-1) + pₖ(n-k).
                dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j] # Chuyển đổi công thức cho mảng dp.
                
    return dp[n][k] # Trả về kết quả tại dp[n][k].

def count_partitions_pmax(n, k): # Hàm đếm số phân hoạch của n có phần tử lớn nhất là k.
    if k <= 0 or n <= 0 or k > n: # Kiểm tra điều kiện biên.
        return 0 # Trả về 0 nếu không hợp lệ.
    
    target_sum = n - k # Bài toán tương đương phân hoạch (n-k) với các phần tử <= k.
    
    # dp[i][j] sẽ lưu số cách phân hoạch số i thành các phần tử <= j.
    dp = [[0] * (k + 1) for _ in range(target_sum + 1)] # Bảng quy hoạch động.

    for j in range(k + 1): # Lặp qua các cột của bảng.
        dp[0][j] = 1 # Khởi tạo: có 1 cách phân hoạch tổng 0 (phân hoạch rỗng).

    for i in range(1, target_sum + 1): # Lặp qua các tổng từ 1 đến (n-k).
        for j in range(1, k + 1): # Lặp qua các giá trị phần tử tối đa từ 1 đến k.
            dp[i][j] = dp[i][j - 1] # Số cách không dùng phần tử j.
            if i >= j: # Nếu có thể dùng phần tử j.
                dp[i][j] += dp[i - j][j] # Cộng thêm số cách có dùng ít nhất một phần tử j.
                
    return dp[target_sum][k] # Trả về kết quả.

def solve_problem_2(): # Hàm chính cho bài toán 2.
    print("\n--- Bai toan 2: So sanh p_k(n) va p_max(n,k) ---") # In tiêu đề bài toán.
    try: # Khối xử lý lỗi.
        n = int(input("Nhap so n: ")) # Nhận n.
        k = int(input("Nhap so k: ")) # Nhận k.

        pk_n = count_partitions_pk(n, k) # Tính pₖ(n).
        pmax_n_k = count_partitions_pmax(n, k) # Tính pₘₐₓ(n, k).

        print(f"So phan hoach cua {n} thanh {k} phan (p_k(n)): {pk_n}") # In kết quả pₖ(n).
        print(f"So phan hoach cua {n} co phan tu lon nhat la {k} (p_max(n,k)): {pmax_n_k}") # In kết quả pₘₐₓ(n, k).

        if pk_n == pmax_n_k: # So sánh hai kết quả.
            print("=> Ket qua: p_k(n) = p_max(n,k). Dinh ly duoc chung minh.") # In kết luận định lý đúng.
        else: # Nếu kết quả khác nhau.
            print("=> Ket qua: p_k(n) != p_max(n,k). Co loi trong tinh toan.") # In kết luận có lỗi.

    except ValueError: # Bắt lỗi nhập sai kiểu.
        print("Vui long nhap so nguyen hop le.") # Thông báo lỗi.

# Chạy bài toán 2.
if __name__ == "__main__": # Điểm vào chương trình.
    solve_problem_2() # Gọi hàm chính.