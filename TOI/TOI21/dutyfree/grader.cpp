#include "duty_free.cpp"
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    int nBag;
    std::cin >> nBag;
    std::vector<int> max_allowed_positions(nBag);
    for (auto &max_allowed_position: max_allowed_positions) {
        std::cin >> max_allowed_position;
    }
    std::cout << minimum_bag_rearrangement_time(max_allowed_positions);
    return 0;
}
