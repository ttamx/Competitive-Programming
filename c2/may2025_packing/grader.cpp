#include "packing.cpp"
#include <ios>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    int B, Z;
    std::cin >> B >> Z;
    std::vector<int> v;
    for (int i = 0; i <= B; i++) {
        int x;
        std::cin >> x;
        v.push_back(x);
    }
    std::cout << minimum_width(B, Z, v) << std::endl;
    return 0;
}