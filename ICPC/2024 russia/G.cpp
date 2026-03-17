#include<bits/stdc++.h>

using namespace std;

struct DS{
    int mx;
    int ans;
    map<int,int> dat;
    DS():mx(0),ans(0),dat(){}
    void insert(int c,int f){
        dat[c]+=f;
        if(dat[c]>mx){
            mx=dat[c];
            ans=c;
        }else if(dat[c]==mx&&c<ans){
            ans=c;
        }
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<bool> bad(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        bad[v]=true;
    }
    int root=-1;
    for(int i=0;i<n;i++){
        if(!bad[i]){
            root=i;
            break;
        }
    }
    assert(root!=-1);
    vector<DS> dp(n);
    vector<int> ans(n);
    function<void(int)> dfs=[&](int u){
        dp[u].insert(a[u],1);
        for(auto v:adj[u]){
            dfs(v);
            if(dp[v].dat.size()>dp[u].dat.size()){
                swap(dp[u],dp[v]);
            }
            for(auto [c,f]:dp[v].dat){
                dp[u].insert(c,f);
            }
        }
        ans[u]=dp[u].ans;
    };
    dfs(root);
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}