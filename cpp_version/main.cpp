#include "problems.h"
#include <iostream>
#include <limits> // Dùng cho việc xử lý lỗi nhập liệu

void print_menu() {
    std::cout << "\n\n==============================================" << std::endl;
    std::cout << "            DO AN MON HOC C++" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Do an 4: Phan Hoach So Nguyen" << std::endl;
    std::cout << "  1. Bai toan 1" << std::endl;
    std::cout << "  2. Bai toan 2" << std::endl;
    std::cout << "  3. Bai toan 3" << std::endl;
    std::cout << "Do an 5: Duyet Do Thi & Cay" << std::endl;
    std::cout << "  4. Bai toan 4: Chuyen doi bieu dien do thi & cay" << std::endl;
    std::cout << "  5. Bai toan 5: Lam bai tap trong sach [Val21]" << std::endl;
    std::cout << "  6. Bai toan 6: Tree Edit Distance" << std::endl;
    std::cout << "  7. Bai toan 7: Duyet Cay" << std::endl;
    std::cout << "  8. Bai toan 8-10: Tim kiem theo chieu rong (BFS)" << std::endl;
    std::cout << "  11. Bai toan 11-13: Tim kiem theo chieu sau (DFS)" << std::endl;
    std::cout << "  14. Bai toan 14-16: Thuat toan Dijkstra" << std::endl;
    std::cout << "  0. Thoat" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << " chon mot bai toan: ";
}

int main() {
    int choice;
    do {
        print_menu();
        std::cin >> choice;

        while (std::cin.fail()) {
            std::cout << " nhap mot so nguyen hop le." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            print_menu();
            std::cin >> choice;
        }

        switch (choice) {
            case 1: solve_problem_1(); break;
            case 2: solve_problem_2(); break;
            case 3: solve_problem_3(); break;
            case 4: solve_problem_4(); break;
            case 5: solve_problem_5(); break;
            case 6: solve_problem_6(); break;
            case 7: solve_problem_7(); break;
            case 8:
            case 9:
            case 10:
                solve_problem_8_10();
                break;
            case 11:
            case 12:
            case 13:
                solve_problem_11_13();
                break;
            case 14:
            case 15:
            case 16:
                solve_problem_14_16();
                break;
            case 0: std::cout << "Thanks!" << std::endl; break;
            default: std::cout << " Vui long chon lai." << std::endl; break;
        }
    } while (choice != 0);

    return 0;
}