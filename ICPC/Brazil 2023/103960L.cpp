#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

ll cnt[N];

struct DS{
    map<int,ll> dat;
    ll ans;
    void insert(int x,ll v){
        ans-=dat[x]*(cnt[x]-dat[x]);
        dat[x]+=v;
        ans+=dat[x]*(cnt[x]-dat[x]);
    }
}ds[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> c(n);
    for(auto &x:c){
        cin >> x;
        cnt[x]++;
    }
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    vector<ll> ans(n-1);
    function<void(int,int)> dfs=[&](int u,int p){
        ds[u].insert(c[u],1);
        for(auto [v,i]:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            ans[i]=ds[v].ans;
            if(ds[v].dat.size()>ds[u].dat.size()){
                swap(ds[u],ds[v]);
            }
            for(auto [c,v]:ds[v].dat){
                ds[u].insert(c,v);
            }
        }
    };
    dfs(0,-1);
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}