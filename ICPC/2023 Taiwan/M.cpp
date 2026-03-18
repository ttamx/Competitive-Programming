#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    
    vector<tuple<int, int, int>> v;
    cin>>n;
    vector<int> id(n), p(n);
    for (auto &x:id) cin>>x;
    for (auto &x:p) cin>>x;
    for (int i=0; i<n; i++) v.push_back({p[i], i, id[i]});
    sort(v.begin(), v.end());
    for (auto [x, y, z]:v) cout<<z<<' ';
    cout<<'\n';
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int _t; cin>>_t;
    while (_t--) solve();
}