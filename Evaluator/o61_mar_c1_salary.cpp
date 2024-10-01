#include<bits/stdc++.h>

using namespace std;

struct DS{
    map<int,int> dat;
    void merge(DS &o){
        if(o.dat.size()>dat.size()){
            swap(o.dat,dat);
        }
        for(auto [x,v]:o.dat){
            dat[x]+=v;
        }
    }
    void insert(int x,int v){
        dat[x]+=v;
        for(auto it=next(dat.find(x));it!=dat.end();){
            if(v>=it->second){
                v-=it->second;
                it=dat.erase(it);
            }else{
                it->second-=v;
                break;
            }
        }
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    vector<DS> dp(n);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u]){
            dfs(v);
            dp[u].merge(dp[v]);
        }
        dp[u].insert(a[u],1);
    };
    dfs(0);
    int ans=n;
    for(auto [_,x]:dp[0].dat){
        ans-=x;
    }
    cout << ans;
}