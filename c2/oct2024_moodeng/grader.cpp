#include "moodeng.cpp"
#include <iostream>

static int T;
static std::pair<int, int> hidden;
static std::vector<int> dirs;
static int t;
static int N, M;
bool query(std::vector<std::vector<bool>> table) {
    if (table.size() != N) {
        std::cout << "Invalid Query" << std::endl;
        exit(0);
    }
    for (int i = 0; i < N; i++) {
        if (table[i].size() != M) {
            std::cout << "Invalid Query" << std::endl;
            exit(0);
        }
    }
    int popcount = 0;
    for (auto &v : table)
        for (bool b : v)
            if (b)
                popcount++;
    if (t >= T) {
        std::cout << "Query Limit Exceeded" << std::endl;
        exit(0);
    }
    switch (dirs[t]) {
    case 0:
        hidden.first--;
        break;
    case 1:
        hidden.first++;
        break;
    case 2:
        hidden.second--;
        break;
    case 3:
        hidden.second++;
        break;
    }
    t++;
    if (table[hidden.first][hidden.second] && popcount == 1) {
        std::cout << "Correct Answer: " << t << std::endl;
        exit(0);
    }
    return table[hidden.first][hidden.second];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> N >> M >> T;
    dirs.clear();
    int x, y;
    std::cin >> x >> y;
    hidden = std::make_pair(x, y);
    std::string s;
    std::cin >> s;
    for (int i = 0; i < T; i++) {
        int d = s[i] == 'U' ? 0 : s[i] == 'D' ? 1 : s[i] == 'L' ? 2 : 3;
        dirs.push_back(d);
    }
    t = 0;
    search(N, M, T);
    std::cout << "Halted" << std::endl;
    return 0;
}