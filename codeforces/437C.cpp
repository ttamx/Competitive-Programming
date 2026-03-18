#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    ll ans=0;
    while(m--){
        int u,v;
        cin >> u >> v;
        u--,v--;
        ans+=min(a[u],a[v]);
    }
    cout << ans << "\n";
}