#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    map<int,long long> mp;
    vector<int> cnt(n+1);
    vector<long long> ans(n);
    mp[0]=1LL*n*(n+1)/2;
    auto upd=[&](int i,int v){
        mp[cnt[i]]-=i;
        if(mp[cnt[i]]==0)mp.erase(cnt[i]);
        cnt[i]+=v;
        mp[cnt[i]]+=i;
    };
    vector<int> sz(n),hv(n,-1),disc(n),pos(n);
    int timer=-1;
    function<void(int,int)> dfs=[&](int u,int p){
        disc[u]=++timer;
        pos[timer]=u;
        sz[u]=1;
        for(auto v:adj[u]){
            if(v!=p){
                dfs(v,u);
                sz[u]+=sz[v];
                if(hv[u]==-1||sz[v]>sz[hv[u]]){
                    hv[u]=v;
                }
            }
        }
    };
    function<void(int,int,bool)> sack=[&](int u,int p,bool del){
        for(auto v:adj[u]){
            if(v!=p&&v!=hv[u]){
                sack(v,u,true);
            }
        }
        if(hv[u]!=-1)sack(hv[u],u,false);
        upd(a[u],+1);
        for(auto v:adj[u]){
            if(v!=p&&v!=hv[u]){
                for(int t=0;t<sz[v];t++){
                    upd(a[pos[disc[v]+t]],+1);
                }
            }
        }
        ans[u]=mp.rbegin()->second;
        if(del){
            for(int t=0;t<sz[u];t++){
                upd(a[pos[disc[u]+t]],-1);
            }
        }
    };
    dfs(0,-1);
    sack(0,-1,false);
    for(auto x:ans){
        cout << x << " ";
    }
}