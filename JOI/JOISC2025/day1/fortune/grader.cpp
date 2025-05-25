#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "Anna.h"
#include "Bruno.h"

namespace {

const int INVALID_X_FIRST = 1;
const int INVALID_X_RANGE = 2;
const int INVALID_DRAW_COUNT = 3;
const int INVALID_ANSWER = 4;

int N, L;
std::vector<int> A;
std::vector<int> C;

int draw_count;

void WrongAnswer(int code) {
    printf("Wrong Answer [%d]\n", code);
    exit(0);
}

}  // namespace

int DrawCard(int x) {
    draw_count++;
    if (draw_count > N + 1) {
        WrongAnswer(INVALID_DRAW_COUNT);
    }
    if (draw_count == 1 && x != -1) {
        WrongAnswer(INVALID_X_FIRST);
    }
    if (draw_count >= 2 && !(-1 <= x && x <= L)) {
        WrongAnswer(INVALID_X_RANGE);
    }
    if (x >= 0) {
        L++;
        C.insert(C.begin() + x, A[draw_count - 2]);
    }
    if (draw_count == N + 1) return -1;
    return A[draw_count - 1];
}

int main() {
    int Q;
    if (scanf("%d %d", &Q, &N) != 2) {
        fprintf(stderr, "Error while reading input.\n");
        exit(1);
    }

    int max_L = 0;
    for (int i = 0; i < Q; i++) {
        A.resize(N);

        for (int j = 0; j < N; j++) {
            if (scanf("%d", &A[j]) != 1) {
                fprintf(stderr, "Error while reading input.\n");
                exit(1);
            }
        }

        C.clear();
        L = 0;
        draw_count = 0;

        Anna(N);

        if (draw_count != N + 1) {
            WrongAnswer(INVALID_DRAW_COUNT);
        }

        int ans = 0;

        for (int j = 0; j < N; j++) ans += A[j];

        int res=Bruno(N, L, C);

        std::cerr << res << " " << ans << "\n";

        if (res != ans) {
            WrongAnswer(INVALID_ANSWER);
        }
        max_L = std::max(max_L, L);
    }
    printf("Accepted: %d\n", max_L);
    return 0;
}
