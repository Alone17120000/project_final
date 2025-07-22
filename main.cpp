#include "problems.h"
#include <iostream>

void print_menu() {
    std::cout << "\n\n==============================================" << std::endl;
    std::cout << "            DO AN MON HOC C++" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Do an 4: Phan Hoach So Nguyen" << std::endl;
    std::cout << "  1. Bai toan 1: In bieu do Ferrers" << std::endl;
    std::cout << "  2. Bai toan 2: So sanh p_k(n) va p_max(n,k)" << std::endl;
    std::cout << "  3. Bai toan 3: Phan hoach tu lien hop" << std::endl;
    std::cout << "Do an 5: Duyet Do Thi & Cay" << std::endl;
    std::cout << "  4. Bai toan 4: Chuyen doi bieu dien do thi" << std::endl;
    std::cout << "  5. Bai toan 5: Cac bai tap trong sach [Val21]" << std::endl;
    std::cout << "  6. Bai toan 6: Tree Edit Distance" << std::endl;
    std::cout << "  7. Bai toan 7: Duyet cay" << std::endl;
    std::cout << "  8. Bai toan 8-16: BFS, DFS, Dijkstra" << std::endl;
    std::cout << "  0. Thoat" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Vui long chon mot bai toan: ";
}

int main() {
    int choice;
    do {
        print_menu();
        std::cin >> choice;
        switch (choice) {
            case 1: solve_problem_1(); break;
            case 2: solve_problem_2(); break;
            case 3: solve_problem_3(); break;
            case 4: solve_problem_4(); break;
            case 5: solve_problem_5(); break;
            case 6: solve_problem_6(); break;
            case 7: solve_problem_7(); break;
            case 8: solve_graph_problems(); break;
            case 0: std::cout << "Tam biet!" << std::endl; break;
            default: std::cout << "Lua chon khong hop le. Vui long chon lai." << std::endl; break;
        }
    } while (choice != 0);

    return 0;
}