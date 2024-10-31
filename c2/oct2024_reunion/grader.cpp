#include "reunion.h"
#include "goat.cpp"
#include "lemon.cpp"
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>

static int N, M;
static std::vector<int> U;
static std::vector<int> V;
static std::vector<int> W;
static int s1, s2;

static const int MAX_N = 2010;
static std::map<int, int> lengths[MAX_N];

void read_input() {
    int dummy;
    dummy = scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        dummy = scanf("%d %d %d", &u, &v, &w);
        U.push_back(u);
        V.push_back(v);
        W.push_back(w);

        lengths[u][v] = w;
        lengths[v][u] = w;
    }
    dummy = scanf("%d %d", &s1, &s2);
}

bool check_meet(int u1, int u2, int ou1, int ou2, long long t1, long long t2) {
    if (t1 <= t2) {
        if (u1 == ou2) {           // p1 moves to ou2
            return ((u2 == ou2) || // p2 stays at ou2
                    (u2 == ou1));  // p1 and p2 cross
        }
    }
    if (t2 <= t1) {
        if (u2 == ou1) {
            return ((u1 == ou1) || // p1 stays at ou1
                    (u1 == ou2));  // p1 and p2 cross
        }
    }
    return false;
}

int main() {
    read_input();
    goat::goat_init(N, M, U, V, W, s1);
    lemon::lemon_init(N, M, U, V, W, s2);

    int u1 = s1;
    int ou1 = -1;
    int u2 = s2;
    int ou2 = -1;
    long long t1 = 0;
    long long t2 = 0;

    // printf("> %d(%d) %d(%d)\n",u1,t1,u2,t2);

    while (true) {
        if ((t1 > 1000000000000L) && (t2 > 1000000000000L)) {
  	    printf("Error: too many steps\n");
	    exit(0);
        }
        if (t1 <= t2) {
            int newu1 = goat::goat_move(u1);

            if (newu1 != u1) {
                if (lengths[u1].find(newu1) == lengths[u1].end()) {
                    printf("Error: wrong move p1 (from %d to %d)\n", u1, newu1);
                    exit(0);
                }
                int tdiff = lengths[u1][newu1];
                ou1 = u1;
                u1 = newu1;
                t1 = t1 + tdiff;
            } else {
                // stays at u1
                ou1 = u1;
                if (t2 > t1) {
                    t1 = t2;
                } else {
                    t1 = t1 + 1;
                }
            }
        } else {
            int newu2 = lemon::lemon_move(u2);

            if (newu2 != u2) {
                if (lengths[u2].find(newu2) == lengths[u2].end()) {
                    printf("Error: wrong move p2 (from %d to %d)\n", u2, newu2);
                    exit(0);
                }
                int tdiff = lengths[u2][newu2];
                ou2 = u2;
                u2 = newu2;
                t2 = t2 += tdiff;
            } else {
                // stays at u2
                ou2 = u2;
                if (t1 > t2) {
                    t2 = t1;
                } else {
                    t2 = t2 + 1;
                }
            }
        }

        // printf("> %d(%d) %d(%d)\n",u1,t1,u2,t2);
        if (check_meet(u1, u2, ou1, ou2, t1, t2)) {
            long long tmin = t1;
            if (t2 < tmin)
                tmin = t2;
            printf("%lld\n", tmin);
            exit(0);
        }
    }

    return 0;
}
