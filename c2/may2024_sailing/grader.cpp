#include <cstdio>
#include <algorithm>
#include "sailing.cpp"

static int T, S, N, Q, current_position, cntt;
static double return_value;
static bool f[1000010];

bool sail_forward() {
  cntt++;
  current_position = (current_position + 1) % N;
  return f[current_position];
}

bool sail_backward() {
  cntt++;
  current_position = (current_position + N - 1) % N;
  return f[current_position];
}

void flag() {
  f[current_position] = !f[current_position];
}

int main() {
  scanf("%d", &T);
  while (T--) {
    current_position = cntt = 0;
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; ++i) scanf("%d ", &f[i]);
    int returned_ans = set_sail();
    if (cntt > Q) {
      printf("Wrong Answer: function called more than %d times\n", Q);
    }
    else if (returned_ans != N) {
      printf("Wrong Answer: retunred value %d mismatch actual N %d\n", returned_ans, N);
    }
    else {
      printf("Correct\n");
    }
    printf("Total calls: %d\n", cntt);
  }
}