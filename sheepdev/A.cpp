#include<bits/stdc++.h>

using namespace std;

const int N=1e7+5;

int col[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> id(n,-1);
    for(auto x:a)col[x]=-1;
    vector<int> ans(n);
    function<void(int,int)> dfs=[&](int u,int d){
        id[d]=u;
        int t=col[a[u]];
        ans[u]=id[t+1];
        col[a[u]]=d;
        for(auto v:adj[u])dfs(v,d+1);
        col[a[u]]=t;
    };
    dfs(0,0);
    for(auto x:ans){
        cout << x << " ";
    }
}