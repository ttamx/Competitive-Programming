#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q,k;
    cin >> n >> q >> k;
    vector<ll> a(n),d(k);
    for(auto &x:d)cin >> x;
    for(auto &x:a)cin >> x;
    vector<int> c(k);
    auto update=[&](ll x,int v){
        for(int i=0;i<k;i++){
            if(x%d[i]==0){
                c[i]+=v;
            }
        }
    };
    vector<vector<tuple<int,int,ll>>> adj(q+1);
    for(int i=1;i<=q;i++){
        int p,id;
        ll x;
        cin >> p >> id >> x;
        adj[p].emplace_back(i,id-1,x);
    }
    vector<ll> ans(q+1);
    for(auto x:a)update(x,+1);
    function<void(int)> dfs=[&](int u){
        for(int i=0;i<k;i++){
            if(c[i]==n){
                ans[u]+=d[i];
            }
        }
        for(auto [v,i,x]:adj[u]){
            ll t=a[i];
            a[i]=x;
            update(t,-1);
            update(x,+1);
            dfs(v);
            update(x,-1);
            update(t,+1);
            a[i]=t;
        }
    };
    dfs(0);
    for(auto x:ans)cout << x << "\n";
}