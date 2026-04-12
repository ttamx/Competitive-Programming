#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "voltage.cpp"

namespace {

enum {
    INVALID_X_LENGTH = 3,
    INVALID_X_VALUE = 4,
    INVALID_Y_LENGTH = 5,
    INVALID_Y_VALUE = 6,
    QUERY_LIMIT_EXCEEDED = 7,
    INVALID_ANSWER_VALUE = 8,
    SAME_ANSWER_VALUE = 9,
    ANSWER_LIMIT_EXCEEDED = 10,
    INVALID_ANSWER_COUNT = 11,
    WRONG_ANSWER_VALUE = 12
};

const int N_MAX = 500;
const int QUERY_LIMIT = 30000;
int QUERY_COUNT = 0;
int ANSWER_COUNT = 0;

int N, M;
bool edge_exist[N_MAX][N_MAX];
bool edge_answered[N_MAX][N_MAX];
bool returned_value;
std::vector<std::pair<int, int>> edge;
std::vector<std::pair<int, int>> answered_edge;

void wrong_answer(int code) {
    printf("Wrong Answer [%d]\n", code);
    exit(1);
}

}  // namespace

int temperature(std::vector<int> voltage) {
    int res = 0;
    for (auto [a, b] : edge) {
        if (voltage[a] == 1 && voltage[b] == 0) {
            res++;
        }
    }
    return res;
}

int query(std::vector<int> x, std::vector<int> y) {
    if ((int)x.size() != N) {
        wrong_answer(INVALID_X_LENGTH);
    }
    for (int v : x) {
        if (v != 0 && v != 1) {
            wrong_answer(INVALID_X_VALUE);
        }
    }
    if ((int)y.size() != N) {
        wrong_answer(INVALID_Y_LENGTH);
    }
    for (int v : y) {
        if (v != 0 && v != 1) {
            wrong_answer(INVALID_Y_VALUE);
        }
    }
    QUERY_COUNT++;
    if (QUERY_COUNT > QUERY_LIMIT) {
        wrong_answer(QUERY_LIMIT_EXCEEDED);
    }
    int temp_x = temperature(x);
    int temp_y = temperature(y);
    if (temp_x > temp_y) return -1;
    if (temp_x < temp_y) return 1;
    return 0;
}

void answer(int a, int b) {
    if (!(0 <= a && a <= N - 1)) {
        wrong_answer(INVALID_ANSWER_VALUE);
    }
    if (!(0 <= b && b <= N - 1)) {
        wrong_answer(INVALID_ANSWER_VALUE);
    }
    if (ANSWER_COUNT >= M) {
        wrong_answer(ANSWER_LIMIT_EXCEEDED);
    }
    if (edge_answered[a][b]) {
        wrong_answer(SAME_ANSWER_VALUE);
    }
    ANSWER_COUNT++;
    answered_edge.emplace_back(a, b);
    edge_answered[a][b] = true;
}

int main() {
    assert(scanf("%d %d", &N, &M) == 2);
    assert(N > 1);

    for (int i = 0; i < M; i++) {
        int a, b;
        assert(scanf("%d %d", &a, &b) == 2);
        assert(0 <= a && a < N);
        assert(0 <= b && b < N);
        assert(a != b);
        assert(!edge_exist[a][b] && !edge_exist[b][a]);
        edge.emplace_back(a, b);
        edge_exist[a][b] = true;
    }

    returned_value = solve(N, M);

    if (returned_value == true) {
        if (ANSWER_COUNT != M) {
            wrong_answer(INVALID_ANSWER_COUNT);
        }
        for (auto [a, b] : answered_edge) {
            if (!edge_exist[a][b]) {
                wrong_answer(WRONG_ANSWER_VALUE);
            }
        }
    }
    printf("Accepted: %d %s\n", QUERY_COUNT, returned_value ? "true" : "false");
    return 0;
}
