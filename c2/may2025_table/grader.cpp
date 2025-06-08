#include "table.cpp"
#include <ios>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> T(N);
    for (int i = 0; i < N; i++) {
        T[i].resize(M, 0);
        for (int j = 0; j < M; j++) {
            std::cin >> T[i][j];
        }
    }
    int r1, c1, r2, c2;
    std::cin >> r1 >> c1 >> r2 >> c2;
    std::cout << minimum_obstruction(N, M, T, r1, c1, r2, c2) << std::endl;
    return 0;
}