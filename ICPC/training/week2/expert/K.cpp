#include <bits/stdc++.h>

using namespace std;

const int MxN = 100010;

int a[MxN], cnt[33];

void solve() {
    int n;
    cin >> n;
    memset(cnt, 0, sizeof cnt);
    for(int i=1; i<=n; ++i) {
        cin >> a[i];
        cnt[__lg(a[i])]++;
    }
    cout << *max_element(cnt, cnt + 33) << "\n";
    return ;
}

signed main(int argc, char *argv[]) {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}