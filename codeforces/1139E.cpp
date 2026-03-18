#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n),c(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:c){
        cin >> x;
        x--;
    }
    int q;
    cin >> q;
    vector<int> b(q);
    vector<bool> ban(n);
    for(auto &x:b){
        cin >> x;
        x--;
        ban[x]=true;
    }
    reverse(b.begin(),b.end());
    vector<bool> vis(m+n+1);
    vector<vector<int>> adj(n+m+1);
    vector<int> match(n+m+1,-1);
    function<bool(int)> kuhn=[&](int u){
        if(vis[u])return false;
        vis[u]=true;
        for(auto v:adj[u]){
            if(match[v]==-1||kuhn(match[v])){
                match[u]=v;
                match[v]=u;
                return true;
            }
        }
        return false;
    };
    auto work=[&](int st){
        vis.assign(n+m+1,false);
        return kuhn(st);
    };
    auto link=[&](int i){
        if(a[i]<=n){
            adj[a[i]].emplace_back(c[i]+n+1);
        }
    };
    int mex=0;
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(!ban[i]){
            link(i);
        }
    }
    for(auto i:b){
        while(work(mex))mex++;
        ans.emplace_back(mex);
        link(i);
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << x << "\n";
    }
}