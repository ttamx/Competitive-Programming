#include <bits/stdc++.h>

using namespace std;

const int MxN = 100010;

int a[MxN], cnt[33];

struct query_t {
    string opr;
    int val_1, val_2;
};

void solve() {
    int n;
    cin >> n;
    vector<query_t> queries(n + 1);
    vector<bitset<256>> done(n + 1, 0);
    for(int i=1; i<=n; ++i) {
        cin >> queries[i].opr >> queries[i].val_1;
        if(queries[i].opr != "add") {
            cin >> queries[i].val_2;
        }
    }
    for(int pos = 1, reg = 0; pos <= n; ) {
        auto [opr, u, v] = queries[pos];
        if(done[pos][reg]) {
            cout << "No\n"; 
            return ;
        }
        done[pos][reg] = true;
        if(opr == "add") {
            reg = (reg + u) % 256;
            pos += 1;
        }
        else if(opr == "beq") {
            pos = (reg == u ? v: pos + 1);
        }
        else if(opr == "bne") {
            pos = (reg != u ? v: pos + 1);
        }
        else if(opr == "blt") {
            pos = (reg < u ? v: pos + 1);
        }
        else {
            pos = (reg > u ? v: pos + 1);
        }
    }
    cout << "Yes\n";
    return ;
}

signed main(int argc, char *argv[]) {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        solve();
        // cerr << "-----\n";
    }
    return 0;
}