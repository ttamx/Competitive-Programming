// J.cpp
#include <bits/stdc++.h>

using namespace std;

using db = long double;

const int MxN = 12;
const db INF = 1e18;

pair<db, db> p[MxN];
db dist[MxN][MxN];
db dp[1 << MxN][MxN];

signed main(int argc, char *argv[]) {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0; i<n; ++i) {
        cin >> p[i].first >> p[i].second;
    }

    auto norm = [&](db x, db y) {
        return sqrtl(x * x + y * y);
    };

    auto find_dist = [&](pair<db, db> a, pair<db, db> b, db angle) {
        db theta = atan2l(b.second - a.second, b.first - a.first);
        db hyp = norm(b.first - a.first, b.second - a.second);
        db dx, dy;
        sincosl(theta + angle, &dx, &dy);
        return (abs(dx) + abs(dy)) * hyp;
    };

    auto try_angle = [&](db angle) {
        for(int i=0; i<n; ++i) {
            for(int j=i+1; j<n; ++j) {
                dist[i][j] = dist[j][i] = find_dist(p[i], p[j], angle);
            }
        }
        int max_mask = (1 << n);
        for(int mask=0; mask<max_mask; ++mask) {
            for(int i=0; i<n; ++i) {
                dp[mask][i] = INF;
            }
        }
        for(int i=0; i<n; ++i) {
            int cur_mask = (1 << i);
            dp[cur_mask][i] = 0;
        }
        for(int mask=0; mask<max_mask; ++mask) {
            for(int from=0; from<n; ++from) {
                int with_from = (1 << from);
                if(!(mask & with_from)) {
                    continue;
                }
                for(int to=0; to<n; ++to) {
                    int with_to = (1 << to);
                    if(mask & with_to) {
                        continue;
                    }
                    int mask_with_to = (mask | with_to);
                    dp[mask_with_to][to] = min(dp[mask_with_to][to], dp[mask][from] + dist[from][to]);
                }
            }
        }
        return *min_element(dp[max_mask - 1], dp[max_mask - 1] + n);
    };

    db answer = INF;
    for(int i=0; i<n; ++i) {
        for(int j=i+1; j<n; ++j) {
            db angle = atan2l(p[i].first - p[j].first, p[i].second - p[j].second);
            db cur_dist = try_angle(angle);
            answer = min(answer, cur_dist);
        }
    }
    cout << fixed << setprecision(12) << answer << "\n";
    return 0;
}