try:
    from bai_toan_1 import solve_problem_1
    from bai_toan_2 import solve_problem_2
    from bai_toan_3 import solve_problem_3
    from bai_toan_4 import solve_problem_4
    from bai_toan_5 import solve_problem_5
    from bai_toan_6 import solve_problem_6
    from bai_toan_7 import solve_problem_7
    from bai_toan_8_10 import solve_problem_8_10
    from bai_toan_11_13 import solve_problem_11_13
    from bai_toan_14_16 import solve_problem_14_16
except ImportError as e:
    print(f"!!! LOI IMPORT")
    print(f"    Vui long kiem tra ten file .")
    print(f"     loi: {e}")
    exit()

def print_menu():
    
    print("\n\n==============================================")
    print("            DO AN MON HOC PYTHON")
    print("==============================================")
    print("Do an 4: Phan Hoach So Nguyen")
    print("  1. Bai toan 1: Bieu do Ferrers & chuyen vi")
    print("  2. Bai toan 2: So sanh p_k(n) va p_max(n,k)")
    print("  3. Bai toan 3: Phan hoach tu lien hop")
    print("Do an 5: Duyet Do Thi & Cay")
    print("  4. Bai toan 4: Chuyen doi bieu dien do thi")
    print("  5. Bai toan 5: Lam bai tap trong sach [Val21]")
    print("  6. Bai toan 6: Tree Edit Distance")
    print("  7. Bai toan 7: Duyet Cay")
    print("  8. Bai toan 8-10: Tim kiem theo chieu rong (BFS)")
    print("  11. Bai toan 11-13: Tim kiem theo chieu sau (DFS)")
    print("  14. Bai toan 14-16: Thuat toan Dijkstra")
    print("  0. Thoat")
    print("----------------------------------------------")
    print(" chon mot bai toan: ", end="")

def main():
    
    problem_solvers = {
        1: solve_problem_1,
        2: solve_problem_2,
        3: solve_problem_3,
        4: solve_problem_4,
        5: solve_problem_5,
        6: solve_problem_6,
        7: solve_problem_7,
        8: solve_problem_8_10,
        9: solve_problem_8_10,
        10: solve_problem_8_10,
        11: solve_problem_11_13,
        12: solve_problem_11_13,
        13: solve_problem_11_13,
        14: solve_problem_14_16,
        15: solve_problem_14_16,
        16: solve_problem_14_16,
    }

    while True:
        print_menu()
        try:
            choice_str = input()
            if not choice_str.strip(): continue
            choice = int(choice_str)
            
            if choice == 0:
                print("Thanks!")
                break
            
            solver = problem_solvers.get(choice)
            if solver:
                solver()
            else:
                print("Lua chon khong hop le")
        
        except ValueError:
            print("Vui long nhap mot so nguyen hop le.")
        except Exception as e:
            print(f" loi : {e}")

if __name__ == "__main__":
    main()