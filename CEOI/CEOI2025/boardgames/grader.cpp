#include <iostream>
#include <vector>
#include "boardgames.cpp"
using namespace std;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> x(m), y(m);
    for (int i = 0; i < m; i++) {
        std::cin >> x[i] >> y[i];
    }
    
    std::vector<int> result = partition_players(n, m, x, y);
    
    std::cout << result.size() << std::endl;
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << result[i];
    }
    std::cout << std::endl;
    
    return 0;
}
