#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct state_t {
    int i, j, last_dir, cnt;
    state_t(int _i, int _j, int _last_dir, int _cnt):
        i(_i), j(_j), last_dir(_last_dir), cnt(_cnt) {}
};

const int di[] = {-1, 0, 0, 1};
const int dj[] = {0, -1, 1, 0};

signed main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<string> a(n + 1);
    vector<vector<array<array<int, 3>, 4>>> dist(n + 1, vector<array<array<int, 3>, 4>> (m + 1));
    pair<int, int> stp, edp;
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=m; ++j) {
            for(int k=0; k<4; ++k) {
                for(int l=0; l<3; ++l) {
                    dist[i][j][k][l] = -1;
                }
            }
        }
    }
    for(int i=1; i<=n; ++i) {
        cin >> a[i];
        a[i] = " " + a[i];
        for(int j=1; j<=m; ++j) {
            if(a[i][j] == 'S') {
                stp = make_pair(i, j);
                for(int k=0; k<4; ++k) {
                    dist[i][j][k][0] = 0;
                }
            }
            if(a[i][j] == 'T') {
                edp = make_pair(i, j);
            }
        }
    }
    queue<state_t> q;
    for(int i=0; i<4; ++i) {
        q.emplace(stp.first, stp.second, i, 0);
    }

    while(!q.empty()) {
        state_t cur = q.front(); q.pop();
        // cerr << "D: " << cur.i << " " << cur.j << " " << cur.last_dir << "\n";
        if(make_pair(cur.i, cur.j) == edp) {
            cout << dist[cur.i][cur.j][cur.last_dir][cur.cnt] << "\n";
            return 0;
        }
        for(int k=0; k<4; ++k) {
            int ii = cur.i + di[k], jj = cur.j + dj[k];
            if(ii < 1 || jj < 1 || ii > n || jj > m) {
                continue;
            }
            int nxt_cnt = k == cur.last_dir ? cur.cnt + 1: 0;
            if(a[ii][jj] == '#' || nxt_cnt == 3 || dist[ii][jj][k][nxt_cnt] != -1) {
                continue;
            }
            dist[ii][jj][k][nxt_cnt] = dist[cur.i][cur.j][cur.last_dir][cur.cnt] + 1;
            q.emplace(ii, jj, k, nxt_cnt);
        }
    }  
    cout << -1 << "\n";
    return 0;
}